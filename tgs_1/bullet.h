//=============================================================================
//
// �|���S������ [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct {

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��

	BOOL					use;						// �o�邩�ǂ���

	VERTEX_2D				wk[NUM_VERTEX];		// ���_���i�[���[�N
} BULLET;

// �}�N����`
#define BULLET_TEXTURE_GAME_SAMPLE00		_T("data/TEXTURE/tama.png")	// �T���v���p�摜
#define BULLET_TEXTURE_SIZE_X				(32) // �e�N�X�`���T�C�Y
#define BULLET_TEXTURE_SIZE_Y				(32) // ����

#define BULLET_MAX							(20)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(int bid);

void RemoveBullet(BULLET* bullet);

#endif
