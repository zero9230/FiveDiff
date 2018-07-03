// LanguageChoose.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "LanguageChoose.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CLanguageChoose 对话框

IMPLEMENT_DYNAMIC(CLanguageChoose, CDialogEx)

BOOL m_bRestartFlag;
extern HWND mainhwnd;
CLanguageChoose::CLanguageChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLanguageChoose::IDD, pParent)
	//, m_languageChoose(0)
{

}

CLanguageChoose::~CLanguageChoose()
{
}

void CLanguageChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_CHINESE, m_languageChoose);
}


BEGIN_MESSAGE_MAP(CLanguageChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLanguageChoose::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLanguageChoose::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_CHINESE, &CLanguageChoose::OnBnClickedRadioChinese)
	ON_BN_CLICKED(IDC_RADIO_ENGLISH, &CLanguageChoose::OnBnClickedRadioEnglish)
	ON_BN_CLICKED(IDC_RADIO_FRENCH, &CLanguageChoose::OnBnClickedRadioFrench)
	ON_BN_CLICKED(IDC_RADIO_RUSSIAN, &CLanguageChoose::OnBnClickedRadioRussian)
	ON_BN_CLICKED(IDC_RADIO_SPANISH, &CLanguageChoose::OnBnClickedRadioSpanish)
END_MESSAGE_MAP()


// CLanguageChoose 消息处理程序


BOOL CLanguageChoose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	LCID lcidNew = GetThreadUILanguage();
	int curLang = PRIMARYLANGID(LANGIDFROMLCID(lcidNew));
	switch (curLang){
	case LANG_CHINESE:
		((CButton*)GetDlgItem(IDC_RADIO_CHINESE))->SetCheck(1);
		break;
	case LANG_ENGLISH:
		((CButton*)GetDlgItem(IDC_RADIO_ENGLISH))->SetCheck(1);
		break;
	case LANG_FRENCH:
		((CButton*)GetDlgItem(IDC_RADIO_FRENCH))->SetCheck(1);
		break;
	case LANG_RUSSIAN:
		((CButton*)GetDlgItem(IDC_RADIO_RUSSIAN))->SetCheck(1);
		break;
	case LANG_SPANISH:
		((CButton*)GetDlgItem(IDC_RADIO_SPANISH))->SetCheck(1);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CLanguageChoose::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//读入选项，写到配置文件中
	LCID lcidNew = GetThreadUILanguage();
	int curLang = PRIMARYLANGID(LANGIDFROMLCID(lcidNew));
	switch (m_languageChoose){
	case 0://chinese
		if (curLang == LANG_CHINESE){//当前语言为中文，则不切换
			return;
		}
		else{						//否则,切换当前语言为中文
			lcidNew = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),
				SORT_DEFAULT);
		}

		break;
	case 1://english
		if (curLang == LANG_ENGLISH){//当前语言为英文，则不切换
			return;
		}
		else{						//否则,切换当前语言为英文
			lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				SORT_DEFAULT);
		}

		break;
	case 2://french
		if (curLang == LANG_FRENCH){//当前语言为法文，则不切换
			return;
		}
		else{						//否则,切换当前语言为法文
			lcidNew = MAKELCID(MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH),
				SORT_DEFAULT);
		}

		break;
	case 3://russian
		if (curLang == LANG_RUSSIAN){//当前语言为俄文，则不切换
			return;
		}
		else{						//否则,切换当前语言为俄文
			lcidNew = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA),
				SORT_DEFAULT);
		}

		break;
	case 4:// spanish
		if (curLang == LANG_SPANISH){//当前语言为西班牙文，则不切换
			return;
		}
		else{						//否则,切换当前语言为西班牙文
			lcidNew = MAKELCID(MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH),
				SORT_DEFAULT);
		}

		break;

	}



	////切换语言
	//// 读取当前线程的语言，并根据当前线程语言进行语言切换
	//LCID lcidNew = GetThreadUILanguage();
	//if (LANG_ENGLISH == PRIMARYLANGID(LANGIDFROMLCID(lcidNew)))//当前语言为英文
	//{
	//	lcidNew = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),
	//		SORT_DEFAULT);
	//}
	//else
	//{
	//	lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
	//		SORT_DEFAULT);
	//}

	// 把语言设置写入配置文件
	CFile file;
	file.Open(_T("Language.ini"), CFile::modeWrite | CFile::modeCreate | CFile::typeBinary);
	file.Write(&lcidNew, sizeof(lcidNew));
	file.Close();

	// 关闭窗口
	m_bRestartFlag = TRUE;
	//CWnd* mainwnd = AfxGetMainWnd();
	::PostMessageW(mainhwnd, WM_CLOSE, 0, 0);
	//PostMessage( WM_CLOSE, 0, 0);
	CDialogEx::OnOK();
}


void CLanguageChoose::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CLanguageChoose::OnBnClickedRadioChinese()
{
	// TODO:  在此添加控件通知处理程序代码
	m_languageChoose = 0;
}


void CLanguageChoose::OnBnClickedRadioEnglish()
{
	// TODO:  在此添加控件通知处理程序代码
	m_languageChoose = 1;
}


void CLanguageChoose::OnBnClickedRadioFrench()
{
	// TODO:  在此添加控件通知处理程序代码
	m_languageChoose = 2;
}


void CLanguageChoose::OnBnClickedRadioRussian()
{
	// TODO:  在此添加控件通知处理程序代码
	m_languageChoose = 3;
}


void CLanguageChoose::OnBnClickedRadioSpanish()
{
	// TODO:  在此添加控件通知处理程序代码
	m_languageChoose = 4;
}

