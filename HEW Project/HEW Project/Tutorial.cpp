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
#include "Tutorial.h"
#include "EffectGame.h"

// ゲームステート遷移用変数
static TUTO_STATE g_TutoStateIndex;
static TUTO_STATE g_TutoStateNextIndex;


// スビート計算用
static std::vector<int> Speed_Array;
static int Max_Count;
static int Judge_Count;
// アクションUI
static ActionUI *Action;
// アクションゲージ
static ActionSlot Action_s;
// アクション失敗画像
static GameObject Failed;
// Live2Dキャラクター
static Live2D Character;
// ゲーム進行バー
static GameProgress *gameprogress;
// スタミナゲージ
static StaminaGauge *stamina;
//背景
static BackGround background;

static GameObject ExcellentFrame;

static GameObject ExcellentImg;

static GameObject Alphabg;

static GameObject obj[4];

//バトンタッチ
static BatonTouch batonTouch;

static GameOver *gameover;

static GameClear *gameclear;

// アクションエフェクト用
static std::vector<ActionAffect*> ActionEffectVector;

static std::vector <ActionPointAnime*> ActionPointVector;

// ゲームエフェクト
static EGManager *egmanager;

static GameObject ActionBoard;

static int sehandle;

static bool uiflag;

typedef void(*TutoStateFunc)(void);

static bool ASE_DoOnce = true;     // アクション成功時DoOnce



static const TutoStateFunc Initialize[] = {
	Init_GameStart,     //バトンタッチのゲームスタート処理のInit
	Init_TutoState,     //2区間, ３区間用Init
	Init_BatonTouch,
};


void TutoState_Initialize(TUTO_STATE index)
{
	g_TutoStateNextIndex = g_TutoStateIndex = index;

	Initialize[g_TutoStateIndex]();
}


void Init_Tutorial()
{
	TutoState_Initialize(TUTO_STATE_START);

	gameprogress = new GameProgress;
	stamina = new StaminaGauge;
	gameover = new GameOver;
	gameclear = new GameClear;
	Action = new ActionUI;
	g_TutoStateIndex = TUTO_STATE_START;
	g_TutoStateNextIndex = TUTO_STATE_START;

	//画面の背景表示
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.0f;
	obj[0].Object.Scale.y = 1.0f;

	// 「SL+SR+L」を押せ！画像
	obj[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_CHARENGE]);
	obj[1].Object.Pos.x = SCREEN_WIDTH/2;
	obj[1].Object.Pos.y = SCREEN_HEIGHT/2;
	obj[1].Object.Scale.x = 0.7f;
	obj[1].Object.Scale.y = 0.7f;

	obj[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_TUTORIAL_LOGO]);
	obj[2].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[2].Object.Pos.y = 100;
	obj[2].Object.Scale.x = 1.0f;
	obj[2].Object.Scale.y = 1.0f;

	obj[3].LoadTexture(TextureDict["skip"]);
	obj[3].Object.Pos.x = SCREEN_WIDTH-100 ;
	obj[3].Object.Pos.y = 50;
	obj[3].Object.Scale.x = 0.3f;
	obj[3].Object.Scale.y = 0.3f;



	//スタミナゲージ初期化
	stamina->Init();


	// アクションUI初期化	

	Action->Init();

	Action->Pos.x = 600;

	Action->Pos.y = 250;

	Action->Interval.x = 190;

	Action->Interval.y = 0;

	// アクションゲージ初期化

	Action_s.Load();

	Action_s.Pos.x = 210;

	Action_s.Pos.y = 480;

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
	gameprogress->Tutoflag = true;

	background.Init();

	gameover->Init();

	batonTouch.Init();

	//Init_GameClear();


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

	PlaySoundFile("asset/sound/BGM_ActionBoard.mp3", DX_PLAYTYPE_LOOP);

	sehandle = LoadSoundMem("asset/sound/SE_ActionBoard.mp3");

	ActionBoard.LoadTexture(TextureDict["board"]);
	ActionBoard.Object.Pos.x = Action->Pos.x + 270;
	ActionBoard.Object.Pos.y = Action->Pos.y;
	ActionBoard.Object.Scale.x = 0.8;
	ActionBoard.Object.Scale.y = 0.5;

	uiflag = false;

}

void Init_TutoState()
{
	stamina->SetStaminaGauge(2.0, 2.0);
	batonTouch.Timer = 0;
	batonTouch.Uninit_DoOnce = true;
}


void Uninit_Tutorial()
{
	Character.~Live2D();

	gameprogress = nullptr;
	delete gameprogress;

	stamina = nullptr;
	delete stamina;

	gameover = nullptr;
	delete gameover;

	gameclear = nullptr;
	delete gameclear;

	Action = nullptr;
	delete Action;

	//エフェクト終了処理
	egmanager->Uninit();
	egmanager = nullptr;
	delete egmanager;

	obj[0].Destroy();
	obj[1].Destroy();
	obj[2].Destroy();


	obj[0].~GameObject();
	obj[1].~GameObject();
	obj[2].~GameObject();



	ActionEffectVector.~vector();
	ActionPointVector.~vector();


	Alphabg.Destroy();
	ExcellentFrame.Destroy();
	ExcellentImg.Destroy();

	Alphabg.~GameObject();
	ExcellentFrame.~GameObject();
	ExcellentImg.~GameObject();


	batonTouch.Uninit();

}

void Update_Tutorial()
{


	switch (g_TutoStateIndex)
	{

	case TUTO_STATE_START:     // BattonTouchのチュートリアルスタート処理--------------------------------------------------------

		background.Update();
		//Character.SetMontionIndex(GetRand(8));

		if (keyboard.IsTrigger(DIK_A)) {
			TutoState_Change(TUTO_STATE_GAME);
			uiflag = true;

		}

		batonTouch.Update(BT_GameStart);


		break;


	case TUTO_STATE_GAME:      //ゲーム内処理------------------------------------------------------------------------------

		//エフェクト更新処理
		egmanager->Update();

		if (uiflag == true)
		{
			static float timer = 0.0f;

			timer += SECONDS;

			if (timer >= 0.58f)
			{
				call_E_tutorial_AAA();
				timer = 0.0f;
				//uiflag = false;

			}
		}


		//スタミナゲージ更新処理
		stamina->Update();

		//Character.SetMontionIndex(GetRand(8));

		// アクションUI更新
		Action->Update();
		// アクションゲージ更新
		Action_s.Update(stamina->GetStaminaScale_x(), gamedata.GetExcellentMode());
		
		// アクション完成判定
		if (Action->GetFinishFlag()) {
			static float timer = 0.0f;
			

			timer += SECONDS;
/*
			if (timer == 0.20f)
			{
				call_E_tutorial_up();
				timer = 0.0f;

			}
*/
			if (ASE_DoOnce)
			{
				call_E_tutorial_up();
				ASE_DoOnce = false;
			}


			if (Action->GetProgress() == Action->GetActionAmount()) {

				switch (Action->GetState())
				{
				case ACTION_STATE_LONGJUMP:
					// change
					Action_s.AddValue(0.152 * 9);
					break;
				case ACTION_STATE_TRAMPOLINING:
					// change
					Action_s.AddValue(0.132 * 9);
					break;
				case ACTION_STATE_BALANCEBOARD:
					// change
					Action_s.AddValue(0.068 * 9);
					break;
				case ACTION_STATE_WEIGHT:
					// change
					Action_s.AddValue(0.16 * 9);
					break;
				case ACTION_STATE_UNEVENBARS:
					// change
					Action_s.AddValue(0.152 * 9);
					break;
				default:
					break;
				}
			}
			else {

			}
		}
		else
		{
			ASE_DoOnce = true;
		}
		
		// スビート更新
		gamedata.UpdateSpeed();

		// 走る処理
		TutoRunning();

		// ゲーム進行バー処理
		gameprogress->Update(*Action);

		// キャラクター処理

		//TutoCharacterMove();


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
			///GameState_Change(GAME_STATE_GAME_OVER);
		}

		Debug_TutoRunning();

		
		///////////////////////////////////////
		// エフェクト実験用（Enterを押したらエフェクト再生）
		if (keyboard.IsTrigger(DIK_RETURN))
		{
			static bool DoOnce = true;
			if (DoOnce)
			{
				//call_E_game_Sample();     //エフェクト再生
				//call_E_game_ActionSucsess();

				DoOnce = false;     // 消さない！
			}
		}
		///////////////////////////////////////
		
		break;


	case TUTO_STATE_BATONTOUCH:     // BattonTouchのバトンタッチ処理--------------------------------------------------

			// 区間間の初期化処理
		if (batonTouch.Uninit_DoOnce)
		{
			//スタミナゲージ初期化
			stamina->Init();

			// アクションゲージ初期化
			Action_s.AddValue(VALUE_DEFAULT - Action_s.GetValue());     //Valueがデフォルト値になる
			Action_s.Pos.x = 210;
			Action_s.Pos.y = 480;
			Action_s.Update(stamina->GetStaminaScale_x(), gamedata.GetExcellentMode());

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


	}




	// Go Title
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

	// Remove Trash
	if (keyboard.IsPress(DIK_Q)) {

		std::vector<ActionAffect*>().swap(ActionEffectVector);
		std::vector<ActionPointAnime*>().swap(ActionPointVector);
	}

	if (keyboard.IsPress(DIK_E)) {
		Action_s.AddValue(0.5);
	}

	if (keyboard.IsPress(DIK_P)) {
		if (gamedata.ExcellentModeInitFlag == false) {
			gamedata.InitExcellentMode();
		}
	}

	if (keyboard.IsRelease(DIK_O)) {
		gamedata.ExcellentModeInitFlag = false;
	}






	//スキップ
	if (keyboard.IsTrigger(DIK_Z)|| joycon[0].IsPress(JOYCON_MIN)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

}

void Draw_Tutorial()
{

	switch (g_TutoStateIndex)
	{

	case TUTO_STATE_START:     // BattonTouchのゲームスタート処理--------------------------------------------------------

		//background.Draw();
		obj[0].Draw();
		obj[1].Draw();
		obj[2].Draw();

		//スキップ
		obj[3].Draw();


		Character.Draw();

		break;

	case TUTO_STATE_GAME:      //ゲーム内処理------------------------------------------------------------------------------

		background.Draw();

		//スタミナゲージ描画
		stamina->Draw();

		//スキップ
		obj[3].Draw();

		// ゲーム進行ゲージ描画
		gameprogress->Draw();

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

		//エフェクト描画処理
		egmanager->Draw();

		// アクションUI+背景描画
		ActionBoard.Draw();
		Action->Draw();
		// アクションゲージ描画
		Action_s.Draw();

		
		// アクション完成判定
		if (Action->GetFinishFlag()) {
			if (Action->GetProgress() == Action->GetActionAmount()) {
				if (Action_s.GetValue() <= 90.0) {
					Action_s.AddValue(0.5);
				}
			}
			else {

			}
		}



		Character.Draw();

		break;


	case TUTO_STATE_BATONTOUCH:     // BattonTouchのバトンタッチ処理--------------------------------------------------

		background.Draw();

		gameprogress->Draw();

		// アクションゲージ描画
		Action_s.Draw();

		Character.Draw();

		batonTouch.Draw(BT_BatonTouch);

		//エフェクト描画処理
		egmanager->Draw();

		break;


	}


	TutoState_Check();     //ゲームステート切り替え処理


#ifdef DEBUG
	Debug_Panel();
#endif // DEBUG



}

//ステート切り替え処理
void TutoState_Check(void)
{
	if (g_TutoStateIndex != g_TutoStateNextIndex) {
		TutoState_Initialize(g_TutoStateNextIndex);
	}
}

//切り替えステート設定
void TutoState_Change(TUTO_STATE index)
{
	g_TutoStateNextIndex = index;
}

void TutoRunning() {

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

		ActionAffect *tmp = new ActionAffect(Action_s.GetState());

		switch (Action_s.GetState())
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

void TutoCharacterMove() {

	// 右

	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.3) {

		Character.Pos.x += 5.0f;

		Character.Zoom.x += 0.0025f;

		Character.Zoom.y += 0.0025f;

		Character.Pos.y -= 0.75f;

		Action_s.Pos.x += 5.0f;

		Action_s.Pos.y += 0.75f;

		Action_s.Scale += D3DXVECTOR2(0.0025f, 0.0025f);

		Action_s.Fire_Offset += D3DXVECTOR2(0.75f, 0.15f);

		Action_s.offsect_dis += 0.03;
	}

	// 左

	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 1.0) {

		Character.Pos.x -= 5.0f;

		Character.Zoom.x -= 0.0025f;

		Character.Zoom.y -= 0.0025f;

		Character.Pos.y += 0.75f;

		Action_s.Pos.x -= 5.0f;

		Action_s.Pos.y -= 0.75f;

		Action_s.Scale -= D3DXVECTOR2(0.0025f, 0.0025f);

		Action_s.Fire_Offset -= D3DXVECTOR2(0.75f, 0.15f);

		Action_s.offsect_dis -= 0.03;
	}

}

void Debug_TutoRunning() {

	if (keyboard.IsTrigger(DIK_RIGHTARROW)) {
		Judge_Count += 350;
	}

	if (Judge_Count >= 350) {

		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

		gamedata.SetRunningSpeed(405);

		Judge_Count = 0;

		gamedata.Action_Point_Update(Action_s.GetState());

		ActionPointAnime *obj = new ActionPointAnime();

		ActionAffect *tmp = new ActionAffect(Action_s.GetState());

		switch (Action_s.GetState())
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

