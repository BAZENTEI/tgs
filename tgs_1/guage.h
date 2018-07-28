//=============================================================================
//
// ポリゴン処理 [gauge.h]
// Author : 
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

#define GUAGE_TEXTURE						_T("data/TEXTURE/gradient.png")	// サンプル用画像
#define GUAGE_TEXTURE_SIZE_X				(128) // テクスチャサイズ
#define GUAGE_TEXTURE_SIZE_Y				(16) // 同上
		
#define GUAGE_TEXTURE_DIVIDE_X				(1)	// アニメパターンのテクスチャ内分割数（X)
#define GUAGE_TEXTURE_DIVIDE_Y				(1)	// アニメパターンのテクスチャ内分割数（Y)
		
#define GUAGE_WIDTH							(GUAGE_TEXTURE_SIZE_X / GUAGE_TEXTURE_DIVIDE_X)

//HRESULT InitGuage(void);
//void DrawGuage(void);
//void UpdateGuage(void);
//void UninitGuage(void);

#endif // !_SCORE_H_
