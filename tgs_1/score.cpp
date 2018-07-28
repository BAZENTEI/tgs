#include "main.h"
#include "score.h"

static LPDIRECT3DTEXTURE9		g_pD3DScoreTexture = NULL;

static int						g_nScore;
static int						g_nTempScore;
static VERTEX_2D				scoreVtx[SCORE_DIGIT_MAX][NUM_VERTEX];

void SetVertexScore(int);

void SetTextureScore(int, int);

HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nTempScore = g_nScore = 0;

	for (int i = 0; i < SCORE_DIGIT_MAX; i++) {

		scoreVtx[i][0].rhw =
		scoreVtx[i][1].rhw =
		scoreVtx[i][2].rhw =
		scoreVtx[i][3].rhw = 1.0f;

		// 反射光の設定
		scoreVtx[i][0].diffuse = 
		scoreVtx[i][1].diffuse = 
		scoreVtx[i][2].diffuse = 
		scoreVtx[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		SetVertexScore(i);

		SetTextureScore(i, 0);
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		SCORE_TEXTURE,				// ファイルの名前
		&g_pD3DScoreTexture);			// 読み込むメモリのポインタ
	
	return S_OK;
}

void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DScoreTexture);
	
	int i = SCORE_DIGIT_MAX;

	while (i--) {
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, scoreVtx[i], sizeof(VERTEX_2D));
	}
}

void UpdateScore(void)
{
	int scr = g_nScore;

	int nPosition = SCORE_DIGIT_MAX;

	int nDigit;

	while (nPosition--) {
		nDigit = scr % 10;

		SetVertexScore(nPosition);

		SetTextureScore(nPosition, nDigit);

		scr /= 10;
	}
}

void UninitScore(void)
{
	if(g_pD3DScoreTexture != NULL){
		g_pD3DScoreTexture->Release();
		g_pD3DScoreTexture = NULL;
	}
}

void AddScore(int value)
{
	g_nScore += value;
	if (g_nScore > SCORE_MAX) {
		g_nScore = SCORE_MAX;
	}
}

void SetVertexScore(int digitPosition)
{
	// 右上に置く
	scoreVtx[digitPosition][0].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH - (SCORE_DIGIT_MAX - digitPosition) * SCORE_WIDTH), 0.0f, 0.0f);
	scoreVtx[digitPosition][1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH - (SCORE_DIGIT_MAX - digitPosition - 1) * SCORE_WIDTH), 0.0f, 0.0f);
	scoreVtx[digitPosition][2].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH - (SCORE_DIGIT_MAX - digitPosition) * SCORE_WIDTH), (float)SCORE_TEXTURE_SIZE_Y, 0.0f);
	scoreVtx[digitPosition][3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH - (SCORE_DIGIT_MAX - digitPosition - 1) * SCORE_WIDTH), (float)SCORE_TEXTURE_SIZE_Y, 0.0f);
}

void SetTextureScore(int digitPosition, int pattern)
{
	float sizeX = 1.0f / SCORE_TEXTURE_DIVIDE_X;

	scoreVtx[digitPosition][0].tex = D3DXVECTOR2((float)(pattern) * sizeX, 0.0f);
	scoreVtx[digitPosition][1].tex = D3DXVECTOR2((float)(pattern + 1) * sizeX, 0.0f);
	scoreVtx[digitPosition][2].tex = D3DXVECTOR2((float)(pattern) * sizeX, 1.0f);
	scoreVtx[digitPosition][3].tex = D3DXVECTOR2((float)(pattern + 1) * sizeX, 1.0f);
}
