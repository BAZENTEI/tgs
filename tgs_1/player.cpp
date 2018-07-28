//=============================================================================
//
// �|���S������ [player.cpp]
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);

void SetVertexPlayer(void);
void SetTexturePlayer( int cntPattern );

BOOL Escaped();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S��

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

PLAYER							g_Player[PLAYER_MAX];

//=============================================================================
// ����������
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

	// ���_���̍쐬
	MakeVertexPlayer();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice,		// �f�o�C�X�̃|�C���^
		PLAYER_TEXTURE,				// �t�@�C���̖��O
		&g_pD3DTexture);			// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	if(g_pD3DTexture != NULL )	//
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER* player = GetPlayer(0);

	MAP*	map = GetMap();

	LPDIRECTSOUNDBUFFER8 pSoundBuffer = LoadSound(SE_WALK);

	// �A�j���[�V����
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
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	// �e�N�X�`�����g��Ȃ�
	// pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWk, sizeof(VERTEX_2D));
}

PLAYER *GetPlayer(int pid)
{
	return &g_Player[pid];
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	PLAYER* player = GetPlayer(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexPlayer();

	// rhw�̐ݒ�
	g_vertexWk[0].rhw =
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetTexturePlayer(player->nCountAnim);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer()
{
	PLAYER
		*player = GetPlayer(0);

	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 1)),	(float)(MAP_BLOCK_SIZE * (player->y + 1)),	0.0f);
	g_vertexWk[1].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 2)),	(float)(MAP_BLOCK_SIZE * (player->y + 1)),	0.0f);
	g_vertexWk[2].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 1)),	(float)(MAP_BLOCK_SIZE * (player->y + 2)),	0.0f);
	g_vertexWk[3].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (player->x + 2)),	(float)(MAP_BLOCK_SIZE * (player->y + 2)),	0.0f);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// �e�N�X�`�����W�̌v�Z
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (cntPattern % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (cntPattern / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// �e�N�X�`�����W�̐ݒ�
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
