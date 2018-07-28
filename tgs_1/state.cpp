#include "state.h"
#include "enemy.h"
#include "fog.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "state.h"
#include "wall.h"

STATE state = GAME_PLAY;

HRESULT InitState(void)
{
	switch (state) {
	case GAME_INTRO:
		break;
	case GAME_PLAY:
		InitMap();
		InitWall();

		InitPlayer();
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

	UninitFog();
}

void SetState(STATE newState) {
	state = newState;
}

STATE GetState()
{
	return state;
}
