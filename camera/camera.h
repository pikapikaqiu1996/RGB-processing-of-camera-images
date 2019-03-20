// camera.h : main header file for the CAMERA application
//

#if !defined(AFX_CAMERA_H__DA774FA1_C10F_43B2_A53B_3718745C6EF3__INCLUDED_)
#define AFX_CAMERA_H__DA774FA1_C10F_43B2_A53B_3718745C6EF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCameraApp:
// See camera.cpp for the implementation of this class
//

class CCameraApp : public CWinApp
{
public:
	CCameraApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCameraApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERA_H__DA774FA1_C10F_43B2_A53B_3718745C6EF3__INCLUDED_)
