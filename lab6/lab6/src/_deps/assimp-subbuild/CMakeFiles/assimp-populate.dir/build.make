# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild

# Utility rule file for assimp-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/assimp-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/assimp-populate.dir/progress.make

CMakeFiles/assimp-populate: CMakeFiles/assimp-populate-complete

CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-mkdir
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-build
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install
CMakeFiles/assimp-populate-complete: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'assimp-populate'"
	/usr/bin/cmake -E make_directory /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles/assimp-populate-complete
	/usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-done

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update:
.PHONY : assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-build: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E echo_append
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-build

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure: assimp-populate-prefix/tmp/assimp-populate-cfgcmd.txt
assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E echo_append
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-gitinfo.txt
assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps && /usr/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/tmp/assimp-populate-gitclone.cmake
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps && /usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E echo_append
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'assimp-populate'"
	/usr/bin/cmake -Dcfgdir= -P /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/tmp/assimp-populate-mkdirs.cmake
	/usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-mkdir

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch-info.txt
assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'assimp-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update:
.PHONY : assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-test: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E echo_append
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-build && /usr/bin/cmake -E touch /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-test

assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update: assimp-populate-prefix/tmp/assimp-populate-gitupdate.cmake
assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update-info.txt
assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'assimp-populate'"
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-src && /usr/bin/cmake -Dcan_fetch=YES -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/assimp-populate-prefix/tmp/assimp-populate-gitupdate.cmake

CMakeFiles/assimp-populate.dir/codegen:
.PHONY : CMakeFiles/assimp-populate.dir/codegen

assimp-populate: CMakeFiles/assimp-populate
assimp-populate: CMakeFiles/assimp-populate-complete
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-build
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-configure
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-download
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-install
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-mkdir
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-patch
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-test
assimp-populate: assimp-populate-prefix/src/assimp-populate-stamp/assimp-populate-update
assimp-populate: CMakeFiles/assimp-populate.dir/build.make
.PHONY : assimp-populate

# Rule to build all files generated by this target.
CMakeFiles/assimp-populate.dir/build: assimp-populate
.PHONY : CMakeFiles/assimp-populate.dir/build

CMakeFiles/assimp-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assimp-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assimp-populate.dir/clean

CMakeFiles/assimp-populate.dir/depend:
	cd /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild /home/teoblow/Программы/study/CG/lab6/src/_deps/assimp-subbuild/CMakeFiles/assimp-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/assimp-populate.dir/depend
