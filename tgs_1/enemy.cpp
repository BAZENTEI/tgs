//=============================================================================
//
// ポリゴン処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "state.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(ENEMY* enemy);

void SetVertexEnemy(ENEMY* enemy);

void SetTextureEnemy(ENEMY* enemy);

void GameOver(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// テクスチャへのポリゴン

static VERTEX_2D				g_vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

ENEMY enemies[ENEMY_MAX];

static UINT timeTick = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MAP* map = GetMap();

	int n = 0;
	ENEMY* enemy;

	int m = 0;
	for (m = 0; m < MAP_NUMBER; m++) {
		map = GetMap(m);

		for (int i = 0, j; i < MAP_SIZE_Y; i++) {
			for (j = 0; j < MAP_SIZE_X; j++) {
				if (map->mapData[i][j] & MAP_ENEMY) {
					if (n < ENEMY_MAX) {
						enemy = GetEnemy(n);

						enemy->x = j;
						enemy->y = i;

						enemy->use = true;
						enemy->nMap = m;

						enemy->nCountAnim = 2;

						// 頂点情報の作成
						MakeVertexEnemy(enemy);

						map->mapData[i][j] &= ~MAP_ENEMY;

						n++;
					}
				}
			}
		}
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

	MAP* map = GetMap();

	timeTick = (timeTick + 1) % 60;
	if (!timeTick) {

		for (int i = 0; i < ENEMY_MAX; i++) {
			enemy = GetEnemy(i);

			enemy->nCountAnim = rand() % 4;

			switch (enemy->nCountAnim) {
			case 0:
				if ((enemy->y - 1 >= 0) && !(map->mapData[enemy->y - 1][enemy->x] & MAP_WALL)) {
					enemy->y -= 1;
				}

				break;
			case 1:
				if ((enemy->x + 1 < MAP_SIZE_Y) && !(map->mapData[enemy->y][enemy->x + 1] & MAP_WALL)) {
					enemy->x += 1;
				}
				break;

			case 2:
				if ((enemy->y + 1 < MAP_SIZE_Y) && !(map->mapData[enemy->y + 1][enemy->x] & MAP_WALL)) {
					enemy->y += 1;
				}
				break;

			case 3:
				if ((enemy->x - 1 >= 0) && !(map->mapData[enemy->y][enemy->x - 1] & MAP_WALL)) {
					enemy->x -= 1;
				}
				break;
			}

			SetVertexEnemy(enemy);
			SetTextureEnemy(enemy);
		}
	}
	GameOver();
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

		if (enemy->nMap == GetMapId()) {

			if (enemy->use) {
				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemy->vtxWk, sizeof(VERTEX_2D));
			}
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
	enemy->vtxWk[0].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 1)), (float)(MAP_BLOCK_SIZE * (enemy->y + 1)), 0.0f);
	enemy->vtxWk[1].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 2)), (float)(MAP_BLOCK_SIZE * (enemy->y + 1)), 0.0f);
	enemy->vtxWk[2].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 1)), (float)(MAP_BLOCK_SIZE * (enemy->y + 2)), 0.0f);
	enemy->vtxWk[3].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 2)), (float)(MAP_BLOCK_SIZE * (enemy->y + 2)), 0.0f);
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(ENEMY* enemy)
{
	// テクスチャ座標の計算
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (enemy->nCountAnim % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (enemy->nCountAnim / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// テクスチャ座標の設定
	enemy->vtxWk[0].tex = D3DXVECTOR2(x, y);
	enemy->vtxWk[1].tex = D3DXVECTOR2(sizeX + x, y);
	enemy->vtxWk[2].tex = D3DXVECTOR2(x, y + sizeY);
	enemy->vtxWk[3].tex = D3DXVECTOR2(sizeX + x, y + sizeY);
}

void GameOver(void)
{
	PLAYER* player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++) {
		ENEMY* enemy = GetEnemy(i);
		if (enemy->use && enemy->nMap == player->nMap && (enemy->x == player->x) && (enemy->y == player->y)) {
			SetState(GAME_OVER);
		}
	}
}
