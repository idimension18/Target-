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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\idime\OneDrive\Bureau\Target++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Target__.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\Target__.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Target__.dir\flags.make

CMakeFiles\Target__.dir\src\main.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\main.cpp.obj: ..\src\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Target__.dir/src/main.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\main.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\main.cpp
<<

CMakeFiles\Target__.dir\src\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\main.cpp
<<

CMakeFiles\Target__.dir\src\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\main.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\main.cpp
<<

CMakeFiles\Target__.dir\src\Ship.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\Ship.cpp.obj: ..\src\Ship.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Target__.dir/src/Ship.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\Ship.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\Ship.cpp
<<

CMakeFiles\Target__.dir\src\Ship.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/Ship.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\Ship.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\Ship.cpp
<<

CMakeFiles\Target__.dir\src\Ship.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/Ship.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\Ship.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\Ship.cpp
<<

CMakeFiles\Target__.dir\src\Laser.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\Laser.cpp.obj: ..\src\Laser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Target__.dir/src/Laser.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\Laser.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\Laser.cpp
<<

CMakeFiles\Target__.dir\src\Laser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/Laser.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\Laser.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\Laser.cpp
<<

CMakeFiles\Target__.dir\src\Laser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/Laser.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\Laser.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\Laser.cpp
<<

CMakeFiles\Target__.dir\src\Target.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\Target.cpp.obj: ..\src\Target.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Target__.dir/src/Target.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\Target.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\Target.cpp
<<

CMakeFiles\Target__.dir\src\Target.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/Target.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\Target.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\Target.cpp
<<

CMakeFiles\Target__.dir\src\Target.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/Target.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\Target.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\Target.cpp
<<

CMakeFiles\Target__.dir\src\Asteroide.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\Asteroide.cpp.obj: ..\src\Asteroide.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Target__.dir/src/Asteroide.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\Asteroide.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\Asteroide.cpp
<<

CMakeFiles\Target__.dir\src\Asteroide.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/Asteroide.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\Asteroide.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\Asteroide.cpp
<<

CMakeFiles\Target__.dir\src\Asteroide.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/Asteroide.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\Asteroide.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\Asteroide.cpp
<<

CMakeFiles\Target__.dir\src\Sprite.cpp.obj: CMakeFiles\Target__.dir\flags.make
CMakeFiles\Target__.dir\src\Sprite.cpp.obj: ..\src\Sprite.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Target__.dir/src/Sprite.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Target__.dir\src\Sprite.cpp.obj /FdCMakeFiles\Target__.dir\ /FS -c C:\Users\idime\OneDrive\Bureau\Target++\src\Sprite.cpp
<<

CMakeFiles\Target__.dir\src\Sprite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Target__.dir/src/Sprite.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Target__.dir\src\Sprite.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\idime\OneDrive\Bureau\Target++\src\Sprite.cpp
<<

CMakeFiles\Target__.dir\src\Sprite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Target__.dir/src/Sprite.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Target__.dir\src\Sprite.cpp.s /c C:\Users\idime\OneDrive\Bureau\Target++\src\Sprite.cpp
<<

# Object files for target Target__
Target___OBJECTS = \
"CMakeFiles\Target__.dir\src\main.cpp.obj" \
"CMakeFiles\Target__.dir\src\Ship.cpp.obj" \
"CMakeFiles\Target__.dir\src\Laser.cpp.obj" \
"CMakeFiles\Target__.dir\src\Target.cpp.obj" \
"CMakeFiles\Target__.dir\src\Asteroide.cpp.obj" \
"CMakeFiles\Target__.dir\src\Sprite.cpp.obj"

# External object files for target Target__
Target___EXTERNAL_OBJECTS =

Target__.exe: CMakeFiles\Target__.dir\src\main.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\src\Ship.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\src\Laser.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\src\Target.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\src\Asteroide.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\src\Sprite.cpp.obj
Target__.exe: CMakeFiles\Target__.dir\build.make
Target__.exe: CMakeFiles\Target__.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Target__.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Target__.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Target__.dir\objects1.rsp @<<
 /out:Target__.exe /implib:Target__.lib /pdb:C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\Target__.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\idime\OneDrive\Bureau\Target++\SDL2\lib\x86  SDL2main.lib SDL2.lib SDL2_mixer.lib SDL2_image.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Target__.dir\build: Target__.exe
.PHONY : CMakeFiles\Target__.dir\build

CMakeFiles\Target__.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Target__.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Target__.dir\clean

CMakeFiles\Target__.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\idime\OneDrive\Bureau\Target++ C:\Users\idime\OneDrive\Bureau\Target++ C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug C:\Users\idime\OneDrive\Bureau\Target++\cmake-build-debug\CMakeFiles\Target__.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Target__.dir\depend

