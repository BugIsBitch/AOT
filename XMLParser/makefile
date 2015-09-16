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
!MESSAGE "XMLParser - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "XMLParser - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\XMLParser.exe"


CLEAN :
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\main_test.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xml.obj"
	-@erase "$(INTDIR)\xml_internal.obj"
	-@erase "$(INTDIR)\xml_parse_engine.obj"
	-@erase "$(INTDIR)\xml_stack.obj"
	-@erase "$(OUTDIR)\XMLParser.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\XMLParser.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLParser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\XMLParser.pdb" /machine:I386 /out:"$(OUTDIR)\XMLParser.exe" 
LINK32_OBJS= \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\main_test.obj" \
	"$(INTDIR)\xml.obj" \
	"$(INTDIR)\xml_internal.obj" \
	"$(INTDIR)\xml_parse_engine.obj" \
	"$(INTDIR)\xml_stack.obj"

"$(OUTDIR)\XMLParser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "XMLParser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\XMLParser.exe"


CLEAN :
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\main_test.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xml.obj"
	-@erase "$(INTDIR)\xml_internal.obj"
	-@erase "$(INTDIR)\xml_parse_engine.obj"
	-@erase "$(INTDIR)\xml_stack.obj"
	-@erase "$(OUTDIR)\XMLParser.exe"
	-@erase "$(OUTDIR)\XMLParser.ilk"
	-@erase "$(OUTDIR)\XMLParser.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\XMLParser.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLParser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\XMLParser.pdb" /debug /machine:I386 /out:"$(OUTDIR)\XMLParser.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\main_test.obj" \
	"$(INTDIR)\xml.obj" \
	"$(INTDIR)\xml_internal.obj" \
	"$(INTDIR)\xml_parse_engine.obj" \
	"$(INTDIR)\xml_stack.obj"

"$(OUTDIR)\XMLParser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("XMLParser.dep")
!INCLUDE "XMLParser.dep"
!ELSE 
!MESSAGE Warning: cannot find "XMLParser.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "XMLParser - Win32 Release" || "$(CFG)" == "XMLParser - Win32 Debug"
SOURCE=.\global.c

"$(INTDIR)\global.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main_test.c

"$(INTDIR)\main_test.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xml.c

"$(INTDIR)\xml.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xml_internal.c

"$(INTDIR)\xml_internal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xml_parse_engine.c

"$(INTDIR)\xml_parse_engine.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\xml_stack.c

"$(INTDIR)\xml_stack.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

