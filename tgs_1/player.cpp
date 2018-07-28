//=============================================================================
//
// ポリゴン処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "fog.h"
#include "map.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "state.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);

void SetVertexPlayer(void);
void SetTexturePlayer( int cntPattern );

BOOL Escaped();

//*****************************************************************************
// グローバル変数
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポリゴン

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

PLAYER							g_Player[PLAYER_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PLAYER* player = GetPlayer(0);

	//player->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//player->pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
	//player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	player->x = 0;
	player->y = 0;
	player->nMap = 0;

	MAP* map = GetMap();

	for (int i = 0, j; i < MAP_SIZE_Y; i++) {
		for (j = 0; j < MAP_SIZE_X; j++) {
			if (map->mapData[i][j] & MAP_PLAYER) {
				player->x = j;
				player->y = i;

				map->mapData[i][j] &= ~MAP_PLAYER;
			}
		}
	}

	player->nCountAnim = 2;

	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice,		// デバイスのポインタ
		PLAYER_TEXTURE,				// ファイルの名前
		&g_pD3DTexture);			// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	if(g_pD3DTexture != NULL )	//
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER* player = GetPlayer(0);

	MAP*	map = GetMap();

	LPDIRECTSOUNDBUFFER8 pSoundBuffer = LoadSound(SE_WALK);

	// アニメーション
	if (GetKeyboardTrigger(DIK_RIGHT)) {
		if ((player->x + 1 < MAP_SIZE_X) && !(map->mapData[player->y][player->x + 1] & MAP_WALL)) {
			player->x += 1;
			player->nCountAnim = 1;

			if (pSoundBuffer) {
				PlaySound(pSoundBuffer, E_DS8_FLAG_NONE);
			}
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT)) {
		if ((player->x - 1 >= 0) && !(map->mapData[player->y][player->x - 1] & MAP_WALL)) {
			player->x -= 1;
			player->nCountAnim = 3;

			if (pSoundBuffer) {
				PlaySound(pSoundBuffer, E_DS8_FLAG_NONE);
			}
		}
	}

	if (GetKeyboardTrigger(DIK_DOWN)) {
		if ((player->y + 1 < MAP_SIZE_Y) && !(map->mapData[player->y + 1][player->x] & MAP_WALL)) {
			player->y += 1;
			player->nCountAnim = 2;

			if (pSoundBuffer) {
				PlaySound(pSoundBuffer, E_DS8_FLAG_NONE);
			}
		}
	}
	else if (GetKeyboardTrigger(DIK_UP)) {

		if ((player->y - 1 >= 0) && !(map->mapData[player->y - 1][player->x] & MAP_WALL)) {
			player->y -= 1;
			player->nCountAnim = 0;

			if (pSoundBuffer) {
				PlaySound(pSoundBuffer, E_DS8_FLAG_NONE);
			}
		}
	}

	SetFog(player->x, player->y);

	SetVertexPlayer();
	SetTexturePlayer(player->nCountAnim);

	Escaped();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	// テクスチャを使わない
	// pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWk, sizeof(VERTEX_2D));
}

PLAYER *GetPlayer(int pid)
{
	return &g_Player[pid];
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexPlayer();

	// rhwの設定
	g_vertexWk[0].rhw =
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetTexturePlayer(player->nCountAnim);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer()
{
	PLAYER
		*player = GetPlayer(0);

	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 1)),	(float)(MAP_BLOCK_SIZE * (player->y + 1)),	0.0f);
	g_vertexWk[1].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 2)),	(float)(MAP_BLOCK_SIZE * (player->y + 1)),	0.0f);
	g_vertexWk[2].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 1)),	(float)(MAP_BLOCK_SIZE * (player->y + 2)),	0.0f);
	g_vertexWk[3].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 2)),	(float)(MAP_BLOCK_SIZE * (player->y + 2)),	0.0f);
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// テクスチャ座標の計算
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (cntPattern % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (cntPattern / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// テクスチャ座標の設定
	g_vertexWk[0].tex = D3DXVECTOR2(x, y);
	g_vertexWk[1].tex = D3DXVECTOR2(sizeX + x, y);
	g_vertexWk[2].tex = D3DXVECTOR2(x, y + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2(sizeX + x, y + sizeY);
}

BOOL Escaped()
{
	PLAYER* player = GetPlayer(0);

	MAP* map = GetMap();

	if (map->mapData[player->y][player->x] & MAP_EXIT) {
		int id = GetMapId();

		if (++id < MAP_NUMBER) {
			ChangeMap(id);
			player->nMap = id;
		}
		else {
			SetState(GAME_CLEAR);
		}

		return TRUE;
	}
	return FALSE;
}
