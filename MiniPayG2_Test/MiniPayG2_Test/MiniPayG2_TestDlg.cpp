// MiniPayG2_TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiniPayG2_Test.h"
#include "MiniPayG2_TestDlg.h"
#include "TestItem.h"
#include "PCSC.h"
#include "SmartCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT MyThread(LPVOID pParam);
CWinThread * pMyThread;

int g_itemCount = 0;


ListInfo g_TestInfo[] = 
{
	{0, _T(" A- USB"), TEST_USB, _T(""), _T("����ʧ��")},
	{1, _T(" B- SPI"), TEST_SPI, _T(""), _T("����ʧ��")},
	{2,_T(" C- SAM��"), TEST_SAM, _T(""), _T("����ʧ��")},
	{3, _T(" D- ������"), TEST_BUZZER, _T(""), _T("����ʧ��")},
	{4, _T(" E- LCD�Աȶ�"), TEST_LCDLevel, _T(""), _T("����ʧ��")},
	{5, _T(" F- LCD����"), TEST_LCDBackLight, _T(""), _T("����ʧ��")},
	{6,_T(" G- ����"), TEST_KeyBoard, _T(""), _T("����ʧ��")},
	{7, _T(" H- �Ӵ���"), TEST_ICC, _T(""), _T("��鿨Ƭ")},
	{8,_T(" I- �ǽӿ�"), TEST_PICC, _T(""), _T("��鿨Ƭ")},
	{0,_T(""),NULL,_T(""),_T("")}

};







// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMiniPayG2_TestDlg �Ի���




CMiniPayG2_TestDlg::CMiniPayG2_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiniPayG2_TestDlg::IDD, pParent)
	, m_Info_out(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniPayG2_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_dev);
	DDX_Control(pDX, IDC_LIST2, m_list_test);
	DDX_Control(pDX, IDC_EDIT1, m_edit_info);
	DDX_Text(pDX, IDC_EDIT1, m_Info_out);
}

BEGIN_MESSAGE_MAP(CMiniPayG2_TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CMiniPayG2_TestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK1, &CMiniPayG2_TestDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMiniPayG2_TestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMiniPayG2_TestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMiniPayG2_TestDlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CMiniPayG2_TestDlg::OnLbnDblclkList1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMiniPayG2_TestDlg ��Ϣ�������

BOOL CMiniPayG2_TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData(TRUE);
	m_Info_out = "�������㸶   �������Գ���\r\n";	
	m_Info_out += "_________________________________________________________\r\n";


	m_Font.CreateFont(
		15,							// nHeight
		0,							// nWidth
		0,							// nEscapement
		0,							// nOrientation
		FW_BLACK,				// nWeight
		FALSE,						// bItalic
		FALSE,						// bUnderline
		0,							// cStrikeOut
		GB2312_CHARSET,				// nCharSet
		//ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH  | FF_SWISS,	// nPitchAndFamily
		_T("����")					// lpszFacename
		);



    if(!m_tip.Create(this, TTS_ALWAYSTIP));
	m_tip.SetFont(&m_Font);
	m_tip.AddTool(GetDlgItem(IDC_LIST1), "˫��ˢ�³������豸����,�������豸");
    m_tip.AddTool(GetDlgItem(IDC_LIST2), "���ѡ�����Ϊѡ�У��ɶ�ѡ");


	CListBox *m_ListInfo = (CListBox *)GetDlgItem(IDC_LIST2);
	m_ListInfo->SetFont(&m_Font,TRUE);


	for( int i = 0; ; i++)
	{
        if(g_TestInfo[i].strName == _T(""))
			break;

        m_list_test.AddString(g_TestInfo[i].strName);
	}

	GetDlgItem(IDC_EDIT1)->SetFont(&m_Font);
	GetDlgItem(IDC_EDIT_CONTACTLESS)->SetFont(&m_Font);
	SetDlgItemText(IDC_EDIT_CONTACTLESS, _T("״̬"));
    GetDlgItem(IDC_LIST2)->SetFocus();
	UpdateData(FALSE);
	 
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMiniPayG2_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMiniPayG2_TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMiniPayG2_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT MyThread(LPVOID pParam)
{
	CMiniPayG2_TestDlg *pDlg = (CMiniPayG2_TestDlg *)pParam;

	pDlg->Test();
	return 0;
}

void CMiniPayG2_TestDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
    g_itemCount = 0;
    UpdateData(TRUE);
	g_itemCount= m_list_test.GetSelCount();  
    UpdateData(FALSE);


    pMyThread = AfxBeginThread(MyThread, this);
}


BOOL CMiniPayG2_TestDlg::Test()
{
	int i, j;
	BOOL bRet = FALSE;
	BOOL bChoose = FALSE;

	CArray<int,int> aryListBoxSel; 
	aryListBoxSel.SetSize(g_itemCount);
	m_list_test.GetSelItems(g_itemCount, aryListBoxSel.GetData());   //��ȡѡ�е���Ϣ
    CString selStr;
	CString str;
	for (i=0; i<g_itemCount;i++)
	{   
		selStr = "";
		m_list_test.GetText(aryListBoxSel[i],selStr);

		for(j = 0; j < (sizeof(g_TestInfo)/sizeof(ListInfo)); j++)
		{
			if(selStr.Compare(g_TestInfo[j].strName) ==0)
			{
			   
			bChoose = TRUE;
			str = _T("");
			bRet = g_TestInfo[j].func(str);

			if(bRet != TRUE)
			{
				 AddInfo(str,TRUE,TRUE,TRUE,TRUE);
				  goto END;
			}
			else
			{ 
				 AddInfo(str,TRUE,TRUE,TRUE,TRUE);
				 break;
		    }
			
			}

			if( j == sizeof(g_TestInfo) / sizeof(ListInfo))
			{
				str ="����, δ�ҵ��ò�����\r\n";
				AddInfo(str,TRUE,TRUE,TRUE,TRUE);
				goto END;
			}
		}
	}


	if(!bChoose)
	{   
	 str = "��ѡ�������\r\n";
	 AddInfo(str,TRUE,TRUE,TRUE,TRUE);
	return FALSE;
	}

END:
	return TRUE;
}



void CMiniPayG2_TestDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
	{
		for( int i = 0; ; i++)
		{
			if(g_TestInfo[i].strName == _T(""))
				break;
			m_list_test.SetSel(i, TRUE);
		}
	}
	else
	{
		for( int i = 0; ; i++)
		{
			if(g_TestInfo[i].strName == _T(""))
				break;
			m_list_test.SetSel(i, FALSE);
		}
	}
	UpdateData(FALSE);
}

void CMiniPayG2_TestDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_edit_info.SetWindowText("");
}

void CMiniPayG2_TestDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_BUTTON4, str);
    if(str == _T("��ʼä������"))
	{
		SetDlgItemText(IDC_BUTTON4, _T("����ä������"));
		SetTimer(1,100,NULL);

	}else if(str == _T("����ä������"))
	{
		SetDlgItemText(IDC_BUTTON4, _T("��ʼä������"));  
	    KillTimer(1);
		SetDlgItemText(IDC_EDIT_CONTACTLESS, "״̬");
	}
    
}

void CMiniPayG2_TestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
    UpdateDev();
}

void CMiniPayG2_TestDlg::UpdateDev()
{

	LPTSTR pReader;
	DWORD dwResult = 0;
	int temp = 0;
	CString cStr;
	pReader = (LPTSTR)ReaderName;
	
	UpdateData(TRUE);
	m_list_dev.ResetContent();
	dwResult = SCard_UpdateDevice();
	if(SCARD_S_SUCCESS == dwResult)
	{
		while(*pReader != 0)
		{
			m_list_dev.InsertString(-1, pReader);
			pReader = pReader +50;
		}

	}
	else
	{

		cStr = "ע��:û�м�⵽�豸������\r\n";
		cStr += "1����ȷ�϶������Ƿ���ȷ�����˵��ԡ�\r\n";
		cStr += "2������ڶ���������ȷ���ӵ��Ե�����£�����USB�豸��usb�ӿ��Ƿ�ɹ��ĺ���";
		AddInfo(cStr, TRUE, TRUE, TRUE, TRUE);
	}

	UpdateData(FALSE);	
}
void CMiniPayG2_TestDlg::OnLbnDblclkList1()
{
	// TODO: Add your control notification handler code here
	BYTE pbReadName[256] = {0};
	DWORD  dwResult = 0;
	DWORD  dwAP = 0;
	BYTE bATR[64] = {0};
	CString csATR;


	int iItemPos = m_list_dev.GetCurSel();
	if(iItemPos == CB_ERR)
	{
		MessageBox("NO Device");
		return;
	}
	m_list_dev.GetText(iItemPos, (char *)pbReadName);
	dwResult = SCard_Connect((LPCTSTR)pbReadName, bATR);
	if(SCARD_S_SUCCESS == dwResult)
	{

		AddInfo(("�����豸�ɹ�"), TRUE, TRUE, TRUE, TRUE);	
	}
	else
	{
		AddInfo(("�����豸ʧ�ܣ�����"), TRUE, TRUE, TRUE, TRUE);
	}



}



void CMiniPayG2_TestDlg::AddInfo(CString str, BOOL addtime, BOOL newline, BOOL upline, BOOL downline)
{

	((CEdit *)GetDlgItem(IDC_EDIT1))->SetSel(-1);
	char time[10];
	CString tempstr;
	CString Msg;
	DWORD i;
	static DWORD n = 0;
    Msg = "";

	if(TRUE == upline)
	{
		n++;
		tempstr.Format("%d", n);
		Msg += _T("\r\n");
		Msg += _T("INFO��");
		Msg += tempstr;
		Msg += _T("\r\n\r\n");
	}


	Msg += str;

	if(TRUE == addtime)
	{
		_strtime(time);
		tempstr = time;

		Msg += _T("(") + tempstr + _T(")");
	}

	if(TRUE == newline)
	{
		Msg += _T("\r\n");

	}

	if(TRUE == downline)
	{

		Msg += _T("_________________________________________________________\r\n");
	}

	i = m_edit_info.GetLineCount();
	m_edit_info.LineScroll(i, 0);
	m_edit_info.ReplaceSel(Msg);

}
BOOL CMiniPayG2_TestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_tip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}


void CMiniPayG2_TestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	BOOL  bReturn = FALSE;
	
	bReturn = CheckPICC();	

	if(bReturn == TRUE)
	{   
		SetDlgItemText(IDC_EDIT_CONTACTLESS, "�п�");
	}
	else 
	{
		SetDlgItemText(IDC_EDIT_CONTACTLESS, "�޿�");
	}	

	CDialog::OnTimer(nIDEvent);
}
