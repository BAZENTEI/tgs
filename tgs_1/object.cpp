#include "object.h"
#include "map.h"

static LPDIRECT3DTEXTURE9	g_pD3DTextureWall = NULL;			// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9	g_pD3DTextureExit = NULL;			// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9	g_pD3DTextureFinish = NULL;			// �e�N�X�`���ւ̃|���S��

static VERTEX_2D			g_vertexWkObj[NUM_VERTEX];

HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	g_vertexWkObj[0].vtx = D3DXVECTOR3(32.0f, 32.0f, 0.0f);
	g_vertexWkObj[1].vtx = D3DXVECTOR3(32.0f, 64.0f, 0.0f);
	g_vertexWkObj[2].vtx = D3DXVECTOR3(64.0f, 32.0f, 0.0f);
	g_vertexWkObj[3].vtx = D3DXVECTOR3(64.0f, 64.0f, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkObj[0].rhw =
	g_vertexWkObj[1].rhw =
	g_vertexWkObj[2].rhw =
	g_vertexWkObj[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkObj[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkObj[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkObj[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkObj[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkObj[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkObj[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkObj[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkObj[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	if (!g_pD3DTextureFinish) {
		D3DXCreateTextureFromFile(pDevice,
			FINISH_TEXTURE,
			&g_pD3DTextureFinish);
	}

	if (!g_pD3DTextureWall) {
		D3DXCreateTextureFromFile(pDevice,
			WALL_TEXTURE,
			&g_pD3DTextureWall);
	}

	if (!g_pD3DTextureExit) {
		D3DXCreateTextureFromFile(pDevice,
			EXIT_TEXTURE,
			&g_pD3DTextureExit);
	}

	return S_OK;
}

void UpdateWall(void)
{
	//
}


void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureWall);

	// �|���S���̕`��
	MAP* map = GetMap();

	for (int i = 0, j; i < MAP_SIZE_Y; i++) {
		for (j = 0; j < MAP_SIZE_X; j++) {

			g_vertexWkObj[0].vtx = D3DXVECTOR3((float)(WALL_SIZE * (j + 1)), (float)(WALL_SIZE * (i + 1)), 0.0f);
			g_vertexWkObj[1].vtx = D3DXVECTOR3((float)(WALL_SIZE * (j + 2)), (float)(WALL_SIZE * (i + 1)), 0.0f);
			g_vertexWkObj[2].vtx = D3DXVECTOR3((float)(WALL_SIZE * (j + 1)), (float)(WALL_SIZE * (i + 2)), 0.0f);
			g_vertexWkObj[3].vtx = D3DXVECTOR3((float)(WALL_SIZE * (j + 2)), (float)(WALL_SIZE * (i + 2)), 0.0f);

			if (map->mapData[i][j] & MAP_WALL) {
				pDevice->SetTexture(0, g_pD3DTextureWall);

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkObj, sizeof(VERTEX_2D));
			}
			if (map->mapData[i][j] & MAP_EXIT) {
				pDevice->SetTexture(0, g_pD3DTextureExit);

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkObj, sizeof(VERTEX_2D));
			}
			if (map->mapData[i][j] & MAP_FINISH) {
				pDevice->SetTexture(0, g_pD3DTextureFinish);

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkObj, sizeof(VERTEX_2D));
			}
		}
	}
}

void UninitWall(void) {

	if (g_pD3DTextureWall != NULL)	//
	{	// �e�N�X�`���̊J��
		g_pD3DTextureWall->Release();
		g_pD3DTextureWall = NULL;
	}
	if (g_pD3DTextureExit != NULL)	//
	{	// �e�N�X�`���̊J��
		g_pD3DTextureExit->Release();
		g_pD3DTextureExit = NULL;
	}
	if (g_pD3DTextureFinish != NULL)	//
	{	// �e�N�X�`���̊J��
		g_pD3DTextureFinish->Release();
		g_pD3DTextureFinish = NULL;
	}
}

void RemoveWall(int x, int y)
{
	MAP* map = GetMap();
	int m = -1, n = -1;
	for (m = -1; m <= 1; m++) {
		for (n = -1; n <= 1; n++) {
			if ((x + m) >= 0 && (x + m) < MAP_SIZE_X && (y + n) >= 0 && (y + n) < MAP_SIZE_Y) {
				map->fogData[y + n][x + m] = 1;
			}
		}
	}
}
