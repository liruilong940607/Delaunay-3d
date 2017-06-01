# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_SOURCE_DIR = /home/dongx12/Homework/Delaunay-3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dongx12/Homework/Delaunay-3d

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dongx12/Homework/Delaunay-3d/CMakeFiles /home/dongx12/Homework/Delaunay-3d/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dongx12/Homework/Delaunay-3d/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named voronoi-3d

# Build rule for target.
voronoi-3d: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 voronoi-3d
.PHONY : voronoi-3d

# fast build rule for target.
voronoi-3d/fast:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/build
.PHONY : voronoi-3d/fast

src/Application.o: src/Application.cpp.o
.PHONY : src/Application.o

# target to build an object file
src/Application.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Application.cpp.o
.PHONY : src/Application.cpp.o

src/Application.i: src/Application.cpp.i
.PHONY : src/Application.i

# target to preprocess a source file
src/Application.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Application.cpp.i
.PHONY : src/Application.cpp.i

src/Application.s: src/Application.cpp.s
.PHONY : src/Application.s

# target to generate assembly for a file
src/Application.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Application.cpp.s
.PHONY : src/Application.cpp.s

src/Cube.o: src/Cube.cpp.o
.PHONY : src/Cube.o

# target to build an object file
src/Cube.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o
.PHONY : src/Cube.cpp.o

src/Cube.i: src/Cube.cpp.i
.PHONY : src/Cube.i

# target to preprocess a source file
src/Cube.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Cube.cpp.i
.PHONY : src/Cube.cpp.i

src/Cube.s: src/Cube.cpp.s
.PHONY : src/Cube.s

# target to generate assembly for a file
src/Cube.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Cube.cpp.s
.PHONY : src/Cube.cpp.s

src/Delaunay.o: src/Delaunay.cpp.o
.PHONY : src/Delaunay.o

# target to build an object file
src/Delaunay.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o
.PHONY : src/Delaunay.cpp.o

src/Delaunay.i: src/Delaunay.cpp.i
.PHONY : src/Delaunay.i

# target to preprocess a source file
src/Delaunay.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.i
.PHONY : src/Delaunay.cpp.i

src/Delaunay.s: src/Delaunay.cpp.s
.PHONY : src/Delaunay.s

# target to generate assembly for a file
src/Delaunay.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.s
.PHONY : src/Delaunay.cpp.s

src/Line.o: src/Line.cpp.o
.PHONY : src/Line.o

# target to build an object file
src/Line.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Line.cpp.o
.PHONY : src/Line.cpp.o

src/Line.i: src/Line.cpp.i
.PHONY : src/Line.i

# target to preprocess a source file
src/Line.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Line.cpp.i
.PHONY : src/Line.cpp.i

src/Line.s: src/Line.cpp.s
.PHONY : src/Line.s

# target to generate assembly for a file
src/Line.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Line.cpp.s
.PHONY : src/Line.cpp.s

src/Tetrahedron.o: src/Tetrahedron.cpp.o
.PHONY : src/Tetrahedron.o

# target to build an object file
src/Tetrahedron.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o
.PHONY : src/Tetrahedron.cpp.o

src/Tetrahedron.i: src/Tetrahedron.cpp.i
.PHONY : src/Tetrahedron.i

# target to preprocess a source file
src/Tetrahedron.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.i
.PHONY : src/Tetrahedron.cpp.i

src/Tetrahedron.s: src/Tetrahedron.cpp.s
.PHONY : src/Tetrahedron.s

# target to generate assembly for a file
src/Tetrahedron.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.s
.PHONY : src/Tetrahedron.cpp.s

src/Triangle.o: src/Triangle.cpp.o
.PHONY : src/Triangle.o

# target to build an object file
src/Triangle.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o
.PHONY : src/Triangle.cpp.o

src/Triangle.i: src/Triangle.cpp.i
.PHONY : src/Triangle.i

# target to preprocess a source file
src/Triangle.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.i
.PHONY : src/Triangle.cpp.i

src/Triangle.s: src/Triangle.cpp.s
.PHONY : src/Triangle.s

# target to generate assembly for a file
src/Triangle.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.s
.PHONY : src/Triangle.cpp.s

src/Vector3.o: src/Vector3.cpp.o
.PHONY : src/Vector3.o

# target to build an object file
src/Vector3.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o
.PHONY : src/Vector3.cpp.o

src/Vector3.i: src/Vector3.cpp.i
.PHONY : src/Vector3.i

# target to preprocess a source file
src/Vector3.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.i
.PHONY : src/Vector3.cpp.i

src/Vector3.s: src/Vector3.cpp.s
.PHONY : src/Vector3.s

# target to generate assembly for a file
src/Vector3.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.s
.PHONY : src/Vector3.cpp.s

src/convhull.o: src/convhull.cpp.o
.PHONY : src/convhull.o

# target to build an object file
src/convhull.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull.cpp.o
.PHONY : src/convhull.cpp.o

src/convhull.i: src/convhull.cpp.i
.PHONY : src/convhull.i

# target to preprocess a source file
src/convhull.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull.cpp.i
.PHONY : src/convhull.cpp.i

src/convhull.s: src/convhull.cpp.s
.PHONY : src/convhull.s

# target to generate assembly for a file
src/convhull.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull.cpp.s
.PHONY : src/convhull.cpp.s

src/convhull_demo.o: src/convhull_demo.cpp.o
.PHONY : src/convhull_demo.o

# target to build an object file
src/convhull_demo.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull_demo.cpp.o
.PHONY : src/convhull_demo.cpp.o

src/convhull_demo.i: src/convhull_demo.cpp.i
.PHONY : src/convhull_demo.i

# target to preprocess a source file
src/convhull_demo.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull_demo.cpp.i
.PHONY : src/convhull_demo.cpp.i

src/convhull_demo.s: src/convhull_demo.cpp.s
.PHONY : src/convhull_demo.s

# target to generate assembly for a file
src/convhull_demo.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/convhull_demo.cpp.s
.PHONY : src/convhull_demo.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... voronoi-3d"
	@echo "... src/Application.o"
	@echo "... src/Application.i"
	@echo "... src/Application.s"
	@echo "... src/Cube.o"
	@echo "... src/Cube.i"
	@echo "... src/Cube.s"
	@echo "... src/Delaunay.o"
	@echo "... src/Delaunay.i"
	@echo "... src/Delaunay.s"
	@echo "... src/Line.o"
	@echo "... src/Line.i"
	@echo "... src/Line.s"
	@echo "... src/Tetrahedron.o"
	@echo "... src/Tetrahedron.i"
	@echo "... src/Tetrahedron.s"
	@echo "... src/Triangle.o"
	@echo "... src/Triangle.i"
	@echo "... src/Triangle.s"
	@echo "... src/Vector3.o"
	@echo "... src/Vector3.i"
	@echo "... src/Vector3.s"
	@echo "... src/convhull.o"
	@echo "... src/convhull.i"
	@echo "... src/convhull.s"
	@echo "... src/convhull_demo.o"
	@echo "... src/convhull_demo.i"
	@echo "... src/convhull_demo.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

