//=============================================================================
//
// �|���S������ [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��

	BOOL					use;						// �o�邩�ǂ���
	INT						value;

	UINT					nCountAnim;					// �A�j���[�V�����J�E���g
	UINT					nPatternAnim;				// �A�j���[�V�����p�^�[���i���o�[

	VERTEX_2D				vtxWk[NUM_VERTEX];			// ���_���i�[���[�N
} ENEMY;

// �}�N����`
#define ENEMY_TEXTURE					_T("data/TEXTURE/runningman001.png")	// �T���v���p�摜
#define ENEMY_TEXTURE_SIZE_X			(140) // �e�N�X�`���T�C�Y
#define ENEMY_TEXTURE_SIZE_Y			(200) // ����

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ENEMY_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY_MAX						(3)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(int);

void RemoveEnemy(ENEMY*);

#endif
