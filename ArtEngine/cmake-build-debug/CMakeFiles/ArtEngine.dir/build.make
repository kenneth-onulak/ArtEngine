# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Experimentation\ArtEngine\ArtEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\ArtEngine.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\ArtEngine.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\ArtEngine.dir\flags.make

CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.obj: ..\examples\voronoi\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ArtEngine.dir/examples/voronoi/main.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\examples\voronoi\main.cpp
<<

CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/examples/voronoi/main.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\examples\voronoi\main.cpp
<<

CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/examples/voronoi/main.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\examples\voronoi\main.cpp
<<

CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.obj: ..\include\ArtEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ArtEngine.dir/include/ArtEngine.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\ArtEngine.cpp
<<

CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/ArtEngine.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\ArtEngine.cpp
<<

CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/ArtEngine.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\ArtEngine.cpp
<<

CMakeFiles\ArtEngine.dir\include\view.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\view.cpp.obj: ..\include\view.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ArtEngine.dir/include/view.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\view.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\view.cpp
<<

CMakeFiles\ArtEngine.dir\include\view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/view.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\view.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\view.cpp
<<

CMakeFiles\ArtEngine.dir\include\view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/view.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\view.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\view.cpp
<<

CMakeFiles\ArtEngine.dir\include\event.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\event.cpp.obj: ..\include\event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ArtEngine.dir/include/event.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\event.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\event.cpp
<<

CMakeFiles\ArtEngine.dir\include\event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/event.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\event.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\event.cpp
<<

CMakeFiles\ArtEngine.dir\include\event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/event.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\event.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\event.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.obj: ..\include\helpers\camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/camera.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\camera.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/camera.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\camera.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/camera.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\camera.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.obj: ..\include\helpers\color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/color.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\color.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\color.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/color.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\color.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/color.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\color.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\color.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.obj: ..\include\helpers\object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/object.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\object.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\object.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/object.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\object.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/object.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\object.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\object.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.obj: ..\include\helpers\image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/image.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\image.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\image.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/image.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\image.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/image.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\image.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\image.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.obj: ..\include\helpers\log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/log.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\log.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\log.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/log.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\log.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/log.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\log.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\log.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.obj: ..\include\helpers\parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ArtEngine.dir/include/helpers/parse.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\parse.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/helpers/parse.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\helpers\parse.cpp
<<

CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/helpers/parse.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\helpers\parse.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.obj: ..\include\utility\buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/buffer.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\buffer.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/buffer.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\buffer.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/buffer.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\buffer.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\model.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\model.cpp.obj: ..\include\utility\model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/model.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\model.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\model.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/model.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\model.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\model.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/model.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\model.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\model.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.obj: ..\include\utility\instance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/instance.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\instance.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\instance.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/instance.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\instance.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/instance.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\instance.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\instance.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.obj: ..\include\utility\shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/shader.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\shader.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\shader.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/shader.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\shader.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/shader.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\shader.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\shader.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.obj: ..\include\utility\texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/texture.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\texture.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\texture.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/texture.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\texture.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/texture.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\texture.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\texture.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\target.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\utility\target.cpp.obj: ..\include\utility\target.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/ArtEngine.dir/include/utility/target.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\utility\target.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\utility\target.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\target.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/utility/target.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\utility\target.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\utility\target.cpp
<<

CMakeFiles\ArtEngine.dir\include\utility\target.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/utility/target.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\utility\target.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\utility\target.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.obj: ..\include\imgui\imgui_impl_sdl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_sdl.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_sdl.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_sdl.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_sdl.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_sdl.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_sdl.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.obj: CMakeFiles\ArtEngine.dir\flags.make
CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.obj: ..\include\imgui\imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_opengl3.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.obj /FdCMakeFiles\ArtEngine.dir\ /FS -c D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_opengl3.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_opengl3.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe > CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_opengl3.cpp
<<

CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtEngine.dir/include/imgui/imgui_impl_opengl3.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.s /c D:\Experimentation\ArtEngine\ArtEngine\include\imgui\imgui_impl_opengl3.cpp
<<

# Object files for target ArtEngine
ArtEngine_OBJECTS = \
"CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\view.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\event.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\model.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\utility\target.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.obj" \
"CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.obj"

# External object files for target ArtEngine
ArtEngine_EXTERNAL_OBJECTS =

ArtEngine.exe: CMakeFiles\ArtEngine.dir\examples\voronoi\main.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\ArtEngine.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\view.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\event.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\camera.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\color.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\object.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\image.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\log.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\helpers\parse.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\buffer.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\model.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\instance.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\shader.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\texture.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\utility\target.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_sdl.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\include\imgui\imgui_impl_opengl3.cpp.obj
ArtEngine.exe: CMakeFiles\ArtEngine.dir\build.make
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\freetyped.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\glew32d.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\manual-link\SDL2maind.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2_ttf.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2_image.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\boost_filesystem-vc140-mt-gd.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\imguid.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\freetyped.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2d.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\libpng16d.lib
ArtEngine.exe: C:\dev\vcpkg\installed\x64-windows\debug\lib\zlibd.lib
ArtEngine.exe: CMakeFiles\ArtEngine.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX executable ArtEngine.exe"
	"C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ArtEngine.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\ArtEngine.dir\objects1.rsp @<<
 /out:ArtEngine.exe /implib:ArtEngine.lib /pdb:D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\ArtEngine.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console  C:\dev\vcpkg\installed\x64-windows\debug\lib\freetyped.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\glew32d.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\manual-link\SDL2maind.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2_ttf.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2_image.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\boost_filesystem-vc140-mt-gd.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\imguid.lib opengl32.lib glu32.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\freetyped.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\SDL2d.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\libpng16d.lib C:\dev\vcpkg\installed\x64-windows\debug\lib\zlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	echo >nul && "C:\Program Files\PowerShell\7\pwsh.exe" -noprofile -executionpolicy Bypass -file C:/dev/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary D:/Experimentation/ArtEngine/ArtEngine/cmake-build-debug/ArtEngine.exe -installedDir C:/dev/vcpkg/installed/x64-windows/debug/bin -OutVariable out
	echo >nul && "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E copy_directory D:/Experimentation/ArtEngine/ArtEngine/examples/voronoi/shader/ D:/Experimentation/ArtEngine/ArtEngine/cmake-build-debug/shader/
	echo >nul && "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E copy D:/Experimentation/ArtEngine/ArtEngine/examples/voronoi/starry_night.png D:/Experimentation/ArtEngine/ArtEngine/cmake-build-debug/

# Rule to build all files generated by this target.
CMakeFiles\ArtEngine.dir\build: ArtEngine.exe
.PHONY : CMakeFiles\ArtEngine.dir\build

CMakeFiles\ArtEngine.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ArtEngine.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ArtEngine.dir\clean

CMakeFiles\ArtEngine.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Experimentation\ArtEngine\ArtEngine D:\Experimentation\ArtEngine\ArtEngine D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug D:\Experimentation\ArtEngine\ArtEngine\cmake-build-debug\CMakeFiles\ArtEngine.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\ArtEngine.dir\depend
