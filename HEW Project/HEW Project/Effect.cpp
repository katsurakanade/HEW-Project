/*
		エフェクトパーティクル処理
		高橋 智裕
*/


#include <algorithm>
#include <vector>
#include "Effect.h"
#include "EffectGame.h"


//EffectGameのメンバに触る為の変数
static EffectGame* peg;


Effect::Effect()
{
}

Effect::Effect(Effect* pEft)
{
	// 子クラスのメンバに触る為の操作 //
	peg = (EffectGame*)pEft;
	// 子クラスのメンバに触る為の操作 //
	aryNum = peg->MaxAryNum;     // 自分自身の配列番号確保
	peg->MaxAryNum++;
}
Effect::~Effect()
{
	peg->MaxAryNum--;
	aryNum = -1;
}

//ゲームループ
void Effect::Init()
{
}
void Effect::Uninit()
{
}
void Effect::Update()
{
}
void Effect::Draw()
{
}



//// エフェクト関数群 ////
// ※使い方はDelay_○○と同じ
// ※アニメーション終了前に同じエフェクトで同じ名前の関数を呼び出すと情報が上書きされる(前のアニメーションを中断して新しいアニメーションを再生し始める)

// 直線移動(時間,x,y)
void Effect::Move(float sec, float x, float y)
{

	if (FinishedFancNum < MyFancNum_Move && this->MoveSec == sec && this->MoveX == x && this->MoveY == y     // まだ終了してないエフェクト再生
		|| this->SleepNow && MyFancNum_Move == -1)     // Sleep中じゃない && 初回で実行
	{
		if (DoOnce_Move)     // 初回処理
		{
			//IsUse = true;     // 使用フラグ
			this->IsDraw = true;     // 描画フラグ
			this->MoveSec = sec;     //値保持
			this->MoveX = x;     //値保持
			this->MoveY = y;     //値保持
			this->obj.SetDelayFlag(E_MOVE);     // Delayフラグを立てる
			LastFancNum++;     //関数の個数カウント
			MyFancNum_Move = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Move = false;
		}

		if (this->obj.Delay_Move(this->MoveSec, this->MoveX, this->MoveY))     // エフェクト再生
		{
			// 終了時処理
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;     // 使用フラグ
			DoOnce_Move = true;
			MyFancNum_Move = -1;

			/*
			if(DrawEnd(デフォルト値引数))     //描画終了
			{
				IsDraw = false;
			}
			*/

		}

	}// if (FinishedFancNum < MyFancNum_Move || this->SleepNow && MyFancNum_Move == -1)

}

// 曲線移動(反時計回り==true, 曲線の弧の大きさ(0.0f~10.0f程度), 時間, x, y)
void Effect::Curve(bool cw, float curveSize, float sec, float x, float y)
{
	
	if (FinishedFancNum < MyFancNum_Curve && this->CurveCW == cw && this->CurveSize == curveSize && this->CurveSec == sec && this->CurveX == x && this->CurveY == y      // まだ終了してない && 上書きじゃないエフェクト再生
		|| this->SleepNow && MyFancNum_Curve == -1)     // Sleep中じゃない && 初回で実行
	{
		if (DoOnce_Curve)     // 初回処理
		{
			//IsUse = true;     // 使用フラグ
			this->IsDraw = true;     // 描画フラグ
			this->CurveCW = cw;
			this->CurveSize = curveSize;
			this->CurveSec = sec;
			this->CurveX = x;
			this->CurveY = y;
			this->VecA = { this->CurveX , this->CurveY };
			this->obj.SetDelayFlag(E_CURVE);     // Delayフラグを立てる
			LastFancNum++;     //関数の個数カウント
			MyFancNum_Curve = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Curve = false;
		}
		
		// エフェクト再生
		if (this->obj.Delay_CurveMove(this->CurveCW, this->CurveSize, this->CurveSec, this->VecA, this->Rad))
		{     // 終了時処理
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Curve = true;
			MyFancNum_Curve = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Curve || this->SleepNow && MyFancNum_Curve == -1)

}

// 拡大縮小(時間,拡大率)     ※拡大率のところがおかしい
void Effect::Zoom(float sec, double scale)
{

	if (FinishedFancNum < MyFancNum_Zoom && this->ZoomSec == sec && this->ZoomScale == scale     // まだ終了してないエフェクト再生
		|| this->SleepNow && MyFancNum_Zoom == -1)     // Sleep中じゃない && 初回で実行
	{
		if (DoOnce_Zoom)     // 初回処理
		{
			//IsUse = true;     // 使用フラグ
			this->IsDraw = true;     // 描画フラグ
			this->ZoomSec = sec;
			this->ZoomScale = scale;
			this->obj.SetDelayFlag(E_ZOOM);     // Delayフラグを立てる
			LastFancNum++;     //関数の個数カウント
			MyFancNum_Zoom = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Zoom = false;
		}

		// エフェクト再生
		if (this->obj.Delay_Zoom(this->ZoomSec, this->ZoomScale))
		{     // 終了時処理
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Zoom = true;
			MyFancNum_Zoom = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Zoom || this->SleepNow && MyFancNum_Zoom == -1)

}

// 回転(時間,回転角度)     // 回転角度がマイナス判定しない
void Effect::Rotate(float sec, double rotate)
{

	if (FinishedFancNum < MyFancNum_Rot && this->RotSec == sec && this->RotRotate == rotate     // まだ終了してないエフェクト再生
		|| this->SleepNow && MyFancNum_Rot == -1)     // Sleep中じゃない && 初回で実行
	{
		if (DoOnce_Rot)     // 初回処理
		{
			//IsUse = true;     // 使用フラグ
			this->IsDraw = true;     // 描画フラグ
			this->RotSec = sec;
			this->RotRotate = rotate;
			this->obj.SetDelayFlag(E_ROT);     // Delayフラグを立てる
			LastFancNum++;     //関数の個数カウント
			MyFancNum_Rot = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Rot = false;
		}

		// エフェクト再生
		if (this->obj.Delay_Rotate(this->RotSec, this->RotRotate))
		{     // 終了時処理
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Rot = true;
			MyFancNum_Rot = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Rot || this->SleepNow && MyFancNum_Rot == -1)

}

// エフェクト再生待ち関数 (待ち時間)
void Effect::Sleep(float sec)
{
	if (FinishedFancNum < MyFancNum_Sleep && this->SleepSec == sec     // まだ終了してないエフェクト再生
		|| MyFancNum_Sleep == -1)     // 初回で実行
	{
		if (DoOnce_Sleep)     // 初回処理
		{
			this->SleepNow = false;
			this->lastSleepFlag = false;
			this->SleepSec = sec;
			LastFancNum++;     // 関数の個数カウント
			MyFancNum_Sleep = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Sleep = false;
		}


		this->SleepCnt += SECONDS;     // Sleep時間計測

		if (this->SleepCnt >= this->SleepSec)     // Sleep終了処理
		{
			this->SleepCnt = 0;
			this->SleepNow = true;
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			DoOnce_Sleep = true;
			MyFancNum_Sleep = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Sleep || this->SleepNow && MyFancNum_Sleep == -1)

}


// エフェクト再生最終待ち関数 (待ち時間)
void Effect::LastSleep(float sec)
{
	if (FinishedFancNum < MyFancNum_Sleep && this->SleepSec == sec     // まだ終了してないエフェクト再生
		|| MyFancNum_Sleep == -1)     // 初回で実行
	{
		if (DoOnce_Sleep)     // 初回処理
		{
			this->SleepNow = false;
			this->SleepSec = sec;
			LastFancNum++;     // 関数の個数カウント
			MyFancNum_Sleep = LastFancNum;     // 自分の関数の数字を保持
			DoOnce_Sleep = false;
		}


		this->SleepCnt += SECONDS;     // Sleep時間計測

		if (this->SleepCnt >= this->SleepSec)     // Sleep終了処理
		{
			this->lastSleepFlag = true;
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
		}

	}// if (FinishedFancNum < MyFancNum_Sleep || this->SleepNow && MyFancNum_Sleep == -1)

}




