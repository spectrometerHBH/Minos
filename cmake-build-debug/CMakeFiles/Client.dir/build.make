# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/spectre/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/spectre/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/spectre/CLionProjects/Minos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/spectre/CLionProjects/Minos/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/client.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/client.cpp.o -c /home/spectre/CLionProjects/Minos/client.cpp

CMakeFiles/Client.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/client.cpp > CMakeFiles/Client.dir/client.cpp.i

CMakeFiles/Client.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/client.cpp -o CMakeFiles/Client.dir/client.cpp.s

CMakeFiles/Client.dir/KDTree.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/KDTree.cpp.o: ../KDTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Client.dir/KDTree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/KDTree.cpp.o -c /home/spectre/CLionProjects/Minos/KDTree.cpp

CMakeFiles/Client.dir/KDTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/KDTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/KDTree.cpp > CMakeFiles/Client.dir/KDTree.cpp.i

CMakeFiles/Client.dir/KDTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/KDTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/KDTree.cpp -o CMakeFiles/Client.dir/KDTree.cpp.s

CMakeFiles/Client.dir/PCNode.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PCNode.cpp.o: ../PCNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Client.dir/PCNode.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/PCNode.cpp.o -c /home/spectre/CLionProjects/Minos/PCNode.cpp

CMakeFiles/Client.dir/PCNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PCNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/PCNode.cpp > CMakeFiles/Client.dir/PCNode.cpp.i

CMakeFiles/Client.dir/PCNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PCNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/PCNode.cpp -o CMakeFiles/Client.dir/PCNode.cpp.s

CMakeFiles/Client.dir/PointCloud.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PointCloud.cpp.o: ../PointCloud.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Client.dir/PointCloud.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/PointCloud.cpp.o -c /home/spectre/CLionProjects/Minos/PointCloud.cpp

CMakeFiles/Client.dir/PointCloud.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PointCloud.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/PointCloud.cpp > CMakeFiles/Client.dir/PointCloud.cpp.i

CMakeFiles/Client.dir/PointCloud.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PointCloud.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/PointCloud.cpp -o CMakeFiles/Client.dir/PointCloud.cpp.s

CMakeFiles/Client.dir/Render.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Render.cpp.o: ../Render.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Client.dir/Render.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/Render.cpp.o -c /home/spectre/CLionProjects/Minos/Render.cpp

CMakeFiles/Client.dir/Render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Render.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/Render.cpp > CMakeFiles/Client.dir/Render.cpp.i

CMakeFiles/Client.dir/Render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Render.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/Render.cpp -o CMakeFiles/Client.dir/Render.cpp.s

CMakeFiles/Client.dir/RenderInf.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/RenderInf.cpp.o: ../RenderInf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Client.dir/RenderInf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/RenderInf.cpp.o -c /home/spectre/CLionProjects/Minos/RenderInf.cpp

CMakeFiles/Client.dir/RenderInf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/RenderInf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/RenderInf.cpp > CMakeFiles/Client.dir/RenderInf.cpp.i

CMakeFiles/Client.dir/RenderInf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/RenderInf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/RenderInf.cpp -o CMakeFiles/Client.dir/RenderInf.cpp.s

CMakeFiles/Client.dir/Splitter.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Splitter.cpp.o: ../Splitter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Client.dir/Splitter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/Splitter.cpp.o -c /home/spectre/CLionProjects/Minos/Splitter.cpp

CMakeFiles/Client.dir/Splitter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Splitter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/Splitter.cpp > CMakeFiles/Client.dir/Splitter.cpp.i

CMakeFiles/Client.dir/Splitter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Splitter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/Splitter.cpp -o CMakeFiles/Client.dir/Splitter.cpp.s

CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o: ../RenderRemoteCaller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o -c /home/spectre/CLionProjects/Minos/RenderRemoteCaller.cpp

CMakeFiles/Client.dir/RenderRemoteCaller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/RenderRemoteCaller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spectre/CLionProjects/Minos/RenderRemoteCaller.cpp > CMakeFiles/Client.dir/RenderRemoteCaller.cpp.i

CMakeFiles/Client.dir/RenderRemoteCaller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/RenderRemoteCaller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spectre/CLionProjects/Minos/RenderRemoteCaller.cpp -o CMakeFiles/Client.dir/RenderRemoteCaller.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/client.cpp.o" \
"CMakeFiles/Client.dir/KDTree.cpp.o" \
"CMakeFiles/Client.dir/PCNode.cpp.o" \
"CMakeFiles/Client.dir/PointCloud.cpp.o" \
"CMakeFiles/Client.dir/Render.cpp.o" \
"CMakeFiles/Client.dir/RenderInf.cpp.o" \
"CMakeFiles/Client.dir/Splitter.cpp.o" \
"CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client: CMakeFiles/Client.dir/client.cpp.o
Client: CMakeFiles/Client.dir/KDTree.cpp.o
Client: CMakeFiles/Client.dir/PCNode.cpp.o
Client: CMakeFiles/Client.dir/PointCloud.cpp.o
Client: CMakeFiles/Client.dir/Render.cpp.o
Client: CMakeFiles/Client.dir/RenderInf.cpp.o
Client: CMakeFiles/Client.dir/Splitter.cpp.o
Client: CMakeFiles/Client.dir/RenderRemoteCaller.cpp.o
Client: CMakeFiles/Client.dir/build.make
Client: /usr/local/lib/libOgreBites.so.1.12.6
Client: /usr/local/lib/libOgreOverlay.so.1.12.6
Client: /usr/local/lib/libOgreRTShaderSystem.so.1.12.6
Client: /usr/local/lib/libOgreMain.so.1.12.6
Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client

.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/spectre/CLionProjects/Minos/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spectre/CLionProjects/Minos /home/spectre/CLionProjects/Minos /home/spectre/CLionProjects/Minos/cmake-build-debug /home/spectre/CLionProjects/Minos/cmake-build-debug /home/spectre/CLionProjects/Minos/cmake-build-debug/CMakeFiles/Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

