# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aucker/Develop/clox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aucker/Develop/clox/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/clox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/clox.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clox.dir/flags.make

CMakeFiles/clox.dir/main.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/main.c.o: /Users/aucker/Develop/clox/main.c
CMakeFiles/clox.dir/main.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/clox.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/main.c.o -MF CMakeFiles/clox.dir/main.c.o.d -o CMakeFiles/clox.dir/main.c.o -c /Users/aucker/Develop/clox/main.c

CMakeFiles/clox.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/main.c > CMakeFiles/clox.dir/main.c.i

CMakeFiles/clox.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/main.c -o CMakeFiles/clox.dir/main.c.s

CMakeFiles/clox.dir/chunk.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/chunk.c.o: /Users/aucker/Develop/clox/chunk.c
CMakeFiles/clox.dir/chunk.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/clox.dir/chunk.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/chunk.c.o -MF CMakeFiles/clox.dir/chunk.c.o.d -o CMakeFiles/clox.dir/chunk.c.o -c /Users/aucker/Develop/clox/chunk.c

CMakeFiles/clox.dir/chunk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/chunk.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/chunk.c > CMakeFiles/clox.dir/chunk.c.i

CMakeFiles/clox.dir/chunk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/chunk.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/chunk.c -o CMakeFiles/clox.dir/chunk.c.s

CMakeFiles/clox.dir/memory.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/memory.c.o: /Users/aucker/Develop/clox/memory.c
CMakeFiles/clox.dir/memory.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/clox.dir/memory.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/memory.c.o -MF CMakeFiles/clox.dir/memory.c.o.d -o CMakeFiles/clox.dir/memory.c.o -c /Users/aucker/Develop/clox/memory.c

CMakeFiles/clox.dir/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/memory.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/memory.c > CMakeFiles/clox.dir/memory.c.i

CMakeFiles/clox.dir/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/memory.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/memory.c -o CMakeFiles/clox.dir/memory.c.s

CMakeFiles/clox.dir/debug.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/debug.c.o: /Users/aucker/Develop/clox/debug.c
CMakeFiles/clox.dir/debug.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/clox.dir/debug.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/debug.c.o -MF CMakeFiles/clox.dir/debug.c.o.d -o CMakeFiles/clox.dir/debug.c.o -c /Users/aucker/Develop/clox/debug.c

CMakeFiles/clox.dir/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/debug.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/debug.c > CMakeFiles/clox.dir/debug.c.i

CMakeFiles/clox.dir/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/debug.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/debug.c -o CMakeFiles/clox.dir/debug.c.s

CMakeFiles/clox.dir/value.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/value.c.o: /Users/aucker/Develop/clox/value.c
CMakeFiles/clox.dir/value.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/clox.dir/value.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/value.c.o -MF CMakeFiles/clox.dir/value.c.o.d -o CMakeFiles/clox.dir/value.c.o -c /Users/aucker/Develop/clox/value.c

CMakeFiles/clox.dir/value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/value.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/value.c > CMakeFiles/clox.dir/value.c.i

CMakeFiles/clox.dir/value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/value.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/value.c -o CMakeFiles/clox.dir/value.c.s

CMakeFiles/clox.dir/vm.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/vm.c.o: /Users/aucker/Develop/clox/vm.c
CMakeFiles/clox.dir/vm.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/clox.dir/vm.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/vm.c.o -MF CMakeFiles/clox.dir/vm.c.o.d -o CMakeFiles/clox.dir/vm.c.o -c /Users/aucker/Develop/clox/vm.c

CMakeFiles/clox.dir/vm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/vm.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/vm.c > CMakeFiles/clox.dir/vm.c.i

CMakeFiles/clox.dir/vm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/vm.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/vm.c -o CMakeFiles/clox.dir/vm.c.s

CMakeFiles/clox.dir/compiler.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/compiler.c.o: /Users/aucker/Develop/clox/compiler.c
CMakeFiles/clox.dir/compiler.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/clox.dir/compiler.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/compiler.c.o -MF CMakeFiles/clox.dir/compiler.c.o.d -o CMakeFiles/clox.dir/compiler.c.o -c /Users/aucker/Develop/clox/compiler.c

CMakeFiles/clox.dir/compiler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/compiler.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/compiler.c > CMakeFiles/clox.dir/compiler.c.i

CMakeFiles/clox.dir/compiler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/compiler.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/compiler.c -o CMakeFiles/clox.dir/compiler.c.s

CMakeFiles/clox.dir/scanner.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/scanner.c.o: /Users/aucker/Develop/clox/scanner.c
CMakeFiles/clox.dir/scanner.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/clox.dir/scanner.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/scanner.c.o -MF CMakeFiles/clox.dir/scanner.c.o.d -o CMakeFiles/clox.dir/scanner.c.o -c /Users/aucker/Develop/clox/scanner.c

CMakeFiles/clox.dir/scanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/scanner.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/scanner.c > CMakeFiles/clox.dir/scanner.c.i

CMakeFiles/clox.dir/scanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/scanner.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/scanner.c -o CMakeFiles/clox.dir/scanner.c.s

CMakeFiles/clox.dir/object.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/object.c.o: /Users/aucker/Develop/clox/object.c
CMakeFiles/clox.dir/object.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/clox.dir/object.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/object.c.o -MF CMakeFiles/clox.dir/object.c.o.d -o CMakeFiles/clox.dir/object.c.o -c /Users/aucker/Develop/clox/object.c

CMakeFiles/clox.dir/object.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/object.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/object.c > CMakeFiles/clox.dir/object.c.i

CMakeFiles/clox.dir/object.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/object.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/object.c -o CMakeFiles/clox.dir/object.c.s

CMakeFiles/clox.dir/table.c.o: CMakeFiles/clox.dir/flags.make
CMakeFiles/clox.dir/table.c.o: /Users/aucker/Develop/clox/table.c
CMakeFiles/clox.dir/table.c.o: CMakeFiles/clox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/clox.dir/table.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/clox.dir/table.c.o -MF CMakeFiles/clox.dir/table.c.o.d -o CMakeFiles/clox.dir/table.c.o -c /Users/aucker/Develop/clox/table.c

CMakeFiles/clox.dir/table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clox.dir/table.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aucker/Develop/clox/table.c > CMakeFiles/clox.dir/table.c.i

CMakeFiles/clox.dir/table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clox.dir/table.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aucker/Develop/clox/table.c -o CMakeFiles/clox.dir/table.c.s

# Object files for target clox
clox_OBJECTS = \
"CMakeFiles/clox.dir/main.c.o" \
"CMakeFiles/clox.dir/chunk.c.o" \
"CMakeFiles/clox.dir/memory.c.o" \
"CMakeFiles/clox.dir/debug.c.o" \
"CMakeFiles/clox.dir/value.c.o" \
"CMakeFiles/clox.dir/vm.c.o" \
"CMakeFiles/clox.dir/compiler.c.o" \
"CMakeFiles/clox.dir/scanner.c.o" \
"CMakeFiles/clox.dir/object.c.o" \
"CMakeFiles/clox.dir/table.c.o"

# External object files for target clox
clox_EXTERNAL_OBJECTS =

clox: CMakeFiles/clox.dir/main.c.o
clox: CMakeFiles/clox.dir/chunk.c.o
clox: CMakeFiles/clox.dir/memory.c.o
clox: CMakeFiles/clox.dir/debug.c.o
clox: CMakeFiles/clox.dir/value.c.o
clox: CMakeFiles/clox.dir/vm.c.o
clox: CMakeFiles/clox.dir/compiler.c.o
clox: CMakeFiles/clox.dir/scanner.c.o
clox: CMakeFiles/clox.dir/object.c.o
clox: CMakeFiles/clox.dir/table.c.o
clox: CMakeFiles/clox.dir/build.make
clox: CMakeFiles/clox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable clox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clox.dir/build: clox
.PHONY : CMakeFiles/clox.dir/build

CMakeFiles/clox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clox.dir/clean

CMakeFiles/clox.dir/depend:
	cd /Users/aucker/Develop/clox/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aucker/Develop/clox /Users/aucker/Develop/clox /Users/aucker/Develop/clox/cmake-build-debug /Users/aucker/Develop/clox/cmake-build-debug /Users/aucker/Develop/clox/cmake-build-debug/CMakeFiles/clox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clox.dir/depend

