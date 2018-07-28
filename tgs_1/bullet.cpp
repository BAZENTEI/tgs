//=============================================================================
//
// �|���S������ [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(BULLET*);

void SetVertexBullet(BULLET*);

void SetTextureBullet(BULLET*);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// �e�N�X�`���ւ̃|���S��

BULLET bullets[BULLET_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BULLET* bullet;

	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);

		bullet->use = FALSE;

		// ���_���̍쐬
		MakeVertexBullet(bullet);
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		BULLET_TEXTURE_GAME_SAMPLE00,		// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
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
void UpdateBullet(void)
{
	BULLET *bullet;
	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		// �g�p��
		if (bullet->use) {
			bullet->pos.x -= 8.0f;
		}
		// Out of bound
		if (bullet->pos.x < -BULLET_TEXTURE_SIZE_X) {
			// ���g�p�ɂ���
			RemoveBullet(bullet);
		}

		SetVertexBullet(bullet);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	// �e�N�X�`�����g��Ȃ�
	// pDevice->SetTexture(0, NULL);

	BULLET* bullet;

	for (int i = 0; i < BULLET_MAX; i++) {
		bullet = GetBullet(i);

		if (bullet->use) {
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bullet->wk, sizeof(VERTEX_2D));
		}
	}
}

BULLET *GetBullet(int bid)
{
	return &bullets[bid];
}

void RemoveBullet(BULLET* bullet)
{
	bullet->use = false;
	bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(BULLET* bullet)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexBullet(bullet);

	// rhw�̐ݒ�
	bullet->wk[0].rhw =
	bullet->wk[1].rhw =
	bullet->wk[2].rhw =
	bullet->wk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bullet->wk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->wk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetTextureBullet(bullet);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(BULLET* bullet)
{
	// ���_���W�̐ݒ�
	bullet->wk[0].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
	bullet->wk[1].vtx = D3DXVECTOR3(bullet->pos.x + BULLET_TEXTURE_SIZE_X, bullet->pos.y, bullet->pos.z);
	bullet->wk[2].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + BULLET_TEXTURE_SIZE_Y, bullet->pos.z);
	bullet->wk[3].vtx = D3DXVECTOR3(bullet->pos.x + BULLET_TEXTURE_SIZE_X, bullet->pos.y + BULLET_TEXTURE_SIZE_Y, bullet->pos.z);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(BULLET* bullet)
{
	// �e�N�X�`�����W�̐ݒ�
	bullet->wk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet->wk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bullet->wk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bullet->wk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
