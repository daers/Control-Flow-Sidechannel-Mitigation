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
CMAKE_SOURCE_DIR = /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build

# Utility rule file for install-CF_SEC.

# Include the progress variables for this target.
include pass/CMakeFiles/install-CF_SEC.dir/progress.make

pass/CMakeFiles/install-CF_SEC: pass/CF_SEC.so
	cd /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build/pass && /usr/bin/cmake -DCMAKE_INSTALL_COMPONENT="CF_SEC" -P /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build/cmake_install.cmake

install-CF_SEC: pass/CMakeFiles/install-CF_SEC
install-CF_SEC: pass/CMakeFiles/install-CF_SEC.dir/build.make

.PHONY : install-CF_SEC

# Rule to build all files generated by this target.
pass/CMakeFiles/install-CF_SEC.dir/build: install-CF_SEC

.PHONY : pass/CMakeFiles/install-CF_SEC.dir/build

pass/CMakeFiles/install-CF_SEC.dir/clean:
	cd /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build/pass && $(CMAKE_COMMAND) -P CMakeFiles/install-CF_SEC.dir/cmake_clean.cmake
.PHONY : pass/CMakeFiles/install-CF_SEC.dir/clean

pass/CMakeFiles/install-CF_SEC.dir/depend:
	cd /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/pass /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build/pass /home/cnoujaim/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CMakeFiles/install-CF_SEC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pass/CMakeFiles/install-CF_SEC.dir/depend

