#include "map.h"

HRESULT MakeVertexBG(void);

static MAP map[MAP_NUMBER] = {
	{
		{	// map data
			{ 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 },//1
			{ 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x2, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0 },//2
			{ 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0 },//3
			{ 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0 },//4
			{ 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 },//5
			{ 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x2, 0x0 },//6
			{ 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0 },//7
			{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x0 },//8
			{ 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0 },//9
			{ 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x2, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0 },//10
			{ 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1 },//11
			{ 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x1, 0x1, 0x0, 0x1, 0x1, 0x0, 0x0 },//12
			{ 0x0, 0x8, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }//13
		}
	}, {
		{
			{ 0x0, 0x0,	0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x8, 0x0, 0x0 },
			{ 0x0, 0x1,	0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x0, 0x1, 0x0, 0x2, 0x0 },
			{ 0x0, 0x2,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x1 },
			{ 0x0, 0x0,	0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x2, 0x0, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0 },
			{ 0x1, 0x1,	0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x1,	0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0 },
			{ 0x0, 0x1,	0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x1,	0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0 },
			{ 0x0, 0x0,	0x0, 0x0, 0x1, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0 },
		}
	}, {
		{
			{ 0x0, 0x0,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
			{ 0x0, 0x1,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x2, 0x0 },
			{ 0x0, 0x2,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x18,0x0, 0x2, 0x0, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
			{ 0x0, 0x0,	0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 },
			{ 0x0, 0x1,	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0 },
			{ 0x0, 0x0,	0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
		}
	}
};

static int currentMap = 0;

static LPDIRECT3DTEXTURE9	g_pD3DTextureBG = NULL;			// テクスチャへのポリゴン

static D3DXVECTOR3			g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

static VERTEX_2D			g_vertexWkFog[NUM_VERTEX];

HRESULT InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			MAP_TEXTURE,		// ファイルの名前
			&g_pD3DTextureBG);		// 読み込むメモリー
	}

	g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexBG();

	return S_OK;
}

void UpdateMap(void)
{
}

void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureBG);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkFog, sizeof(VERTEX_2D));
}

void UninitMap(void)
{
	if (g_pD3DTextureBG != NULL)
	{// テクスチャの開放
		g_pD3DTextureBG->Release();
		g_pD3DTextureBG = NULL;
	}

}

HRESULT MakeVertexBG(void)
{
	// 頂点座標の設定
	g_vertexWkFog[0].vtx = D3DXVECTOR3(0.0f,		 0.0f,			0.0f);
	g_vertexWkFog[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f,			0.0f);
	g_vertexWkFog[2].vtx = D3DXVECTOR3(0.0f,		 SCREEN_HEIGHT,	0.0f);
	g_vertexWkFog[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,	0.0f);

	// rhwの設定
	g_vertexWkFog[0].rhw =
	g_vertexWkFog[1].rhw =
	g_vertexWkFog[2].rhw =
	g_vertexWkFog[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkFog[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkFog[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkFog[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkFog[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkFog[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkFog[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkFog[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkFog[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

void ChangeMap(int id) {
	currentMap = id;
}

MAP* GetMap(void) {
	return &map[currentMap];
}

MAP* GetMap(int id) {
	return &map[id];
}

int GetMapId(void) {
	return currentMap;
}