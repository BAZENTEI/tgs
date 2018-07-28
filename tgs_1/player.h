//=============================================================================
//
// ポリゴン処理 [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// マクロ定義
#define PLAYER_TEXTURE						_T("data/texture/player.png")	// サンプル用画像
#define PLAYER_TEXTURE_SIZE_X				(128) // テクスチャサイズ
#define PLAYER_TEXTURE_SIZE_Y				(32) // 同上

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X		(4)	// アニメパターンのテクスチャ内分割数（X)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y		(1)	// アニメパターンのテクスチャ内分割数（Y)
#define PLAYER_ANIM_PATTERN_NUM				(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define PLAYER_TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント

#define PLAYER_MAX							(1)

#define PLAYER_SPEED_DEFAULT				(2)

typedef struct{
	//D3DXVECTOR3				pos;						// ポリゴンの移動量
	//D3DXVECTOR3				rot;						// ポリゴンの回転量
	//D3DXVECTOR3				scale;

	int						x;
	int						y;
	int						nMap;

	int						nCountAnim;					// アニメーションカウント
} PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(int pid);

#endif
