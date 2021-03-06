# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/user/Documents/DevTechnics/GameOfLifezProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Documents/DevTechnics/GameOfLifezProject/build

# Include any dependencies generated for this target.
include draw_animation_library/CMakeFiles/draw_animation_library.dir/depend.make

# Include the progress variables for this target.
include draw_animation_library/CMakeFiles/draw_animation_library.dir/progress.make

# Include the compile flags for this target's objects.
include draw_animation_library/CMakeFiles/draw_animation_library.dir/flags.make

draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.o: draw_animation_library/CMakeFiles/draw_animation_library.dir/flags.make
draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.o: ../draw_animation_library/board_drawer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Documents/DevTechnics/GameOfLifezProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.o"
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/draw_animation_library.dir/board_drawer.c.o   -c /home/user/Documents/DevTechnics/GameOfLifezProject/draw_animation_library/board_drawer.c

draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/draw_animation_library.dir/board_drawer.c.i"
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/Documents/DevTechnics/GameOfLifezProject/draw_animation_library/board_drawer.c > CMakeFiles/draw_animation_library.dir/board_drawer.c.i

draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/draw_animation_library.dir/board_drawer.c.s"
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/Documents/DevTechnics/GameOfLifezProject/draw_animation_library/board_drawer.c -o CMakeFiles/draw_animation_library.dir/board_drawer.c.s

# Object files for target draw_animation_library
draw_animation_library_OBJECTS = \
"CMakeFiles/draw_animation_library.dir/board_drawer.c.o"

# External object files for target draw_animation_library
draw_animation_library_EXTERNAL_OBJECTS =

draw_animation_library/libdraw_animation_library.a: draw_animation_library/CMakeFiles/draw_animation_library.dir/board_drawer.c.o
draw_animation_library/libdraw_animation_library.a: draw_animation_library/CMakeFiles/draw_animation_library.dir/build.make
draw_animation_library/libdraw_animation_library.a: draw_animation_library/CMakeFiles/draw_animation_library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Documents/DevTechnics/GameOfLifezProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libdraw_animation_library.a"
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && $(CMAKE_COMMAND) -P CMakeFiles/draw_animation_library.dir/cmake_clean_target.cmake
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/draw_animation_library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
draw_animation_library/CMakeFiles/draw_animation_library.dir/build: draw_animation_library/libdraw_animation_library.a

.PHONY : draw_animation_library/CMakeFiles/draw_animation_library.dir/build

draw_animation_library/CMakeFiles/draw_animation_library.dir/clean:
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library && $(CMAKE_COMMAND) -P CMakeFiles/draw_animation_library.dir/cmake_clean.cmake
.PHONY : draw_animation_library/CMakeFiles/draw_animation_library.dir/clean

draw_animation_library/CMakeFiles/draw_animation_library.dir/depend:
	cd /home/user/Documents/DevTechnics/GameOfLifezProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Documents/DevTechnics/GameOfLifezProject /home/user/Documents/DevTechnics/GameOfLifezProject/draw_animation_library /home/user/Documents/DevTechnics/GameOfLifezProject/build /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library /home/user/Documents/DevTechnics/GameOfLifezProject/build/draw_animation_library/CMakeFiles/draw_animation_library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : draw_animation_library/CMakeFiles/draw_animation_library.dir/depend

