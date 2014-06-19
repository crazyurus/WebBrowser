// MyView.h : CMyView 类的接口
//
#include "MainFrm.h"
#include "ChildFrm.h"

#pragma once

class CMyView : public CHtmlView
{
protected: // 仅从序列化创建
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// 特性
public:
	CWebBrowserDoc* GetDocument() const;
    CMainFrame *pMainFrame;
    CChildFrame *pChildFrame;
    BOOL isBack;
    BOOL isForward;
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEditBack();
    afx_msg void OnEditForward();
    afx_msg void OnEditRefresh();
    afx_msg void OnEditStop();
    afx_msg void OnEditHome();
    afx_msg void OnAdd();
    virtual void OnDocumentComplete(LPCTSTR lpszURL);
    void OpenUrl(CString);
    virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
    afx_msg void OnFileSelect();
    afx_msg void OnFileFind();
    afx_msg void OnFileSave();
    afx_msg void OnFilePrint();
    afx_msg void OnFilePrintSetup();
    afx_msg void OnSlider();
    virtual void OnStatusTextChange(LPCTSTR lpszText);
    virtual void OnProgressChange(long nProgress, long nProgressMax);
    virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
    void GetMainFrame();
    afx_msg void OnColor();
    afx_msg void OnBHao123();
    afx_msg void OnBBaidu();
    afx_msg void OnBGoogle();
    afx_msg void OnBBing();
    afx_msg void OnBTencent();
    afx_msg void OnB163();
    afx_msg void OnBTaobao();
    afx_msg void OnBJd();
    afx_msg void OnBAmz();
    afx_msg void OnBWeibo();
    afx_msg void OnBTqq();
    afx_msg void OnBQzone();
    afx_msg void OnBRenren();
    afx_msg void OnBWhut();
    afx_msg void OnBWutnews();
    afx_msg void OnBXuan();
};

#ifndef _DEBUG  // MyView.cpp 中的调试版本
inline CWebBrowserDoc* CMyView::GetDocument() const
   { return reinterpret_cast<CWebBrowserDoc*>(m_pDocument); }
#endif

