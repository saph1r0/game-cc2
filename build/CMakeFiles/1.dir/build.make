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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu20/c++/gaamee-cc2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu20/c++/gaamee-cc2/build

# Include any dependencies generated for this target.
include CMakeFiles/1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1.dir/flags.make

CMakeFiles/1.dir/src/main.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/main.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/main.cpp
CMakeFiles/1.dir/src/main.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/main.cpp.o -MF CMakeFiles/1.dir/src/main.cpp.o.d -o CMakeFiles/1.dir/src/main.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/main.cpp

CMakeFiles/1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/main.cpp > CMakeFiles/1.dir/src/main.cpp.i

CMakeFiles/1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/main.cpp -o CMakeFiles/1.dir/src/main.cpp.s

CMakeFiles/1.dir/src/Platform.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/Platform.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/Platform.cpp
CMakeFiles/1.dir/src/Platform.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/1.dir/src/Platform.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/Platform.cpp.o -MF CMakeFiles/1.dir/src/Platform.cpp.o.d -o CMakeFiles/1.dir/src/Platform.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/Platform.cpp

CMakeFiles/1.dir/src/Platform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/Platform.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/Platform.cpp > CMakeFiles/1.dir/src/Platform.cpp.i

CMakeFiles/1.dir/src/Platform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/Platform.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/Platform.cpp -o CMakeFiles/1.dir/src/Platform.cpp.s

CMakeFiles/1.dir/src/Player.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/Player.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/Player.cpp
CMakeFiles/1.dir/src/Player.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/1.dir/src/Player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/Player.cpp.o -MF CMakeFiles/1.dir/src/Player.cpp.o.d -o CMakeFiles/1.dir/src/Player.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/Player.cpp

CMakeFiles/1.dir/src/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/Player.cpp > CMakeFiles/1.dir/src/Player.cpp.i

CMakeFiles/1.dir/src/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/Player.cpp -o CMakeFiles/1.dir/src/Player.cpp.s

CMakeFiles/1.dir/src/Fireball.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/Fireball.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/Fireball.cpp
CMakeFiles/1.dir/src/Fireball.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/1.dir/src/Fireball.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/Fireball.cpp.o -MF CMakeFiles/1.dir/src/Fireball.cpp.o.d -o CMakeFiles/1.dir/src/Fireball.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/Fireball.cpp

CMakeFiles/1.dir/src/Fireball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/Fireball.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/Fireball.cpp > CMakeFiles/1.dir/src/Fireball.cpp.i

CMakeFiles/1.dir/src/Fireball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/Fireball.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/Fireball.cpp -o CMakeFiles/1.dir/src/Fireball.cpp.s

CMakeFiles/1.dir/src/Item.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/Item.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/Item.cpp
CMakeFiles/1.dir/src/Item.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/1.dir/src/Item.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/Item.cpp.o -MF CMakeFiles/1.dir/src/Item.cpp.o.d -o CMakeFiles/1.dir/src/Item.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/Item.cpp

CMakeFiles/1.dir/src/Item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/Item.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/Item.cpp > CMakeFiles/1.dir/src/Item.cpp.i

CMakeFiles/1.dir/src/Item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/Item.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/Item.cpp -o CMakeFiles/1.dir/src/Item.cpp.s

CMakeFiles/1.dir/src/Subject.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/Subject.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/Subject.cpp
CMakeFiles/1.dir/src/Subject.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/1.dir/src/Subject.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/Subject.cpp.o -MF CMakeFiles/1.dir/src/Subject.cpp.o.d -o CMakeFiles/1.dir/src/Subject.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/Subject.cpp

CMakeFiles/1.dir/src/Subject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/Subject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/Subject.cpp > CMakeFiles/1.dir/src/Subject.cpp.i

CMakeFiles/1.dir/src/Subject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/Subject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/Subject.cpp -o CMakeFiles/1.dir/src/Subject.cpp.s

CMakeFiles/1.dir/src/ItemFactory.cpp.o: CMakeFiles/1.dir/flags.make
CMakeFiles/1.dir/src/ItemFactory.cpp.o: /home/ubuntu20/c++/gaamee-cc2/src/ItemFactory.cpp
CMakeFiles/1.dir/src/ItemFactory.cpp.o: CMakeFiles/1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/1.dir/src/ItemFactory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1.dir/src/ItemFactory.cpp.o -MF CMakeFiles/1.dir/src/ItemFactory.cpp.o.d -o CMakeFiles/1.dir/src/ItemFactory.cpp.o -c /home/ubuntu20/c++/gaamee-cc2/src/ItemFactory.cpp

CMakeFiles/1.dir/src/ItemFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1.dir/src/ItemFactory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu20/c++/gaamee-cc2/src/ItemFactory.cpp > CMakeFiles/1.dir/src/ItemFactory.cpp.i

CMakeFiles/1.dir/src/ItemFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1.dir/src/ItemFactory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu20/c++/gaamee-cc2/src/ItemFactory.cpp -o CMakeFiles/1.dir/src/ItemFactory.cpp.s

# Object files for target 1
1_OBJECTS = \
"CMakeFiles/1.dir/src/main.cpp.o" \
"CMakeFiles/1.dir/src/Platform.cpp.o" \
"CMakeFiles/1.dir/src/Player.cpp.o" \
"CMakeFiles/1.dir/src/Fireball.cpp.o" \
"CMakeFiles/1.dir/src/Item.cpp.o" \
"CMakeFiles/1.dir/src/Subject.cpp.o" \
"CMakeFiles/1.dir/src/ItemFactory.cpp.o"

# External object files for target 1
1_EXTERNAL_OBJECTS =

1 : CMakeFiles/1.dir/src/main.cpp.o
1 : CMakeFiles/1.dir/src/Platform.cpp.o
1 : CMakeFiles/1.dir/src/Player.cpp.o
1 : CMakeFiles/1.dir/src/Fireball.cpp.o
1 : CMakeFiles/1.dir/src/Item.cpp.o
1 : CMakeFiles/1.dir/src/Subject.cpp.o
1 : CMakeFiles/1.dir/src/ItemFactory.cpp.o
1 : CMakeFiles/1.dir/build.make
1 : /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
1 : /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
1 : /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
1 : CMakeFiles/1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable 1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1.dir/build: 1
.PHONY : CMakeFiles/1.dir/build

CMakeFiles/1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1.dir/clean

CMakeFiles/1.dir/depend:
	cd /home/ubuntu20/c++/gaamee-cc2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu20/c++/gaamee-cc2 /home/ubuntu20/c++/gaamee-cc2 /home/ubuntu20/c++/gaamee-cc2/build /home/ubuntu20/c++/gaamee-cc2/build /home/ubuntu20/c++/gaamee-cc2/build/CMakeFiles/1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/1.dir/depend

