; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCameraDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "camera.h"

ClassCount=3
Class1=CCameraApp
Class2=CCameraDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CAMERA_DIALOG

[CLS:CCameraApp]
Type=0
HeaderFile=camera.h
ImplementationFile=camera.cpp
Filter=N

[CLS:CCameraDlg]
Type=0
HeaderFile=cameraDlg.h
ImplementationFile=cameraDlg.cpp
Filter=D
LastObject=IDC_ImageStop
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=cameraDlg.h
ImplementationFile=cameraDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CAMERA_DIALOG]
Type=1
Class=CCameraDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PICL,static,1342177284
Control4=IDC_PICR,static,1342177284
Control5=IDC_OpenCamera,button,1342242816
Control6=IDC_ImageShow,button,1342242816
Control7=IDC_ImageStop,button,1342242816
Control8=IDC_CloseCamera,button,1342242816
Control9=IDC_STATIC,button,1342177287

