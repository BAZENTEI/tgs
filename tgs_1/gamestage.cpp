#include "gamestage.h"
#include "state.h"
#include "input.h"

HRESULT MakeVertexGameStage(void);

static LPDIRECT3DTEXTURE9	g_pD3DTextureStart = NULL;			// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9	g_pD3DTextureClear = NULL;			// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9	g_pD3DTextureOver =  NULL;			// �e�N�X�`���ւ̃|���S��

static VERTEX_2D			g_vertexWkGame[NUM_VERTEX];

HRESULT InitGameStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if(!g_pD3DTextureStart)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			START_TEXTURE,
			&g_pD3DTextureStart);

		D3DXCreateTextureFromFile(pDevice,
			CLEAR_TEXTURE,
			&g_pD3DTextureClear);

		D3DXCreateTextureFromFile(pDevice,
			OVER_TEXTURE,
			&g_pD3DTextureOver);
	}

	// ���_���̍쐬
	MakeVertexGameStage();

	return S_OK;
}

void UpdateGameStage(void)
{
	if (GetKeyboardPress(DIK_X) || GetKeyboardPress(DIK_SPACE)) {
		switch (GetState()) {
		case GAME_INTRO:

			if (GetState() != GAME_PLAY) {
				SetState(GAME_PLAY);
				InitState();
			}
			break;

		case GAME_OVER:
		case GAME_CLEAR:
			PostQuitMessage(0);
			break;
		}
	}
}

void DrawGameStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	switch (GetState()) {
	case GAME_INTRO:
		pDevice->SetTexture(0, g_pD3DTextureStart);
		break;
	case GAME_CLEAR:
		pDevice->SetTexture(0, g_pD3DTextureClear);
		break;
	case GAME_OVER:
		pDevice->SetTexture(0, g_pD3DTextureOver);
		break;
	}
	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGame, sizeof(VERTEX_2D));
}

void UninitGameStage(void)
{
	if (g_pD3DTextureStart != NULL)
	{
		g_pD3DTextureStart->Release();
		g_pD3DTextureStart = NULL;
	}

	if (g_pD3DTextureClear != NULL)
	{
		g_pD3DTextureClear->Release();
		g_pD3DTextureClear = NULL;
	}

	if (g_pD3DTextureOver != NULL)
	{
		g_pD3DTextureOver->Release();
		g_pD3DTextureOver = NULL;
	}

}

HRESULT MakeVertexGameStage(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkGame[0].vtx = D3DXVECTOR3(0.0f,		 0.0f,			0.0f);
	g_vertexWkGame[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f,			0.0f);
	g_vertexWkGame[2].vtx = D3DXVECTOR3(0.0f,		 SCREEN_HEIGHT,	0.0f);
	g_vertexWkGame[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,	0.0f);

	// rhw�̐ݒ�
	g_vertexWkGame[0].rhw =
	g_vertexWkGame[1].rhw =
	g_vertexWkGame[2].rhw =
	g_vertexWkGame[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkGame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkGame[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkGame[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkGame[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkGame[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
