#include "scene.h"
#include "title.h"
#include "game.h"
#include "Result.h"
#include "BatonTouch.h"
#include "DxLib.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;
static BatonTouch baton;
typedef void (*SceneFunc)(void);

static const SceneFunc Initialize[] = {
	Init_Title,
	Init_Game,
	Init_Result,
};


void Scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;
	
	Initialize[g_SceneIndex]();
}

void Scene_Finalize(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Uninit_Title();
		break;

	case SCENE_INDEX_GAME:
		Uninit_Game();
		break;

	case SCENE_INDEX_BATON_TOUCH:
		baton.Uninit();
		break;

	case SCENE_INDEX_RESULT:
		Uninit_Result();
		break;

	}
}

void Scene_Update(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Update_Title();
		break;

	case SCENE_INDEX_GAME:
		Update_Game();
		break;

		///////////////////////////////////////////////////////////////
	case SCENE_INDEX_BATON_TOUCH:
		//baton.Update();
		break;
		///////////////////////////////////////////////////////////////

	case SCENE_INDEX_RESULT:
		Update_Result();
		break;

	}
}

void Scene_Draw(void)
{

	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Draw_Title();
		break;

	case SCENE_INDEX_GAME:
		Draw_Game();
		break;

	case SCENE_INDEX_BATON_TOUCH:
		baton.Draw();
		break;

	case SCENE_INDEX_RESULT:
		Draw_Result();
		break;
	}
}

void Scene_Check(void)
{
	if( g_SceneIndex != g_SceneNextIndex ) {
		Scene_Finalize();
		Scene_Initialize(g_SceneNextIndex);
	}
}

void Scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}

