# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /skylendar/skylendar-4.1nn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /skylendar/builds/ubuntu

# Include any dependencies generated for this target.
include src/CMakeFiles/skyservice.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/skyservice.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/skyservice.dir/flags.make

src/CMakeFiles/skyservice.dir/skyservice.cpp.o: src/CMakeFiles/skyservice.dir/flags.make
src/CMakeFiles/skyservice.dir/skyservice.cpp.o: /skylendar/skylendar-4.1nn/src/skyservice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/skylendar/builds/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/skyservice.dir/skyservice.cpp.o"
	cd /skylendar/builds/ubuntu/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skyservice.dir/skyservice.cpp.o -c /skylendar/skylendar-4.1nn/src/skyservice.cpp

src/CMakeFiles/skyservice.dir/skyservice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skyservice.dir/skyservice.cpp.i"
	cd /skylendar/builds/ubuntu/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /skylendar/skylendar-4.1nn/src/skyservice.cpp > CMakeFiles/skyservice.dir/skyservice.cpp.i

src/CMakeFiles/skyservice.dir/skyservice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skyservice.dir/skyservice.cpp.s"
	cd /skylendar/builds/ubuntu/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /skylendar/skylendar-4.1nn/src/skyservice.cpp -o CMakeFiles/skyservice.dir/skyservice.cpp.s

src/CMakeFiles/skyservice.dir/skyservice.cpp.o.requires:

.PHONY : src/CMakeFiles/skyservice.dir/skyservice.cpp.o.requires

src/CMakeFiles/skyservice.dir/skyservice.cpp.o.provides: src/CMakeFiles/skyservice.dir/skyservice.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/skyservice.dir/build.make src/CMakeFiles/skyservice.dir/skyservice.cpp.o.provides.build
.PHONY : src/CMakeFiles/skyservice.dir/skyservice.cpp.o.provides

src/CMakeFiles/skyservice.dir/skyservice.cpp.o.provides.build: src/CMakeFiles/skyservice.dir/skyservice.cpp.o


# Object files for target skyservice
skyservice_OBJECTS = \
"CMakeFiles/skyservice.dir/skyservice.cpp.o"

# External object files for target skyservice
skyservice_EXTERNAL_OBJECTS =

src/skyservice: src/CMakeFiles/skyservice.dir/skyservice.cpp.o
src/skyservice: src/CMakeFiles/skyservice.dir/build.make
src/skyservice: src/libskyldr.so.4.1nn
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Xml.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Sql.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5DBus.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Svg.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.5.1
src/skyservice: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.5.1
src/skyservice: src/swe/libswe.a
src/skyservice: src/CMakeFiles/skyservice.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/skylendar/builds/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable skyservice"
	cd /skylendar/builds/ubuntu/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/skyservice.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/skyservice.dir/build: src/skyservice

.PHONY : src/CMakeFiles/skyservice.dir/build

src/CMakeFiles/skyservice.dir/requires: src/CMakeFiles/skyservice.dir/skyservice.cpp.o.requires

.PHONY : src/CMakeFiles/skyservice.dir/requires

src/CMakeFiles/skyservice.dir/clean:
	cd /skylendar/builds/ubuntu/src && $(CMAKE_COMMAND) -P CMakeFiles/skyservice.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/skyservice.dir/clean

src/CMakeFiles/skyservice.dir/depend:
	cd /skylendar/builds/ubuntu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /skylendar/skylendar-4.1nn /skylendar/skylendar-4.1nn/src /skylendar/builds/ubuntu /skylendar/builds/ubuntu/src /skylendar/builds/ubuntu/src/CMakeFiles/skyservice.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/skyservice.dir/depend

