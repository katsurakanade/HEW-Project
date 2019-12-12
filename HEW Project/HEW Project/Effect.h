#pragma once


void EffectInit();
void EffectUpdate();
void EffectDraw();


// まだ使用できない
class Effect
{
	// 変数宣言
	GameObject obj;     // Draw()等
	GameData data;     // ステート
	bool IsUse = false;     // 使用フラグ
	bool IsDraw = false;     // 描画フラグ (基本的にアニメーション終了時にエフェクトは消えないが、指定する事でアニメーション終了時にエフェクトを消すことができる)
	bool sleepnow = false;     //Sleepフラグ


	// メンバ関数
	void SleepCount();     //sleep時間カウント     Update()に入れる


public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// 遅れフラグ設定(インデックス)     DoOnece
	void SetDelayFlag(int index);

	// エフェクト再生待ち関数(待ち時間)
	void eftSleep(float sec);
	



};


// タイトル_エフェクト
class TitleEffect : public Effect
{

};


// チュートリアル_エフェクト
class TutorialEffect : public Effect
{

};


// ゲーム_エフェクト
class GameEffect : public Effect
{

};


// リザルト_エフェクト
class ResultEffect : public Effect
{

};



