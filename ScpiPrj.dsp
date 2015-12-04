# Microsoft Developer Studio Project File - Name="ScpiPrj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ScpiPrj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScpiPrj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScpiPrj.mak" CFG="ScpiPrj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScpiPrj - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ScpiPrj - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScpiPrj - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ScpiPrj - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "ScpiLib/Inc" /I "User" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ScpiPrj - Win32 Release"
# Name "ScpiPrj - Win32 Debug"
# Begin Group "ScpiLib"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ScpiInc"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=.\ScpiLib\Inc\config.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\constants.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\debug.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\error.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\fifo.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\ieee488.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\minimal.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\parser.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\scpi.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\snprintf.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\types.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\units.h
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Inc\utils.h
# End Source File
# End Group
# Begin Group "ScpiSrc"

# PROP Default_Filter "c;cpp"
# Begin Source File

SOURCE=.\ScpiLib\Src\debug.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\error.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\fifo.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\ieee488.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\minimal.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\parser.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\snprintf.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\units.c
# End Source File
# Begin Source File

SOURCE=.\ScpiLib\Src\utils.c
# End Source File
# End Group
# End Group
# Begin Group "User"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "UserInc"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\User\datatype.h
# End Source File
# Begin Source File

SOURCE=".\User\scpi-interface.h"
# End Source File
# End Group
# Begin Group "UserSrc"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=".\User\scip-def.c"
# End Source File
# Begin Source File

SOURCE=.\User\ScpiTest.c
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
