cmake_minimum_required(VERSION 3.15)
project(Minos)

set(CMAKE_CXX_STANDARD 14)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)
# add the source files as usual
add_executable(Minos main.cpp KDTree.h KDTree.cpp PCNode.h PCNode.cpp PointCloud.h PointCloud.cpp Render.h RenderInf.h Render.cpp)
# this also sets the includes and pulls third party dependencies
target_link_libraries(Minos OgreBites OgreRTShaderSystem)
