// MiniPayG2_TestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

typedef BOOL(*fun_ptr)(CString&str);

typedef struct _listInfo{
    UINT nindex;           // ����
	CString strName;       // ����������
	fun_ptr func;          // ���Ժ���
	CString strPCInfo;     //PC��ʾ��Ϣ
	CString strErrorInfo;  //������Ϣ
}ListInfo;


// CMiniPayG2_TestDlg �Ի���
class CMiniPayG2_TestDlg : public CDialog
{
// ����
public:
	CMiniPayG2_TestDlg(CWnd* pParent = NULL);	// ��׼���캯��

    CFont  m_Font;
    CToolTipCtrl m_tip;


// �Ի�������
	enum { IDD = IDD_MINIPAYG2_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
   

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();

	
	CListBox m_list_dev;
	CListBox m_list_test;
	CEdit m_edit_info;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	void UpdateDev();
	BOOL Test();
	afx_msg void OnLbnDblclkList1();
	void AddInfo(CString str, BOOL addtime, BOOL newline, BOOL upline, BOOL downline);
	CString m_Info_out;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
