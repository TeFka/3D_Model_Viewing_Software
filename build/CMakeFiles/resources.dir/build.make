# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19\build

# Utility rule file for resources.

# Include the progress variables for this target.
include CMakeFiles/resources.dir/progress.make

CMakeFiles/resources: resources.rcc


resources.rcc: ../GUI_source/images/openIcon.png
resources.rcc: ../GUI_source/images/saveIcon.png
resources.rcc: ../GUI_source/images/newIcon.png
resources.rcc: ../GUI_source/images/helpIcon.png
resources.rcc: GUI_source/images/resource.qrc.depends
resources.rcc: ../GUI_source/images/resource.qrc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating resources.rcc"
	C:\Qt\5.15.1\mingw81_64\bin\rcc.exe -no-compress --binary --name resources --output D:/danka/University/Year_2/Practical_engineering_design/Computing_project/2020_GROUP_19/build/resources.rcc D:/danka/University/Year_2/Practical_engineering_design/Computing_project/2020_GROUP_19/GUI_source/images/resource.qrc

resources: CMakeFiles/resources
resources: resources.rcc
resources: CMakeFiles/resources.dir/build.make

.PHONY : resources

# Rule to build all files generated by this target.
CMakeFiles/resources.dir/build: resources

.PHONY : CMakeFiles/resources.dir/build

CMakeFiles/resources.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\resources.dir\cmake_clean.cmake
.PHONY : CMakeFiles/resources.dir/clean

CMakeFiles/resources.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19 D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19 D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19\build D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19\build D:\danka\University\Year_2\Practical_engineering_design\Computing_project\2020_GROUP_19\build\CMakeFiles\resources.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/resources.dir/depend

