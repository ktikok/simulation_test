# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /cvmfs/sft.cern.ch/lcg/contrib/CMake/3.14.2/Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /cvmfs/sft.cern.ch/lcg/contrib/CMake/3.14.2/Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /fcc/tikim/ky_example/DR_tag_001

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /fcc/tikim/ky_example/DR_tag_001/build

# Include any dependencies generated for this target.
include analysis/CMakeFiles/calib.dir/depend.make

# Include the progress variables for this target.
include analysis/CMakeFiles/calib.dir/progress.make

# Include the compile flags for this target's objects.
include analysis/CMakeFiles/calib.dir/flags.make

analysis/CMakeFiles/calib.dir/calib.cc.o: analysis/CMakeFiles/calib.dir/flags.make
analysis/CMakeFiles/calib.dir/calib.cc.o: ../analysis/calib.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fcc/tikim/ky_example/DR_tag_001/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object analysis/CMakeFiles/calib.dir/calib.cc.o"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calib.dir/calib.cc.o -c /fcc/tikim/ky_example/DR_tag_001/analysis/calib.cc

analysis/CMakeFiles/calib.dir/calib.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calib.dir/calib.cc.i"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /fcc/tikim/ky_example/DR_tag_001/analysis/calib.cc > CMakeFiles/calib.dir/calib.cc.i

analysis/CMakeFiles/calib.dir/calib.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calib.dir/calib.cc.s"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /fcc/tikim/ky_example/DR_tag_001/analysis/calib.cc -o CMakeFiles/calib.dir/calib.cc.s

analysis/CMakeFiles/calib.dir/src/functions.cc.o: analysis/CMakeFiles/calib.dir/flags.make
analysis/CMakeFiles/calib.dir/src/functions.cc.o: ../analysis/src/functions.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fcc/tikim/ky_example/DR_tag_001/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object analysis/CMakeFiles/calib.dir/src/functions.cc.o"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calib.dir/src/functions.cc.o -c /fcc/tikim/ky_example/DR_tag_001/analysis/src/functions.cc

analysis/CMakeFiles/calib.dir/src/functions.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calib.dir/src/functions.cc.i"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /fcc/tikim/ky_example/DR_tag_001/analysis/src/functions.cc > CMakeFiles/calib.dir/src/functions.cc.i

analysis/CMakeFiles/calib.dir/src/functions.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calib.dir/src/functions.cc.s"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && /cvmfs/sft.cern.ch/lcg/releases/gcc/8.3.0-cebb0/x86_64-centos7/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /fcc/tikim/ky_example/DR_tag_001/analysis/src/functions.cc -o CMakeFiles/calib.dir/src/functions.cc.s

# Object files for target calib
calib_OBJECTS = \
"CMakeFiles/calib.dir/calib.cc.o" \
"CMakeFiles/calib.dir/src/functions.cc.o"

# External object files for target calib
calib_EXTERNAL_OBJECTS =

analysis/calib: analysis/CMakeFiles/calib.dir/calib.cc.o
analysis/calib: analysis/CMakeFiles/calib.dir/src/functions.cc.o
analysis/calib: analysis/CMakeFiles/calib.dir/build.make
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/hepmc3/3.1.2/x86_64-centos7-gcc8-opt/lib64/libHepMC3.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/hepmc3/3.1.2/x86_64-centos7-gcc8-opt/lib64/libHepMC3rootIO.so
analysis/calib: rootIO/librootIO.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libCore.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libImt.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libRIO.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libNet.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libHist.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGraf.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGraf3d.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGpad.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libROOTDataFrame.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libTree.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libTreePlayer.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libRint.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libPostscript.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMatrix.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libPhysics.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMathCore.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libThread.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMultiProc.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/fastjet/3.3.2/x86_64-centos7-gcc8-opt/lib/libfastjet.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libCore.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libImt.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libRIO.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libNet.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libHist.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGraf.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGraf3d.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libGpad.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libROOTDataFrame.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libTree.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libTreePlayer.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libRint.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libPostscript.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMatrix.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libPhysics.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMathCore.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libThread.so
analysis/calib: /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib/libMultiProc.so
analysis/calib: analysis/CMakeFiles/calib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/fcc/tikim/ky_example/DR_tag_001/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable calib"
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
analysis/CMakeFiles/calib.dir/build: analysis/calib

.PHONY : analysis/CMakeFiles/calib.dir/build

analysis/CMakeFiles/calib.dir/clean:
	cd /fcc/tikim/ky_example/DR_tag_001/build/analysis && $(CMAKE_COMMAND) -P CMakeFiles/calib.dir/cmake_clean.cmake
.PHONY : analysis/CMakeFiles/calib.dir/clean

analysis/CMakeFiles/calib.dir/depend:
	cd /fcc/tikim/ky_example/DR_tag_001/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fcc/tikim/ky_example/DR_tag_001 /fcc/tikim/ky_example/DR_tag_001/analysis /fcc/tikim/ky_example/DR_tag_001/build /fcc/tikim/ky_example/DR_tag_001/build/analysis /fcc/tikim/ky_example/DR_tag_001/build/analysis/CMakeFiles/calib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : analysis/CMakeFiles/calib.dir/depend
