// QualityTargetValueView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityTargetValueView.h"
#include "afxdialogex.h"
#include "QualityFileExit.h"

// CQualityTargetValueView 对话框

IMPLEMENT_DYNAMIC(CQualityTargetValueView, CDialogEx)

extern int rc;
qc_edit_data_info qcLjEditData;

CQualityTargetValueView::CQualityTargetValueView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityTargetValueView::IDD, pParent)
{
	for (int i = 0; i < 26; i++)
	{
		Qctarget[i] = "";
		TargetLimit[i] = "";
	}

	VERIFY(textfont.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"宋体"));                 // lpszFacename
}

CQualityTargetValueView::~CQualityTargetValueView()
{
}

void CQualityTargetValueView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUALITY_TARGETVALUE_LIST, m_TargetValueList);
}


BEGIN_MESSAGE_MAP(CQualityTargetValueView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_QUALITY_TARGETVALUE_LIST, &CQualityTargetValueView::OnNMClickQualityTargetvalueList)
	ON_BN_CLICKED(IDC_QUALITYTARGET_CONFIRM, &CQualityTargetValueView::OnQualitytargetConfirm)
	ON_BN_CLICKED(IDC_RANGE_CONFIRM, &CQualityTargetValueView::OnRangeConfirm)
END_MESSAGE_MAP()


// CQualityTargetValueView 消息处理程序
int	 CQualityTargetValueView::item_focused = 0;


void CQualityTargetValueView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CQualityTargetValueView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_STATIC0, item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);

	InitTargetValueList();
	GetDlgItem(IDC_PROJECT_EDIT)->EnableWindow(false);
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->EnableWindow(false);
	GetDlgItem(IDC_PROJECT_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 0));
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 2));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CQualityTargetValueView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CQualityTargetValueView::InitTargetValueList()
{
	CRect rect;
	CString table[26] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
							"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	// 获取编程语言列表视图控件的位置和大小   
	m_TargetValueList.GetClientRect(&rect);
	m_TargetValueList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_TargetValueList.SetExtendedStyle(m_TargetValueList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// 为列表视图控件添加四列
	m_TargetValueList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, rect.Width() * 1 / 8, 0);
	m_TargetValueList.InsertColumn(1, _T("下限"), LVCFMT_CENTER, rect.Width() * 1 / 4, 1);
	m_TargetValueList.InsertColumn(2, _T("靶值"), LVCFMT_CENTER, rect.Width() * 1 / 4, 2);
	m_TargetValueList.InsertColumn(3, _T("上限"), LVCFMT_CENTER, rect.Width() * 1 / 4, 3);
	m_TargetValueList.InsertColumn(4, _T("单位"), LVCFMT_CENTER, rect.Width() * 1 / 8, 4);


	// 在列表视图控件中插入列表项，并设置列表子项文本
	//m_TargetValueList.InsertItem(0, _T("WBC"));
	////m_CoefficientList.InsertItem(0, _T(""));
	//m_TargetValueList.InsertItem(1, _T("平均值"));
	//m_TargetValueList.InsertItem(2, _T("CV值"));
	//m_TargetValueList.InsertItem(3, _T("当前系数"));
	//m_TargetValueList.InsertItem(4, _T("新系数"));
	for (int i = 0; i < 26; i++)
	{
		m_TargetValueList.InsertItem(i,table[i]);
	}

	m_TargetValueList.SetItemText(0, 4, L"10^9/L");
	m_TargetValueList.SetItemText(1, 4, L"%");
	m_TargetValueList.SetItemText(2, 4, L"%");
	m_TargetValueList.SetItemText(3, 4, L"%");
	m_TargetValueList.SetItemText(4, 4, L"%");
	m_TargetValueList.SetItemText(5, 4, L"%");
	m_TargetValueList.SetItemText(6, 4, L"%");
	m_TargetValueList.SetItemText(7, 4, L"%");
	m_TargetValueList.SetItemText(8, 4, L"10^9/L");
	m_TargetValueList.SetItemText(9, 4, L"10^9/L");
	m_TargetValueList.SetItemText(10, 4, L"10^9/L");
	m_TargetValueList.SetItemText(11, 4, L"10^9/L");
	m_TargetValueList.SetItemText(12, 4, L"10^9/L");
	m_TargetValueList.SetItemText(13, 4, L"10^9/L");
	m_TargetValueList.SetItemText(14, 4, L"10^9/L");
	m_TargetValueList.SetItemText(15, 4, L"10^12/L");
	m_TargetValueList.SetItemText(16, 4, L"g/L");
	m_TargetValueList.SetItemText(17, 4, L"%");
	m_TargetValueList.SetItemText(18, 4, L"fL");
	m_TargetValueList.SetItemText(19, 4, L"pg");
	m_TargetValueList.SetItemText(20, 4, L"g/L");
	m_TargetValueList.SetItemText(21, 4, L"%");
	m_TargetValueList.SetItemText(22, 4, L"10^9/L");
	m_TargetValueList.SetItemText(23, 4, L"fL");
	m_TargetValueList.SetItemText(24, 4, L"fL");
	m_TargetValueList.SetItemText(25, 4, L"%");
}



void CQualityTargetValueView::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//创建编辑框对象,IDC_EDIT_CREATEID为控件ID号3000，在文章开头定义
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createdit->SetParent(&m_TargetValueList);//将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要
	CRect  EditRect;
	m_TargetValueList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_TargetValueList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_TargetValueList.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createdit->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createdit->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createdit->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
	createdit->SetFocus();//设置为焦点 
	createdit->SetSel(-1);//设置光标在文本框文字的最后
}

void CQualityTargetValueView::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//获得相应单元格字符
	distroyedit->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}


void CQualityTargetValueView::OnNMClickQualityTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	printf("行：%d，列：%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	item_focused = pEditCtrl->iItem;
	GetDlgItem(IDC_PROJECT_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 0));
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 2));

	if (pEditCtrl->iItem == -1)//点击到非工作区
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);//销毁单元格编辑框对象
			haveeditcreate = false;
		}
	}
	else if ((pEditCtrl->iItem >= 0 && pEditCtrl->iItem <= 25) && (pEditCtrl->iSubItem ==2))//如果不是性别选项
	{
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
			{
				distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_QualityTargetEdit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
			}
			else//点中的单元格是之前创建好的
			{
				m_QualityTargetEdit.SetFocus();//设置为焦点 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createEdit(pEditCtrl, &m_QualityTargetEdit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
		}
	}
	else
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);
			haveeditcreate = false;
		}
	}
	//POSITION pos = m_TargetValueList.GetFirstSelectedItemPosition();
	//if (pos == NULL)
	//	TRACE("No items were selected!\n");
	//else
	//{
	//	int nItem = m_TargetValueList.GetNextSelectedItem(pos);
	//	TRACE1("Item %d was selected!\n", nItem);
	//	CString selectnum = m_TargetValueLists.GetItemText(nItem, 1);

	//}
	*pResult = 0;
}


void CQualityTargetValueView::GetQcLimitData()
{
	qcLjEditData.qctype = Controltype;
	qcLjEditData.filenum =Controlfile;

	USES_CONVERSION;

	strcpy(qcLjEditData.Number, W2A(tempLjNumber));
	strcpy(qcLjEditData.Deadline, W2A(tempLjDeadline));

	strcpy(qcLjEditData.wbctarget.wbc, W2A(m_TargetValueList.GetItemText(0, 3)));
	strcpy(qcLjEditData.wbctarget.lymp, W2A(m_TargetValueList.GetItemText(1, 3)));
	strcpy(qcLjEditData.wbctarget.neup, W2A(m_TargetValueList.GetItemText(2, 3)));
	strcpy(qcLjEditData.wbctarget.monop, W2A(m_TargetValueList.GetItemText(3, 3)));
	strcpy(qcLjEditData.wbctarget.eosp, W2A(m_TargetValueList.GetItemText(4, 3)));
	strcpy(qcLjEditData.wbctarget.basp, W2A(m_TargetValueList.GetItemText(5, 3)));
	strcpy(qcLjEditData.wbctarget.alyp, W2A(m_TargetValueList.GetItemText(6, 3)));
	strcpy(qcLjEditData.wbctarget.licp, W2A(m_TargetValueList.GetItemText(7, 3)));
	strcpy(qcLjEditData.wbctarget.lym, W2A(m_TargetValueList.GetItemText(8, 3)));
	strcpy(qcLjEditData.wbctarget.neu, W2A(m_TargetValueList.GetItemText(9, 3)));
	strcpy(qcLjEditData.wbctarget.mono, W2A(m_TargetValueList.GetItemText(10, 3)));
	strcpy(qcLjEditData.wbctarget.eos, W2A(m_TargetValueList.GetItemText(11, 3)));
	strcpy(qcLjEditData.wbctarget.bas, W2A(m_TargetValueList.GetItemText(12, 3)));
	strcpy(qcLjEditData.wbctarget.aly, W2A(m_TargetValueList.GetItemText(13, 3)));
	strcpy(qcLjEditData.wbctarget.lic, W2A(m_TargetValueList.GetItemText(14, 3)));
	strcpy(qcLjEditData.rbctarget.rbc, W2A(m_TargetValueList.GetItemText(15, 3)));
	strcpy(qcLjEditData.rbctarget.hgb, W2A(m_TargetValueList.GetItemText(16, 3)));
	strcpy(qcLjEditData.rbctarget.hct, W2A(m_TargetValueList.GetItemText(17, 3)));
	strcpy(qcLjEditData.rbctarget.mcv, W2A(m_TargetValueList.GetItemText(18, 3)));
	strcpy(qcLjEditData.rbctarget.mch, W2A(m_TargetValueList.GetItemText(19, 3)));
	strcpy(qcLjEditData.rbctarget.mchc,W2A(m_TargetValueList.GetItemText(20, 3)));
	strcpy(qcLjEditData.rbctarget.rdw, W2A(m_TargetValueList.GetItemText(21, 3)));
	strcpy(qcLjEditData.plttarget.plt, W2A(m_TargetValueList.GetItemText(22, 3)));
	strcpy(qcLjEditData.plttarget.mpv, W2A(m_TargetValueList.GetItemText(23, 3)));
	strcpy(qcLjEditData.plttarget.pdw, W2A(m_TargetValueList.GetItemText(24, 3)));
	strcpy(qcLjEditData.plttarget.pct, W2A(m_TargetValueList.GetItemText(25, 3)));

	strcpy(qcLjEditData.wbcsd.wbc, W2A(TargetLimit[0]));
	strcpy(qcLjEditData.wbcsd.lymp, W2A(TargetLimit[1]));
	strcpy(qcLjEditData.wbcsd.neup, W2A(TargetLimit[2]));
	strcpy(qcLjEditData.wbcsd.monop, W2A(TargetLimit[3]));
	strcpy(qcLjEditData.wbcsd.eosp, W2A(TargetLimit[4]));
	strcpy(qcLjEditData.wbcsd.basp, W2A(TargetLimit[5]));
	strcpy(qcLjEditData.wbcsd.alyp, W2A(TargetLimit[6]));
	strcpy(qcLjEditData.wbcsd.licp, W2A(TargetLimit[7]));
	strcpy(qcLjEditData.wbcsd.lym, W2A(TargetLimit[8]));
	strcpy(qcLjEditData.wbcsd.neu, W2A(TargetLimit[9]));
	strcpy(qcLjEditData.wbcsd.mono, W2A(TargetLimit[10]));
	strcpy(qcLjEditData.wbcsd.eos, W2A(TargetLimit[11]));
	strcpy(qcLjEditData.wbcsd.bas, W2A(TargetLimit[12]));
	strcpy(qcLjEditData.wbcsd.aly, W2A(TargetLimit[13]));
	strcpy(qcLjEditData.wbcsd.lic, W2A(TargetLimit[14]));
	strcpy(qcLjEditData.rbcsd.rbc, W2A(TargetLimit[15]));
	strcpy(qcLjEditData.rbcsd.hgb, W2A(TargetLimit[16]));
	strcpy(qcLjEditData.rbcsd.hct, W2A(TargetLimit[17]));
	strcpy(qcLjEditData.rbcsd.mcv, W2A(TargetLimit[18]));
	strcpy(qcLjEditData.rbcsd.mch, W2A(TargetLimit[19]));
	strcpy(qcLjEditData.rbcsd.mchc, W2A(TargetLimit[20]));
	strcpy(qcLjEditData.rbcsd.rdw, W2A(TargetLimit[21]));
	strcpy(qcLjEditData.pltsd.plt, W2A(TargetLimit[22]));
	strcpy(qcLjEditData.pltsd.mpv, W2A(TargetLimit[23]));
	strcpy(qcLjEditData.pltsd.pdw, W2A(TargetLimit[24]));
	strcpy(qcLjEditData.pltsd.pct, W2A(TargetLimit[25]));
}

void CQualityTargetValueView::OnQualitytargetConfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_QUALITY_NUMBER)->GetWindowText(tempLjNumber);
	GetDlgItem(IDC_QUALITY_DEADLINE)->GetWindowText(tempLjDeadline);
	if (tempLjNumber == "" || tempLjDeadline == "")
	{
		MessageBox(L"信息不能为空!",L"警告!");
		return;
	}
	for (int i = 0; i < 26; i++)
	{
		if (_wtof(m_TargetValueList.GetItemText(i, 3))<0.00001)
		{
			MessageBox(L"靶值不能为0!", L"警告!");
			return;
		}
		if (_wtof(TargetLimit[i]) < 0.00001)
		{
			MessageBox(L"偏差值不能为0!", L"警告!");
			return;
		}
	}
	GetQcLimitData();

	if (QcLjFileExist == 1)
		//CreateQcLjEditFileExistDlg(hDlg, &qcLjEditData, &rc);
	{
		CDialog  m_QualityFileExitDlg;
		m_QualityFileExitDlg.DoModal();
	}
	else//文件未使用
		rc = QcLjXXrEditFileAdd(&qcLjEditData);

	if (rc == 0)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"保存成功",L"提示", MB_OK | MB_ICONINFORMATION);
		//else if (systemcfg.language == ENGLISH)
		//	CreateWarningBoxNonCHDlg(hDlg, "Successfully", "Presentation");
	}
	else if (rc != -5)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"保存失败",L"提示", MB_OK | MB_ICONINFORMATION);
	/*	else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed", "Presentation");*/
	}
}


void CQualityTargetValueView::OnRangeConfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	CString Content;
	
	
	
	USES_CONVERSION;
	GetDlgItem(IDC_PROJECTRANGE_EDIT)->GetWindowText(Content);
	if (Content == "")
	{
		MessageBox(L"限制范围输入为空");
		return;
	}
	if (!JudgmentValid(Content))
	{
		return;
	}
	TargetLimit[item_focused] = Content;
	CString targettemp;
	float   TargetLimit1, TargetLimit2;
	CString CTargetLimit1, CTargetLimit2;
	targettemp=m_TargetValueList.GetItemText(item_focused, 2);
	TargetLimit1=_wtof(targettemp) - _wtof(Content);
	TargetLimit2=_wtof(targettemp) + _wtof(Content);
	CTargetLimit1.Format(L"%.2f",TargetLimit1);
	CTargetLimit2.Format(L"%.2f",TargetLimit2);

	m_TargetValueList.SetItemText(0, 1, CTargetLimit1);
	m_TargetValueList.SetItemText(0, 3, CTargetLimit2);
}

bool CQualityTargetValueView::JudgmentValid(CString Content)
{
	char temp[10];
	int  temp_len;
	int	 dot_count;
	USES_CONVERSION;
	sprintf(temp, "%s", W2A(Content));
	temp_len = strlen(temp);
	dot_count = 0;
	for (int j = 0; j < temp_len; j++)
	{
		if ((temp[j] >= '0' && temp[j] <= '9') || temp[j] == '.')
		{
			if (temp[j] == '.')
				dot_count++;
			if (dot_count > 1)
			{
				if (systemcfg.language == CHINESE)
					MessageBox(L"小数点个数过多!", L"警告!", MB_OK | MB_ICONINFORMATION);
				//else if (systemcfg.language == ENGLISH)
				//	CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Only one dot is permitted!", "Warning!");
				return false;
			}
		}
		else
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"请输入合法字符!", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input legal number!", "Warning!");*/
			return false;
		}
	}
	return true;
}


bool CQualityTargetValueView::GetQcFile()
{

	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	int temprow;

	qctypetemp.Format( L"%d",Controltype);
	qcFileNumtemp.Format(L"%d",Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp +"'and filenum ='" + qcFileNumtemp + "';";
	if (OpenDataBase(filename, m_pDB, m_pRs) != -1)
	{
		temprow = int(m_pRs->GetRecordCount());
		if (temprow == 0)
		{
			QcLjFileExist = 0;
			tempLjNumber="";
			tempLjDeadline="";
			for (int i = 0; i < 26; i++)
			{
				Qctarget[26]="";
				TargetLimit[26]="";
			}
		}
		else
		{
			QcLjFileExist = 1;
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("number");
				tempLjNumber.Format(L"%d",qctype);
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("deadline");
				tempLjDeadline.Format(L"%d", qctype);
			}
			for (int j = 0; j < 26;j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j+5)->Value;//读取当前记录质控26个项目的靶值
				Qctarget[j] = var;
			}
			for (int j = 0; j < 26; j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j +26+ 5)->Value;//读取当前记录质控26个项目的偏差值
				TargetLimit[j]=var;
			}
		}
		CloseDataBase(m_pDB, m_pRs);
		return true;
	}
	else return false;
	//int rc;
	//unsigned int i;
	//unsigned nRow = 0, nColumn = 0;
	//unsigned int tempRow = 0;
	//static char **dbResult;
	//static char *zErrMsg = NULL;
	//char *zStatement = NULL;
	//char inital_target[] = "select * from qceditdata where qctype = %d and filenum = %d;";
	//if (OpenDataBase(DATABASE_PATH, &db) == -1)
	//	return -1;
	//zStatement = sqlite3_mprintf(inital_target, 1, QcLjFileNum);
	//rc = sqlite3_get_table(db, zStatement, &dbResult, &nRow, &nColumn, &zErrMsg);
	//sqlite3_free(zStatement);
	//zStatement = NULL;
	//CloseDataBase(db);
	//if (SQLITE_OK != rc)
	//{
	//	printf("SQL error: %s---------!\n", zErrMsg);
	//	sqlite3_free_table(dbResult);
	//	return -1;
	//}
	//else
	//{
	//	tempRow = nRow;
	//}
	//if (tempRow == 0)
	//{
	//	QcLjFileExist = 0;
	//	strcpy(tempLjNumber, "");
	//	strcpy(tempLjDeadline, "");
	//	for (i = 0; i < 52; i++)
	//		strcpy(qcLjParam[i], "");
	//}
	//else//将对应质控方式对应文件的数据读出来
	//{
	//	QcLjFileExist = 1;
	//	strcpy(tempLjNumber, dbResult[nColumn + 2]);
	//	strcpy(tempLjDeadline, dbResult[nColumn + 3]);
	//	for (i = 4; i < 56; i++)
	//		strcpy(qcLjParam[i - 4], dbResult[nColumn + i]);    //nColumn*tempRow+i	
	//}
}
	