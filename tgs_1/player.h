//=============================================================================
//
// �|���S������ [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// �}�N����`
#define PLAYER_TEXTURE						_T("data/texture/player.png")	// �T���v���p�摜
#define PLAYER_TEXTURE_SIZE_X				(128) // �e�N�X�`���T�C�Y
#define PLAYER_TEXTURE_SIZE_Y				(32) // ����

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X		(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y		(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ANIM_PATTERN_NUM				(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX							(1)

#define PLAYER_SPEED_DEFAULT				(2)

typedef struct{
	//D3DXVECTOR3				pos;						// �|���S���̈ړ���
	//D3DXVECTOR3				rot;						// �|���S���̉�]��
	//D3DXVECTOR3				scale;

	int						x;
	int						y;
	int						nMap;

	int						nCountAnim;					// �A�j���[�V�����J�E���g
} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(int pid);

#endif
