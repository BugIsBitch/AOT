# Microsoft Developer Studio Generated NMAKE File, Based on XMLParser.dsp
!IF "$(CFG)" == ""
CFG=XMLParser - Win32 Debug
!MESSAGE No configuration specified. Defaulting to XMLParser - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "XMLParser - Win32 Release" && "$(CFG)" != "XMLParser - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMLParser.mak" CFG="XMLParser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLParser - Win32 Release" (based on "Win32 (x64) Console Application")
!MESSAGE "XMLParser - Win32 Debug" (based on "Win32 (x64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "XMLParser - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
OUTBIN=..\..\bin\release
LIBDIR= ..\..\lib
DEF_FILE= .\xml_parser.def
INCPATH = ..\..\..\CADNS-SW-SCAT-2021-SRC
# 开始自定义宏
ProjectName=XMLParser
TargetName=XMLParser
# 结束自定义宏

ALL : "$(OUTBIN)\$(TargetName).dll"


CLEAN :
	-@erase "$(INTDIR)\xml.obj"
	-@erase "$(INTDIR)\xml_global.obj"
	-@erase "$(INTDIR)\xml_internal.obj"
	-@erase "$(INTDIR)\xml_stack.obj"
	-@erase "$(INTDIR)\xml_parse_engine.obj"
    -@erase "$(OUTDIR)\$(ProjectName).pdb"
	-@erase "$(OUTBIN)\$(ProjectName).dll"
	-@erase "$(OUTBIN)\$(ProjectName).ilk"
	-@erase "$(LIBDIR)\$(TargetName).exp"
	-@erase "$(LIBDIR)\$(TargetName).lib"
"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
CPP=cl.exe
CPP_PROJ=  /nologo /MDd /W3 /Oy- /WX- /Od /I "$(INCPATH)" /GS /Gy /fp:precise /Zc:wchar_t  /D "WIN32" /D "_WINDLL" /D "NDEBUG" /D "_CONSOLE" /D "UNICODE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE"  /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD  /c  

{..\src}.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS= /dll "$(LIBDIR)\GenCRC32.lib" /INCREMENTAL:NO /SUBSYSTEM:CONSOLE /nologo /DEF:"$(DEF_FILE)" /pdb:"$(OUTDIR)\$(ProjectName).pdb" /debug /machine:x64 /out:"$(OUTBIN)\$(ProjectName).dll" /TLBID:1 /DYNAMICBASE /NXCOMPAT /implib:"$(LIBDIR)\$(TargetName).lib"
LINK32_OBJS= \
	"$(INTDIR)\xml_global.obj" \
	"$(INTDIR)\xml_stack.obj"\
	"$(INTDIR)\xml_internal.obj" \
	"$(INTDIR)\xml_parse_engine.obj"\
	"$(INTDIR)\xml.obj"
	

"$(OUTBIN)\$(ProjectName).dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "XMLParser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OUTBIN=..\..\bin\debug
LIBDIR=..\..\lib
DEF_FILE= .\xml_parser.def
ProjectName=XMLParser
TargetName=XMLParser
INCPATH = ..\..\..\CADNS-SW-SCAT-2021-SRC
# 结束自定义宏

ALL : "$(OUTBIN)\XMLParser.dll"


CLEAN :
	-@erase "$(INTDIR)\xml.obj"
	-@erase "$(INTDIR)\xml_global.obj"
	-@erase "$(INTDIR)\xml_internal.obj"
	-@erase "$(INTDIR)\xml_stack.obj"
	-@erase "$(INTDIR)\xml_parse_engine.obj"
    -@erase "$(OUTDIR)\$(ProjectName).pdb"
	-@erase "$(OUTBIN)\$(ProjectName).dll"
	-@erase "$(OUTBIN)\$(ProjectName).ilk"
	-@erase "$(LIBDIR)\$(TargetName).exp"
	-@erase "$(LIBDIR)\$(TargetName).lib"
"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=  /nologo /MDd /W3 /Oy- /WX- /Od /I "$(INCPATH)" /GS /Gy /fp:precise /Zc:wchar_t  /D "WIN32" /D "_WINDLL" /D "_DEBUG" /D "_CONSOLE" /D "UNICODE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE"  /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD  /c 

{..\src}.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


RSC=rc.exe
BSC32=bscmake.exe 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=  /dll "$(LIBDIR)\GenCRC32.lib" /INCREMENTAL:NO /SUBSYSTEM:CONSOLE /nologo /DEF:"$(DEF_FILE)" /pdb:"$(OUTDIR)\$(ProjectName).pdb" /debug /machine:x64  /out:"$(OUTBIN)\$(ProjectName).dll" /TLBID:1 /DYNAMICBASE /NXCOMPAT /implib:"$(LIBDIR)\$(TargetName).lib" 
LINK32_OBJS= \
	"$(INTDIR)\xml_global.obj" \
	"$(INTDIR)\xml_stack.obj"\
	"$(INTDIR)\xml_internal.obj" \
	"$(INTDIR)\xml_parse_engine.obj"\
	"$(INTDIR)\xml.obj"

"$(OUTBIN)\$(ProjectName).dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 



!IF "$(CFG)" == "XMLParser - Win32 Release" || "$(CFG)" == "XMLParser - Win32 Debug"
SOURCE=  ../src/xml_global.c ../include/xml_global.h 

"$(INTDIR)\xml_global.obj" : $(SOURCE) "$(INTDIR)"


SOURCE= ../include/xml_stack.h ../src/xml_stack.c 

"$(INTDIR)\xml_stack.obj" : $(SOURCE) "$(INTDIR)"



SOURCE=../include/xml_internal.h ../src/xml_internal.c 
        

"$(INTDIR)\xml_internal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=../include/xml_parse_engine.h ../src/xml_parse_engine.c 

"$(INTDIR)\xml_parse_engine.obj" : $(SOURCE) "$(INTDIR)"


SOURCE= ../include/xml.h ../src/xml.c 

"$(INTDIR)\xml.obj" : $(SOURCE) "$(INTDIR)"




!ENDIF 

