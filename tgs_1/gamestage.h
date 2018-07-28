#ifndef _GAMESTAGE_H_
#define _GAMESTAGE_H_

#include "main.h"

#define START_TEXTURE				_T("data/texture/start.png")
#define CLEAR_TEXTURE				_T("data/texture/clear.png")
#define OVER_TEXTURE				_T("data/texture/over.png")



HRESULT InitGameStage(void);
void UpdateGameStage(void);
void DrawGameStage(void);
void UninitGameStage(void);

#endif