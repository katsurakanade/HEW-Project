#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "GameObject.h"
#include "main.h"

using namespace std;

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
extern map<const char *, const char *> Live2D_Dict;
