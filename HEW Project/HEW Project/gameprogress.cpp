/*------------------------------------------------------------------
@brief	�Q�[���̐i�s�o�[
@author	�������V
@date	2019/11/12
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

static GameObject ProgressBar[3];

void Init_GameProgress() 
{

	ProgressBar[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BAR_FRAME]);
	ProgressBar[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_PROGRESS_BAR]);
	ProgressBar[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

}


GameProgress::GameProgress()
{
	stime = 0;
	stime = SECONDS;
	ProgressMax = 5000;
	NowProgress = 200.0f;
	Section = 0;
	GameFinish = false;
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
	NowProgress += stime/10;
	
	if (stime < 5450)	//90�b
	{

		stime++;

	}
	//===================���1===============================

	//10�b�o������(1�b��60)
	if (stime > 600 && stime < 660) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//15�b�o������(1�b��60)
	if (stime > 900 && stime < 960) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�A�N�V�����`�F���W");

		//�A�N�V�������ς�鏈��

	}

	//25�b�o������(1�b��60)
	if (stime > 1500 && stime < 1560) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//30�b�o������(1�b��60)
	if (stime > 1800 && stime < 1860) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�o�g���^�b�`");

		//�o�g���^�b�`����
		if (Section == 0) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 1;
		}
	}
	//===================���2===============================

	//40�b�o������(1�b��60)
	if (stime > 2400 && stime < 2460)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//45�b�o������(1�b��60)
	if (stime > 2700 && stime < 2760)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�A�N�V�����`�F���W");

		//�A�N�V�������ς�鏈��

	}

	//55�b�o������(1�b��60)
	if (stime > 3300 && stime < 3360)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//30�b�o������(1�b��60)
	if (stime > 3600 && stime < 3660)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�o�g���^�b�`");

		//�o�g���^�b�`����
		if (Section == 1) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 2;
		}
	}

	//===================���3===============================

	//70�b�o������(1�b��60)
	if (stime > 4200 && stime < 4260)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//75�b�o������(1�b��60)
	if (stime > 4500 && stime < 4560)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�A�N�V�����`�F���W");

		//�A�N�V�������ς�鏈��

	}

	//85�b�o������(1�b��60)
	if (stime > 5100 && stime < 5160)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��10m!!");

		//�����Ōv�����鏈��

	}

	//90�b�o������(1�b��60)
	if (stime > 5400 && stime < 5460)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "GOAL!!");

		//�o�g���^�b�`����
		if (Section == 2) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 3;
		}
	}

}

void GameProgress::Draw()
{
	//�f�o�b�N�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�o��:%d�b",  stime/60);

	//�v���O���X�o�[�̃t���[��
	ProgressBar[0].Draw(160, 40, PROGRESS_WIDTH+20, PROGRESS_HEIGHT+20, TRUE);

	//��������v���O���X�o�[
	ProgressBar[1].Draw(200, 50, NowProgress+200.0f, PROGRESS_HEIGHT,TRUE);

	//�L�����A�C�R��
	ProgressBar[2].Draw(NowProgress+180.0f, 50, 2.0f,2.0f, 256, 256, TRUE, FALSE);

}


int GameProgress::GetSection() {
	return Section;
}