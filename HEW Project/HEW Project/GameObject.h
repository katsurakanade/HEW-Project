#pragma once

#include "main.h"
#include "main.h"
#include "texture.h"

/*
ゲームオブジェクト：　	
ゲーム内使うオブジェクトのベース、基本ほかクラスの継承用
*/

class GameObject {

private:

	// テクスチャ
	TextureIndex Texture;

	// 長
	int width;

	// 高
	int height;

	// 隠し
	bool Display_Hide = false;

public:

	// コンストラクタ (テクスチャ)
	GameObject(TextureIndex texture);

	// 座標
	D3DXVECTOR2 pos;

	// 表示
	void Draw();

	// 隠し設定
	void SetHide(bool hide);

};