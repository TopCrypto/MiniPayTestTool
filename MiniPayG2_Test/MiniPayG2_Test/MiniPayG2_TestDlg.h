// MiniPayG2_TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

typedef BOOL(*fun_ptr)(CString&str);

typedef struct _listInfo{
    UINT nindex;           // 索引
	CString strName;       // 测试项名称
	fun_ptr func;          // 测试函数
	CString strPCInfo;     //PC提示信息
	CString strErrorInfo;  //错误信息
}ListInfo;


// CMiniPayG2_TestDlg 对话框
class CMiniPayG2_TestDlg : public CDialog
{
// 构造
public:
	CMiniPayG2_TestDlg(CWnd* pParent = NULL);	// 标准构造函数

    CFont  m_Font;
    CToolTipCtrl m_tip;


// 对话框数据
	enum { IDD = IDD_MINIPAYG2_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
   

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
