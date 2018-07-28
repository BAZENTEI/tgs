//=============================================================================
//
// ポリゴン処理 [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

// マクロ定義
#define ENEMY_TEXTURE					_T("data/texture/enemy.png")	// サンプル用画像
#define ENEMY_TEXTURE_SIZE_X			(128) // テクスチャサイズ
#define ENEMY_TEXTURE_SIZE_Y			(32) // 同上

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(4)	// アニメパターンのテクスチャ内分割数（X)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ENEMY_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント

#define ENEMY_MAX						(10)

typedef struct {

	BOOL					use;						// 出るかどうか
	INT						x;
	INT						y;
	INT						nMap;

	UINT					nCountAnim;					// アニメーションカウント

	VERTEX_2D				vtxWk[NUM_VERTEX];			// 頂点情報格納ワーク
} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(int);

void RemoveEnemy(ENEMY*);

#endif
