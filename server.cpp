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
      RenderInfNode render_inf_node;
      render_inf_node.fromBuffer(buffer);
      std::cout << len << std::endl;
      std::cout << render_inf_node.id << std::endl;
      std::cout << render_inf_node.size << std::endl;
      std::cout << render_inf_node.updateObject << std::endl;
      std::cout << render_inf_node.nodePos << std::endl;
      std::cout << render_inf_node.nodeScale << std::endl;
      std::cout << render_inf_node.size << std::endl;
      for (int i = 0; i < render_inf_node.size; ++i) std::cout << render_inf_node.data.get()[i] << std::endl;
      TotalRecvSize += len;
      total_packet_num++;
      return len;
    });

    session->setDisConnectCallback([](const TcpConnection::Ptr& session) {
      total_client_num--;
    });
  };

  wrapper::ListenerBuilder listener;
  listener.configureService(service)
      .configureSocketOptions({
                                  [](TcpSocket& socket) {
                                    socket.setNodelay();
                                  }
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
    if (TotalRecvSize / 1024 == 0)
    {
      std::cout << "total recv : " << TotalRecvSize << " bytes/s, of client num:" << total_client_num << std::endl;
    }
    else if ((TotalRecvSize / 1024) / 1024 == 0)
    {
      std::cout << "total recv : " << TotalRecvSize / 1024 << " K/s, of client num:" << total_client_num << std::endl;
    }
    else
    {
      std::cout << "total recv : " << (TotalRecvSize / 1024) / 1024 << " M/s, of client num:" << total_client_num << std::endl;
    }

    std::cout << "packet num:" << total_packet_num << std::endl;
    total_packet_num = 0;
    TotalRecvSize = 0;
  }
}