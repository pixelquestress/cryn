# Microsoft Developer Studio Project File - Name="RPGMap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RPGMap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RPGMap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RPGMap.mak" CFG="RPGMap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RPGMap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RPGMap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RPGMap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib cdx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib cdx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bass.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Cryn The Dark Reflection.exe"

!ELSEIF  "$(CFG)" == "RPGMap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib cdxd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dsound.lib dxguid.lib dinput.lib winmm.lib cdxd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bass.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RPGMap - Win32 Release"
# Name "RPGMap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Bat.cpp
# End Source File
# Begin Source File

SOURCE=.\BattleEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\BlackRainDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\Branch.cpp
# End Source File
# Begin Source File

SOURCE=.\Cdxmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Character.cpp
# End Source File
# Begin Source File

SOURCE=.\Cloud.cpp
# End Source File
# Begin Source File

SOURCE=.\FadeTile.cpp
# End Source File
# Begin Source File

SOURCE=.\FallingLeaf.cpp
# End Source File
# Begin Source File

SOURCE=.\FireDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\Gnat.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\MistSpot.cpp
# End Source File
# Begin Source File

SOURCE=.\NPC.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\RainDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\RPGMap.cpp
# End Source File
# Begin Source File

SOURCE=.\RPGMap.rc
# End Source File
# Begin Source File

SOURCE=.\SnowFlake.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitTimer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Bat.h
# End Source File
# Begin Source File

SOURCE=.\BattleEngine.h
# End Source File
# Begin Source File

SOURCE=.\BlackRainDrop.h
# End Source File
# Begin Source File

SOURCE=.\Branch.h
# End Source File
# Begin Source File

SOURCE=.\Cdxmenu.h
# End Source File
# Begin Source File

SOURCE=.\Character.h
# End Source File
# Begin Source File

SOURCE=.\Cloud.h
# End Source File
# Begin Source File

SOURCE=.\FadeTile.h
# End Source File
# Begin Source File

SOURCE=.\FallingLeaf.h
# End Source File
# Begin Source File

SOURCE=.\FireDrop.h
# End Source File
# Begin Source File

SOURCE=.\Gnat.h
# End Source File
# Begin Source File

SOURCE=.\InfoBox.h
# End Source File
# Begin Source File

SOURCE=.\Menu.h
# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\MistSpot.h
# End Source File
# Begin Source File

SOURCE=.\NPC.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\RainDrop.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SnowFlake.h
# End Source File
# Begin Source File

SOURCE=.\WaitTimer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RPGMap.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project