#include "scene.h"
#include "title.h"
#include "game.h"
#include "BatonTouch.h"
#include "DxLib.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void (*SceneFunc)(void);

static const SceneFunc Initialize[] = {
	Init_Title,
	Init_Game,
	Init_BatonTouch
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
		Uninit_BatonTouch();
		break;
		/*
	case SCENE_INDEX_RESULT:
		Uninit_BatonTouch();
		break;
		*/
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

	case SCENE_INDEX_BATON_TOUCH:
		Update_BatonTouch();
		break;
		/*
	case SCENE_INDEX_RESULT:
		Update_BatonTouch();
		break;
		*/
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
		Draw_BatonTouch();
		break;
		/*
	case SCENE_INDEX_RESULT:
		Draw_BatonTouch();
		break;
		*/
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

