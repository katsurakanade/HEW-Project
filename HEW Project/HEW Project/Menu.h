#pragma once
#include "Menu.h"
#include "GameObject.h"

/*
メニューシステム：
選択用メニューを作るクラスです。
使う前必ずグローバルでテクスチャ配列用意してください。
(2019/10/3 いま上下選択だけ対応します。)
*/

class Menu
{

private:

	//	選択肢数
	int Arrow;

	// いま選択していた選択肢
	int select_now;

public:

	// コンストラクタ(選択肢数)
	Menu(int arrow);

	//	デストラクタ
	~Menu();

	/*	
	選択肢
	(Updateの中で使ってください)
	(Return  選択している選択肢)
	*/
	int UpdateSelectMenu();

	// 表示(テクスチャ配列,横位置,縦位置,間隔,テクスチャ横,テクスチャ縦)
	void Draw(LPDIRECT3DTEXTURE9 texturearray[], int sx, int sy, int interval,int tx,int tw);
};

