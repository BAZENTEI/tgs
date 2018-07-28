//=============================================================================
//
// ポリゴン処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(BULLET*);

void SetVertexBullet(BULLET*);

void SetTextureBullet(BULLET*);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// テクスチャへのポリゴン

BULLET bullets[BULLET_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BULLET* bullet;

	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);

		bullet->use = FALSE;

		// 頂点情報の作成
		MakeVertexBullet(bullet);
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		BULLET_TEXTURE_GAME_SAMPLE00,		// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
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
void UpdateBullet(void)
{
	BULLET *bullet;
	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		// 使用中
		if (bullet->use) {
			bullet->pos.x -= 8.0f;
		}
		// Out of bound
		if (bullet->pos.x < -BULLET_TEXTURE_SIZE_X) {
			// 未使用にする
			RemoveBullet(bullet);
		}

		SetVertexBullet(bullet);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	// テクスチャを使わない
	// pDevice->SetTexture(0, NULL);

	BULLET* bullet;

	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		if (bullet->use) {
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bullet->wk, sizeof(VERTEX_2D));
		}
	}
}

BULLET *GetBullet(int bid)
{
	return &bullets[bid];
}

void RemoveBullet(BULLET* bullet)
{
	bullet->use = false;
	bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet(BULLET* bullet)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexBullet(bullet);

	// rhwの設定
	bullet->wk[0].rhw =
	bullet->wk[1].rhw =
	bullet->wk[2].rhw =
	bullet->wk[3].rhw = 1.0f;

	// 反射光の設定
	bullet->wk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetTextureBullet(bullet);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet(BULLET* bullet)
{
	// 頂点座標の設定
	bullet->wk[0].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
	bullet->wk[1].vtx = D3DXVECTOR3(bullet->pos.x + BULLET_TEXTURE_SIZE_X, bullet->pos.y, bullet->pos.z);
	bullet->wk[2].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + BULLET_TEXTURE_SIZE_Y, bullet->pos.z);
	bullet->wk[3].vtx = D3DXVECTOR3(bullet->pos.x + BULLET_TEXTURE_SIZE_X, bullet->pos.y + BULLET_TEXTURE_SIZE_Y, bullet->pos.z);
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet(BULLET* bullet)
{
	// テクスチャ座標の設定
	bullet->wk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet->wk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bullet->wk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bullet->wk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
