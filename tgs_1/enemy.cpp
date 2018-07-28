//=============================================================================
//
// �|���S������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(ENEMY* enemy);

void SetVertexEnemy(ENEMY* enemy);

void SetTextureEnemy(ENEMY* enemy);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// �e�N�X�`���ւ̃|���S��

static VERTEX_2D				g_vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

ENEMY enemies[ENEMY_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	ENEMY* enemy;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);

		enemy->pos = D3DXVECTOR3(100.0f, 200.0f * (float)i , 0.0f);
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		enemy->use = true;
		enemy->value = 100*(i+1);

		enemy->nCountAnim = 0;
		enemy->nPatternAnim = 0;

		// ���_���̍쐬
		MakeVertexEnemy(enemy);
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

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy = GetEnemy(i);
		enemy->nCountAnim++;

		if (!(enemy->nCountAnim % PLAYER_TIME_ANIMATION)) {
			enemy->nPatternAnim = (enemy->nPatternAnim + 1) % PLAYER_ANIM_PATTERN_NUM;
	
			SetTextureEnemy(enemy);
		}

		SetVertexEnemy(enemy);
	}
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

		if (enemy->use) {
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemy->vtxWk, sizeof(VERTEX_2D));
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
	enemy->vtxWk[0].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y, enemy->pos.z);
	enemy->vtxWk[1].vtx = D3DXVECTOR3(enemy->pos.x + ENEMY_TEXTURE_SIZE_X, enemy->pos.y, enemy->pos.z);
	enemy->vtxWk[2].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y + ENEMY_TEXTURE_SIZE_Y, enemy->pos.z);
	enemy->vtxWk[3].vtx = D3DXVECTOR3(enemy->pos.x + ENEMY_TEXTURE_SIZE_X, enemy->pos.y + ENEMY_TEXTURE_SIZE_Y, enemy->pos.z);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(ENEMY* enemy)
{
	// �e�N�X�`�����W�̌v�Z
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	float x = sizeX * (enemy->nPatternAnim % PLAYER_TEXTURE_PATTERN_DIVIDE_X);
	float y = sizeY * (enemy->nPatternAnim / PLAYER_TEXTURE_PATTERN_DIVIDE_X);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vtxWk[0].tex = D3DXVECTOR2(x, y);
	enemy->vtxWk[1].tex = D3DXVECTOR2(sizeX + x, y);
	enemy->vtxWk[2].tex = D3DXVECTOR2(x, y + sizeY);
	enemy->vtxWk[3].tex = D3DXVECTOR2(sizeX + x, y + sizeY);
}
