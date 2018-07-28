//=============================================================================
//
// �|���S������ [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_


#define SCORE_TEXTURE						_T("data/TEXTURE/digital.png")	// �T���v���p�摜
#define SCORE_TEXTURE_SIZE_X				(512) // �e�N�X�`���T�C�Y
#define SCORE_TEXTURE_SIZE_Y				(64) // ����

#define SCORE_TEXTURE_DIVIDE_X				(16)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SCORE_TEXTURE_DIVIDE_Y				(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define SCORE_WIDTH							(SCORE_TEXTURE_SIZE_X / SCORE_TEXTURE_DIVIDE_X)

#define SCORE_DIGIT_MAX						(8)
#define SCORE_MAX							((int)(1e8 - 1))

HRESULT InitScore(void);
void DrawScore(void);
void UpdateScore(void);
void UninitScore(void);

void AddScore(int value);

#endif // !_SCORE_H_
