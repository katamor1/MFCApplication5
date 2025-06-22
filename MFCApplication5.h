
// MFCApplication5.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCApplication5App:
// このクラスの実装については、MFCApplication5.cpp を参照してください
//

class CMFCApplication5App : public CWinApp
{
public:
	CMFCApplication5App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication5App theApp;
