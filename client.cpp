#include <iostream>
#include <string>
#include "RenderInf.h"
#include "OGRE/Ogre.h"

#include <brynet/net/SocketLibFunction.hpp>
#include <brynet/net/TcpService.hpp>
#include <brynet/net/AsyncConnector.hpp>
#include <brynet/net/wrapper/ConnectionBuilder.hpp>

using namespace brynet;
using namespace brynet::net;

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: <host> <port>\n");
    exit(-1);
  }

  RenderInfNode render_inf_node;
  render_inf_node.id = 2;
  render_inf_node.size = 2;
  float *data = new float[2];
  render_inf_node.data.reset(data);
  render_inf_node.data.get()[0] = 12.0;
  render_inf_node.data.get()[1] = 13.0;
  render_inf_node.updateObject = true;
  render_inf_node.nodePos = Ogre::Vector3(0.2, 0.3, 0.4);
  render_inf_node.nodeScale = Ogre::Vector3(1, 1, 2);

  char* buffer = new char[200000], *start = buffer;
  buffer = render_inf_node.toBuffer(buffer);
  std::cout << buffer - start << std::endl;

  auto service = TcpService::Create();
  service->startWorkerThread(1);

  auto connector = AsyncConnector::Create();
  connector->startWorkerThread();

  auto enterCallback = [start, buffer](const TcpConnection::Ptr& session) {
    session->setDataCallback([session](const char* buffer, size_t len) {
      return len;
    });
    session->send(start, buffer - start);
  };

  auto failedCallback = []() {
    std::cout << "connect failed" << std::endl;
  };

  wrapper::ConnectionBuilder connectionBuilder;
  connectionBuilder.configureService(service)
      .configureConnector(connector)
      .configureConnectionOptions({
                                      brynet::net::AddSocketOption::AddEnterCallback(enterCallback),
                                      brynet::net::AddSocketOption::WithMaxRecvBufferSize(20 * 1024 * 1024)
                                  });

  const auto ip = argv[1];
  const auto port = std::atoi(argv[2]);
  try
  {
    connectionBuilder.configureConnectOptions({
                                                  ConnectOption::WithAddr(ip, port),
                                                  ConnectOption::WithTimeout(std::chrono::seconds(10)),
                                                  ConnectOption::WithFailedCallback(failedCallback),
                                                  ConnectOption::AddProcessTcpSocketCallback([](TcpSocket& socket) {
                                                    socket.setNodelay();
                                                  })
                                              })
        .asyncConnect();
  }
  catch (std::runtime_error& e)
  {
    std::cout << "error:" << e.what() << std::endl;
  }

  std::cin.get();
}