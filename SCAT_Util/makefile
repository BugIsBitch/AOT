# Microsoft Developer Studio Generated NMAKE File, Based on SCAT_Util.dsp
!IF "$(CFG)" == ""
CFG=SCAT_Util - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SCAT_Util - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SCAT_Util - Win32 Release" && "$(CFG)" != "SCAT_Util - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SCAT_Util.mak" CFG="SCAT_Util - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SCAT_Util - Win32 Release" (based on "Win32 (x64) Console Application")
!MESSAGE "SCAT_Util - Win32 Debug" (based on "Win32 (x64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SCAT_Util - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
OUTBIN=..\bin\release
LIBDIR= ..\lib
DEF_FILE= .\scat_comm_util.def
INCPATH = ..\..\CADNS-SW-SCAT-2021-SRC
# 开始自定义宏
ProjectName=SCAT_Util
TargetName=SCAT_Util
# 结束自定义宏

ALL : "$(OUTBIN)\$(TargetName).dll"


CLEAN :
	-@erase "$(INTDIR)\scat_comm_util.obj"
    -@erase "$(OUTDIR)\$(ProjectName).pdb"
	-@erase "$(OUTBIN)\$(ProjectName).dll"
	-@erase "$(OUTBIN)\$(ProjectName).ilk"
	-@erase "$(LIBDIR)\$(TargetName).exp"
	-@erase "$(LIBDIR)\$(TargetName).lib"
"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
CPP=cl.exe
CPP_PROJ= /nologo /MDd /W3 /Oy- /WX- /Od /I "$(INCPATH)" /GS /Gy /fp:precise /Zc:wchar_t  /D "WIN32" /D "_WINDLL" /D "NDEBUG"  /D "_CONSOLE" /D "UNICODE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE"  /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gd  /c

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS= /INCREMENTAL:NO /nologo /DEF:"$(DEF_FILE)" /pdb:"$(OUTDIR)\$(ProjectName).pdb" /debug /machine:x64 /out:"$(OUTBIN)\$(ProjectName).dll" /TLBID:1 /DYNAMICBASE /NXCOMPAT /implib:"$(LIBDIR)\$(TargetName).lib"
LINK32_OBJS= \
	"$(INTDIR)\scat_comm_util.obj" \
	

"$(OUTBIN)\$(ProjectName).dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SCAT_Util - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OUTBIN=..\bin\debug
LIBDIR=..\lib
DEF_FILE= .\scat_comm_util.def
ProjectName=SCAT_Util
TargetName=SCAT_Util
INCPATH = ..\..\CADNS-SW-SCAT-2021-SRC
# 结束自定义宏

ALL : "$(OUTBIN)\SCAT_Util.dll"


CLEAN :
	-@erase "$(INTDIR)\scat_comm_util.obj"
    -@erase "$(OUTDIR)\$(ProjectName).pdb"
	-@erase "$(OUTBIN)\$(ProjectName).dll"
	-@erase "$(OUTBIN)\$(ProjectName).ilk"
	-@erase "$(LIBDIR)\$(TargetName).exp"
	-@erase "$(LIBDIR)\$(TargetName).lib"
"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=  /nologo /MDd /W3 /Oy- /WX- /Od /I "$(INCPATH)" /GS  /fp:precise /Zc:wchar_t  /D "WIN32" /D "_WINDLL" /D "_DEBUG"  /D "_CONSOLE" /D "UNICODE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gd /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


RSC=rc.exe
BSC32=bscmake.exe 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=  /INCREMENTAL:NO  /nologo /DEF:"$(DEF_FILE)" /pdb:"$(OUTDIR)\$(ProjectName).pdb" /debug /machine:x64  /out:"$(OUTBIN)\$(ProjectName).dll" /TLBID:1 /DYNAMICBASE /NXCOMPAT /implib:"$(LIBDIR)\$(TargetName).lib" 
LINK32_OBJS= \
	"$(INTDIR)\scat_comm_util.obj" 

"$(OUTBIN)\$(ProjectName).dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 



!IF "$(CFG)" == "SCAT_Util - Win32 Release" || "$(CFG)" == "SCAT_Util - Win32 Debug"
SOURCE=  scat_comm_util.c scat_comm_util.h scat_comm_defs.h

"$(INTDIR)\scat_comm_util.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

