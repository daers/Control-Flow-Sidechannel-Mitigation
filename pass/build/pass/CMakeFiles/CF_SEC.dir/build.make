# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build

# Include any dependencies generated for this target.
include pass/CMakeFiles/CF_SEC.dir/depend.make

# Include the progress variables for this target.
include pass/CMakeFiles/CF_SEC.dir/progress.make

# Include the compile flags for this target's objects.
include pass/CMakeFiles/CF_SEC.dir/flags.make

pass/CMakeFiles/CF_SEC.dir/pass.cpp.o: pass/CMakeFiles/CF_SEC.dir/flags.make
pass/CMakeFiles/CF_SEC.dir/pass.cpp.o: ../pass/pass.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pass/CMakeFiles/CF_SEC.dir/pass.cpp.o"
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CF_SEC.dir/pass.cpp.o -c /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/pass/pass.cpp

pass/CMakeFiles/CF_SEC.dir/pass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CF_SEC.dir/pass.cpp.i"
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/pass/pass.cpp > CMakeFiles/CF_SEC.dir/pass.cpp.i

pass/CMakeFiles/CF_SEC.dir/pass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CF_SEC.dir/pass.cpp.s"
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/pass/pass.cpp -o CMakeFiles/CF_SEC.dir/pass.cpp.s

pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.requires:

.PHONY : pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.requires

pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.provides: pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.requires
	$(MAKE) -f pass/CMakeFiles/CF_SEC.dir/build.make pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.provides.build
.PHONY : pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.provides

pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.provides.build: pass/CMakeFiles/CF_SEC.dir/pass.cpp.o


# Object files for target CF_SEC
CF_SEC_OBJECTS = \
"CMakeFiles/CF_SEC.dir/pass.cpp.o"

# External object files for target CF_SEC
CF_SEC_EXTERNAL_OBJECTS =

pass/CF_SEC.so: pass/CMakeFiles/CF_SEC.dir/pass.cpp.o
pass/CF_SEC.so: pass/CMakeFiles/CF_SEC.dir/build.make
pass/CF_SEC.so: pass/CMakeFiles/CF_SEC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module CF_SEC.so"
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CF_SEC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pass/CMakeFiles/CF_SEC.dir/build: pass/CF_SEC.so

.PHONY : pass/CMakeFiles/CF_SEC.dir/build

pass/CMakeFiles/CF_SEC.dir/requires: pass/CMakeFiles/CF_SEC.dir/pass.cpp.o.requires

.PHONY : pass/CMakeFiles/CF_SEC.dir/requires

pass/CMakeFiles/CF_SEC.dir/clean:
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass && $(CMAKE_COMMAND) -P CMakeFiles/CF_SEC.dir/cmake_clean.cmake
.PHONY : pass/CMakeFiles/CF_SEC.dir/clean

pass/CMakeFiles/CF_SEC.dir/depend:
	cd /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/pass /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass /home/jakehage/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CMakeFiles/CF_SEC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pass/CMakeFiles/CF_SEC.dir/depend

