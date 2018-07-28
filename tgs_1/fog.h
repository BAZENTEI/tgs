#pragma once

#include "main.h"

#define FOG_SIZE			32

HRESULT InitFog(void);
void UpdateFog(void);
void DrawFog(void);
void UninitFog(void);

void SetFog(int x, int y);