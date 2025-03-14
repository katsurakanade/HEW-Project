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
#include "DxLib.h"
#include "gameprogress.h"
#include "Staminagauge.h"
#include "ActionAffect.h"
#include "BackGround.h"
#include "GameOver.h"
#include "BatonTouch.h"
#include "GameClear.h"
#include "EffectGame.h"


// Debug Mode
#define DEBUG


/*
グローバル変数
*/

// ゲームステート遷移用変数
static GAME_STATE g_GameStateIndex;
static GAME_STATE g_GameStateNextIndex;

// スビート計算用
std::vector<int> Speed_Array;
static int Max_Count;
static int Judge_Count;
// アクションUI
ActionUI Action;
// アクションゲージ
ActionSlot Actionslot;
// アクション失敗画像
GameObject Failed;
// Live2Dキャラクター
Live2D Character;
// ゲーム進行バー
GameProgress *gameprogress;
// スタミナゲージ
StaminaGauge *stamina;
//背景
BackGround background;

GameObject ExcellentFrame;

GameObject ExcellentImg;

GameObject Alphabg;

//バトンタッチ
BatonTouch batonTouch;

GameOver *gameover;

GameClear *gameclear;
// ゲームエフェクト
EGManager *egmanager;

GameObject ActionBoard;

// アクションエフェクト用
std::vector<ActionAffect*> ActionEffectVector;

std::vector <ActionPointAnime*> ActionPointVector;

//static int sehandle;
static int seHandle;     // SEハンドル

typedef void(*GameStateFunc)(void);

static const GameStateFunc Initialize[] = {
	Init_GameStart,     //バトンタッチのゲームスタート処理のInit
	Init_GameState,     //2区間, ３区間用Init
	Init_BatonTouch,
	Init_GameOver,     //ゲームオーバーのゲームスタート処理のInit
	Init_GameClear,     //ゲームクリアのゲームスタート処理のInit
};


void GameState_Initialize(GAME_STATE index)
{
	g_GameStateNextIndex = g_GameStateIndex = index;

	Initialize[g_GameStateIndex]();
}



void Init_Game() {

	GameState_Initialize(GAME_STATE_START);

	gameprogress = new GameProgress;
	stamina = new StaminaGauge;
	gameover = new GameOver;
	gameclear = new GameClear;

	g_GameStateIndex = GAME_STATE_START;
	g_GameStateNextIndex = GAME_STATE_START;


	//スタミナゲージ初期化
	stamina->Init();

	// アクションUI初期化	

	Action.Init();

	Action.Pos.x = 600;

	Action.Pos.y = 250;

	Action.Interval.x = 190;

	Action.Interval.y = 0;

	// アクションゲージ初期化

	Actionslot.Load();

	Actionslot.Pos.x = 210;

	Actionslot.Pos.y = 480;

	// キャラクター初期化

	Character.LoadModel(Live2D_Dict["KYARA"]);

	Character.Zoom.x = 1.0f;

	Character.Zoom.y = 1.0f;

	Character.Pos.x = -400;

	Character.Pos.y = -150;

	Character.SetMontionIndex(0);

	// アクション失敗初期化

	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_END]);

	Failed.Object.Pos.x = 600;

	Failed.Object.Pos.y = 200;

	// ゲームデータ初期化

	gamedata.Init();

	//ゲーム進行バー初期化
	gameprogress->Init();

	background.Init();

	gameover->Init();

	batonTouch.Init();

	Init_GameClear();

	ExcellentFrame.LoadTexture(TextureDict["alpha"]);
	ExcellentFrame.Object.Pos.x = SCREEN_WIDTH / 2;
	ExcellentFrame.Object.Pos.y = SCREEN_HEIGHT / 2;
	ExcellentFrame.Object.Scale.x = 2.0;
	ExcellentFrame.Object.Scale.y = 2.0;

	ExcellentImg.LoadTexture(TextureDict["excellent"]);
	ExcellentImg.Object.Pos.x = 800;
	ExcellentImg.Object.Pos.y = 200;

	Alphabg.LoadTexture(TextureDict["alphabg"]);
	Alphabg.Object.Pos.x = 0;
	Alphabg.Object.Pos.y = 0;
	Alphabg.Object.Scale.x = 10.0f;
	Alphabg.Object.Scale.y = 10.0f;


	//エフェクト初期化処理
	egmanager->Init();

	//PlaySoundFile("asset/sound/BGM_ActionBoard.mp3", DX_PLAYTYPE_LOOP);
	//sehandle = LoadSoundMem("asset/sound/SE_ActionBoard.mp3");

	ActionBoard.LoadTexture(TextureDict["board"]);
	ActionBoard.Object.Pos.x = Action.Pos.x + 270;
	ActionBoard.Object.Pos.y = Action.Pos.y;
	ActionBoard.Object.Scale.x = 0.8;
	ActionBoard.Object.Scale.y = 0.5;


	// BGM再生
	PlaySoundFile("asset/sound/BGM/gameplay.mp3", DX_PLAYTYPE_LOOP);

	// SEロード
	seHandle = LoadSoundMem("asset/sound/SE/running.mp3");

}


// ２区間, ３区間用Init(関数名は気にしないで)
void Init_GameState()
{
	stamina->SetStaminaGauge(2.0, 2.0);
	batonTouch.Timer = 0;
	batonTouch.Uninit_DoOnce = true;
	// SE再生
	PlaySoundFile("asset/sound/SE/touch-start.mp3", DX_PLAYTYPE_BACK);
	// BGM再生
	PlaySoundFile("asset/sound/BGM/gameplay.mp3", DX_PLAYTYPE_LOOP);
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

	//エフェクト終了処理
	egmanager->Uninit();
	egmanager = nullptr;
	delete egmanager;

	ActionEffectVector.~vector();
	ActionPointVector.~vector();


	Alphabg.Destroy();
	ExcellentFrame.Destroy();
	ExcellentImg.Destroy();

	Alphabg.~GameObject();
	ExcellentFrame.~GameObject();
	ExcellentImg.~GameObject();


	batonTouch.Uninit();

	// BGMを止める
	StopSoundFile();

}

void Update_Game() {

	switch (g_GameStateIndex)
	{

	case GAME_STATE_START:     // BattonTouchのゲームスタート処理--------------------------------------------------------

		// アクションゲージ初期化
		Actionslot.AddValue(VALUE_DEFAULT - Actionslot.GetValue());     //Valueがデフォルト値になる
		Actionslot.Pos.x = 210;
		Actionslot.Pos.y = 480;
		if (batonTouch.Uninit_DoOnce)
		{     //一回だけ更新
			Actionslot.Update(stamina->GetStaminaScale_x(), gamedata.GetExcellentMode());
			batonTouch.Uninit_DoOnce = false;
		}

		batonTouch.Update(BT_GameStart);


		break;


	case GAME_STATE_GAME:      //ゲーム内処理------------------------------------------------------------------------------


		//エフェクト更新処理
		egmanager->Update();

		//スタミナゲージ更新処理
		stamina->Update();

		//Character.SetMontionIndex(GetRand(8));

		// アクションUI更新
		Action.Update();

		// アクションゲージ更新
		Actionslot.Update(stamina->GetStaminaScale_x(),gamedata.GetExcellentMode());

		// アクション完成判定
		if (Action.GetFinishFlag()) {
			if (Action.GetProgress() == Action.GetActionAmount()) {

				switch (Action.GetState())
				{
				case ACTION_STATE_LONGJUMP:
					// change
					Actionslot.AddValue(0.152 * 9);
					break;
				case ACTION_STATE_TRAMPOLINING:
					// change
					Actionslot.AddValue(0.132 * 9);
					break;
				case ACTION_STATE_BALANCEBOARD:
					// change
					Actionslot.AddValue(0.068 * 9);
					break;
				case ACTION_STATE_WEIGHT:
					// change
					Actionslot.AddValue(0.16 * 9);
					break;
				case ACTION_STATE_UNEVENBARS:
					// change
					Actionslot.AddValue(0.152 * 9);
					break;
				default:
					break;
				}
			}
			else {

			}
		}


		// スビート更新
		gamedata.UpdateSpeed();

		// 走る処理
		Running();

		// ゲーム進行バー処理
		gameprogress->Update(Action);

		// キャラクター処理
		CharacterMove();

		gameover->Update();

		if (gamedata.ExcellentModeCount >= 5) {
			gamedata.InitExcellentMode();
		}

		if (gamedata.GetExcellentMode()) {

			gamedata.UpdateExcellentMode(ActionPointVector);
		}


		// アクションエフェクト処理
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


		if (gamedata.GetExcellentMode()) {
			gamedata.UpdateExcellentMode(ActionPointVector);
		}



		if (gamedata.GetRunningSpeed() != 0) {
			background.SetSpeed(gamedata.GetRunningSpeed() / 10);
		}

		else {
			background.SetSpeed(1.0);
		}

		background.Update();

		//聖火が消えたらGAME OVER
		if (gamedata.Gethp() == 0)
		{
			// BGMを止める
			StopSoundFile();

			// BGM再生
			PlaySoundFile("asset/sound/BGM/gameover.mp3", DX_PLAYTYPE_LOOP);

			GameState_Change(GAME_STATE_GAME_OVER);
		}

		Debug_Running();

		///////////////////////////////////////
		// エフェクト実験用（Enterを押したらエフェクト再生）
		if (keyboard.IsTrigger(DIK_RETURN))
		{

			//call_E_game_Sample();     //エフェクト再生
			
		}
		///////////////////////////////////////

		break;


	case GAME_STATE_BATONTOUCH:     // BattonTouchのバトンタッチ処理--------------------------------------------------

			// 区間間の初期化処理
		if (batonTouch.Uninit_DoOnce)
		{
			// SE再生
			PlaySoundFile("asset/sound/SE/touch-start.mp3", DX_PLAYTYPE_BACK);

			//スタミナゲージ初期化
			stamina->Init();

			// アクションゲージ初期化
			Actionslot.AddValue(VALUE_DEFAULT - Actionslot.GetValue());     //Valueがデフォルト値になる
			Actionslot.Pos.x = 210;
			Actionslot.Pos.y = 480;
			Actionslot.Update(stamina->GetStaminaScale_x(), gamedata.GetExcellentMode());

			// キャラクター初期化

			Character.Zoom.x = 1.0f;

			Character.Zoom.y = 1.0f;

			Character.Pos.x = -400;

			Character.Pos.y = -150;

			batonTouch.Uninit_DoOnce = false;
			batonTouch.CharengeFlag = false;
		}


		//エフェクト更新処理
		egmanager->Update();


		batonTouch.Update(BT_BatonTouch);

		// アクションエフェクト処理
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


		break;


	case GAME_STATE_GAME_OVER:     // GAME OVERのUpdate処理----------------------------------------------------------

		gameover->Update();

		break;


	case 	GAME_STATE_GAME_CLEAR:     // GAME CLEARのUpdate処理--------------------------------------------------------

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
		if (Actionslot.GetValue() <= 70.0) {
			Actionslot.AddValue(0.5);
			//PlaySoundMem(sehandle, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	if (keyboard.IsPress(DIK_P)) {
		if (gamedata.ExcellentModeInitFlag == false) {
			gamedata.InitExcellentMode();
		}
	}

	if (keyboard.IsPress(DIK_1)) {
		Character.SetMontionIndex(1);
	}




#endif // DEBUG


}

void Draw_Game() {


	switch (g_GameStateIndex)
	{

	case GAME_STATE_START:     // BattonTouchのゲームスタート処理--------------------------------------------------------

		background.Draw();

		gameprogress->Draw();

		// アクションゲージ描画
		Actionslot.Draw();

		Character.Draw();

		batonTouch.Draw(BT_GameStart);

		break;


	case GAME_STATE_GAME:      //ゲーム内処理------------------------------------------------------------------------------

		// 背景描画
		background.Draw();

		//スタミナゲージ描画
		stamina->Draw();

		// ゲーム進行ゲージ描画
		gameprogress->Draw();

		//エフェクト描画処理
		egmanager->Draw();

		// アクションUI+背景描画
		ActionBoard.Draw();
		Action.Draw();

		// エクセレントモード描画
		if (gamedata.GetExcellentMode()) {
			Alphabg.Draw();
			ExcellentFrame.Draw();
			ExcellentImg.Draw();
		}

		// 流れるアクションポイント描画
		for (int i = 0; i < ActionPointVector.size(); i++) {
			ActionPointVector[i]->Draw();
		}

		// アクションエフェクト描画
		for (int i = 0; i < ActionEffectVector.size(); i++) {
			if (ActionEffectVector[i] != NULL) {
				ActionEffectVector[i]->Draw_Affect();
			}
		}

		// キャラクター+アクションゲージ(腕)描画
		Actionslot.Draw(); 
		Character.Draw();


		break;


	case GAME_STATE_BATONTOUCH:     // BattonTouchのバトンタッチ処理--------------------------------------------------

		background.Draw();

		gameprogress->Draw();

		// アクションゲージ描画
		Actionslot.Draw();

		Character.Draw();

		batonTouch.Draw(BT_BatonTouch);

		//エフェクト描画処理
		egmanager->Draw();

		break;


	case GAME_STATE_GAME_OVER:     // GAME OVERのUpdate処理----------------------------------------------------------

		//---------------------------------↓ゲーム画面描画↓----------------------------------------

		background.Draw();

		//スタミナゲージ描画
		stamina->Draw();

		// アクションUI描画
		Action.Draw();
		// アクションゲージ描画
		Actionslot.Draw();

		gameprogress->Draw();

		// アクション完成判定
		if (Action.GetFinishFlag()) {
			if (Action.GetProgress() == Action.GetActionAmount()) {
				if (Actionslot.GetValue() <= 90.0) {
					Actionslot.AddValue(0.5);
				}
			}
			else {

			}
		}

		// アクションエフェクト描画
		for (int i = 0; i < ActionEffectVector.size(); i++) {
			if (ActionEffectVector[i] != NULL) {
				ActionEffectVector[i]->Draw_Affect();
			}
		}

		for (int i = 0; i < ActionPointVector.size(); i++) {
			ActionPointVector[i]->Draw();
		}

		Character.Draw();

		//---------------------------------↑ゲーム画面描画↑----------------------------------------

		gameover->Draw();     //GAME OVERの描画

		break;

	case 	GAME_STATE_GAME_CLEAR:     // GAME CLEARのUpdate処理--------------------------------------------------------

		gameclear->Draw();

		break;

	}


	GameState_Check();     //ゲームステート切り替え処理


#ifdef DEBUG
	//Debug_Panel();
#endif // DEBUG

}


//ステート切り替え処理
void GameState_Check(void)
{
	if (g_GameStateIndex != g_GameStateNextIndex) {
		GameState_Initialize(g_GameStateNextIndex);
	}
}

//切り替えステート設定
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
			PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);     // SE再生
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
			gamedata.ExcellentModeCount++;
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

	//gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void CharacterMove() {

	// 右

	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.3) {

		Character.Pos.x += 5.0f;

		Character.Zoom.x += 0.0025f;

		Character.Zoom.y += 0.0025f;

		Character.Pos.y -= 0.75f;

		Actionslot.Pos.x += 5.2f;

		Actionslot.Pos.y += 0.70f;

		Actionslot.Scale += D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset += D3DXVECTOR2(0.75f, 0.15f);

		Actionslot.offsect_dis += 0.03;
	}

	// 左

	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 1.0) {

		Character.Pos.x -= 5.0f;

		Character.Zoom.x -= 0.0025f;

		Character.Zoom.y -= 0.0025f;

		Character.Pos.y += 0.75f;

		Actionslot.Pos.x -= 5.2f;

		Actionslot.Pos.y -= 0.70f;

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
			gamedata.ExcellentModeCount = 0;
			obj->Create(150);
			break;
		case ACTIONSLOT_GREAT:
			obj->Create(120);
			if (!gamedata.GetExcellentMode()) {
				gamedata.ExcellentModeCount++;
			}
			break;
		case ACTIONSLOT_GOOD:
			gamedata.ExcellentModeCount = 0;
			obj->Create(50);
			break;
		case ACTIONSLOT_BAD:
			gamedata.ExcellentModeCount = 0;
			break;
		}

		ActionEffectVector.push_back(tmp);

		ActionPointVector.push_back(obj);

		PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);     // SE再生
	}

	if (gamedata.GetRunningSpeed() > 0) {

		gamedata.AddRunningSpeed(-15);

	}

	//gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

}

void Debug_Panel() {

	SetFontSize(24);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "走る距離 : %d", gamedata.GetRunningMeter());

	DrawFormatString(0, 30, GetColor(255, 255, 255), "アクションゲージ : %f", Actionslot.GetValue());

	DrawFormatString(0, 60, GetColor(255, 255, 255), "アクションゲージ状態 : %d", Actionslot.GetState());

	DrawFormatString(0, 90, GetColor(255, 255, 255), "アクション状態 : %d", Action.GetState());

	DrawFormatString(0, 120, GetColor(255, 255, 255), "スビート : %d", gamedata.GetRunningSpeed());

	DrawFormatString(0, 150, GetColor(255, 255, 255), "聖火 : %d", gamedata.Gethp());

	DrawFormatString(0, 180, GetColor(255, 255, 255), "アクションポイント： %d", gamedata.GetActionPoint());

	DrawFormatString(0, 210, GetColor(255, 255, 255), "経過:%f秒", gameprogress->stime / 60);

	DrawFormatString(0, 240, GetColor(255, 255, 255), "%d", gamedata.ExcellentModeCount);
}