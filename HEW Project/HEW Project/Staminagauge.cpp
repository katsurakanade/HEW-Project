//13250_スタミナゲージ
/*------------------------------------------------------------------
@brief	スタミナゲージ
@author	萩原直之
@date	2019/11/21
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

GameObject staminagauge[1];

void StaminaGauge::Init()
{

	if (Initflag == true) 
	{
		staminagauge[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_STAMINA_GAUGE]);
		staminagauge[0].Object.Pos.x = SCREEN_WIDTH / 2;
		staminagauge[0].Object.Pos.y = SCREEN_HEIGHT / 2;
		SetStaminaGauge(StaminaScale_x, StaminaScale_y);
		StaminaCount = 0.005;
		//NowCount = 1000.0f;
		FlameCount = SECONDS;
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
	StaminaReduce(StaminaCount);
	if(StaminaScale_x<=1.0&&StaminaScale_y<=1.0)
	{
		StaminaScale_x = 1.0;
		StaminaScale_y = 1.0;
	}
}

void StaminaGauge::Draw()
{
	staminagauge[0].Draw();

}

void StaminaGauge::SetStaminaGauge(double scale_x, double scale_y)
{
	staminagauge[0].Object.Scale.x = scale_x;
	staminagauge[0].Object.Scale.y = scale_y;

}

double StaminaGauge::GetStaminaScale_x()
{
	return StaminaScale_x;
}


void StaminaGauge::StaminaState(int state)
{
	//Bad
	if (state == 3)
	{
		StaminaCount -= 0.050;
	}
	else
	{
		StaminaCount = 0.005;
	}
	//Over
	if (state==1)
	{
		StaminaCount += 0.015;
	}
	//Great
	if (state==2)
	{
		StaminaCount -= 0.002;
	}
	
}

void StaminaGauge::StaminaReduce(double s_count)
{
	FlameCount++;
	if (FlameCount > 60.0f)
	{
		StaminaScale_x -= s_count;
		StaminaScale_y -= s_count;
		SetStaminaGauge(StaminaScale_x, StaminaScale_y);
		FlameCount = 0.0f;
	}

}