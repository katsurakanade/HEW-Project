//13250_スタミナゲージ
/*------------------------------------------------------------------
@brief	スタミナゲージ
@author	萩原直之
@date	2019/11/18
-------------------------------------------------------------------*/
#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "DxLib.h"
#include <time.h>
#include "Staminagauge.h"

static GameObject staminagauge[1];

void StaminaGauge::Init()
{

	if (Initflag == true) 
	{
		staminagauge[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_STAMINA_GAUGE]);
		staminagauge[0].Object.Pos.x = SCREEN_WIDTH / 2;
		staminagauge[0].Object.Pos.y = SCREEN_HEIGHT / 2;
		SetStaminaGauge(StaminaScale);
		StaminaCount = SECONDS;
		Initflag = false;
	}
}

StaminaGauge::StaminaGauge()
{
}

StaminaGauge::~StaminaGauge()
{

}



void StaminaGauge::Update()
{
	StaminaCount++;
	if (StaminaCount > 60.0f)
	{
		StaminaScale -= 0.005;
		SetStaminaGauge(StaminaScale);
		StaminaCount = 0.0f;
	}

}

void StaminaGauge::Draw()
{
	staminagauge[0].Draw();

}

void StaminaGauge::SetStaminaGauge(double scale)
{
	staminagauge[0].Object.Scale = scale;

}

float StaminaGauge::GetStaminaCount()
{
	return StaminaCount;
}

double StaminaGauge::GetStaminaScale()
{
	return StaminaScale;
}
