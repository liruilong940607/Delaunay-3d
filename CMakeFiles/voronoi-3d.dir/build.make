# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d

# Include any dependencies generated for this target.
include CMakeFiles/voronoi-3d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/voronoi-3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voronoi-3d.dir/flags.make

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o: src/Voronoi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Voronoi.cpp

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Voronoi.cpp > CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.i

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Voronoi.cpp -o CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.s

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o: src/Cube.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Cube.cpp

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Cube.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Cube.cpp > CMakeFiles/voronoi-3d.dir/src/Cube.cpp.i

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Cube.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Cube.cpp -o CMakeFiles/voronoi-3d.dir/src/Cube.cpp.s

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o: src/Delaunay.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Delaunay.cpp

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Delaunay.cpp > CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.i

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Delaunay.cpp -o CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.s

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o

CMakeFiles/voronoi-3d.dir/src/Line.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Line.cpp.o: src/Line.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Line.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Line.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Line.cpp

CMakeFiles/voronoi-3d.dir/src/Line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Line.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Line.cpp > CMakeFiles/voronoi-3d.dir/src/Line.cpp.i

CMakeFiles/voronoi-3d.dir/src/Line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Line.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Line.cpp -o CMakeFiles/voronoi-3d.dir/src/Line.cpp.s

CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Line.cpp.o

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o: src/Vector3.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Vector3.cpp

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Vector3.cpp > CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.i

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Vector3.cpp -o CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.s

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o: src/Triangle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Triangle.cpp

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Triangle.cpp > CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.i

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Triangle.cpp -o CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.s

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o: src/Tetrahedron.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Tetrahedron.cpp

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Tetrahedron.cpp > CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.i

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Tetrahedron.cpp -o CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.s

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o

CMakeFiles/voronoi-3d.dir/src/Application.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/Application.cpp.o: src/Application.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/Application.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/Application.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Application.cpp

CMakeFiles/voronoi-3d.dir/src/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/Application.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Application.cpp > CMakeFiles/voronoi-3d.dir/src/Application.cpp.i

CMakeFiles/voronoi-3d.dir/src/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/Application.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/Application.cpp -o CMakeFiles/voronoi-3d.dir/src/Application.cpp.s

CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/Application.cpp.o

CMakeFiles/voronoi-3d.dir/src/main.cpp.o: CMakeFiles/voronoi-3d.dir/flags.make
CMakeFiles/voronoi-3d.dir/src/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voronoi-3d.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voronoi-3d.dir/src/main.cpp.o -c /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/main.cpp

CMakeFiles/voronoi-3d.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoi-3d.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/main.cpp > CMakeFiles/voronoi-3d.dir/src/main.cpp.i

CMakeFiles/voronoi-3d.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoi-3d.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/src/main.cpp -o CMakeFiles/voronoi-3d.dir/src/main.cpp.s

CMakeFiles/voronoi-3d.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/voronoi-3d.dir/src/main.cpp.o.requires

CMakeFiles/voronoi-3d.dir/src/main.cpp.o.provides: CMakeFiles/voronoi-3d.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/voronoi-3d.dir/build.make CMakeFiles/voronoi-3d.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/voronoi-3d.dir/src/main.cpp.o.provides

CMakeFiles/voronoi-3d.dir/src/main.cpp.o.provides.build: CMakeFiles/voronoi-3d.dir/src/main.cpp.o

# Object files for target voronoi-3d
voronoi__3d_OBJECTS = \
"CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Line.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/Application.cpp.o" \
"CMakeFiles/voronoi-3d.dir/src/main.cpp.o"

# External object files for target voronoi-3d
voronoi__3d_EXTERNAL_OBJECTS =

voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Line.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/Application.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/src/main.cpp.o
voronoi-3d: CMakeFiles/voronoi-3d.dir/build.make
voronoi-3d: /usr/lib/x86_64-linux-gnu/libGLU.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libGL.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libSM.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libICE.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libX11.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libXext.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libGLEW.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libglut.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libXmu.so
voronoi-3d: /usr/lib/x86_64-linux-gnu/libXi.so
voronoi-3d: CMakeFiles/voronoi-3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable voronoi-3d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voronoi-3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voronoi-3d.dir/build: voronoi-3d
.PHONY : CMakeFiles/voronoi-3d.dir/build

CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Voronoi.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Cube.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Delaunay.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Line.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Vector3.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Triangle.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Tetrahedron.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/Application.cpp.o.requires
CMakeFiles/voronoi-3d.dir/requires: CMakeFiles/voronoi-3d.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/voronoi-3d.dir/requires

CMakeFiles/voronoi-3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voronoi-3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voronoi-3d.dir/clean

CMakeFiles/voronoi-3d.dir/depend:
	cd /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d /home/dalong/Workspace/CG-Voronoi/My-voronoi-3d/CMakeFiles/voronoi-3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voronoi-3d.dir/depend

