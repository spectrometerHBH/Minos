#include <iostream>
#include <mutex>
#include <atomic>
#include "RenderInf.h"

#include <brynet/net/EventLoop.hpp>
#include <brynet/net/TcpService.hpp>
#include <brynet/net/wrapper/ServiceBuilder.hpp>

using namespace brynet;
using namespace brynet::net;

std::atomic_llong TotalRecvSize = ATOMIC_VAR_INIT(0);
std::atomic_llong total_client_num = ATOMIC_VAR_INIT(0);
std::atomic_llong total_packet_num = ATOMIC_VAR_INIT(0);

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: <listen port>\n");
    exit(-1);
  }

  auto service = TcpService::Create();
  service->startWorkerThread(1);

  auto enterCallback = [](const TcpConnection::Ptr& session) {
    total_client_num++;

    session->setDataCallback([session](const char* buffer, size_t len) {
      int command;
      RenderInfNode::deserialize(buffer, command);
      std::cout << command << " " << len << std::endl;
      return len;
    });

    session->setDisConnectCallback([](const TcpConnection::Ptr& session) {
      total_client_num--;
      std::cout << "client num: " << total_client_num << std::endl;
    });
  };

  wrapper::ListenerBuilder listener;
  listener.configureService(service)
      .configureSocketOptions({
        [](TcpSocket& socket) { socket.setNodelay(); }
      })
      .configureConnectionOptions({
        brynet::net::AddSocketOption::WithMaxRecvBufferSize(1024 * 1024),
        brynet::net::AddSocketOption::AddEnterCallback(enterCallback)
      })
      .configureListen([=](wrapper::BuildListenConfig config) {
        config.setAddr(false, "0.0.0.0", atoi(argv[1]));
      })
      .asyncRun();

  EventLoop mainLoop;
  while (true)
  {
    mainLoop.loop(1000);
  }
}