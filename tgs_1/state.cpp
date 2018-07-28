#include "state.h"
#include "enemy.h"
#include "fog.h"
#include "input.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "state.h"

STATE state = GAME_PLAY;

HRESULT InitState(void)
{
	LPDIRECTSOUNDBUFFER8 pSoundBuffer = LoadSound(BGM_00);

	switch (state) {
	case GAME_INTRO:
		break;
	case GAME_PLAY:

		if (pSoundBuffer) {
			PlaySound(pSoundBuffer, E_DS8_FLAG_LOOP);
		}

		InitMap();
		InitWall();

		InitPlayer();
		InitEnemy();

		InitFog();
		break;
	case GAME_CLEAR:
		break;
	case GAME_OVER:
		break;
	}

	return S_OK;
}

void UpdateState(void)
{
	switch (state) {
	case GAME_INTRO:
		break;
	case GAME_PLAY:

		UpdateMap();
		UpdateWall();
		UpdatePlayer();
		UpdateEnemy();
		UpdateFog();

		break;
	case GAME_CLEAR:
		break;
	case GAME_OVER:
		break;
	}
}

void Draw_State(void) 
{
	switch (state) {
	case GAME_INTRO:
		break;
	case GAME_PLAY:

		DrawMap();
		DrawWall();

		DrawPlayer();
		DrawEnemy();

		// DrawFog();

		break;
	case GAME_CLEAR:
		break;
	case GAME_OVER:
		break;
	}
}

void UninitState(void)
{
	UninitMap();
	UninitWall();

	UninitPlayer();
	UninitEnemy();

	UninitFog();
}

void SetState(STATE newState) {
	state = newState;
}

STATE GetState()
{
	return state;
}
