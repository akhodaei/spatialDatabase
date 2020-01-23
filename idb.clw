; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIdbDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "idb.h"
LastPage=0

ClassCount=36
Class1=CIdbApp
Class2=CIdbDoc
Class3=CMatrixView
Class4=CMainFrame
Class7=CGraphView
Class8=CPointView

ResourceCount=66
Resource1=IDD_ABOUTBOX
Resource2=IDD_RENDER
Class5=CAboutDlg
Class6=CChildFrame
Resource3=IDD_MAXMIN_DLG
Class9=CIdbView
Class10=COwnListBox
Resource4=IDR_DRAWTOOLS (Chinese (P.R.C.))
Class11=CDlgInsR
Resource5=IDD_AGRESQL
Class12=CDlgProp
Resource6=IDD_DLG_GEN_REL
Resource7=IDD_PROP_RECT (Chinese (P.R.C.))
Resource8=IDR_DRAWTOOLS1
Resource9=IDD_TABLE_SELECT
Resource10=IDD_DLG_GEN_REL1
Resource11=IDD_DLG_INSRELATION
Class13=CDlgGenN
Resource12=IDD_NESTED_SQL
Class14=CDlgArea
Resource13=IDD_DIALOG_NAME
Resource14=IDD_DLG_AREA
Class15=CDlgRelName
Resource15=IDR_IDBTYPE
Class16=CDlgBuffer
Resource16=IDD_INPUT
Resource17=IDD_BASICSQL
Class17=CDlgExport
Resource18=IDD_DLG_RANGE
Class18=CDlgName
Resource19=IDD_DLG_COLOR
Class19=CDlgNtime
Resource20=IDD_SQLSETS
Resource21=IDD_SQLDIALOGBOX
Class20=CDlgBlock
Class21=CDlgArea2
Resource22=IDD_DIALOG_TIME
Class22=CDlgColor
Resource23=IDD_EXPO_DLG
Class23=CDlgRange
Resource24=IDD_DLG_TIME
Class24=CDlgInput
Resource25=IDD_DLG_REL_LIST
Class25=CDlgExpo
Resource26=IDD_DLG_PROPERTY
Class26=CMaxMinDlg
Class27=CDlgMaxMin
Resource27=IDR_DRAWTOOLS
Class28=BasicSQL
Resource28=IDD_EXPORT_FILE
Class29=Render
Class30=SQLDialog
Class31=SQLAGGRE
Resource29=IDD_DIALOG_BLOCK
Class32=SqlAggregation
Resource30=IDD_PROP_RECT
Class33=SqlSets
Resource31=IDD_DIALOG_AREA2
Class34=OnNestedSql
Resource32=IDD_DIALOG_BUFFER
Class35=basicsqldialogbox
Resource33=IDR_MAINFRAME
Resource34=IDR_IDBTYPE (English (U.S.))
Resource35=IDD_DLG_COLOR (English (U.S.))
Resource36=IDD_DIALOG_NEGATION (English (U.S.))
Resource37=IDD_EXPORT_FILE (English (U.S.))
Resource38=IDD_PROP_RECT (English (U.S.))
Resource39=IDR_DRAWTOOLS (English (U.S.))
Resource40=IDD_DLG_TIME (English (U.S.))
Resource41=IDD_DLG_GEN_REL1 (English (U.S.))
Resource42=IDD_SQLDIALOGBOX (English (U.S.))
Resource43=IDD_MAXMIN_DLG (English (U.S.))
Resource44=IDR_DRAWTOOLS1 (English (U.S.))
Resource45=IDD_SQLSETS (English (U.S.))
Resource46=IDD_EXPO_DLG (English (U.S.))
Resource47=IDD_DIALOG_TIME (English (U.S.))
Resource48=IDD_TABLE_SELECT (English (U.S.))
Resource49=IDD_DIALOG_AREA2 (English (U.S.))
Resource50=IDD_DLG_REL_LIST (English (U.S.))
Resource51=IDD_INPUT (English (U.S.))
Resource52=IDD_DLG_NEGATION
Resource53=IDD_NESTED_SQL (English (U.S.))
Resource54=IDD_BASICSQL (English (U.S.))
Resource55=IDD_ABOUTBOX (English (U.S.))
Resource56=IDD_DLG_AREA (English (U.S.))
Resource57=IDD_DLG_INSRELATION (English (U.S.))
Resource58=IDD_DLG_RANGE (English (U.S.))
Resource59=IDD_DLG_GEN_REL (English (U.S.))
Resource60=IDD_DIALOG_BLOCK (English (U.S.))
Resource61=IDD_RENDER (English (U.S.))
Resource62=IDD_DIALOG_BUFFER (English (U.S.))
Resource63=IDD_DIALOG_NAME (English (U.S.))
Resource64=IDD_AGRESQL (English (U.S.))
Resource65=IDD_DLG_PROPERTY (English (U.S.))
Class36=CDlgNegation
Resource66=IDR_MAINFRAME (English (U.S.))

[CLS:CIdbApp]
Type=0
HeaderFile=idb.h
ImplementationFile=idb.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CIdbApp

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_APP_ABOUT
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame

[CLS:CAboutDlg]
Type=0
HeaderFile=idb.cpp
ImplementationFile=idb.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=14
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=IDC_LISTEN
Command10=IDC_TEST
CommandCount=10

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_VIEW_ZOOMIN
Command5=ID_OP_COLOR
Command6=ID_COLOR_RELATION
Command7=ID_VIEW_TIME
Command8=ID_VIEW_PLAY
Command9=ID_VIEW_PLAYBACK
Command10=ID_VIEW_NEXTSTEP
Command11=ID_VIEW_PRIORSTEP
Command12=ID_VIEW_GOHEAD
Command13=ID_VIEW_GOEND
Command14=ID_REGRESION
Command15=ID_SHAPE_ANIM
Command16=ID_VIEW_PLAYSHAPEBACK
Command17=ID_SHAPE_NEXTSTEP
Command18=ID_VIEW_SHAPEPRIOR
Command19=ID_VIEW_SHAPEGOHEAD
Command20=ID_VIEW_SHAPEGOEND
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:IDR_IDBTYPE]
Type=1
Class=CIdbDoc
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_IMPORT_POLYGON
Command7=ID_FILE_IMPORTFILE_POINT
Command8=ID_IMPORT_MDB
Command9=ID_IMPORT_LINE
Command10=ID_FILE_IMPORTFILE_ELEVATION
Command11=ID_FILE_EXPORT
Command12=ID_FILE_PRINT
Command13=ID_FILE_PRINT_PREVIEW
Command14=ID_FILE_PRINT_SETUP
Command15=ID_FILE_MRU_FILE1
Command16=ID_APP_EXIT
Command17=ID_EDIT_UNDO
Command18=ID_EDIT_CUT
Command19=ID_EDIT_COPY
Command20=ID_EDIT_PASTE
Command21=ID_EDIT_INSRELATION
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_VIEW_ZOOMIN
Command25=ID_VIEW_ZOOMOUT
Command26=ID_VIEW_TIME
Command27=ID_VIEW_PLAY
Command28=ID_VIEW_PLAYBACK
Command29=ID_VIEW_GOHEAD
Command30=ID_VIEW_GOEND
Command31=ID_VIEW_NEXTSTEP
Command32=ID_VIEW_PRIORSTEP
Command33=ID_VIEW_EXECUTIONTIME
Command34=ID_VIEW_SAMERELATIONCOLOR
Command35=ID_WINDOW_NEW
Command36=ID_WINDOW_CASCADE
Command37=ID_WINDOW_TILE_HORZ
Command38=ID_WINDOW_ARRANGE
Command39=ID_WINDOW_SPLIT
Command40=ID_APP_ABOUT
CommandCount=40

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_VIEW_ZOOMIN
Command10=ID_NEXT_PANE
Command11=ID_VIEW_ZOOMOUT
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[CLS:CGraphView]
Type=0
HeaderFile=GraphView.h
ImplementationFile=GraphView.cpp
BaseClass=CScrollView
Filter=C
LastObject=ID_DRAW_RECT
VirtualFilter=VWC

[CLS:CPointView]
Type=0
HeaderFile=PointView.h
ImplementationFile=PointView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CPointView

[CLS:CMatrixView]
Type=0
HeaderFile=MatrixView.h
ImplementationFile=MatrixView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CMatrixView

[DLG:IDD_DLG_REL_LIST]
Type=1
Class=CIdbView
ControlCount=1
Control1=IDC_LIST1,listbox,1344340249

[CLS:CIdbView]
Type=0
HeaderFile=IdbView.h
ImplementationFile=IdbView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_LIST1

[CLS:COwnListBox]
Type=0
HeaderFile=OwnListBox.h
ImplementationFile=OwnListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=COwnListBox

[DLG:IDD_DLG_INSRELATION]
Type=1
Class=CDlgInsR
ControlCount=3
Control1=IDC_EDIT1,edit,1353781444
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CDlgInsR]
Type=0
HeaderFile=DlgInsR.h
ImplementationFile=DlgInsR.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgInsR

[DLG:IDD_DLG_PROPERTY]
Type=1
Class=CDlgProp
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1353779332

[CLS:CDlgProp]
Type=0
HeaderFile=DlgProp.h
ImplementationFile=DlgProp.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgProp

[DLG:IDD_PROP_RECT (Chinese (P.R.C.))]
Type=1
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_WEIGHT,edit,1350631552
Control4=IDC_SPIN,msctls_updown32,1342177334
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NOFILL,button,1342242819
Control7=ID_OBJECT_LINECOLOR,button,1342242816
Control8=ID_OBJECT_FILLCOLOR,button,1342242816

[TB:IDR_DRAWTOOLS (Chinese (P.R.C.))]
Type=1
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_ARC
Command4=ID_DRAW_RECT
Command5=ID_DRAW_GROUND
Command6=ID_DRAW_ELLIPSE
Command7=ID_DRAW_CIRCLE
Command8=ID_DRAW_POLY
Command9=ID_DRAW_3PARC
Command10=ID_DRAW_TEXT
Command11=ID_VIEW_ZOOM_ZOOM
CommandCount=11
Class=CIdbDoc

[DLG:IDD_PROP_RECT]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_WEIGHT,edit,1350631552
Control4=IDC_SPIN,msctls_updown32,1342177334
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NOFILL,button,1342242819
Control7=ID_OBJECT_LINECOLOR,button,1342242816
Control8=ID_OBJECT_FILLCOLOR,button,1342242816

[TB:IDR_DRAWTOOLS]
Type=1
Class=CIdbDoc
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_RECT
Command4=ID_DRAW_POLY
Command5=ID_OP_INTERSECTION
Command6=ID_OP_UNION
Command7=ID_OP_MINUS
Command8=ID_OP_COMPLEMENT
Command9=ID_OP_AREA
Command10=ID_BUFFER
Command11=ID_EDIT_INSRELATION
Command12=ID_SQL_DIALOG
Command13=ID_BUTTON_MAX
Command14=ID_BUTTON_MIN
Command15=ID_OP_BLOCK
Command16=ID_OP_COLLIDE
Command17=ID_BUTTON_SIM_QUERY
CommandCount=17

[TB:IDR_DRAWTOOLS1]
Type=1
Class=?
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_ARC
Command4=ID_DRAW_RECT
Command5=ID_DRAW_GROUND
Command6=ID_DRAW_ELLIPSE
Command7=ID_DRAW_CIRCLE
Command8=ID_DRAW_POLY
Command9=ID_DRAW_3PARC
Command10=ID_DRAW_TEXT
Command11=ID_VIEW_ZOOM_ZOOM
CommandCount=11

[DLG:IDD_DLG_GEN_REL]
Type=1
Class=CDlgGenN
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CDlgGenN]
Type=0
HeaderFile=DlgGenN.h
ImplementationFile=DlgGenN.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgGenN

[DLG:IDD_DLG_AREA]
Type=1
Class=CDlgArea
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_MIN,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_MAX,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_STEP,edit,1350631552

[CLS:CDlgArea]
Type=0
HeaderFile=DlgArea.h
ImplementationFile=DlgArea.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CIdbDoc]
Type=0
HeaderFile=idbdoc.h
ImplementationFile=idbdoc.cpp
BaseClass=CDocument
LastObject=ID_FILE_SAVE_AS
Filter=N
VirtualFilter=DC

[DLG:IDD_DLG_TIME]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ANI_START,edit,1350631552
Control3=IDC_TIME_RANGE,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ANI_STEP,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ANI_NOOFSTEP,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ANI_SPEED,edit,1350639616
Control10=IDC_SPIN1,msctls_updown32,1342177302
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[DLG:IDD_DLG_GEN_REL1]
Type=1
Class=CDlgRelName
ControlCount=4
Control1=65535,static,1342308352
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CDlgRelName]
Type=0
HeaderFile=DlgRelName.h
ImplementationFile=DlgRelName.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[DLG:IDD_DIALOG_BUFFER]
Type=1
Class=CDlgBuffer
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgBuffer]
Type=0
HeaderFile=DlgBuffer.h
ImplementationFile=DlgBuffer.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

[DLG:IDD_TABLE_SELECT]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[DLG:IDD_EXPORT_FILE]
Type=1
Class=CDlgExport
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SPATIAL,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DESCRIPTIVE,edit,1350631552

[CLS:CDlgExport]
Type=0
HeaderFile=DlgExport.h
ImplementationFile=DlgExport.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgExport

[DLG:IDD_DIALOG_NAME]
Type=1
Class=CDlgName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[CLS:CDlgName]
Type=0
HeaderFile=DlgName.h
ImplementationFile=DlgName.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgName
VirtualFilter=dWC

[DLG:IDD_DIALOG_TIME]
Type=1
Class=CDlgNtime
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_EDIT4,edit,1350631552
Control12=IDC_EDIT5,edit,1350631552

[CLS:CDlgNtime]
Type=0
HeaderFile=DlgNtime.h
ImplementationFile=DlgNtime.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT3

[DLG:IDD_DIALOG_BLOCK]
Type=1
Class=CDlgBlock
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552

[CLS:CDlgBlock]
Type=0
HeaderFile=DlgBlock.h
ImplementationFile=DlgBlock.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgBlock

[DLG:IDD_DIALOG_AREA2]
Type=1
Class=CDlgArea2
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CDlgArea2]
Type=0
HeaderFile=DlgArea2.h
ImplementationFile=DlgArea2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgArea2

[DLG:IDD_DLG_COLOR]
Type=1
Class=CDlgColor
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_DELETE,button,1342242817
Control3=IDC_ADD,button,1342242817
Control4=IDC_CUR_COLOR,static,1342177287
Control5=IDC_RANGE_LIST,listbox,1352728835
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CDlgColor]
Type=0
HeaderFile=DlgColor.h
ImplementationFile=DlgColor.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ADD

[DLG:IDD_DLG_RANGE]
Type=1
Class=CDlgRange
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RANGE_LEFT,edit,1350631552
Control4=IDC_RANGE_RIGHT,edit,1350631552
Control5=IDC_RANGE_COLOR,static,1342177287
Control6=IDC_RANGE_COLOR_SELECT,button,1342242817
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CDlgRange]
Type=0
HeaderFile=DlgRange.h
ImplementationFile=DlgRange.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RANGE_COLOR_SELECT

[DLG:IDD_INPUT]
Type=1
Class=CDlgInput
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_X,edit,1350631552
Control8=IDC_Y,edit,1350631552
Control9=IDC_AS,edit,1350631552

[CLS:CDlgInput]
Type=0
HeaderFile=DlgInput.h
ImplementationFile=DlgInput.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgInput

[DLG:IDD_EXPO_DLG]
Type=1
Class=CDlgExpo
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CDlgExpo]
Type=0
HeaderFile=DlgExpo.h
ImplementationFile=DlgExpo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgExpo

[DLG:IDD_MAXMIN_DLG]
Type=1
Class=CDlgMaxMin
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MAXMIN_NAME,edit,1350631552
Control6=IDC_MAXMIN_FUNCTION,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MAXMIN_CONSTANT,edit,1350631552
Control9=IDC_STATIC,button,1342177287

[CLS:CDlgMaxMin]
Type=0
HeaderFile=DlgMaxMin.h
ImplementationFile=DlgMaxMin.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MAXMIN_FUNCTION

[DLG:IDD_BASICSQL]
Type=1
Class=BasicSQL
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1353781252

[CLS:BasicSQL]
Type=0
HeaderFile=basicsql.h
ImplementationFile=basicsql.cpp
BaseClass=CDialog
LastObject=IDOK

[DLG:IDD_RENDER]
Type=1
Class=Render
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552

[CLS:Render]
Type=0
HeaderFile=render.h
ImplementationFile=render.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[CLS:SQLDialog]
Type=0
HeaderFile=sqldialog.h
ImplementationFile=sqldialog.cpp
BaseClass=CDialog
LastObject=ID_APP_ABOUT
Filter=D
VirtualFilter=dWC

[CLS:SQLAGGRE]
Type=0
HeaderFile=SQLAGGRE.h
ImplementationFile=SQLAGGRE.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[DLG:IDD_AGRESQL]
Type=1
Class=SqlAggregation
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT5,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT6,edit,1353781252

[CLS:SqlAggregation]
Type=0
HeaderFile=SqlAggregation.h
ImplementationFile=SqlAggregation.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_SQLSETS]
Type=1
Class=SqlSets
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT11,edit,1350631552
Control12=IDC_EDIT12,edit,1350631552
Control13=IDC_EDIT13,edit,1350631552
Control14=IDC_EDIT14,edit,1353781252
Control15=IDC_EDIT15,edit,1350631552
Control16=IDC_EDIT16,edit,1350631552
Control17=IDC_EDIT17,edit,1350631552
Control18=IDC_EDIT18,edit,1353781252

[CLS:SqlSets]
Type=0
HeaderFile=SqlSets.h
ImplementationFile=SqlSets.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL
VirtualFilter=dWC

[DLG:IDD_NESTED_SQL]
Type=1
Class=OnNestedSql
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT1,edit,1350631552
Control11=IDC_EDIT2,edit,1350631552
Control12=IDC_EDIT3,edit,1350631552
Control13=IDC_EDIT4,edit,1353781252
Control14=IDC_EDIT5,edit,1350631552
Control15=IDC_EDIT6,edit,1350631552
Control16=IDC_EDIT7,edit,1350631552
Control17=IDC_EDIT8,edit,1353781252

[CLS:OnNestedSql]
Type=0
HeaderFile=onnestedsql.h
ImplementationFile=onnestedsql.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[DLG:IDD_SQLDIALOGBOX]
Type=1
Class=basicsqldialogbox
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_BUTTONBSQL,button,1342242816
Control3=IDC_BUTTONASQL,button,1342242816
Control4=IDC_BUTTONSSQL,button,1342242816
Control5=IDC_BUTTONNSQL,button,1342242816

[CLS:basicsqldialogbox]
Type=0
HeaderFile=basicsqldialogbox.h
ImplementationFile=basicsqldialogbox.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_BUTTON_SIM_QUERY

[TB:IDR_DRAWTOOLS (English (U.S.))]
Type=1
Class=?
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_RECT
Command4=ID_DRAW_POLY
Command5=ID_OP_INTERSECTION
Command6=ID_OP_UNION
Command7=ID_OP_MINUS
Command8=ID_OP_COMPLEMENT
Command9=ID_OP_AREA
Command10=ID_BUFFER
Command11=ID_EDIT_INSRELATION
Command12=ID_SQL_DIALOG
Command13=ID_BUTTON_MAX
Command14=ID_BUTTON_MIN
Command15=ID_OP_BLOCK
Command16=ID_OP_COLLIDE
Command17=ID_BUTTON_SIM_QUERY
CommandCount=17

[TB:IDR_DRAWTOOLS1 (English (U.S.))]
Type=1
Class=?
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_ARC
Command4=ID_DRAW_RECT
Command5=ID_DRAW_GROUND
Command6=ID_DRAW_ELLIPSE
Command7=ID_DRAW_CIRCLE
Command8=ID_DRAW_POLY
Command9=ID_DRAW_3PARC
Command10=ID_DRAW_TEXT
Command11=ID_VIEW_ZOOM_ZOOM
CommandCount=11

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE_AS
Command4=ID_VIEW_ZOOMIN
Command5=ID_OP_COLOR
Command6=ID_COLOR_RELATION
Command7=ID_VIEW_TIME
Command8=ID_VIEW_PLAY
Command9=ID_VIEW_PLAYBACK
Command10=ID_VIEW_NEXTSTEP
Command11=ID_VIEW_PRIORSTEP
Command12=ID_VIEW_GOHEAD
Command13=ID_VIEW_GOEND
Command14=ID_REGRESION
Command15=ID_SHAPE_ANIM
Command16=ID_VIEW_PLAYSHAPEBACK
Command17=ID_SHAPE_NEXTSTEP
Command18=ID_VIEW_SHAPEPRIOR
Command19=ID_VIEW_SHAPEGOHEAD
Command20=ID_VIEW_SHAPEGOEND
Command21=ID_APP_ABOUT
Command22=ID_RECTMAG
CommandCount=22

[DLG:IDD_PROP_RECT (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_WEIGHT,edit,1350631552
Control4=IDC_SPIN,msctls_updown32,1342177334
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NOFILL,button,1342242819
Control7=ID_OBJECT_LINECOLOR,button,1342242816
Control8=ID_OBJECT_FILLCOLOR,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=14
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_REL_LIST (English (U.S.))]
Type=1
Class=CIdbView
ControlCount=1
Control1=IDC_LIST1,listbox,1344340249

[DLG:IDD_DLG_INSRELATION (English (U.S.))]
Type=1
Class=CDlgInsR
ControlCount=3
Control1=IDC_EDIT1,edit,1353781444
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DLG_PROPERTY (English (U.S.))]
Type=1
Class=CDlgProp
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1353779332

[DLG:IDD_DLG_GEN_REL (English (U.S.))]
Type=1
Class=CDlgGenN
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[DLG:IDD_DLG_AREA (English (U.S.))]
Type=1
Class=CDlgArea
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_MIN,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_MAX,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_STEP,edit,1350631552

[DLG:IDD_DLG_TIME (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ANI_START,edit,1350631552
Control3=IDC_TIME_RANGE,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ANI_STEP,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ANI_NOOFSTEP,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ANI_SPEED,edit,1350639616
Control10=IDC_SPIN1,msctls_updown32,1342177302
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[DLG:IDD_DLG_GEN_REL1 (English (U.S.))]
Type=1
Class=CDlgRelName
ControlCount=4
Control1=65535,static,1342308352
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_BUFFER (English (U.S.))]
Type=1
Class=CDlgBuffer
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_SELECT (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[DLG:IDD_EXPORT_FILE (English (U.S.))]
Type=1
Class=CDlgExport
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SPATIAL,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DESCRIPTIVE,edit,1350631552

[DLG:IDD_DIALOG_NAME (English (U.S.))]
Type=1
Class=CDlgName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[DLG:IDD_DIALOG_TIME (English (U.S.))]
Type=1
Class=CDlgNtime
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT2,edit,1350631552
Control11=IDC_EDIT4,edit,1350631552
Control12=IDC_EDIT5,edit,1350631552

[DLG:IDD_DIALOG_BLOCK (English (U.S.))]
Type=1
Class=CDlgBlock
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552

[DLG:IDD_DIALOG_AREA2 (English (U.S.))]
Type=1
Class=CDlgArea2
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_COLOR (English (U.S.))]
Type=1
Class=CDlgColor
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_DELETE,button,1342242817
Control3=IDC_ADD,button,1342242817
Control4=IDC_CUR_COLOR,static,1342177287
Control5=IDC_RANGE_LIST,listbox,1352728835
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_RANGE (English (U.S.))]
Type=1
Class=CDlgRange
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RANGE_LEFT,edit,1350631552
Control4=IDC_RANGE_RIGHT,edit,1350631552
Control5=IDC_RANGE_COLOR,static,1342177287
Control6=IDC_RANGE_COLOR_SELECT,button,1342242817
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_INPUT (English (U.S.))]
Type=1
Class=CDlgInput
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_X,edit,1350631552
Control8=IDC_Y,edit,1350631552
Control9=IDC_AS,edit,1350631552

[DLG:IDD_EXPO_DLG (English (U.S.))]
Type=1
Class=CDlgExpo
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_MAXMIN_DLG (English (U.S.))]
Type=1
Class=CDlgMaxMin
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MAXMIN_NAME,edit,1350631552
Control6=IDC_MAXMIN_FUNCTION,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MAXMIN_CONSTANT,edit,1350631552
Control9=IDC_STATIC,button,1342177287

[DLG:IDD_BASICSQL (English (U.S.))]
Type=1
Class=BasicSQL
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1353781252

[DLG:IDD_RENDER (English (U.S.))]
Type=1
Class=Render
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552

[DLG:IDD_AGRESQL (English (U.S.))]
Type=1
Class=SqlAggregation
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT5,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT6,edit,1353781252

[DLG:IDD_SQLSETS (English (U.S.))]
Type=1
Class=SqlSets
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT11,edit,1350631552
Control12=IDC_EDIT12,edit,1350631552
Control13=IDC_EDIT13,edit,1350631552
Control14=IDC_EDIT14,edit,1353781252
Control15=IDC_EDIT15,edit,1350631552
Control16=IDC_EDIT16,edit,1350631552
Control17=IDC_EDIT17,edit,1350631552
Control18=IDC_EDIT18,edit,1353781252

[DLG:IDD_NESTED_SQL (English (U.S.))]
Type=1
Class=OnNestedSql
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT1,edit,1350631552
Control11=IDC_EDIT2,edit,1350631552
Control12=IDC_EDIT3,edit,1350631552
Control13=IDC_EDIT4,edit,1353781252
Control14=IDC_EDIT5,edit,1350631552
Control15=IDC_EDIT6,edit,1350631552
Control16=IDC_EDIT7,edit,1350631552
Control17=IDC_EDIT8,edit,1353781252

[DLG:IDD_SQLDIALOGBOX (English (U.S.))]
Type=1
Class=basicsqldialogbox
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_BUTTONBSQL,button,1342242816
Control3=IDC_BUTTONASQL,button,1342242816
Control4=IDC_BUTTONSSQL,button,1342242816
Control5=IDC_BUTTONNSQL,button,1342242816

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=IDC_LISTEN
Command10=IDC_TEST
CommandCount=10

[MNU:IDR_IDBTYPE (English (U.S.))]
Type=1
Class=CIdbDoc
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_IMPORT_POLYGON
Command7=ID_FILE_IMPORTFILE_POINT
Command8=ID_IMPORT_MDB
Command9=ID_IMPORT_LINE
Command10=ID_FILE_IMPORTFILE_ELEVATION
Command11=ID_FILE_EXPORT
Command12=ID_FILE_PRINT
Command13=ID_FILE_PRINT_PREVIEW
Command14=ID_FILE_PRINT_SETUP
Command15=ID_FILE_MRU_FILE1
Command16=ID_APP_EXIT
Command17=ID_EDIT_UNDO
Command18=ID_EDIT_CUT
Command19=ID_EDIT_COPY
Command20=ID_EDIT_PASTE
Command21=ID_EDIT_INSRELATION
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_VIEW_ZOOMIN
Command25=ID_VIEW_ZOOMOUT
Command26=ID_VIEW_TIME
Command27=ID_VIEW_PLAY
Command28=ID_VIEW_PLAYBACK
Command29=ID_VIEW_GOHEAD
Command30=ID_VIEW_GOEND
Command31=ID_VIEW_NEXTSTEP
Command32=ID_VIEW_PRIORSTEP
Command33=ID_VIEW_EXECUTIONTIME
Command34=ID_VIEW_SAMERELATIONCOLOR
Command35=ID_WINDOW_NEW
Command36=ID_WINDOW_CASCADE
Command37=ID_WINDOW_TILE_HORZ
Command38=ID_WINDOW_ARRANGE
Command39=ID_WINDOW_SPLIT
Command40=ID_APP_ABOUT
CommandCount=40

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_VIEW_ZOOMIN
Command10=ID_NEXT_PANE
Command11=ID_VIEW_ZOOMOUT
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_DIALOG_NEGATION (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_XRange,static,1342308352
Control4=IDC_EDIT1,edit,1350639744
Control5=IDC_YRange,static,1342308352
Control6=IDC_EDIT3,edit,1350639744

[DLG:IDD_DLG_NEGATION]
Type=1
Class=CDlgNegation
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_XRange,edit,1350639744
Control6=IDC_YRange,edit,1350639744

[CLS:CDlgNegation]
Type=0
HeaderFile=DlgNegation.h
ImplementationFile=DlgNegation.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgNegation

