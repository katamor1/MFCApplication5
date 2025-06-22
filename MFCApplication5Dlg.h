
// MFCApplication5Dlg.h : ヘッダー ファイル
//

#pragma once


// CMFCApplication5Dlg ダイアログ
class CMFCApplication5Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCApplication5Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
	CEdit m_editData; // データ表示用のエディットコントロール

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonGetData(); // ボタンクリックハンドラ
	afx_msg void OnBnClickedButtonSetData(); // ボタンクリックハンドラ
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct); // データ受信ハンドラ

	DECLARE_MESSAGE_MAP()
};
