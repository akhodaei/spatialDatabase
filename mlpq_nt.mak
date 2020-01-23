# Microsoft Developer Studio Generated NMAKE File, Based on mlpq_nt.dsp
!IF "$(CFG)" == ""
CFG=idb - Win32 Debug
!MESSAGE No configuration specified. Defaulting to idb - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "idb - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mlpq_nt.mak" CFG="idb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "idb - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mlpq_nt.exe" "$(OUTDIR)\mlpq_nt.pch" "$(OUTDIR)\mlpq_nt.bsc"


CLEAN :
	-@erase "$(INTDIR)\arg.obj"
	-@erase "$(INTDIR)\arg.sbr"
	-@erase "$(INTDIR)\BasicSQL.obj"
	-@erase "$(INTDIR)\BasicSQL.sbr"
	-@erase "$(INTDIR)\basicsqldialogbox.obj"
	-@erase "$(INTDIR)\basicsqldialogbox.sbr"
	-@erase "$(INTDIR)\BitmapFile.obj"
	-@erase "$(INTDIR)\BitmapFile.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\construct.obj"
	-@erase "$(INTDIR)\construct.sbr"
	-@erase "$(INTDIR)\csa_debug.obj"
	-@erase "$(INTDIR)\csa_debug.sbr"
	-@erase "$(INTDIR)\csa_q_main.obj"
	-@erase "$(INTDIR)\csa_q_main.sbr"
	-@erase "$(INTDIR)\csa_stack.obj"
	-@erase "$(INTDIR)\csa_stack.sbr"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\db.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\DlgApproximation.obj"
	-@erase "$(INTDIR)\DlgApproximation.sbr"
	-@erase "$(INTDIR)\DlgArea.obj"
	-@erase "$(INTDIR)\DlgArea.sbr"
	-@erase "$(INTDIR)\DlgArea2.obj"
	-@erase "$(INTDIR)\DlgArea2.sbr"
	-@erase "$(INTDIR)\DlgBlock.obj"
	-@erase "$(INTDIR)\DlgBlock.sbr"
	-@erase "$(INTDIR)\DlgBuffer.obj"
	-@erase "$(INTDIR)\DlgBuffer.sbr"
	-@erase "$(INTDIR)\DlgColor.obj"
	-@erase "$(INTDIR)\DlgColor.sbr"
	-@erase "$(INTDIR)\DlgExpo.obj"
	-@erase "$(INTDIR)\DlgExpo.sbr"
	-@erase "$(INTDIR)\DlgExport.obj"
	-@erase "$(INTDIR)\DlgExport.sbr"
	-@erase "$(INTDIR)\DlgGenN.obj"
	-@erase "$(INTDIR)\DlgGenN.sbr"
	-@erase "$(INTDIR)\DlgInput.obj"
	-@erase "$(INTDIR)\DlgInput.sbr"
	-@erase "$(INTDIR)\DlgInsR.obj"
	-@erase "$(INTDIR)\DlgInsR.sbr"
	-@erase "$(INTDIR)\DlgMaxMin.obj"
	-@erase "$(INTDIR)\DlgMaxMin.sbr"
	-@erase "$(INTDIR)\DlgName.obj"
	-@erase "$(INTDIR)\DlgName.sbr"
	-@erase "$(INTDIR)\DlgNtime.obj"
	-@erase "$(INTDIR)\DlgNtime.sbr"
	-@erase "$(INTDIR)\DlgProp.obj"
	-@erase "$(INTDIR)\DlgProp.sbr"
	-@erase "$(INTDIR)\DlgRange.obj"
	-@erase "$(INTDIR)\DlgRange.sbr"
	-@erase "$(INTDIR)\DlgRelName.obj"
	-@erase "$(INTDIR)\DlgRelName.sbr"
	-@erase "$(INTDIR)\dlist.obj"
	-@erase "$(INTDIR)\dlist.sbr"
	-@erase "$(INTDIR)\engine.obj"
	-@erase "$(INTDIR)\engine.sbr"
	-@erase "$(INTDIR)\ex29aView.obj"
	-@erase "$(INTDIR)\ex29aView.sbr"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\globals.sbr"
	-@erase "$(INTDIR)\GraphView.obj"
	-@erase "$(INTDIR)\GraphView.sbr"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\hash.sbr"
	-@erase "$(INTDIR)\hulconvt.obj"
	-@erase "$(INTDIR)\hulconvt.sbr"
	-@erase "$(INTDIR)\hulreconvt.obj"
	-@erase "$(INTDIR)\hulreconvt.sbr"
	-@erase "$(INTDIR)\idb.obj"
	-@erase "$(INTDIR)\idb.res"
	-@erase "$(INTDIR)\idb.sbr"
	-@erase "$(INTDIR)\idbDoc.obj"
	-@erase "$(INTDIR)\idbDoc.sbr"
	-@erase "$(INTDIR)\idbView.obj"
	-@erase "$(INTDIR)\idbView.sbr"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\list.sbr"
	-@erase "$(INTDIR)\LP.OBJ"
	-@erase "$(INTDIR)\LP.SBR"
	-@erase "$(INTDIR)\lp_solve.obj"
	-@erase "$(INTDIR)\lp_solve.sbr"
	-@erase "$(INTDIR)\lpkit.obj"
	-@erase "$(INTDIR)\lpkit.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MatrixView.obj"
	-@erase "$(INTDIR)\MatrixView.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\mlpq_nt.pch"
	-@erase "$(INTDIR)\monotone.obj"
	-@erase "$(INTDIR)\monotone.sbr"
	-@erase "$(INTDIR)\myparse.obj"
	-@erase "$(INTDIR)\myparse.sbr"
	-@erase "$(INTDIR)\NewSocket.obj"
	-@erase "$(INTDIR)\NewSocket.sbr"
	-@erase "$(INTDIR)\OnNestedSql.obj"
	-@erase "$(INTDIR)\OnNestedSql.sbr"
	-@erase "$(INTDIR)\OnsetReg.obj"
	-@erase "$(INTDIR)\OnsetReg.sbr"
	-@erase "$(INTDIR)\OwnListBox.obj"
	-@erase "$(INTDIR)\OwnListBox.sbr"
	-@erase "$(INTDIR)\parse.obj"
	-@erase "$(INTDIR)\parse.sbr"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\parser.sbr"
	-@erase "$(INTDIR)\PointView.obj"
	-@erase "$(INTDIR)\PointView.sbr"
	-@erase "$(INTDIR)\read.obj"
	-@erase "$(INTDIR)\read.sbr"
	-@erase "$(INTDIR)\readmps.obj"
	-@erase "$(INTDIR)\readmps.sbr"
	-@erase "$(INTDIR)\refine.obj"
	-@erase "$(INTDIR)\refine.sbr"
	-@erase "$(INTDIR)\relation.obj"
	-@erase "$(INTDIR)\relation.sbr"
	-@erase "$(INTDIR)\Render.obj"
	-@erase "$(INTDIR)\Render.sbr"
	-@erase "$(INTDIR)\RowView.obj"
	-@erase "$(INTDIR)\RowView.sbr"
	-@erase "$(INTDIR)\scanner.obj"
	-@erase "$(INTDIR)\scanner.sbr"
	-@erase "$(INTDIR)\SCDrawobj.obj"
	-@erase "$(INTDIR)\SCDrawobj.sbr"
	-@erase "$(INTDIR)\SCDrawtool.obj"
	-@erase "$(INTDIR)\SCDrawtool.sbr"
	-@erase "$(INTDIR)\ServerSocket.obj"
	-@erase "$(INTDIR)\ServerSocket.sbr"
	-@erase "$(INTDIR)\simplexlcs.obj"
	-@erase "$(INTDIR)\simplexlcs.sbr"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\slist.sbr"
	-@erase "$(INTDIR)\solve.obj"
	-@erase "$(INTDIR)\solve.sbr"
	-@erase "$(INTDIR)\SqlAggregation.obj"
	-@erase "$(INTDIR)\SqlAggregation.sbr"
	-@erase "$(INTDIR)\SqlDialogBox.obj"
	-@erase "$(INTDIR)\SqlDialogBox.sbr"
	-@erase "$(INTDIR)\SqlSets.obj"
	-@erase "$(INTDIR)\SqlSets.sbr"
	-@erase "$(INTDIR)\stack.obj"
	-@erase "$(INTDIR)\stack.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\string.sbr"
	-@erase "$(INTDIR)\TableSel.obj"
	-@erase "$(INTDIR)\TableSel.sbr"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\timer.sbr"
	-@erase "$(INTDIR)\tri.obj"
	-@erase "$(INTDIR)\tri.sbr"
	-@erase "$(INTDIR)\update_epsilon.obj"
	-@erase "$(INTDIR)\update_epsilon.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mlpq_nt.bsc"
	-@erase "$(OUTDIR)\mlpq_nt.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mlpq_nt.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\arg.sbr" \
	"$(INTDIR)\BasicSQL.sbr" \
	"$(INTDIR)\basicsqldialogbox.sbr" \
	"$(INTDIR)\BitmapFile.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\construct.sbr" \
	"$(INTDIR)\csa_debug.sbr" \
	"$(INTDIR)\csa_q_main.sbr" \
	"$(INTDIR)\csa_stack.sbr" \
	"$(INTDIR)\db.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\DlgArea.sbr" \
	"$(INTDIR)\DlgArea2.sbr" \
	"$(INTDIR)\DlgBlock.sbr" \
	"$(INTDIR)\DlgBuffer.sbr" \
	"$(INTDIR)\DlgColor.sbr" \
	"$(INTDIR)\DlgExpo.sbr" \
	"$(INTDIR)\DlgExport.sbr" \
	"$(INTDIR)\DlgGenN.sbr" \
	"$(INTDIR)\DlgInput.sbr" \
	"$(INTDIR)\DlgInsR.sbr" \
	"$(INTDIR)\DlgMaxMin.sbr" \
	"$(INTDIR)\DlgName.sbr" \
	"$(INTDIR)\DlgNtime.sbr" \
	"$(INTDIR)\DlgProp.sbr" \
	"$(INTDIR)\DlgRange.sbr" \
	"$(INTDIR)\DlgRelName.sbr" \
	"$(INTDIR)\dlist.sbr" \
	"$(INTDIR)\engine.sbr" \
	"$(INTDIR)\ex29aView.sbr" \
	"$(INTDIR)\globals.sbr" \
	"$(INTDIR)\GraphView.sbr" \
	"$(INTDIR)\hash.sbr" \
	"$(INTDIR)\hulconvt.sbr" \
	"$(INTDIR)\hulreconvt.sbr" \
	"$(INTDIR)\idb.sbr" \
	"$(INTDIR)\idbDoc.sbr" \
	"$(INTDIR)\idbView.sbr" \
	"$(INTDIR)\list.sbr" \
	"$(INTDIR)\LP.SBR" \
	"$(INTDIR)\lp_solve.sbr" \
	"$(INTDIR)\lpkit.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MatrixView.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\monotone.sbr" \
	"$(INTDIR)\myparse.sbr" \
	"$(INTDIR)\NewSocket.sbr" \
	"$(INTDIR)\OnNestedSql.sbr" \
	"$(INTDIR)\OnsetReg.sbr" \
	"$(INTDIR)\OwnListBox.sbr" \
	"$(INTDIR)\parse.sbr" \
	"$(INTDIR)\parser.sbr" \
	"$(INTDIR)\PointView.sbr" \
	"$(INTDIR)\read.sbr" \
	"$(INTDIR)\readmps.sbr" \
	"$(INTDIR)\refine.sbr" \
	"$(INTDIR)\relation.sbr" \
	"$(INTDIR)\Render.sbr" \
	"$(INTDIR)\RowView.sbr" \
	"$(INTDIR)\scanner.sbr" \
	"$(INTDIR)\SCDrawobj.sbr" \
	"$(INTDIR)\SCDrawtool.sbr" \
	"$(INTDIR)\ServerSocket.sbr" \
	"$(INTDIR)\simplexlcs.sbr" \
	"$(INTDIR)\slist.sbr" \
	"$(INTDIR)\solve.sbr" \
	"$(INTDIR)\SqlAggregation.sbr" \
	"$(INTDIR)\SqlDialogBox.sbr" \
	"$(INTDIR)\SqlSets.sbr" \
	"$(INTDIR)\stack.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\string.sbr" \
	"$(INTDIR)\TableSel.sbr" \
	"$(INTDIR)\timer.sbr" \
	"$(INTDIR)\tri.sbr" \
	"$(INTDIR)\update_epsilon.sbr" \
	"$(INTDIR)\DlgApproximation.sbr"

"$(OUTDIR)\mlpq_nt.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /profile /debug /machine:I386 /out:"$(OUTDIR)\mlpq_nt.exe" 
LINK32_OBJS= \
	"$(INTDIR)\arg.obj" \
	"$(INTDIR)\BasicSQL.obj" \
	"$(INTDIR)\basicsqldialogbox.obj" \
	"$(INTDIR)\BitmapFile.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\construct.obj" \
	"$(INTDIR)\csa_debug.obj" \
	"$(INTDIR)\csa_q_main.obj" \
	"$(INTDIR)\csa_stack.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\DlgArea.obj" \
	"$(INTDIR)\DlgArea2.obj" \
	"$(INTDIR)\DlgBlock.obj" \
	"$(INTDIR)\DlgBuffer.obj" \
	"$(INTDIR)\DlgColor.obj" \
	"$(INTDIR)\DlgExpo.obj" \
	"$(INTDIR)\DlgExport.obj" \
	"$(INTDIR)\DlgGenN.obj" \
	"$(INTDIR)\DlgInput.obj" \
	"$(INTDIR)\DlgInsR.obj" \
	"$(INTDIR)\DlgMaxMin.obj" \
	"$(INTDIR)\DlgName.obj" \
	"$(INTDIR)\DlgNtime.obj" \
	"$(INTDIR)\DlgProp.obj" \
	"$(INTDIR)\DlgRange.obj" \
	"$(INTDIR)\DlgRelName.obj" \
	"$(INTDIR)\dlist.obj" \
	"$(INTDIR)\engine.obj" \
	"$(INTDIR)\ex29aView.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\GraphView.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\hulconvt.obj" \
	"$(INTDIR)\hulreconvt.obj" \
	"$(INTDIR)\idb.obj" \
	"$(INTDIR)\idbDoc.obj" \
	"$(INTDIR)\idbView.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\LP.OBJ" \
	"$(INTDIR)\lp_solve.obj" \
	"$(INTDIR)\lpkit.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MatrixView.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\monotone.obj" \
	"$(INTDIR)\myparse.obj" \
	"$(INTDIR)\NewSocket.obj" \
	"$(INTDIR)\OnNestedSql.obj" \
	"$(INTDIR)\OnsetReg.obj" \
	"$(INTDIR)\OwnListBox.obj" \
	"$(INTDIR)\parse.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\PointView.obj" \
	"$(INTDIR)\read.obj" \
	"$(INTDIR)\readmps.obj" \
	"$(INTDIR)\refine.obj" \
	"$(INTDIR)\relation.obj" \
	"$(INTDIR)\Render.obj" \
	"$(INTDIR)\RowView.obj" \
	"$(INTDIR)\scanner.obj" \
	"$(INTDIR)\SCDrawobj.obj" \
	"$(INTDIR)\SCDrawtool.obj" \
	"$(INTDIR)\ServerSocket.obj" \
	"$(INTDIR)\simplexlcs.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\solve.obj" \
	"$(INTDIR)\SqlAggregation.obj" \
	"$(INTDIR)\SqlDialogBox.obj" \
	"$(INTDIR)\SqlSets.obj" \
	"$(INTDIR)\stack.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\TableSel.obj" \
	"$(INTDIR)\timer.obj" \
	"$(INTDIR)\tri.obj" \
	"$(INTDIR)\update_epsilon.obj" \
	"$(INTDIR)\idb.res" \
	".\JpegLib.lib" \
	"$(INTDIR)\DlgApproximation.obj"

"$(OUTDIR)\mlpq_nt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

CPP_PROJ=/nologo /MT /W3 /Gi /GR /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mlpq_nt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\idb.res" /d "NDEBUG" 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mlpq_nt.dep")
!INCLUDE "mlpq_nt.dep"
!ELSE 
!MESSAGE Warning: cannot find "mlpq_nt.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "idb - Win32 Debug"
SOURCE=.\arg.cpp

"$(INTDIR)\arg.obj"	"$(INTDIR)\arg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BasicSQL.cpp

"$(INTDIR)\BasicSQL.obj"	"$(INTDIR)\BasicSQL.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\basicsqldialogbox.cpp

"$(INTDIR)\basicsqldialogbox.obj"	"$(INTDIR)\basicsqldialogbox.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BitmapFile.cpp

"$(INTDIR)\BitmapFile.obj"	"$(INTDIR)\BitmapFile.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\construct.cpp

"$(INTDIR)\construct.obj"	"$(INTDIR)\construct.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\csa_debug.c
CPP_SWITCHES=/nologo /MT /W3 /Gi /GR /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mlpq_nt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\csa_debug.obj"	"$(INTDIR)\csa_debug.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


SOURCE=.\csa_q_main.c

"$(INTDIR)\csa_q_main.obj"	"$(INTDIR)\csa_q_main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\csa_stack.c

"$(INTDIR)\csa_stack.obj"	"$(INTDIR)\csa_stack.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\db.cpp

"$(INTDIR)\db.obj"	"$(INTDIR)\db.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\debug.c

"$(INTDIR)\debug.obj"	"$(INTDIR)\debug.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgApproximation.cpp

"$(INTDIR)\DlgApproximation.obj"	"$(INTDIR)\DlgApproximation.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgArea.cpp

"$(INTDIR)\DlgArea.obj"	"$(INTDIR)\DlgArea.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgArea2.cpp

"$(INTDIR)\DlgArea2.obj"	"$(INTDIR)\DlgArea2.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgBlock.cpp

"$(INTDIR)\DlgBlock.obj"	"$(INTDIR)\DlgBlock.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgBuffer.cpp

"$(INTDIR)\DlgBuffer.obj"	"$(INTDIR)\DlgBuffer.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgColor.cpp

"$(INTDIR)\DlgColor.obj"	"$(INTDIR)\DlgColor.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgExpo.cpp

"$(INTDIR)\DlgExpo.obj"	"$(INTDIR)\DlgExpo.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgExport.cpp

"$(INTDIR)\DlgExport.obj"	"$(INTDIR)\DlgExport.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgGenN.cpp

"$(INTDIR)\DlgGenN.obj"	"$(INTDIR)\DlgGenN.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgInput.cpp

"$(INTDIR)\DlgInput.obj"	"$(INTDIR)\DlgInput.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgInsR.cpp

"$(INTDIR)\DlgInsR.obj"	"$(INTDIR)\DlgInsR.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgMaxMin.cpp

"$(INTDIR)\DlgMaxMin.obj"	"$(INTDIR)\DlgMaxMin.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgName.cpp

"$(INTDIR)\DlgName.obj"	"$(INTDIR)\DlgName.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgNtime.cpp

"$(INTDIR)\DlgNtime.obj"	"$(INTDIR)\DlgNtime.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgProp.cpp

"$(INTDIR)\DlgProp.obj"	"$(INTDIR)\DlgProp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgRange.cpp

"$(INTDIR)\DlgRange.obj"	"$(INTDIR)\DlgRange.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgRelName.cpp

"$(INTDIR)\DlgRelName.obj"	"$(INTDIR)\DlgRelName.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dlist.cpp

"$(INTDIR)\dlist.obj"	"$(INTDIR)\dlist.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\engine.cpp

"$(INTDIR)\engine.obj"	"$(INTDIR)\engine.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ex29aView.cpp

"$(INTDIR)\ex29aView.obj"	"$(INTDIR)\ex29aView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\globals.cpp

"$(INTDIR)\globals.obj"	"$(INTDIR)\globals.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GraphView.cpp

"$(INTDIR)\GraphView.obj"	"$(INTDIR)\GraphView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\hash.c

"$(INTDIR)\hash.obj"	"$(INTDIR)\hash.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\hulconvt.cpp

"$(INTDIR)\hulconvt.obj"	"$(INTDIR)\hulconvt.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\hulreconvt.cpp

"$(INTDIR)\hulreconvt.obj"	"$(INTDIR)\hulreconvt.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\idb.cpp

"$(INTDIR)\idb.obj"	"$(INTDIR)\idb.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\idb.rc

"$(INTDIR)\idb.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\idbDoc.cpp

"$(INTDIR)\idbDoc.obj"	"$(INTDIR)\idbDoc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\idbView.cpp

"$(INTDIR)\idbView.obj"	"$(INTDIR)\idbView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\list.cpp

"$(INTDIR)\list.obj"	"$(INTDIR)\list.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LP.C

"$(INTDIR)\LP.OBJ"	"$(INTDIR)\LP.SBR" : $(SOURCE) "$(INTDIR)"


SOURCE=.\lp_solve.c

"$(INTDIR)\lp_solve.obj"	"$(INTDIR)\lp_solve.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\lpkit.c

"$(INTDIR)\lpkit.obj"	"$(INTDIR)\lpkit.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MatrixView.cpp

"$(INTDIR)\MatrixView.obj"	"$(INTDIR)\MatrixView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\misc.cpp

"$(INTDIR)\misc.obj"	"$(INTDIR)\misc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\monotone.cpp

"$(INTDIR)\monotone.obj"	"$(INTDIR)\monotone.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\myparse.c

"$(INTDIR)\myparse.obj"	"$(INTDIR)\myparse.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\NewSocket.cpp

"$(INTDIR)\NewSocket.obj"	"$(INTDIR)\NewSocket.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OnNestedSql.cpp

"$(INTDIR)\OnNestedSql.obj"	"$(INTDIR)\OnNestedSql.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OnsetReg.cpp

"$(INTDIR)\OnsetReg.obj"	"$(INTDIR)\OnsetReg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OwnListBox.cpp

"$(INTDIR)\OwnListBox.obj"	"$(INTDIR)\OwnListBox.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\parse.c

"$(INTDIR)\parse.obj"	"$(INTDIR)\parse.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\parser.cpp

"$(INTDIR)\parser.obj"	"$(INTDIR)\parser.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PointView.cpp

"$(INTDIR)\PointView.obj"	"$(INTDIR)\PointView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\read.c

"$(INTDIR)\read.obj"	"$(INTDIR)\read.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\readmps.c

"$(INTDIR)\readmps.obj"	"$(INTDIR)\readmps.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\refine.c

"$(INTDIR)\refine.obj"	"$(INTDIR)\refine.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\relation.cpp

"$(INTDIR)\relation.obj"	"$(INTDIR)\relation.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Render.cpp

"$(INTDIR)\Render.obj"	"$(INTDIR)\Render.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RowView.cpp

"$(INTDIR)\RowView.obj"	"$(INTDIR)\RowView.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\scanner.cpp

"$(INTDIR)\scanner.obj"	"$(INTDIR)\scanner.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SCDrawobj.cpp

"$(INTDIR)\SCDrawobj.obj"	"$(INTDIR)\SCDrawobj.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SCDrawtool.cpp

"$(INTDIR)\SCDrawtool.obj"	"$(INTDIR)\SCDrawtool.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ServerSocket.cpp

"$(INTDIR)\ServerSocket.obj"	"$(INTDIR)\ServerSocket.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\simplexlcs.cpp

"$(INTDIR)\simplexlcs.obj"	"$(INTDIR)\simplexlcs.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\slist.cpp

"$(INTDIR)\slist.obj"	"$(INTDIR)\slist.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\solve.c

"$(INTDIR)\solve.obj"	"$(INTDIR)\solve.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SqlAggregation.cpp

"$(INTDIR)\SqlAggregation.obj"	"$(INTDIR)\SqlAggregation.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SqlDialogBox.cpp

"$(INTDIR)\SqlDialogBox.obj"	"$(INTDIR)\SqlDialogBox.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SqlSets.cpp

"$(INTDIR)\SqlSets.obj"	"$(INTDIR)\SqlSets.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\stack.cpp

"$(INTDIR)\stack.obj"	"$(INTDIR)\stack.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp
CPP_SWITCHES=/nologo /MT /W3 /Gi /GR /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mlpq_nt.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\mlpq_nt.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


SOURCE=.\string.cpp

"$(INTDIR)\string.obj"	"$(INTDIR)\string.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TableSel.cpp

"$(INTDIR)\TableSel.obj"	"$(INTDIR)\TableSel.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\timer.c

"$(INTDIR)\timer.obj"	"$(INTDIR)\timer.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tri.cpp
CPP_SWITCHES=/nologo /GB /MT /w /W0 /Gm /Gi- /GR- /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mlpq_nt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\tri.obj"	"$(INTDIR)\tri.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


SOURCE=.\update_epsilon.c

"$(INTDIR)\update_epsilon.obj"	"$(INTDIR)\update_epsilon.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

