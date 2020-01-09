#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include <DxLib.h>
#include "ResultScore.h"

static GameObject obj[1];
static ResultScore score[6];
static ResultScore ui;
static int g_TotalScore;
double ranking[RANKING_MAX] = { 0 ,0,0,0,0 };


void Init_Result()
{

	//����������
	int Distance_p = gamedata.GetRunningDistance();

	//�A�N�V�����|�C���g
	int Action_p = gamedata.GetActionPoint();

	//���v�X�R�A
	g_TotalScore = ((Distance_p * 3 / 2 + (Action_p * 2) / 2)*2);


	//�����L���O�̓ǂݍ���
	Ranking_Read();

	//�\�[�g���������L���O�̔��f
	Ranking_Sort(g_TotalScore);

	//��ʂ̔w�i�\��
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.0f;
	obj[0].Object.Scale.y = 1.0f;

	ui.Init();
	
	//�����L���O�̕\��
	for (int i = 0; i < RANKING_MAX; i++)
	{
		score[i].ScoreCreate(ranking[i], SCREEN_WIDTH / 2 - 200, 100*i);

	}

	//���v�X�R�A�̕\��
	score[5].ScoreCreate(g_TotalScore, SCREEN_WIDTH / 2 - 200, 600);

}

void Uninit_Result()
{

}

void Update_Result()
{
	ui.Update();

	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result()
{

	obj[0].Draw();

	for (int i = 0; i < RANKING_MAX; i++)
	{
		DrawFormatString(0, i*30, GetColor(255, 255, 255), "%d ��", i + 1);

		DrawFormatString(100, i*30, GetColor(255, 255, 255), "%f \n", ranking[i]);

	}


	//DrawFormatString(0, 0, GetColor(255, 255, 255), "����������:%d", gamedata.GetRunningDistance());

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "�A�N�V�����|�C���g:%d", gamedata.GetActionPoint());


	DrawFormatString(500, 0, GetColor(255, 255, 255), "���v:%d", g_TotalScore);

	score[0].Draw();
	score[1].Draw();
	score[2].Draw();
	score[3].Draw();
	score[4].Draw();
	score[5].Draw();

	ui.Draw();
}




void Ranking_Sort(double score) {
	FILE* fp;

	fopen_s(&fp, "file.bin", "wb");

	if (fp == NULL)
	{
		printf("%s�̃I�[�v���Ɏ��s���܂����B\n", "file.bin");
		return;
	}

	int i;
	int j;

	//�����L���O�̍~������
	for (i = 0; i < RANKING_MAX; i++) {//1�ʂ����r
		//���̏��ʂ���������΂��ꂪ����̏��ʂƂȂ�
		//(1�ʂ�荂�����1�ʁA1�ʂ��Ⴍ2�ʂ�荂�����2�ʁA�c)
		if (score > ranking[i]) {
			for (j = RANKING_MAX - 1; j > i; j--) {//����̏��ʈȍ~�̃X�R�A�����炷
				ranking[j] = ranking[j - 1];
			}
			ranking[i] = score;//����̃X�R�A���L��
			break;//�ȍ~�̏��ʂ͒��ׂȂ�
		}
	}
	//�����L���O�̕ۑ�
	fwrite(ranking, sizeof(ranking), 5, fp);

	fclose(fp);
}

void Ranking_Read() {

	FILE* fp;

	fopen_s(&fp, "file.bin", "rb");

	if (fp == NULL)
	{
		printf("%s�̃I�[�v���Ɏ��s���܂����B\n", "file.bin");
		return;
	}

	fread(ranking, sizeof(ranking), 5, fp);
	fclose(fp);
}

