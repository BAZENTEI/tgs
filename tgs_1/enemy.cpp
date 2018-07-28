//=============================================================================
//
// �|���S������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "state.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(ENEMY* enemy);

void SetVertexEnemy(ENEMY* enemy);

void SetTextureEnemy(ENEMY* enemy);

void GameOver(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// �e�N�X�`���ւ̃|���S��

static VERTEX_2D				g_vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

ENEMY enemies[ENEMY_MAX];

static UINT timeTick = 0;

//=============================================================================
// ����������
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

						// ���_���̍쐬
						MakeVertexEnemy(enemy);

						map->mapData[i][j] &= ~MAP_ENEMY;

						n++;
					}
				}
			}
		}
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		ENEMY_TEXTURE,				// �t�@�C���̖��O
		&g_pD3DTexture);			// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTexture != NULL)	//
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	// �e�N�X�`�����g��Ȃ�
	// pDevice->SetTexture(0, NULL);
	ENEMY* enemy;

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);

		if (enemy->nMap == GetMapId()) {

			if (enemy->use) {
				// �|���S���̕`��
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
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(ENEMY* enemy)
{
	// rhw�̐ݒ�
	enemy->vtxWk[0].rhw =
	enemy->vtxWk[1].rhw =
	enemy->vtxWk[2].rhw =
	enemy->vtxWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vtxWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vtxWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���W�̐ݒ�
	SetVertexEnemy(enemy);

	// �e�N�X�`���[�ݒ�
	SetTextureEnemy(enemy);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy(ENEMY* enemy)
{
	// ���_���W�̐ݒ�
	enemy->vtxWk[0].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 1)), (float)(MAP_BLOCK_SIZE * (enemy->y + 1)), 0.0f);
	enemy->vtxWk[1].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 2)), (float)(MAP_BLOCK_SIZE * (enemy->y + 1)), 0.0f);
	enemy->vtxWk[2].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 1)), (float)(MAP_BLOCK_SIZE * (enemy->y + 2)), 0.0f);
	enemy->vtxWk[3].vtx = D3DXVECTOR3((float)(MAP_BLOCK_SIZE * (enemy->x + 2)), (float)(MAP_BLOCK_SIZE * (enemy->y + 2)), 0.0f);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(ENEMY* enemy)
{
	// �e�N�X�`�����W�̌v�Z
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (enemy->nCountAnim % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (enemy->nCountAnim / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// �e�N�X�`�����W�̐ݒ�
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
