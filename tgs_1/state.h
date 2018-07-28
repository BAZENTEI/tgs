#ifndef _STATE_H_
#define _STATE_H_

#include "main.h"

typedef enum STATE {
	GAME_INTRO,
	GAME_PLAY,
	GAME_CLEAR,
	GAME_OVER
} STATE;

HRESULT InitState(void);
void UpdateState(void);
void Draw_State(void);
void UninitState(void);

void SetState(STATE);

STATE GetState();

#endif // !_STATE_H_
