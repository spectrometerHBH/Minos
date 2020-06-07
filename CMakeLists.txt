cmake_minimum_required(VERSION 3.15)
project(Minos)

set(CMAKE_CXX_STANDARD 17)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
# add the source files as usual
add_executable(Minos main.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
add_executable(Server server.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
add_executable(Client client.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
# this also sets the includes and pulls third party dependencies
target_link_libraries(Minos OgreBites "/usr/local/lib/libsockpp.so")
target_link_libraries(Server OgreBites "/usr/local/lib/libsockpp.so")
target_link_libraries(Client OgreBites "/usr/local/lib/libsockpp.so")
