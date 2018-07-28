#pragma once

#include "main.h"

#define WALL_SIZE			32

#define WALL_TEXTURE		_T("data/texture/wall.png")

HRESULT InitWall(void);
void UpdateWall(void);
void DrawWall(void);
void UninitWall(void);

void RemoveWall(int x, int y);