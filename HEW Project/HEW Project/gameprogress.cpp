//13210_�Q�[���i�s�o�[
/*------------------------------------------------------------------
@brief	�Q�[���̐i�s�o�[
@author	�������V
@date	2019/12/05
-------------------------------------------------------------------*/
#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "GameData.h"
#include "DxLib.h"
#include "BatonTouch.h"
#include "game.h"
#include "ActionUI.h"

static GameObject ProgressBar[3];
static BatonTouch batontouch;
static ActionUI actionui;

void GameProgress::Init() 
{
		ProgressBar[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BAR_FRAME]);
		ProgressBar[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_PROGRESS_BAR]);
		ProgressBar[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

		ProgressBar[0].Object.Pos.x = SCREEN_WIDTH / 2;
		ProgressBar[0].Object.Pos.y = 100.0f;
		ProgressBar[0].Object.Scale.x = 1.0f;
		ProgressBar[0].Object.Scale.y = 1.0f;

		ProgressBar[1].Object.Pos.x = SCREEN_WIDTH / 2;
		ProgressBar[1].Object.Pos.y = 100.0f;
		ProgressBar[1].Object.Scale.x = 1.0f;
		ProgressBar[1].Object.Scale.y = 1.0f;


		ProgressBar[2].Object.Pos.x = 200.0f;
		ProgressBar[2].Object.Pos.y = 100.0f;
		ProgressBar[2].Object.Scale.x = 0.5f;
		ProgressBar[2].Object.Scale.y = 0.5f;

		//stime = 0.0f;
		stime = SECONDS;
		ProgressMax = 5000;
		NowProgress = 0.0f;
		Section = 0;
		RunDistance = 0.0f;		//�Q�b�g���������f�[�^������
		GameFinish = false;
		MeasureFlag = false;

		actionui.SetState(0);
}



GameProgress::GameProgress()
{
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	//�t���[���ŃQ�[�W�𑝂₷����
	if (MeasureFlag == false)
	{
		NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
		NowProgress += stime / 6.4f;

		//�i�s�o�[�̑�������
		//ProgressBar[1].Object.Scale.x = NowProgress/10000;

		//�L�����A�C�R���̈ړ�����
		ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;		//+100.0f�̓A�C�R���̏����ʒu�̎w��

		if (stime < 5450.0f)	//90�b
		{

			stime++;

		}
	}

	//===================���1===============================

	//10�b�o������(1�b��60)
	if (stime > 600.0f && stime < 660.0f) 
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;
	}
	//�����Ōv�����鏈��
	ChangeMeasure(600.0f,900.0f);
	
	//�A�N�V�����`�F���W�|�C���g�ɒ�������
	//15�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 300 && ProgressBar[2].Object.Pos.x < 310) ||*/ (stime > 900.0f && stime < 960.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		MeasureFlag = false;

		//�A�N�V�������ς�鏈��
		actionui.SetState(1);

	}

	//25�b�o������(1�b��60)
	if (stime > 1500.0f && stime < 1560.0f) 
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	ChangeMeasure(1500.0f,1800.0f);

	//30�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 450 && ProgressBar[2].Object.Pos.x < 460) || */(stime > 1800.0f && stime < 1860.0f))
	{
		MeasureFlag = false;

		//�o�g���^�b�`����
		if (Section == 0) {
			batontouch.StateBaton = true;
			GameState_Change(GAME_STATE_BATONTOUCH);
			Section = 1;

			//�A�N�V�������ς�鏈��
			actionui.SetState(2);

		}
	}
	//===================���2===============================

	//40�b�o������(1�b��60)
	if (stime > 2400.0f && stime < 2460.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	ChangeMeasure(2400.0f,2700.0f);

	//45�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 600 && ProgressBar[2].Object.Pos.x < 660) || */(stime > 2700.0f && stime < 2760.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		MeasureFlag = false;

		//�A�N�V�������ς�鏈��
		actionui.SetState(1);

	}

	//55�b�o������(1�b��60)
	if (stime > 3300.0f && stime < 3360.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;
	}
	//�����Ōv�����鏈��
	ChangeMeasure(3300.0f,3600.0f);

	//60�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 750 && ProgressBar[2].Object.Pos.x < 760) || */(stime > 3600.0f && stime < 3660.0f))
	{
		MeasureFlag = false;

		//�o�g���^�b�`����
		if (Section == 1) {
			batontouch.StateBaton = true;
			GameState_Change(GAME_STATE_BATONTOUCH);
			Section = 2;

			//�A�N�V�������ς�鏈��
			actionui.SetState(1);

		}
	}

	//===================���3===============================

	//70�b�o������(1�b��60)
	if (stime > 4200.0f && stime < 4260.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	ChangeMeasure(4200.0f,4500.0f);

	//75�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 900 && ProgressBar[2].Object.Pos.x < 910) || */(stime > 4500.0f && stime < 4560.0f))
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		MeasureFlag = false;

		//�A�N�V�������ς�鏈��
		actionui.SetState(2);

	}

	//85�b�o������(1�b��60)
	if (stime > 5100.0f && stime < 5160.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	ChangeMeasure(5100.0f,5400.0f);

	//90�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 1050 && ProgressBar[2].Object.Pos.x < 1010) || */(stime > 5400.0f && stime < 5460.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "GOAL!!");
		MeasureFlag = false;

		//�Q�[���N���A����
		if (Section == 2) {
			GameState_Change(GAME_STATE_GAME_CLEAR);
			Section = 3;
		}
	}

}

void GameProgress::Draw()
{
	//�f�o�b�N�p
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�o��:%d�b",  stime/60);
	//DrawFormatString(200, 500, GetColor(255, 255, 255), "airou�̈ʒu:%f", ProgressBar[2].Object.Pos.x);

	//�v���O���X�o�[�̃t���[��
	//ProgressBar[0].Draw(PROGRESS_WIDTH+20, PROGRESS_HEIGHT+20);
	ProgressBar[0].Draw();

	//��������v���O���X�o�[
	//ProgressBar[1].Draw(200, 60, NowProgress, PROGRESS_HEIGHT,TRUE,FALSE);
	ProgressBar[1].Draw();

	//�L�����A�C�R��
	//ProgressBar[2].Draw(NowProgress+180.0f, 50, 2.0f,2.0f, 256, 256, TRUE, FALSE);
	ProgressBar[2].Draw();

	DrawFormatString(0, 300, GetColor(255, 255, 255), "Distance:%f", RunDistance);


}


int GameProgress::GetSection() {
	return Section;
}

void GameProgress::SetMesureflag(bool flag)
{
	MeasureFlag = flag;
}

float GameProgress::GetProgressBarObjectPosx()
{
	return ProgressBar[2].Object.Pos.x;
}

void GameProgress::ChangeMeasure(float time1, float time2)
{
	//�����Ōv�����鏈��
	if (MeasureFlag == true && stime >= time1 && stime <= time2)
	{
		if (keyboard.IsTrigger(DIK_RIGHTARROW))
		{
			RunDistance += gamedata.GetRunningDistance() / 1000;		//�Q�b�g���������f�[�^������
			if (RunDistance >= gamedata.GetRunningDistance() / 1000)
			{
				NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
				NowProgress += stime / 6.4f;
				ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;
				stime += 15.0f;
				RunDistance = 0.0f;
			}

		}

	}

}