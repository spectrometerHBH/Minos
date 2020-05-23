cmake_minimum_required(VERSION 3.15)
project(Minos)

set(CMAKE_CXX_STANDARD 17)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
find_package(httplib)
find_package(nlohmann_json 3.2.0 REQUIRED)
# add the source files as usual
add_executable(Minos main.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp)
# this also sets the includes and pulls third party dependencies
target_link_libraries(Minos OgreBites OgreRTShaderSystem httplib::httplib nlohmann_json::nlohmann_json)
