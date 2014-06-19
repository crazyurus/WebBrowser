// MyView.cpp : CMyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WebBrowser.h"
#endif

#include "WebBrowserDoc.h"
#include "MyView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NEWURL WM_USER+104
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyView, CHtmlView)
	// 标准打印命令
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_COMMAND(ID_EDIT_BACK, &CMyView::OnEditBack)
    ON_COMMAND(ID_EDIT_FORWARD, &CMyView::OnEditForward)
    ON_COMMAND(ID_EDIT_REFRESH, &CMyView::OnEditRefresh)
    ON_COMMAND(ID_EDIT_STOP, &CMyView::OnEditStop)
    ON_COMMAND(ID_EDIT_HOME, &CMyView::OnEditHome)
    ON_COMMAND(ID_FILE_SELECT, &CMyView::OnFileSelect)
    ON_COMMAND(ID_FILE_FIND, &CMyView::OnFileFind)
    ON_COMMAND(ID_FILE_SAVE, &CMyView::OnFileSave)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMyView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyView::OnFilePrintPreview)
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CMyView::OnFilePrintSetup)
    ON_COMMAND(ID_SLIDER2, &CMyView::OnSlider)
    ON_COMMAND(ID_BUTTON17, &CMyView::OnColor)
    ON_COMMAND(ID_B_HAO123, &CMyView::OnBHao123)
    ON_COMMAND(ID_B_BAIDU, &CMyView::OnBBaidu)
    ON_COMMAND(ID_B_GOOGLE, &CMyView::OnBGoogle)
    ON_COMMAND(ID_B_BING, &CMyView::OnBBing)
    ON_COMMAND(ID_B_TENCENT, &CMyView::OnBTencent)
    ON_COMMAND(ID_B_163, &CMyView::OnB163)
    ON_COMMAND(ID_B_TAOBAO, &CMyView::OnBTaobao)
    ON_COMMAND(ID_B_JD, &CMyView::OnBJd)
    ON_COMMAND(ID_B_AMZ, &CMyView::OnBAmz)
    ON_COMMAND(ID_B_WEIBO, &CMyView::OnBWeibo)
    ON_COMMAND(ID_B_TQQ, &CMyView::OnBTqq)
    ON_COMMAND(ID_B_QZONE, &CMyView::OnBQzone)
    ON_COMMAND(ID_B_RENREN, &CMyView::OnBRenren)
    ON_COMMAND(ID_B_WHUT, &CMyView::OnBWhut)
    ON_COMMAND(ID_B_WUTNEWS, &CMyView::OnBWutnews)
    ON_COMMAND(ID_B_XUAN, &CMyView::OnBXuan)
END_MESSAGE_MAP()

// CMyView 构造/析构

CMyView::CMyView()
{
    isBack=isForward=FALSE;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CHtmlView::PreCreateWindow(cs);
}

void CMyView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	OnEditHome();
    SetSilent(TRUE);
}


// CMyView 打印

void CMyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyView 诊断

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CWebBrowserDoc* CMyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebBrowserDoc)));
	return (CWebBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

void CMyView::GetMainFrame()
{   //获取主框架并记录
    pChildFrame=(CChildFrame*)GetParentFrame();
    if(pChildFrame) pMainFrame=(CMainFrame*)pChildFrame->GetParentFrame();
}

// CMyView 消息处理程序
void CMyView::OnEditBack()
{  //浏览器后退
    if(isBack) GoBack();
    else MessageBox(L"Crazy Urus 浏览器不能后退到前一个页面！",L"Crazy Urus 浏览器",MB_ICONWARNING);
}

void CMyView::OnEditForward()
{  //浏览器前进
    if(isForward) GoForward();
    else MessageBox(L"Crazy Urus 浏览器不能前进到指定页面！",L"Crazy Urus 浏览器",MB_ICONWARNING);
}

void CMyView::OnEditRefresh()
{  //浏览器刷新
    Refresh();
}

void CMyView::OnEditStop()
{  //浏览器停止
    Stop();
}

void CMyView::OpenUrl(CString url)
{  //浏览器访问url
    Navigate(url,NULL,NULL);
}

void CMyView::OnEditHome()
{  //浏览器打开百度
    OpenUrl(L"http://www.baidu.com");
}

void CMyView::OnDocumentComplete(LPCTSTR lpszURL)
{  //浏览器加载完成
    CComPtr<IHTMLDocument2> pDoc = (IHTMLDocument2*)this->GetHtmlDocument();
    BSTR *bstrTitle;
    pDoc->get_title(bstrTitle);
    CString title;
    title.Empty();
    title=*bstrTitle;
    title=title.Left(20);
    GetMainFrame();
    //设置当前子框架标题
    pChildFrame->SetWindowText(title);
    //设置地址栏
    pMainFrame->ChangeAddr(GetLocationURL());
    //设置主框架标题
    pMainFrame->UpdateFrameTitleForDocument(title);
    CHtmlView::OnDocumentComplete(lpszURL);
}

void CMyView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{   //浏览器弹出新窗口（自定义消息）
    ::SendMessage(AfxGetMainWnd()->m_hWnd,WM_NEWURL,(WPARAM)ppDisp,NULL);
    *Cancel=TRUE;
    CHtmlView::OnNewWindow2(ppDisp, Cancel);
}

void CMyView::OnFileSelect()
{  //全选
    SetFocus();
    ExecWB(OLECMDID_SELECTALL,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFileFind()
{  //查找
    ExecWB(OLECMDID_FIND,OLECMDEXECOPT_DODEFAULT,NULL,NULL); 
}

void CMyView::OnFileSave()
{  //另存为
    ExecWB(OLECMDID_SAVEAS,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrint()
{  //打印
    ExecWB(OLECMDID_PRINT,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrintPreview()
{  //打印预览
    ExecWB(OLECMDID_PRINTPREVIEW,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrintSetup()
{  //页面设置
    ExecWB(OLECMDID_PAGESETUP,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnSlider()
{  //页面缩放
    GetMainFrame();
    double fZoom=pMainFrame->GetZoom();
    CComPtr<IHTMLDocument2> pDoc = (IHTMLDocument2*)this->GetHtmlDocument();
    ASSERT(pDoc);
    CComPtr<IHTMLElement> pElem;
    pDoc->get_body(&pElem);
    ASSERT(pElem);
    CComPtr<IHTMLStyle> pStyle;
    pElem->get_style(&pStyle);
    CString str;
    str.Format(L"zoom:%f;",fZoom);
    pStyle->put_cssText(str.AllocSysString());
}

void CMyView::OnStatusTextChange(LPCTSTR lpszText)
{  //浏览器状态改变，修改程序的状态栏（有Bug）
    GetMainFrame();
    if(pMainFrame) pMainFrame->SetStatusText(lpszText);
    CHtmlView::OnStatusTextChange(lpszText);
}

void CMyView::OnProgressChange(long nProgress, long nProgressMax)
{  //浏览器进度改变，修改程序的进度条
    GetMainFrame();
    if(pMainFrame) pMainFrame->SetProgress(nProgress,nProgressMax);
    CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CMyView::OnCommandStateChange(long nCommand, BOOL bEnable)
{   //设置按钮状态
    if(pMainFrame)
        if(nCommand==CSC_NAVIGATEFORWARD) isForward=bEnable;
        else if(nCommand==CSC_NAVIGATEBACK) isBack=bEnable;
    GetMainFrame();
    pMainFrame->SetButtonState(isForward,isBack);
    CHtmlView::OnCommandStateChange(nCommand, bEnable);
}

void CMyView::OnColor()
{
}

void CMyView::OnBHao123()
{
    OpenUrl(L"http://www.hao123.com/");
}

void CMyView::OnBBaidu()
{
    OpenUrl(L"http://www.baidu.com/");
}

void CMyView::OnBGoogle()
{
    OpenUrl(L"http://www.google.com/");
}

void CMyView::OnBBing()
{
    OpenUrl(L"http://cn.bing.com/");
}

void CMyView::OnBTencent()
{
    OpenUrl(L"http://www.qq.com/");
}

void CMyView::OnB163()
{
    OpenUrl(L"http://www.163.com/");
}

void CMyView::OnBTaobao()
{
    OpenUrl(L"http://www.taobao.com/");
}

void CMyView::OnBJd()
{
    OpenUrl(L"http://www.jd.com/");
}

void CMyView::OnBAmz()
{
    OpenUrl(L"http://www.z.cn/");
}

void CMyView::OnBWeibo()
{
    OpenUrl(L"http://www.weibo.com/");
}

void CMyView::OnBTqq()
{
    OpenUrl(L"http://t.qq.com/");
}

void CMyView::OnBQzone()
{
    OpenUrl(L"http://qzone.qq.com/");
}

void CMyView::OnBRenren()
{
    OpenUrl(L"http://www.renren.com/");
}

void CMyView::OnBWhut()
{
    OpenUrl(L"http://www.whut.edu.cn/");
}

void CMyView::OnBWutnews()
{
    OpenUrl(L"http://www.wutnews.net/");
}

void CMyView::OnBXuan()
{
    OpenUrl(L"http://xuan.wutnews.net/");
}
