# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aucker/dev/clox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aucker/dev/clox/build

# Include any dependencies generated for this target.
include CMakeFiles/clox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/clox.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clox.dir/flags.make

CMakeFiles/clox.dir/src/chunk.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/src/chunk.c.o: /home/aucker/dev/clox/src/chunk.c
CMakeFiles/clox.dir/src/chunk.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/clox.dir/src/chunk.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/src/chunk.c.o -MF CMakeFiles/clox.dir/src/chunk.c.o.d -o CMakeFiles/clox.dir/src/chunk.c.o -c /home/aucker/dev/clox/src/chunk.c

CMakeFiles/clox.dir/src/chunk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/clox.dir/src/chunk.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aucker/dev/clox/src/chunk.c > CMakeFiles/clox.dir/src/chunk.c.i

CMakeFiles/clox.dir/src/chunk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/clox.dir/src/chunk.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aucker/dev/clox/src/chunk.c -o CMakeFiles/clox.dir/src/chunk.c.s

CMakeFiles/clox.dir/src/debug.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/src/debug.c.o: /home/aucker/dev/clox/src/debug.c
CMakeFiles/clox.dir/src/debug.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/clox.dir/src/debug.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/src/debug.c.o -MF CMakeFiles/clox.dir/src/debug.c.o.d -o CMakeFiles/clox.dir/src/debug.c.o -c /home/aucker/dev/clox/src/debug.c

CMakeFiles/clox.dir/src/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/clox.dir/src/debug.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aucker/dev/clox/src/debug.c > CMakeFiles/clox.dir/src/debug.c.i

CMakeFiles/clox.dir/src/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/clox.dir/src/debug.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aucker/dev/clox/src/debug.c -o CMakeFiles/clox.dir/src/debug.c.s

CMakeFiles/clox.dir/src/main.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/src/main.c.o: /home/aucker/dev/clox/src/main.c
CMakeFiles/clox.dir/src/main.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/clox.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/src/main.c.o -MF CMakeFiles/clox.dir/src/main.c.o.d -o CMakeFiles/clox.dir/src/main.c.o -c /home/aucker/dev/clox/src/main.c

CMakeFiles/clox.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/clox.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aucker/dev/clox/src/main.c > CMakeFiles/clox.dir/src/main.c.i

CMakeFiles/clox.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/clox.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aucker/dev/clox/src/main.c -o CMakeFiles/clox.dir/src/main.c.s

CMakeFiles/clox.dir/src/memory.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/src/memory.c.o: /home/aucker/dev/clox/src/memory.c
CMakeFiles/clox.dir/src/memory.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/clox.dir/src/memory.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/src/memory.c.o -MF CMakeFiles/clox.dir/src/memory.c.o.d -o CMakeFiles/clox.dir/src/memory.c.o -c /home/aucker/dev/clox/src/memory.c

CMakeFiles/clox.dir/src/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/clox.dir/src/memory.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aucker/dev/clox/src/memory.c > CMakeFiles/clox.dir/src/memory.c.i

CMakeFiles/clox.dir/src/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/clox.dir/src/memory.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aucker/dev/clox/src/memory.c -o CMakeFiles/clox.dir/src/memory.c.s

CMakeFiles/clox.dir/src/value.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/src/value.c.o: /home/aucker/dev/clox/src/value.c
CMakeFiles/clox.dir/src/value.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/clox.dir/src/value.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/src/value.c.o -MF CMakeFiles/clox.dir/src/value.c.o.d -o CMakeFiles/clox.dir/src/value.c.o -c /home/aucker/dev/clox/src/value.c

CMakeFiles/clox.dir/src/value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/clox.dir/src/value.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aucker/dev/clox/src/value.c > CMakeFiles/clox.dir/src/value.c.i

CMakeFiles/clox.dir/src/value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/clox.dir/src/value.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aucker/dev/clox/src/value.c -o CMakeFiles/clox.dir/src/value.c.s

# Object files for target clox
clox_OBJECTS = \
"CMakeFiles/clox.dir/src/chunk.c.o" \
"CMakeFiles/clox.dir/src/debug.c.o" \
"CMakeFiles/clox.dir/src/main.c.o" \
"CMakeFiles/clox.dir/src/memory.c.o" \
"CMakeFiles/clox.dir/src/value.c.o"

# External object files for target clox
clox_EXTERNAL_OBJECTS =

clox: CMakeFiles/clox.dir/src/chunk.c.o
clox: CMakeFiles/clox.dir/src/debug.c.o
clox: CMakeFiles/clox.dir/src/main.c.o
clox: CMakeFiles/clox.dir/src/memory.c.o
clox: CMakeFiles/clox.dir/src/value.c.o
clox: CMakeFiles/clox.dir/build.make
clox: CMakeFiles/clox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/aucker/dev/clox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable clox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clox.dir/build: clox
.PHONY : CMakeFiles/clox.dir/build

CMakeFiles/clox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clox.dir/clean

CMakeFiles/clox.dir/depend:
	cd /home/aucker/dev/clox/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aucker/dev/clox /home/aucker/dev/clox /home/aucker/dev/clox/build /home/aucker/dev/clox/build /home/aucker/dev/clox/build/CMakeFiles/clox.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/clox.dir/depend

