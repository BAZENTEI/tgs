#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

#define MAP_SIZE_X				18
#define MAP_SIZE_Y				13

#define MAP_NUMBER				3

#define MAP_WALL				0x1
#define MAP_ENEMY				0x2
#define MAP_PLAYER				0x4
#define MAP_EXIT				0x8
#define MAP_FINISH				0x10

#define MAP_BLOCK_SIZE			32
#define MAP_TEXTURE				_T("data/texture/map.png")


typedef struct MAP {
	UINT	mapData[MAP_SIZE_Y][MAP_SIZE_X];
	UINT	fogData[MAP_SIZE_Y][MAP_SIZE_X] = {};
}MAP;

HRESULT InitMap(void);
void UpdateMap(void);
void DrawMap(void);
void UninitMap(void);

MAP* GetMap(void);
MAP* GetMap(int id);
int GetMapId(void);

void ChangeMap(int id);

#endif