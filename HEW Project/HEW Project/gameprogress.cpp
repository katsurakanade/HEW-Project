//13210_�Q�[���i�s�o�[
/*------------------------------------------------------------------
@brief	�Q�[���̐i�s�o�[
@author	�������V
@date	2019/11/18
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

static GameObject ProgressBar[3];
static GameData rundata;
BatonTouch batontouch;

void GameProgress::Init() 
{
	if (Initflag == true) 
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
		GameFinish = false;
		Initflag = false;
		MeasureFlag = false;
	}
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
		//ProgressBar[1].Object.Scale.x = NowProgress;

		//�L�����A�C�R���̈ړ�����
		ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;

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
		//MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//�A�N�V�����`�F���W�|�C���g�ɒ�������
	//15�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 300 && ProgressBar[2].Object.Pos.x < 310) ||*/ (stime > 900.0f && stime < 960.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		//MeasureFlag = false;

		//�A�N�V�������ς�鏈��

	}

	//25�b�o������(1�b��60)
	if (stime > 1500.0f && stime < 1560.0f) 
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		//MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//30�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 450 && ProgressBar[2].Object.Pos.x < 460) || */(stime > 1800.0f && stime < 1860.0f))
	{
		//MeasureFlag = false;

		//�o�g���^�b�`����
		if (Section == 0) {
			batontouch.StateBaton = true;
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			Section = 1;
		}
	}
	//===================���2===============================

	//40�b�o������(1�b��60)
	if (stime > 2400.0f && stime < 2460.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		//MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//45�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 600 && ProgressBar[2].Object.Pos.x < 660) || */(stime > 3000.0f && stime < 3060.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		//MeasureFlag = false;

		//�A�N�V�������ς�鏈��

	}

	//55�b�o������(1�b��60)
	if (stime > 3300.0f && stime < 3360.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		//MeasureFlag = true;
	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//60�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 750 && ProgressBar[2].Object.Pos.x < 760) || */(stime > 3600.0f && stime < 3660.0f))
	{
		//MeasureFlag = false;

		//�o�g���^�b�`����
		if (Section == 1) {
			batontouch.StateBaton = true;
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			Section = 2;
		}
	}

	//===================���3===============================

	//70�b�o������(1�b��60)
	if (stime > 4200.0f && stime < 4260.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		//MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//75�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 900 && ProgressBar[2].Object.Pos.x < 910) || */(stime > 4500.0f && stime < 4560.0f))
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�A�N�V�����`�F���W");
		//MeasureFlag = false;

		//�A�N�V�������ς�鏈��

	}

	//85�b�o������(1�b��60)
	if (stime > 5100.0f && stime < 5160.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "�c��10m!!");
		//�����Ōv�����鏈���ɐ؂�ւ�
		//MeasureFlag = true;

	}
	//�����Ōv�����鏈��
	if (MeasureFlag == true)
	{
		ProgressBar[2].Object.Pos.x += rundata.GetRunningDistance();
		stime += rundata.GetRunningDistance();
	}

	//90�b�o������(1�b��60)
	if (/*(ProgressBar[2].Object.Pos.x > 1050 && ProgressBar[2].Object.Pos.x < 1010) || */(stime > 5400.0f && stime < 5460.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "GOAL!!");
		//MeasureFlag = false;

		//�o�g���^�b�`����
		if (Section == 2) {
			Scene_Change(SCENE_INDEX_RESULT);
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
	//ProgressBar[1].Draw(200, 50, NowProgress+200.0f, PROGRESS_HEIGHT,TRUE);
	ProgressBar[1].Draw();

	//�L�����A�C�R��
	//ProgressBar[2].Draw(NowProgress+180.0f, 50, 2.0f,2.0f, 256, 256, TRUE, FALSE);
	ProgressBar[2].Draw();

}


int GameProgress::GetSection() {
	return Section;
}

void GameProgress::SetMesureflag(bool flag)
{
	MeasureFlag = flag;
}