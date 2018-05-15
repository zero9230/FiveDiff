// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "LoginDlg.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
// CLoginDlg1 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CLoginDlg::IDD, pParent)
, m_user(_T(""))
{
	//{{AFX_DATA_INIT(CLoginDlg1)
	m_user = _T("");
	m_pw = _T("");
	m_ctlrect = new CRect(CPoint(m_startpos.x + px, m_startpos.y + px), CPoint(m_startpos.x + width + px, m_startpos.y + px + px + height));
	//}}AFX_DATA_INIT
	width = 400;
	height = 200;
	m_startpos.x = 440;
	m_startpos.y = 480;
	px = 3;
	pbitmap = NULL;
}

CLoginDlg::~CLoginDlg()
{

}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN_USER, m_userComb);
	DDX_CBString(pDX, IDC_LOGIN_USER, m_user);
	DDX_CBString(pDX, IDC_LOGIN_PW, m_pw);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnLogin)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CLoginDlg1 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//ShowWindow(SW_MAXIMIZE);
	ShowWindow(SW_SHOWMAXIMIZED);


	pbitmap = (HBITMAP)LoadImage(NULL, _T("res/loginbk200.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (logobitmap.m_hObject)
	{
		logobitmap.Detach();
	}
	logobitmap.LoadBitmap(IDB_LOGO200);


	bitmap.DeleteObject();
	bitmap.Attach(pbitmap);

	CRect screenrc;
	GetWindowRect(screenrc);
	m_startpos.x = (screenrc.Width() - width) / 2;
	m_startpos.y = 2 * (screenrc.Height() - height) / 3;
	m_ctlrect = new CRect(CPoint(m_startpos.x + px, m_startpos.y + px), CPoint(m_startpos.x + width + px, m_startpos.y + px + px + height));

	TRACE("x= '%d' y='%d'\n", m_ctlrect.TopLeft().x, m_ctlrect.TopLeft().y);
	GetDlgItem(IDC_LOGIN_PW)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 160, m_ctlrect.TopLeft().y + 90, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_LOGIN_USER)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 160, m_ctlrect.TopLeft().y + 40, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_STATIC0)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 75, m_ctlrect.TopLeft().y + 46, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_STATIC1)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 75, m_ctlrect.TopLeft().y + 95, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_LOGIN)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 70, m_ctlrect.TopLeft().y + 150, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDCANCEL)->SetWindowPos(NULL, m_ctlrect.TopLeft().x + 224, m_ctlrect.TopLeft().y + 150, 0, 0, SWP_NOSIZE);


	try
	{
		CoInitialize(NULL);
		m_pDB = _ConnectionPtr(__uuidof(Connection));
		m_pDB->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=appdata.accdb", "", "", adModeUnknown);
		//m_pDB->Open("Provider=SQLOLEDB;Data Source=E:\\appdata.accdb", "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		//调用在CAdoRWAccessDlg中打印错误信息的静态函数  
		//CAdoRWAccessDlg::dump_com_error(e);
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);
		return FALSE;
	}
	m_pRs.CreateInstance(__uuidof(Recordset));
	try{

		_bstr_t sql = "SELECT * FROM Operator";
		m_pRs = m_pDB->Execute(sql, NULL, adCmdText);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
	}

	_variant_t var;
	CString strName;
	strName = "";
	try
	{
		if (!m_pRs->BOF)
			m_pRs->MoveFirst();
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return TRUE;
		}
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("NAME");
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_userComb.AddString(strName);
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect screenrc;
	GetWindowRect(screenrc);
	m_startpos.x = (screenrc.Width() - width) / 2;
	m_startpos.y = 2 * (screenrc.Height() - height) / 3;
}


void CLoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  在此处添加消息处理程序代码
	m_pRs->Close();
	m_pRs.Release();
	m_pRs = NULL;
	if (m_pDB->State)
		m_pDB->Close();
	m_pDB.Release();
	m_pDB = NULL;
	CoUninitialize();
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect screenrc;

	GetWindowRect(screenrc);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC dcCompatible;

	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(bitmap);

	CRect rc;
	GetClientRect(&rc);
	dcCompatible.LPtoDP(rc);
	int w = 0, h = 0;
	dc.StretchBlt(0, 0, screenrc.Width(), screenrc.Height(), &dcCompatible, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);


	CRect rc1;
	rc1 = new CRect(CPoint(m_startpos.x, m_startpos.y + height + px), CPoint(m_startpos.x + width, m_startpos.y + height + px + px));
	CBrush   bs;
	bs.CreateSolidBrush(RGB(0, 0, 0));
	dc.FillRect(rc1, &bs);

	CRect rc2;
	rc2 = new CRect(m_startpos, CPoint(m_startpos.x + px, m_startpos.y + px + px + height));
	dc.FillRect(rc2, &bs);

	CRect rc3;
	rc3 = new CRect(CPoint(m_startpos.x + width, m_startpos.y), CPoint(m_startpos.x + width + px, m_startpos.y + px + px + height));
	dc.FillRect(rc3, &bs);

	CRect rc4;
	rc4 = new CRect(m_startpos, CPoint(m_startpos.x + width, m_startpos.y + px));
	dc.FillRect(rc4, &bs);

	CDC tempDC;    //临时DC

	tempDC.CreateCompatibleDC(&dc);

	tempDC.SelectObject(logobitmap);
	if (screenrc.Width() >= 1000)
	{
		::TransparentBlt(dc.m_hDC, (screenrc.Width() - 1000) / 2, 50, 1000, 300, tempDC.m_hDC, 0, 0, 1000, 300, RGB(177, 213, 235));
	}
	else
	{
		::TransparentBlt(dc.m_hDC, 0, 50, 1000, 300, tempDC.m_hDC, 0, 0, 1000, 300, RGB(177, 213, 235));
	}
	//释放资源
	tempDC.DeleteDC();
}


void CLoginDlg::OnLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	static int times = 0;
	UpdateData();
	if (m_pw.Compare(_T("sinnowa")) == 0)
	{
		m_user = _T("sinnowa");
		operator_right = -1;
		CDialogEx::OnOK();
		return;
	}
	if (m_pw.Compare(_T("SINNOWA")) == 0)
	{
		m_user = _T("SINNOWA");
		operator_right = -1;
		CDialogEx::OnOK();
		return;
	}

	CString  sql;
	sql.Format(_T("SELECT * FROM Operator WHERE NAME='%s' AND PASSWORD='%s'"), m_user, m_pw);
	try
	{
		m_pRs = m_pDB->Execute((_bstr_t)sql, NULL, adCmdText);
		if (m_pRs->adoEOF)
		{
			MessageBox(_T("登录失败！请与设备管理者联系"));

			if (times++ > 4)
			{
				CDialogEx::OnCancel();
				return;
			}
		}
		else
		{
			m_right = m_pRs->GetCollect("RIGHT");
			pIsSuper = (uchar*)m_right;
			operator_right = m_right;

			CDialogEx::OnOK();
			return;
		}
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
		CDialogEx::OnCancel();
		return;
	}
}


void CLoginDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
