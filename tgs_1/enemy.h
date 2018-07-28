//=============================================================================
//
// �|���S������ [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

// �}�N����`
#define ENEMY_TEXTURE					_T("data/texture/enemy.png")	// �T���v���p�摜
#define ENEMY_TEXTURE_SIZE_X			(128) // �e�N�X�`���T�C�Y
#define ENEMY_TEXTURE_SIZE_Y			(32) // ����

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ENEMY_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY_MAX						(10)

typedef struct {

	BOOL					use;						// �o�邩�ǂ���
	INT						x;
	INT						y;
	INT						nMap;

	UINT					nCountAnim;					// �A�j���[�V�����J�E���g

	VERTEX_2D				vtxWk[NUM_VERTEX];			// ���_���i�[���[�N
} ENEMY;

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
