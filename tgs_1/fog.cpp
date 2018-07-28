#include "fog.h"
#include "map.h"

static LPDIRECT3DTEXTURE9	g_pD3DTextureFOG = NULL;			// テクスチャへのポリゴン

static VERTEX_2D			g_vertexWkFog[NUM_VERTEX];

HRESULT InitFog(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			NULL,
			&g_pD3DTextureFOG);	
	}

	g_vertexWkFog[0].vtx = D3DXVECTOR3(32.0f, 32.0f, 0.0f);
	g_vertexWkFog[1].vtx = D3DXVECTOR3(32.0f, 64.0f, 0.0f);
	g_vertexWkFog[2].vtx = D3DXVECTOR3(64.0f, 32.0f, 0.0f);
	g_vertexWkFog[3].vtx = D3DXVECTOR3(64.0f, 64.0f, 0.0f);

	// rhwの設定
	g_vertexWkFog[0].rhw =
	g_vertexWkFog[1].rhw =
	g_vertexWkFog[2].rhw =
	g_vertexWkFog[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkFog[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_vertexWkFog[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_vertexWkFog[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_vertexWkFog[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);

	// テクスチャ座標の設定
	g_vertexWkFog[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkFog[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkFog[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkFog[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

void UpdateFog(void)
{
	//
}


void DrawFog(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureFOG);

	// ポリゴンの描画
	MAP* map = GetMap();

	for (int i = 0, j; i < MAP_SIZE_Y; i++) {
		for (j = 0; j < MAP_SIZE_X; j++) {
			if (map->fogData[i][j] != 1) {
				g_vertexWkFog[0].vtx = D3DXVECTOR3((float)(FOG_SIZE * (j + 1)), (float)(FOG_SIZE * (i + 1)), 0.0f);
				g_vertexWkFog[1].vtx = D3DXVECTOR3((float)(FOG_SIZE * (j + 2)), (float)(FOG_SIZE * (i + 1)), 0.0f);
				g_vertexWkFog[2].vtx = D3DXVECTOR3((float)(FOG_SIZE * (j + 1)), (float)(FOG_SIZE * (i + 2)), 0.0f);
				g_vertexWkFog[3].vtx = D3DXVECTOR3((float)(FOG_SIZE * (j + 2)), (float)(FOG_SIZE * (i + 2)), 0.0f);

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkFog, sizeof(VERTEX_2D));
			}
		}
	}
}

void UninitFog(void) {

	if (g_pD3DTextureFOG != NULL)	//
	{	// テクスチャの開放
		g_pD3DTextureFOG->Release();
		g_pD3DTextureFOG = NULL;
	}
}

void SetFog(int x, int y)
{
	MAP* map = GetMap();
	int m, n;
	for (m = -3; m <= 3; m++) {
		for (n = -3; n <= 3; n++) {
			if ((x + m) >= 0 && (x + m) < MAP_SIZE_X && (y + n) >= 0 && (y + n) < MAP_SIZE_Y) {
				map->fogData[y + n][x + m] = 0;
			}
		}
	}

	for (m = -2; m <= 2; m++) {
		for (n = -2; n <= 2; n++) {
			if ((x + m) >= 0 && (x + m) < MAP_SIZE_X && (y + n) >= 0 && (y + n) < MAP_SIZE_Y) {
				map->fogData[y + n][x + m] = 1;
			}
		}
	}

	// nt i, j;
	// or (i = 0; i < MAP_SIZE_Y; i++) {
	// 	for (j = 0; i < MAP_SIZE_X; j++) {
	// 		if (abs(y - 1) <= 1 && abs(x - 1) <= 1) {
	// 			map->fogData[y][x] = 1;
	// 		}
	// 		else {
	// 			map->fogData[y][x] = 0;
	// 		}
	// 	}
	// 
}
