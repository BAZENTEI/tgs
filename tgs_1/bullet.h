//=============================================================================
//
// ポリゴン処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct {

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量

	BOOL					use;						// 出るかどうか

	VERTEX_2D				wk[NUM_VERTEX];		// 頂点情報格納ワーク
} BULLET;

// マクロ定義
#define BULLET_TEXTURE_GAME_SAMPLE00		_T("data/TEXTURE/tama.png")	// サンプル用画像
#define BULLET_TEXTURE_SIZE_X				(32) // テクスチャサイズ
#define BULLET_TEXTURE_SIZE_Y				(32) // 同上

#define BULLET_MAX							(20)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(int bid);

void RemoveBullet(BULLET* bullet);

#endif
