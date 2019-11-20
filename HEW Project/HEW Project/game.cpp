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


// Debug Mode
#define DEBUG

/* 
�v���g�^�C�v�錾
*/

// ���鏈��
void Running();
// Debug�p�l��
void Debug_Panel();
// �L�����N�^�[����
void CharacterMove();
// Debug���� (�L�[�{�[�h)
void Debug_Running();



/*
�O���[�o���ϐ�
*/

// �X�r�[�g�v�Z�p
std::vector<int> Speed_Array;
static int Max_Count;
static int Judge_Count;
// �A�N�V����UI
ActionUI Action;
// �A�N�V�����Q�[�W
ActionSlot Actionslot;
// �A�N�V�������s�摜
GameObject Failed;

Live2D Character;

GameProgress gameprogress;

StaminaGauge stamina;

void Init_Game() {
	
	//�X�^�~�i�Q�[�W������
	stamina.Init();

	// �A�N�V����UI������

	Action.Init();

	Action.Pos.x = 700;

	Action.Pos.y = 200;

	Action.Interval.x = 150;

	Action.Interval.y = 0;



	// �A�N�V�����Q�[�W������

	Actionslot.Pos.x = 80;

	Actionslot.Pos.y = 500;

	Actionslot.Load();


	// �L�����N�^�[������

	Character.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);

	Character.Zoom.x = 0.5f;

	Character.Zoom.y = 0.5f;

	Character.Pos.x = -580;

	Character.Pos.y = -150;



	// �A�N�V�������s������

	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_END]);

	Failed.Object.Pos.x = 600;

	Failed.Object.Pos.y = 200;

	// �Q�[���f�[�^������

	gamedata.Init();

	//�Q�[���i�s�o�[������
	gameprogress.Init();

}

void Uninit_Game() {

	Character.~Live2D();
	Action.~ActionUI();
}

void Update_Game() {

	//�X�^�~�i�Q�[�W�X�V����
	stamina.Update();

	Character.SetMontionIndex(GetRand(8));

	// �A�N�V����UI�X�V
	Action.Update();
	// �A�N�V�����Q�[�W�X�V
	Actionslot.Update();
	// �X�r�[�g�X�V
	gamedata.UpdateSpeed();

	// ���鏈��
	Running();

	gameprogress.Update();

	// �L�����N�^�[����

	CharacterMove();


#ifdef DEBUG

	// Go Title

	if (keyboard.IsTrigger(DIK_R)) {

		Scene_Change(SCENE_INDEX_TITLE);

	}

	// Go Result

	if (keyboard.IsTrigger(DIK_ESCAPE)) {

		Scene_Change(SCENE_INDEX_RESULT);

	}



	Debug_Running();

#endif // DEBUG

}

void Draw_Game() {
	
	//�X�^�~�i�Q�[�W�`��
	stamina.Draw();

	// �A�N�V����UI�`��
	Action.Draw();
	// �A�N�V�����Q�[�W�`��
	Actionslot.Draw();

	Character.Draw();

	gameprogress.Draw();


	// �A�N�V������������
	if (Action.GetFinishFlag()) {
		if (Action.GetProgress() == Action.GetActionAmount()) {
			Actionslot.AddValue(0.5);
		}
		else {
		
		}
	}

#ifdef DEBUG
	Debug_Panel();
#endif // DEBUG

}

void Running() {

	if (joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[0] = true;
		Speed_Array.push_back(joycon[1].GetGyro_Y());
	}

	if (joycon[1].Action_Judge[0] && joycon[1].GetGyro_Y() < -200) {
		joycon[1].Action_Judge[1] = true;
	}

	if (joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[2] = true;
	}

	if ((joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].Action_Judge[2])) {
		for (int i = 0; i < 3; i++) {
			joycon[1].Action_Judge[i] = false;
		}
		vector<int>::iterator iter = max_element(Speed_Array.begin(), Speed_Array.end());
		Max_Count = *iter;
		Judge_Count += Max_Count;

		if (Judge_Count > 1000) {
			gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
			Judge_Count = 0;
		}

		gamedata.SetRunningSpeed(405);

		Speed_Array.clear();
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void CharacterMove() {

	// �E

	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.0) {

		Character.Pos.x += 5.0f;

		Character.Zoom.x += 0.0025f;

		Character.Zoom.y += 0.0025f;

		Character.Pos.y += 0.75f;

		Actionslot.Pos.x += 5.4f;

		Actionslot.Pos.y -= 0.75f;

		Actionslot.Scale += D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset += D3DXVECTOR2(0.45f, 0.25f);

	}



	// ��

	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 0.5) {

		Character.Pos.x -= 5.0f;

		Character.Zoom.x -= 0.0025f;

		Character.Zoom.y -= 0.0025f;

		Character.Pos.y -= 0.75f;

		Actionslot.Pos.x -= 5.4f;

		Actionslot.Pos.y += 0.75f;

		Actionslot.Scale -= D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset -= D3DXVECTOR2(0.45f, 0.25f);

	}



}



void Debug_Running() {



	if (keyboard.IsPress(DIK_RIGHTARROW)) {

		Judge_Count += 350;

	}



	if (Judge_Count > 350) {

		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

		gamedata.SetRunningSpeed(405);

		Judge_Count = 0;

	}



	if (gamedata.GetRunningSpeed() > 0) {

		gamedata.AddRunningSpeed(-15);

	}



	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

}



void Debug_Panel() {

	SetFontSize(24);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "���鋗�� : %d", gamedata.GetRunningMeter());

	DrawFormatString(0, 30, GetColor(255, 255, 255), "�A�N�V�����Q�[�W : %f", Actionslot.GetValue());

	DrawFormatString(0, 60, GetColor(255, 255, 255), "�A�N�V�����Q�[�W��� : %d", Actionslot.GetState());

	DrawFormatString(0, 90, GetColor(255, 255, 255), "�A�N�V������� : %d", Action.GetState());

	DrawFormatString(0, 120, GetColor(255, 255, 255), "�X�r�[�g : %d", gamedata.GetRunningSpeed());

	DrawFormatString(0, 150, GetColor(255, 255, 255), "���� : %d", gamedata.Gethp());

	DrawFormatString(0, 180, GetColor(255, 255, 255), "�A�N�V�����|�C���g�F %d", gamedata.GetActionPoint());

	DrawFormatString(0, 210, GetColor(255, 255, 255), "�o��:%d�b",gameprogress.stime / 60);


}