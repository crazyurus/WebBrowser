// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
    void ChangeAddr(CString);
// 特性
public:
    CMFCRibbonLabel *StatusBar;
    CMFCRibbonProgressBar *ProgressBar;
    BOOL isForward;
    BOOL isBack;
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCCaptionBar    m_wndCaptionBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	DECLARE_MESSAGE_MAP()

	BOOL CreateCaptionBar();
public:
    afx_msg void OnAdd();
    afx_msg void OnAddr();
    afx_msg double GetZoom();
    afx_msg void SetProgress(long value,long max);
protected:
    afx_msg LRESULT OnNewUrl(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnZoom();
    afx_msg void SetStatusText(LPCTSTR str);
    afx_msg void OnClose();
    afx_msg void ButtonEnable(CCmdUI *pCmdUI);
    afx_msg void SetButtonState(BOOL,BOOL);
    afx_msg void OnButtonSystem();
};


