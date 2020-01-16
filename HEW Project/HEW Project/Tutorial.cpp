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
#include "Tutorial.h"

void Init_Tutorial()
{

}

void Uninit_Tutorial()
{

}

void Update_Tutorial()
{
	if (keyboard.IsTrigger(DIK_RETURN)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

}

void Draw_Tutorial()
{

}