/*------------------------------------------------------------------
@brief	�Q�[���̐i�s�o�[
@author	�������V
@date	2019/11/07
-------------------------------------------------------------------*/

#include "gameprogress.h"
#include "GameObject.h"
#include "scene.h"
#include "main.h"
#include <time.h>

GameObject ProgressObj;

GameProgress::GameProgress()
{
	stime = SECONDS;
	ProgressObj.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	stime++;
	if (stime > 300) //5�b�o������
	{
		Scene_Change(SCENE_INDEX_TITLE);
		//������
		stime = 0;
	}
	
}

void GameProgress::Draw()
{
	//�f�o�b�N�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�o��:%d�b",  stime/60);
	ProgressObj.Draw(100, 100);

}
