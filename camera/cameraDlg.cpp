// cameraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "camera.h"
#include "cameraDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraDlg dialog

CCameraDlg::CCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameraDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iWidth = 320 ;
	m_iHeight = 240 ;
	m_bCameraOpen = false ;
	m_bImageShow = false ;
	
}

void CCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CCameraDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenCamera, OnOpenCamera)
	ON_BN_CLICKED(IDC_ImageShow, OnImageShow)
	ON_BN_CLICKED(IDC_ImageStop, OnImageStop)
	ON_BN_CLICKED(IDC_CloseCamera, OnCloseCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraDlg message handlers

BOOL CCameraDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCameraDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCameraDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCameraDlg::OnOpenCamera() 
{
	if(m_bCameraOpen)
	{
		return ;
	}
	cam_count = CCameraDS::CameraCount();	
	if(!cam_count)
	{
		MessageBox("未查找到摄像头!","",MB_ICONINFORMATION);
	}
	else
	{
		//获取所有摄像头的名称
		CString str ;
		for(int i=0; i < cam_count; i++)
		{
			char camera_name[1024];  
			int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );
			
			if(retval >0)
			{
				str.Format("编号为%d摄像机的名字为%s",i,camera_name) ;
				//MessageBox(str,"",MB_ICONINFORMATION);
			}
			else
			{
				str.Format("不能获得编号为%d摄像机的名字",i) ;
				MessageBox(str,"",MB_ICONINFORMATION);
			}		
		}
		//左边显示窗口设置关联
		pDCL = GetDlgItem(IDC_PICL)->GetDC() ;
		hDCL= pDCL->GetSafeHdc();
		GetDlgItem(IDC_PICL)->GetClientRect(&rectL);
		//右边显示窗口设置关联
		pDCR = GetDlgItem(IDC_PICR)->GetDC() ;
		hDCR= pDCR->GetSafeHdc();
		GetDlgItem(IDC_PICR)->GetClientRect(&rectR);

		if(!camera.OpenCamera(0,0,320,240))
		{
			MessageBox("不能打开摄像头!","",MB_ICONINFORMATION);
		}
		else
		{
			MessageBox("摄像头初始完毕!","",MB_ICONINFORMATION);
			m_bCameraOpen = true ;
		}
	}
}

UINT CCameraDlg::ReceiveThread(void *param)
{
	CCameraDlg *pDlg = (CCameraDlg*)param ;
	while(1)
	{
		if(!pDlg->m_bImageShow)
		{
			return 0 ;
		}
		//获取一帧
		IplImage *pFrame = pDlg->camera.QueryFrame();
		
		//左边显示窗口，显示原始图像
		pDlg->m_imageL.CopyOf(pFrame);
		SetRect(pDlg->rectL, 0,0,pFrame->width,pFrame->height);	
		pDlg->m_imageL.DrawToHDC(pDlg->hDCL,&(pDlg->rectL));
		
		//可以添加一个函数用于图像处理，将处理后的结果显示在右边窗口

		pDlg->ImageThreshold(pFrame->imageData,pFrame->width,pFrame->height,pFrame->nChannels,pFrame->widthStep) ;
		
		
		//右边显示窗口，显示处理后的图像
		pDlg->m_imageR.CopyOf(pFrame,1);
		SetRect(pDlg->rectR, 0,0,pFrame->width,pFrame->height);
		pDlg->m_imageR.DrawToHDC(pDlg->hDCR,&(pDlg->rectR));
		//延时200毫秒
		Sleep(200) ;		
	}
	return 0 ;	
}

void CCameraDlg::OnImageShow() 
{
	if(!m_bCameraOpen)
	{
		return ;
	}
	m_bImageShow = true ;
	AfxBeginThread(ReceiveThread, this) ;	
}

void CCameraDlg::OnImageStop() 
{
	m_bImageShow = false ;
}

void CCameraDlg::ImageThreshold(char *pImageData, int width, int height, int nChannels, int widthStep)
{
	char *RImageData,*GImageData,*BImageData ;
	
	for(int i=0; i < height; i++)
	{
		for(int j =0 ; j < width; j++)
		{
			RImageData = pImageData + i*widthStep + j*nChannels + 2 ;
			GImageData = pImageData + i*widthStep + j*nChannels + 1 ;
			BImageData = pImageData + i*widthStep + j*nChannels + 0 ;
			
			
			if((uchar)*RImageData <100)
			{
				*RImageData = (uchar)255 ;
				*GImageData = (uchar)255 ;
				*BImageData = (uchar)255 ;
			}
			else
			{
				*RImageData = 0 ;
				*GImageData = 0 ;
				*BImageData = 0 ;
			}
		}
	}
	
}


void CCameraDlg::OnCloseCamera() 
{
	if(m_bImageShow)
	{
		MessageBox("请先停止显示图像!","",MB_ICONINFORMATION);
		return ;
	}

	if(m_bCameraOpen)
	{
		camera.CloseCamera();
		m_bCameraOpen = false ;
	}
	
}
