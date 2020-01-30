#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include "DxLib.h"
#include <DxLib.h>
#include <string>
#include "ResultScore.h"


static GameObject obj[2];
static ResultScore score[6];
static ResultScore ui;
static int g_TotalScore;
double ranking[RANKING_MAX] = { 0,0,0,0,0 };
double Runranking[RANKING_MAX] = { 0,0,0,0,0 };
static int seSystemHandle;     // �V�X�e��SE�n���h��

// �������L���������L���O�����(���U���g�ɕ\���͂��Ȃ�)


void Init_Result()
{

	//����������
	int Distance_p = gamedata.GetRunningDistance();

	//�A�N�V�����|�C���g
	int Action_p = gamedata.GetActionPoint();

	//���v�X�R�A
	g_TotalScore = ((Distance_p * 3 / 2 + (Action_p * 2) / 2)*2);


	//�����L���O�̓ǂݍ���(�R�����g�A�E�g�Ń����L���O���Z�b�g)
	Ranking_Read();

	//�\�[�g���������L���O�̔��f
	Ranking_Sort(g_TotalScore);

	// �������L���������L���O���\�[�g���ăo�C�i���t�@�C���ɏ�������
	RunningRanking_Wright(Distance_p);

	//��ʂ̔w�i�\��
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.00f;
	obj[0].Object.Scale.y = 1.00f;

	obj[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_RESULT_BG]);
	obj[1].Object.Pos.x = 400.0f;
	obj[1].Object.Pos.y = 460.0f;
	obj[1].Object.Scale.x = 0.75f;
	obj[1].Object.Scale.y = 0.75f;


	ui.Init();
	
	//�����L���O�̕\��
	for (int i = 0; i < RANKING_MAX; i++)
	{
		score[i].ScoreCreate(ranking[i], SCREEN_WIDTH / 2 - 200, 100*i);

	}

	//���v�X�R�A�̕\��
	score[5].ScoreCreate(g_TotalScore, SCREEN_WIDTH / 2 - 200, 600);


	// BGM�Đ�
	PlaySoundFile("asset/sound/BGM/gameclear.mp3", DX_PLAYTYPE_LOOP);

	// �V�X�e��SE�n���h��
	seSystemHandle = LoadSoundMem("asset/sound/SE/UI-systemSE.mp3");

}

void Uninit_Result()
{
	// BGM���~�߂�
	StopSoundFile();
}

void Update_Result()
{
	ui.Update();

	if (keyboard.IsTrigger(DIK_R)) {
		PlaySoundMem(seSystemHandle, DX_PLAYTYPE_BACK);     // SE�Đ�
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result()
{

	obj[0].Draw();
	obj[1].Draw();


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



	// �\�[�g���������L���O��.txt�ŕۑ�
	std::string tmp[RANKING_MAX] = { "0","0","0","0","0" };     // .txt�ɕۑ�����p�̕ϐ�
	FILE* fp_Filetxt;
	const char* FileNametxt = "file.txt";
	fopen_s(&fp_Filetxt, FileNametxt, "w");
	if (fp_Filetxt == NULL) { printf_s("%s �t�@�C�����J���܂���ł����B", FileNametxt); exit(1); }
	for (int n = 0; n < RANKING_MAX; n++)
	{
		tmp[n] = std::to_string((int)ranking[n]);
		fprintf(fp_Filetxt, "%s\n", tmp[n].c_str());     // �����L���O�̕ۑ�
	}
	fclose(fp_Filetxt);


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


// �������L���������L���O(����̑������L����)
void RunningRanking_Wright(double RunningDistans)
{
	FILE* fp_Running;     // �t�@�C���|�C���^
	const char* FileName = "RunningRunkingFile.bin";     // �o�C�i���̃t�@�C���l�[��
	const char* FileNametxt = "RunningRunkingFile.txt";     // .txt�̃t�@�C���l�[��

	//================= �����L���O�t�@�C���ǂݎ�� =================// ���R�����g�A�E�g�Ń����L���O���Z�b�g
	fopen_s(&fp_Running, FileName, "rb");
	if (fp_Running == NULL){ printf_s("%s �t�@�C�����J���܂���ł����B", FileName); exit(1); }
	fread(Runranking, sizeof(Runranking), RANKING_MAX, fp_Running);     // �������L���������L���O�ɏ�ʂT��ǂݎ��
	fclose(fp_Running);
	//================= �����L���O�t�@�C���ǂݎ�� =================//



	//================= �����L���O�\�[�g =================//
	fopen_s(&fp_Running, FileName, "wb");
	if (fp_Running == NULL) { printf_s("%s �t�@�C�����J���܂���ł����B", FileName); exit(1); }
	//// �����L���O�̍~������ ////
	int i, j;
	for (i = 0; i < RANKING_MAX; i++) {//1�ʂ����r
		//���̏��ʂ���������΂��ꂪ����̏��ʂƂȂ�
		//(1�ʂ�荂�����1�ʁA1�ʂ��Ⴍ2�ʂ�荂�����2�ʁA�c)
		if (RunningDistans > Runranking[i]) {
			for (j = RANKING_MAX - 1; j > i; j--) {//����̏��ʈȍ~�̃X�R�A�����炷
				Runranking[j] = Runranking[j - 1];
			}
			Runranking[i] = RunningDistans;//����̃X�R�A���L��
			break;//�ȍ~�̏��ʂ͒��ׂȂ�
		}
	}
	fwrite(Runranking, sizeof(Runranking), RANKING_MAX, fp_Running);     // �����L���O�̕ۑ�
	fclose(fp_Running);
	//================= �����L���O�\�[�g =================//
	


	// �\�[�g���������L���O��.txt�ŕۑ�
	std::string tmp[RANKING_MAX] = { "0","0","0","0","0" };     // .txt�ɕۑ�����p�̕ϐ�
	FILE* fp_Runningtxt;
	fopen_s(&fp_Runningtxt, FileNametxt, "w");
	if (fp_Runningtxt == NULL) { printf_s("%s �t�@�C�����J���܂���ł����B", FileNametxt); exit(1); }
	for(int n = 0; n < RANKING_MAX; n++)
	{
		tmp[n] = std::to_string((int)Runranking[n]);
		fprintf(fp_Runningtxt, "%s\n", tmp[n].c_str());     // �����L���O�̕ۑ�
	}
	fclose(fp_Runningtxt);

}