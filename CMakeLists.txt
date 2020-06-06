cmake_minimum_required(VERSION 3.15)
project(Minos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
find_package(httplib)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Threads)
# add the source files as usual
add_executable(Minos main.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
add_executable(Server server.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
add_executable(Client client.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp RenderInf.cpp Splitter.h Splitter.cpp RenderRemoteCaller.h RenderRemoteCaller.cpp)
# this also sets the includes and pulls third party dependencies
target_link_libraries(Minos OgreBites OgreRTShaderSystem httplib::httplib nlohmann_json::nlohmann_json)
target_link_libraries(Server OgreBites)
target_link_libraries(Client OgreBites)