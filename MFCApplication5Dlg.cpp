
// MFCApplication5Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5Dlg ダイアログ



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editData);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA, &CMFCApplication5Dlg::OnBnClickedButtonGetData) // ボタンのIDをIDC_BUTTON_GET_DATAと仮定
	ON_BN_CLICKED(IDC_BUTTON_SET_DATA, &CMFCApplication5Dlg::OnBnClickedButtonSetData) // この行を追加
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// [データを取得]ボタンのクリックハンドラ
void CMFCApplication5Dlg::OnBnClickedButtonGetData()
{
	// ウィンドウタイトルを元にMFCApplication4のウィンドウハンドルを探す
	// MFCApplication4DlgのOnInitDialogでSetWindowTextを使ってウィンドウタイトルを設定しておく必要があります
	HWND hApp4Wnd = ::FindWindow(NULL, _T("MFCApplication4")); // タイトルはアプリAの実装に合わせる

	if (hApp4Wnd == NULL)
	{
		AfxMessageBox(_T("MFCApplication4が見つかりません。"));
		return;
	}

	// 送信するデータを準備
	COPYDATASTRUCT requestData;
	requestData.dwData = 1; // 1: テキスト要求コマンド
	requestData.cbData = 0;
	requestData.lpData = NULL;

	// WM_COPYDATAメッセージを送信
	// wParamに自ウィンドウのハンドルを渡し、応答先を知らせる
	// SendMessageは同期的なので、相手からの応答が返るまで処理はブロックされる
	::SendMessage(hApp4Wnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&requestData);
}

void CMFCApplication5Dlg::OnBnClickedButtonSetData()
{
	// ウィンドウタイトルを元にMFCApplication4のウィンドウハンドルを探す
	HWND hApp4Wnd = ::FindWindow(NULL, _T("MFCApplication4"));

	if (hApp4Wnd == NULL)
	{
		AfxMessageBox(_T("MFCApplication4が見つかりません。"));
		return;
	}

	// エディットボックスから設定したい文字列を取得
	CString strToSend;
	GetDlgItemText(IDC_EDIT1, strToSend);

	if (strToSend.IsEmpty())
	{
		AfxMessageBox(_T("設定する文字列を入力してください。"));
		return;
	}

	// 送信するデータを準備
	COPYDATASTRUCT setData;
	setData.dwData = 3; // 3: テキスト設定コマンド
	setData.cbData = (strToSend.GetLength() + 1) * sizeof(TCHAR);
	setData.lpData = (PVOID)strToSend.GetString();

	// WM_COPYDATAメッセージを送信
	// 今回は応答を待たないので、戻り値は確認不要
	::SendMessage(hApp4Wnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&setData);
}
// WM_COPYDATA メッセージのハンドラ (応答データ受信)
BOOL CMFCApplication5Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// 2: テキスト応答コマンドか確認
	if (pCopyDataStruct->dwData == 2)
	{
		// 受信したデータをCStringに変換
		CString strReceived((LPCTSTR)pCopyDataStruct->lpData);
		m_editData.SetWindowText(strReceived);
		return TRUE;
	}

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
// CMFCApplication5Dlg メッセージ ハンドラー

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

