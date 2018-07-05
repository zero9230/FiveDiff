//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPChartExample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ConfigSetView.h"
//#include "MainFrm.h"
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
#include "LoginDlg.h"
//#include "Includes_app.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp

//

BEGIN_MESSAGE_MAP(CBCGPChartExampleApp, CBCGPWinApp)
	//{{AFX_MSG_MAP(CBCGPChartExampleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CBCGPWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CBCGPWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CBCGPWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp construction

static void InitSeriesColors(BCGPSeriesColors& sc, const CBCGPColor& color, UINT nTextureResID = 0)
{
	CBCGPColor colorGradient = color;
	colorGradient.MakeLighter(.5);

	if (nTextureResID != 0)
	{
		CBCGPColor colorAlt = color;
		colorAlt.MakeLighter(.2);

		sc.m_brElementFillColor.SetTextureImage(CBCGPImage(nTextureResID), colorAlt);
	}
	else
	{
		sc.m_brElementFillColor.SetColors(color, colorGradient, (CBCGPBrush::BCGP_GRADIENT_TYPE)-1);
	}

	CBCGPColor colorOutline = color;
	colorOutline.MakeDarker(.1);

	sc.m_brElementLineColor.SetColor(colorOutline);
	sc.m_brMarkerFillColor.SetColors(color, colorGradient, CBCGPBrush::BCGP_GRADIENT_DIAGONAL_LEFT);
	sc.m_brMarkerFillColor.MakeLighter(.15);

	sc.m_brMarkerLineColor.SetColor(colorOutline);
	sc.m_brDataLabelLineColor.SetColor(colorOutline);

	sc.m_brDataLabelFillColor.SetColor(color);
	sc.m_brDataLabelFillColor.MakePale();

	CBCGPColor colorText = color;
	colorText.MakeDarker(.2);

	sc.m_brDataLabelTextColor.SetColor(colorText);
}

CBCGPChartExampleApp::CBCGPChartExampleApp()
{
	SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_WHITE);

	// Setup custom color theme:
	CBCGPChartTheme::InitChartColors(m_CustomColorTheme, 
		CBCGPColor::White,	// Fill color
		CBCGPColor::Chocolate,	// Outline color
		CBCGPColor::Maroon,		// Text color
		CBCGPColor(), 
		CBCGPColor::SeaShell, .08);
	
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[0], CBCGPColor::Crimson);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[1], CBCGPColor::BlueViolet);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[2], CBCGPColor::CornflowerBlue);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[3], CBCGPColor::DarkGreen);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[4], CBCGPColor::Coral);

	// Create custom texture theme:
	CBCGPChartTheme::InitChartColors(m_CustomTexturedTheme, 
		CBCGPColor::White,	// Fill color
		CBCGPColor::CadetBlue,	// Outline color
		CBCGPColor::CadetBlue,		// Text color
		CBCGPColor(), 
		CBCGPColor::SeaShell, .08);
	
	CBCGPImage imageBackground(IDR_BACKGROUND);
	
	m_CustomTexturedTheme.m_brChartFillColor.SetTextureImage(imageBackground, CBCGPColor::AliceBlue, TRUE /* Watermark */);
	m_CustomTexturedTheme.m_brPlotFillColor.SetTextureImage(imageBackground, CBCGPColor::AliceBlue, TRUE /* Watermark */);
	m_CustomTexturedTheme.m_brLegendFillColor.SetTextureImage(imageBackground, CBCGPColor::AliceBlue, TRUE /* Watermark */);
	m_CustomTexturedTheme.m_brLegendEntryFillColor.Empty();

	CBCGPImage imageWall(IDR_WALL);
	CBCGPChartTheme::PrepareWallBrushes(m_CustomTexturedTheme, CBCGPBrush(imageWall, CBCGPColor::LightGray, FALSE));
	
    InitSeriesColors(m_CustomTexturedTheme.m_seriesColors[0], CBCGPColor::LightSlateGray, IDR_TEXTURE1);
    InitSeriesColors(m_CustomTexturedTheme.m_seriesColors[1], CBCGPColor::LimeGreen, IDR_TEXTURE2);
    InitSeriesColors(m_CustomTexturedTheme.m_seriesColors[2], CBCGPColor::RosyBrown, IDR_TEXTURE3);
    InitSeriesColors(m_CustomTexturedTheme.m_seriesColors[3], CBCGPColor::CadetBlue, IDR_TEXTURE4);
    InitSeriesColors(m_CustomTexturedTheme.m_seriesColors[4], CBCGPColor::Goldenrod, IDR_TEXTURE5);
	
	m_hLangDLL = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPChartExampleApp object

CBCGPChartExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp initialization

BOOL CBCGPChartExampleApp::InitInstance()
{
	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Sinnowa\\HA7501"));



	// 判断是否存在配置文件，如果存在，从配置文件中读取语言设置
	CString strFileName = _T("Language.ini");
	LCID lcidThread = 0;
	if (PathFileExists(strFileName))
	{

		CFile file;
		file.Open(strFileName, CFile::modeRead | CFile::typeBinary);
		file.Read(&lcidThread, sizeof(LCID));
		file.Close();
		SetThreadUILanguage(lcidThread);
	}
	//多语言支持模块，工程修缮完备后，需制作相关的dll以补全该模块
	switch (PRIMARYLANGID(LANGIDFROMLCID(lcidThread))){
		//case 0:	//加载中文dll
		//	m_hLangDLL = ::LoadLibrary(L"Chinese.dll");
		//	break;
	//case LANG_ENGLISH:	//加载英语dll
	//	m_hLangDLL = ::LoadLibrary(L"English.dll");
	//	AfxSetResourceHandle(m_hLangDLL);
	//	break;
	case LANG_FRENCH:	//加载法语dll
		m_hLangDLL = ::LoadLibrary(L"French.dll");
		AfxSetResourceHandle(m_hLangDLL);
		break;
	case LANG_RUSSIAN:	//加载俄语dll
		m_hLangDLL = ::LoadLibrary(L"Russian.dll");
		AfxSetResourceHandle(m_hLangDLL);
		break;
	case LANG_SPANISH:	//加载西班牙语dll
		m_hLangDLL = ::LoadLibrary(L"Spanish.dll");
		AfxSetResourceHandle(m_hLangDLL);
		break;
	}

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	SetRegistryBase(_T("Settings"));

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPChartExampleDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPChartExampleView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	////////////////////////////////生成开机登录界面//////////////////////
	//CLoginDlg	m_LoginDlg;
	//if (m_LoginDlg.DoModal() != IDOK)
	//{
	//return FALSE;
	//}
	//////////////////////////////////////////////////////////////////////

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//预开启开机画面
	//pMainFrame->SelectView(pMainFrame->GetCurrentViewType());
	pMainFrame->SelectView(1);
	//pMainFrame->SelectView(2);
	//CurView = 1;
	//CurView = 2;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW); 
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp message handlers

// App command to run the dialog
void CBCGPChartExampleApp::OnAppAbout()
{
	//BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
	CAboutDlg m_aboutDlg;
	if (!m_aboutDlg.DoModal())
	{				
		return;
	}
	return;
}

void CBCGPChartExampleApp::PreLoadState ()
{

}


/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp message handlers


int CBCGPChartExampleApp::ExitInstance()
{
	// TODO:  在此添加专用代码和/或调用基类
	if (m_hLangDLL)
		AfxFreeLibrary(m_hLangDLL);
	return CBCGPWinApp::ExitInstance();
}
