//=============================================================================
//
// ポリゴン処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(ENEMY* enemy);

void SetVertexEnemy(ENEMY* enemy);

void SetTextureEnemy(ENEMY* enemy);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// テクスチャへのポリゴン

static VERTEX_2D				g_vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

ENEMY enemies[ENEMY_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	ENEMY* enemy;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);

		enemy->pos = D3DXVECTOR3(100.0f, 200.0f * (float)i , 0.0f);
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		enemy->use = true;
		enemy->value = 100*(i+1);

		enemy->nCountAnim = 0;
		enemy->nPatternAnim = 0;

		// 頂点情報の作成
		MakeVertexEnemy(enemy);
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		ENEMY_TEXTURE,				// ファイルの名前
		&g_pD3DTexture);			// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTexture != NULL)	//
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY* enemy;

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);
		enemy->nCountAnim++;

		if (!(enemy->nCountAnim % PLAYER_TIME_ANIMATION)) {
			enemy->nPatternAnim = (enemy->nPatternAnim + 1) % PLAYER_ANIM_PATTERN_NUM;
	
			SetTextureEnemy(enemy);
		}

		SetVertexEnemy(enemy);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	// テクスチャを使わない
	// pDevice->SetTexture(0, NULL);
	ENEMY* enemy;

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);

		if (enemy->use) {
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemy->vtxWk, sizeof(VERTEX_2D));
		}
	}
}

ENEMY * GetEnemy(int nEnemyId)
{
	return &enemies[nEnemyId];
}

void RemoveEnemy(ENEMY *enemy)
{
	enemy->use = false;
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(ENEMY* enemy)
{
	// rhwの設定
	enemy->vtxWk[0].rhw =
	enemy->vtxWk[1].rhw =
	enemy->vtxWk[2].rhw =
	enemy->vtxWk[3].rhw = 1.0f;

	// 反射光の設定
	enemy->vtxWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点座標の設定
	SetVertexEnemy(enemy);

	// テクスチャー設定
	SetTextureEnemy(enemy);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy(ENEMY* enemy)
{
	// 頂点座標の設定
	enemy->vtxWk[0].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y, enemy->pos.z);
	enemy->vtxWk[1].vtx = D3DXVECTOR3(enemy->pos.x + ENEMY_TEXTURE_SIZE_X, enemy->pos.y, enemy->pos.z);
	enemy->vtxWk[2].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y + ENEMY_TEXTURE_SIZE_Y, enemy->pos.z);
	enemy->vtxWk[3].vtx = D3DXVECTOR3(enemy->pos.x + ENEMY_TEXTURE_SIZE_X, enemy->pos.y + ENEMY_TEXTURE_SIZE_Y, enemy->pos.z);
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(ENEMY* enemy)
{
	// テクスチャ座標の計算
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (enemy->nPatternAnim % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (enemy->nPatternAnim / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// テクスチャ座標の設定
	enemy->vtxWk[0].tex = D3DXVECTOR2(x, y);
	enemy->vtxWk[1].tex = D3DXVECTOR2(sizeX + x, y);
	enemy->vtxWk[2].tex = D3DXVECTOR2(x, y + sizeY);
	enemy->vtxWk[3].tex = D3DXVECTOR2(sizeX + x, y + sizeY);
}
