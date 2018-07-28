
#include "state.h"

#include "enemy.h"
#include "fog.h"
#include "gamestage.h"
#include "input.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "score.h"
#include "sound.h"

STATE state = GAME_INTRO;

static LPDIRECTSOUNDBUFFER8 pSoundBuffer = NULL;


HRESULT InitState(void)
{
	pSoundBuffer = LoadSound(BGM_00);

	switch (state) {
	case GAME_INTRO:
		InitGameStage();

		if (pSoundBuffer) {
			PlaySound(pSoundBuffer, E_DS8_FLAG_LOOP);
		}

		break;

	case GAME_PLAY:

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
	case GAME_PLAY:

		UpdateMap();
		UpdateWall();
		UpdatePlayer();
		UpdateEnemy();
		UpdateFog();

		break;
	case GAME_INTRO:
	case GAME_CLEAR:
	case GAME_OVER:
		UpdateGameStage();
		break;
	}
}

void Draw_State(void) 
{
	switch (state) {
	case GAME_PLAY:

		DrawMap();
		DrawWall();

		DrawPlayer();
		DrawEnemy();

		DrawFog();

		break;
	case GAME_INTRO:
	case GAME_CLEAR:
	case GAME_OVER:
		DrawGameStage();
		break;
	}
}

void UninitState(void)
{
	UninitGameStage();

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
