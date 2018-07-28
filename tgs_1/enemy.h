//=============================================================================
//
// ポリゴン処理 [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量

	BOOL					use;						// 出るかどうか
	INT						value;

	UINT					nCountAnim;					// アニメーションカウント
	UINT					nPatternAnim;				// アニメーションパターンナンバー

	VERTEX_2D				vtxWk[NUM_VERTEX];			// 頂点情報格納ワーク
} ENEMY;

// マクロ定義
#define ENEMY_TEXTURE					_T("data/TEXTURE/runningman001.png")	// サンプル用画像
#define ENEMY_TEXTURE_SIZE_X			(140) // テクスチャサイズ
#define ENEMY_TEXTURE_SIZE_Y			(200) // 同上

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ENEMY_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント

#define ENEMY_MAX						(3)
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
