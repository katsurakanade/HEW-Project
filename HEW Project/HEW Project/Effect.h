#pragma once
#include "GameObject.h"


class Effect
{
	// エフェクト関数の変数保持
	bool DoOnce_Move = true;
	int MyFancNum_Move = -1;     //自分自身の関数の数字を保持
	bool IsMove = false;     //Move実行中フラグ
	float MoveSec = 0.0f;
	float MoveX = 0.0f;
	float MoveY = 0.0f;

	bool DoOnce_Curve = true;
	bool DoOnce_Curve2 = true;
	int MyFancNum_Curve = -1;     // 自分自身の関数の数字を保持
	bool IsCurve = false;     // Curve実行中フラグ
	bool CurveCW = true;     // 時計回り (false:反時計回り)
	float CurveSize = 0.0f;
	float CurveSec = 0.0f;
	float CurveX = 0.0f;
	float CurveY = 0.0f;
	D3DXVECTOR2 VecA = { 0.0f, 0.0f };     // 元座標→移動先座標(処理中に変更される)
	float Rad = 0;     // 弧を描くラジアンの値

	bool DoOnce_Zoom = true;
	int MyFancNum_Zoom = -1;     //自分自身の関数の数字を保持
	bool IsZoom = false;     //Zoom実行中フラグ
	float ZoomSec = 0.0f;
	double ZoomScale = 0.0f;

	bool DoOnce_Rot = true;
	int MyFancNum_Rot = -1;     //自分自身の関数の数字を保持
	bool IsRot = false;     //Rotate実行中フラグ
	float RotSec = 0.0f;
	double RotRotate = 0.0f;

	bool DoOnce_Sleep = true;
	int MyFancNum_Sleep = -1;     //自分自身の関数の数字を保持
	float SleepCnt = 0;     //Sleep時間計測
	bool IsSleep = false;     //Sleep実行中フラグ
	float SleepSec = 0.0f;


public:
	// Draw(), エフェクト関数等
	GameObject obj;
	int aryNum = -1;     // 自身の配列番号
	//bool IsUse = false;     // 使用フラグ     IsUseMaxAryNum更新時に使う
	bool IsDraw = false;     // 描画フラグ (基本的にアニメーション終了時にエフェクトは消えないが、指定する事でアニメーション終了時にエフェクトを消すことができる)
	// エフェクト実行(各パーティクル)が終了した関数の数
	int FinishedFancNum = -1;
	// エフェクトを実行(各パーティクル)する最後の関数の数
	int LastFancNum = 0;
	//Sleepフラグ(false:Sleep以降の関数の実行を止める)
	bool SleepNow = true;
	// アニメーション終了判定フラグ
	bool lastSleepFlag = true;


	// インデックス変数
	const int E_MOVE = 0;
	const int E_CURVE = 1;
	const int E_ZOOM = 2;
	const int E_ROT = 3;


	Effect();
	Effect(Effect* pEft);
	virtual ~Effect();

	//ゲームループ
	void Init();
	void Uninit();
	void Update();
	void Draw();


	//// エフェクト関数群 ////
	// ※使い方はDelay_○○と同じ
	// ※アニメーション終了前に同じエフェクトで同じ名前の関数を呼び出すと情報が上書きされる(前のアニメーションを中断して新しいアニメーションを再生し始める)

	// 直線移動(時間,x,y)
	void Move(float sec, float x, float y);

	// 曲線移動(時計回り==true, 曲線の弧の大きさ(0.0f~10.0f程度), 時間, x, y)
	void Curve(bool cw, float CurveSize, float sec, float x, float y);

	// 拡大縮小(時間,拡大率)
	void Zoom(float sec, double scale);

	// 回転(時間,回転角度)
	void Rotate(float sec, double rotate);

	// エフェクト再生待ち関数 (待ち時間)
	void Sleep(float sec);

	// エフェクト再生最終待ち関数 (待ち時間)
	void LastSleep(float sec);
	
};
