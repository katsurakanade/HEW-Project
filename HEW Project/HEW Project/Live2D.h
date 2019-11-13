#pragma once
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "main.h"

using namespace std;

// Live2D モデルキー
typedef enum {

	LIVE2D_INDEX_HIYORI,
	LIVE2D_INDEX_RICE,

	LIVE2D_INDEX_MAX

}LIVE2D_MODEL_KEY;

class Live2D
{

private:

	// モーションインデックス
	int MotionIndex;

	// モーショングループ
	const char *MotionGroup;

public:

	// ハンドル
	int handle;

	// 座標
	D3DXVECTOR2 Pos;

	// 拡大率
	D3DXVECTOR2 Zoom;

	// モデルロード
	// (Initで使う)
	void LoadModel(const char * name);

	// 描画
	void Draw();

	Live2D();

	~Live2D();

	// Setモーション(モーションインデックス)
	void SetMontionIndex(int index);

	// Setモーションイングループ(モーションイングループ名)
	void SetMontionGroup(const char *name);

	// Getモーションインデックス
	int GetMotionIndex();

	// Getモーショングループ
	const char *GetMontionGroup();
};

// Live2Dモデルパス
extern vector <const char *>Live2DModelPassDict;

