#include "map.h"

HRESULT MakeVertexBG(void);

static MAP map[MAP_NUMBER] = {};

static int currentMap = 0;

static LPDIRECT3DTEXTURE9	g_pD3DTextureBG = NULL;			// テクスチャへのポリゴン

static D3DXVECTOR3			g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

static VERTEX_2D					g_vertexWkBG[NUM_VERTEX];

void ChangeMap(int id) {
	currentMap = id;
}

MAP* GetMap(void) {
	return &map[currentMap];
}


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
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG, sizeof(VERTEX_2D));
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
	g_vertexWkBG[0].vtx = D3DXVECTOR3(0.0f,		0.0f,		0.0f);
	g_vertexWkBG[1].vtx = D3DXVECTOR3(640.0f,	0.0f,		0.0f);
	g_vertexWkBG[2].vtx = D3DXVECTOR3(0.0f,		480.0f,		0.0f);
	g_vertexWkBG[3].vtx = D3DXVECTOR3(640.0f,	480.0f,		0.0f);

	// rhwの設定
	g_vertexWkBG[0].rhw =
	g_vertexWkBG[1].rhw =
	g_vertexWkBG[2].rhw =
	g_vertexWkBG[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
