#include <algorithm>
#include <vector>
#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "ActionSlot.h"
#include "ActionUI.h"
#include "GameData.h"
#include "Live2D.h"
#include "gameprogress.h"
#include "Staminagauge.h"
#include "ActionAffect.h"
#include "BackGround.h"
#include "GameOver.h"
#include "BatonTouch.h"
#include "GameClear.h"
#include "Effect.h"


//static GameObject efc[4];

static GameObject *efc;

void EffectInit()
{
	efc = new GameObject;


	efc->LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);
	efc->Object.Pos.x = 600;
	efc->Object.Pos.y = 350;

	// efc->SetDelayFlag(0);
	// efc->SetDelayFlag(1);
	// efc->SetDelayFlag(2);

}
void EffectUpdate()
{


	if (keyboard.IsTrigger(DIK_RETURN))
	{
		efc->SetDelayFlag(0);
	}

	efc->Delay_CurveMove(true, 7, 2.0f, 400, 200);
	//efc->Delay_Move(2.0f, 400, 200);


}
void EffectDraw()
{
	efc->Draw();
}


