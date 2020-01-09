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

#include "Effect.h"


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

// �Q�[���X�e�[�g�J�ڗp�ϐ�
static GAME_STATE g_GameStateIndex;
static GAME_STATE g_GameStateNextIndex;

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
// Live2D�L�����N�^�[
Live2D Character;
// �Q�[���i�s�o�[
GameProgress *gameprogress;
// �X�^�~�i�Q�[�W
StaminaGauge *stamina;
//�w�i
BackGround background;
//�o�g���^�b�`
BatonTouch batonTouch;

GameOver *gameover;

GameClear *gameclear;

// �A�N�V�����G�t�F�N�g�p
std::vector<ActionAffect*> ActionEffectVector;

std::vector <ActionPointAnime*> ActionPointVector;


typedef void(*GameStateFunc)(void);

static const GameStateFunc Initialize[] = {
	Init_GameStart,     //�o�g���^�b�`�̃Q�[���X�^�[�g������Init
	Init_GameState,     //2���, �R��ԗpInit
	Init_BatonTouch,
	Init_GameOver,     //�Q�[���I�[�o�[�̃Q�[���X�^�[�g������Init
	Init_GameClear,     //�Q�[���N���A�̃Q�[���X�^�[�g������Init
};


void GameState_Initialize(GAME_STATE index)
{
	g_GameStateNextIndex = g_GameStateIndex = index;

	Initialize[g_GameStateIndex]();
}



void Init_Game() {

	gameprogress = new GameProgress;
	stamina = new StaminaGauge;
	gameover = new GameOver;
	gameclear = new GameClear;

	// �Ƃ肠����Game�𓮂����Ă݂�----------------------------------------------------------------
	g_GameStateIndex = GAME_STATE_GAME;
	g_GameStateNextIndex = GAME_STATE_GAME;
	// �Ƃ肠����Game�𓮂����Ă݂�


	//�X�^�~�i�Q�[�W������
	stamina->Init();

	// �A�N�V����UI������	

	Action.Init();

	Action.Pos.x = 700;

	Action.Pos.y = 200;

	Action.Interval.x = 150;

	Action.Interval.y = 0;

	// �A�N�V�����Q�[�W������

	Actionslot.Load();

	Actionslot.Pos.x = 330;

	Actionslot.Pos.y = 450;

	// �L�����N�^�[������

	Character.LoadModel(Live2D_Dict["HIYORI"]);

	Character.Zoom.x = 1.0f;

	Character.Zoom.y = 1.0f;

	Character.Pos.x = -400;

	Character.Pos.y = -150;

	// �A�N�V�������s������

	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_END]);

	Failed.Object.Pos.x = 600;

	Failed.Object.Pos.y = 200;

	// �Q�[���f�[�^������

	gamedata.Init();

	//�Q�[���i�s�o�[������
	gameprogress->Init();

	background.Init();

	gameover->Init();

	batonTouch.Init();

	Init_GameClear();



	////////////////////////////////////////////////////
	EffectInit();		 //�G�t�F�N�g�����p
	////////////////////////////////////////////////////


}


// �Q���, �R��ԗpInit(�֐����͋C�ɂ��Ȃ���)
void Init_GameState()
{

}


void Uninit_Game() {


	Character.~Live2D();

	gameprogress = nullptr;
	delete gameprogress;

	stamina = nullptr;
	delete stamina;

	gameover = nullptr;
	delete gameover;

	gameclear = nullptr;
	delete gameclear;

	ActionEffectVector.~vector();
	ActionPointVector.~vector();

	batonTouch.Uninit();


}

void Update_Game() {

	switch (g_GameStateIndex)
	{

	case GAME_STATE_START:     // BattonTouch�̃Q�[���X�^�[�g����--------------------------------------------------------

		break;


	case GAME_STATE_GAME:      //�Q�[��������------------------------------------------------------------------------------

		//�X�^�~�i�Q�[�W�X�V����
		stamina->Update();

		Character.SetMontionIndex(GetRand(8));

		// �A�N�V����UI�X�V
		Action.Update();
		// �A�N�V�����Q�[�W�X�V
		Actionslot.Update(stamina->GetStaminaScale_x());
		// �X�r�[�g�X�V
		gamedata.UpdateSpeed();

		// ���鏈��
		Running();

		// �Q�[���i�s�o�[����
		gameprogress->Update(Action);

		// �L�����N�^�[����

		CharacterMove();

		gameover->Update();

		// �A�N�V�����G�t�F�N�g����
		for (int i = 0; i < ActionEffectVector.size(); i++) {
			if (ActionEffectVector[i] != NULL) {
				ActionEffectVector[i]->Update();
			}
		}

		for (int i = 0; i < ActionPointVector.size(); i++) {
			if (ActionPointVector[i]->OutFlag) {
				continue;
			}
			ActionPointVector[i]->Update();
		}

		if (gamedata.GetRunningSpeed() != 0) {
			background.SetSpeed(gamedata.GetRunningSpeed() / 10);
		}

		else {
			background.SetSpeed(1.0);
		}

		background.Update();

		//���΂���������GAME OVER
		/*if (gamedata.Gethp() == 0)
		{
			GameState_Change(GAME_STATE_GAME_OVER);
		}
		*/
		Debug_Running();

		////////////////////////////////////////////////////
		EffectUpdate();     //�G�t�F�N�g�����p
		////////////////////////////////////////////////////

		break;


	case GAME_STATE_BATONTOUCH:     // BattonTouch�̃o�g���^�b�`����--------------------------------------------------

		batonTouch.Update();

		break;


	case GAME_STATE_GAME_OVER:     // GAME OVER��Update����----------------------------------------------------------

		gameover->Update();

		break;


	case 	GAME_STATE_GAME_CLEAR:     // GAME CLEAR��Update����--------------------------------------------------------

		gameclear->Update();

		break;

	}



#ifdef DEBUG

	// Go Title
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

	// Go Result
	if (keyboard.IsTrigger(DIK_ESCAPE)) {
		Scene_Change(SCENE_INDEX_RESULT);
	}

	// Remove Trash
	if (keyboard.IsPress(DIK_Q)) {

		std::vector<ActionAffect*>().swap(ActionEffectVector);
		std::vector<ActionPointAnime*>().swap(ActionPointVector);
	}

	if (keyboard.IsPress(DIK_E)) {
		Actionslot.AddValue(0.5);
	}

#endif // DEBUG


}

void Draw_Game() {


	switch (g_GameStateIndex)
	{

	case GAME_STATE_START:     // BattonTouch�̃Q�[���X�^�[�g����--------------------------------------------------------
		
		break;

	case GAME_STATE_GAME:      //�Q�[��������------------------------------------------------------------------------------

		background.Draw();

		//�X�^�~�i�Q�[�W�`��
		stamina->Draw();

		// �A�N�V����UI�`��
		Action.Draw();
		// �A�N�V�����Q�[�W�`��
		Actionslot.Draw();

		gameprogress->Draw();

		// �A�N�V������������
		if (Action.GetFinishFlag()) {
			if (Action.GetProgress() == Action.GetActionAmount()) {
				Actionslot.AddValue(0.5);
			}
			else {

			}
		}


		// �A�N�V�����G�t�F�N�g�`��
		for (int i = 0; i < ActionEffectVector.size(); i++) {
			if (ActionEffectVector[i] != NULL) {
				ActionEffectVector[i]->Draw_Affect();
			}
		}

		for (int i = 0; i < ActionPointVector.size(); i++) {
			ActionPointVector[i]->Draw();
		}

		Character.Draw();


		////////////////////////////////////////////////////
		//EffectDraw();	 //�G�t�F�N�g�����p
		////////////////////////////////////////////////////


		break;


	case GAME_STATE_BATONTOUCH:     // BattonTouch�̃o�g���^�b�`����--------------------------------------------------

		batonTouch.Draw();

		break;


	case GAME_STATE_GAME_OVER:     // GAME OVER��Update����----------------------------------------------------------

		//---------------------------------���Q�[����ʕ`�恫----------------------------------------

		background.Draw();

		//�X�^�~�i�Q�[�W�`��
		stamina->Draw();

		// �A�N�V����UI�`��
		Action.Draw();
		// �A�N�V�����Q�[�W�`��
		Actionslot.Draw();

		gameprogress->Draw();

		// �A�N�V������������
		if (Action.GetFinishFlag()) {
			if (Action.GetProgress() == Action.GetActionAmount()) {
				Actionslot.AddValue(0.5);
			}
			else {

			}
		}

		// �A�N�V�����G�t�F�N�g�`��
		for (int i = 0; i < ActionEffectVector.size(); i++) {
			if (ActionEffectVector[i] != NULL) {
				ActionEffectVector[i]->Draw_Affect();
			}
		}

		for (int i = 0; i < ActionPointVector.size(); i++) {
			ActionPointVector[i]->Draw();
		}

		Character.Draw();

		//---------------------------------���Q�[����ʕ`�恪----------------------------------------

		gameover->Draw();     //GAME OVER�̕`��

		break;

	case 	GAME_STATE_GAME_CLEAR:     // GAME CLEAR��Update����--------------------------------------------------------

		gameclear->Draw();

		break;

	}


	GameState_Check();     //�Q�[���X�e�[�g�؂�ւ�����


#ifdef DEBUG
	Debug_Panel();
#endif // DEBUG

}


//�X�e�[�g�؂�ւ�����
void GameState_Check(void)
{
	if (g_GameStateIndex != g_GameStateNextIndex) {
		GameState_Initialize(g_GameStateNextIndex);
	}
}

//�؂�ւ��X�e�[�g�ݒ�
void GameState_Change(GAME_STATE index)
{
	g_GameStateNextIndex = index;
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


		ActionPointAnime *obj = new ActionPointAnime();

		ActionAffect *tmp = new ActionAffect(Actionslot.GetState());

		switch (Actionslot.GetState())
		{
		case ACTIONSLOT_OVER:
			obj->Create(150);
			break;
		case ACTIONSLOT_GREAT:
			obj->Create(120);
			break;
		case ACTIONSLOT_GOOD:
			obj->Create(50);
			break;
		case ACTIONSLOT_BAD:
			break;
		}

		ActionEffectVector.push_back(tmp);

		ActionPointVector.push_back(obj);
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void CharacterMove() {

	// �E

	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.3) {

		Character.Pos.x += 5.0f;

		Character.Zoom.x += 0.0025f;

		Character.Zoom.y += 0.0025f;

		Character.Pos.y -= 0.75f;

		Actionslot.Pos.x += 5.0f;

		Actionslot.Pos.y += 0.75f;

		Actionslot.Scale += D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset += D3DXVECTOR2(0.75f, 0.15f);

		Actionslot.offsect_dis += 0.03;
	}

	// ��

	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 1.0) {

		Character.Pos.x -= 5.0f;

		Character.Zoom.x -= 0.0025f;

		Character.Zoom.y -= 0.0025f;

		Character.Pos.y += 0.75f;

		Actionslot.Pos.x -= 5.0f;

		Actionslot.Pos.y -= 0.75f;

		Actionslot.Scale -= D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset -= D3DXVECTOR2(0.75f, 0.15f);

		Actionslot.offsect_dis -= 0.03;
	}

}

void Debug_Running() {

	if (keyboard.IsTrigger(DIK_RIGHTARROW)) {
		Judge_Count += 350;
	}

	if (Judge_Count >= 350) {

		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

		gamedata.SetRunningSpeed(405);

		Judge_Count = 0;

		gamedata.Action_Point_Update(Actionslot.GetState());

		ActionPointAnime *obj = new ActionPointAnime();

		ActionAffect *tmp = new ActionAffect(Actionslot.GetState());

		switch (Actionslot.GetState())
		{
		case ACTIONSLOT_OVER:
			obj->Create(150);
			break;
		case ACTIONSLOT_GREAT:
			obj->Create(120);
			break;
		case ACTIONSLOT_GOOD:
			obj->Create(50);
			break;
		case ACTIONSLOT_BAD:
			break;
		}

		ActionEffectVector.push_back(tmp);

		ActionPointVector.push_back(obj);


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

	DrawFormatString(0, 210, GetColor(255, 255, 255), "�o��:%f�b", gameprogress->stime / 60);


}