# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build

# Utility rule file for flash_test.

# Include any custom commands dependencies for this target.
include test/CMakeFiles/flash_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/flash_test.dir/progress.make

test/CMakeFiles/flash_test: test/mytest.elf
	cd /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test && picotool load -f /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test/mytest.elf

flash_test: test/CMakeFiles/flash_test
flash_test: test/CMakeFiles/flash_test.dir/build.make
.PHONY : flash_test

# Rule to build all files generated by this target.
test/CMakeFiles/flash_test.dir/build: flash_test
.PHONY : test/CMakeFiles/flash_test.dir/build

test/CMakeFiles/flash_test.dir/clean:
	cd /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test && $(CMAKE_COMMAND) -P CMakeFiles/flash_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/flash_test.dir/clean

test/CMakeFiles/flash_test.dir/depend:
	cd /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/test /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test/CMakeFiles/flash_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/flash_test.dir/depend

