#pragma once
#include "DxLib.h"
#include "main.h"
#include <vector>

using namespace std;

class Menu
{

private:

	unsigned int Red = GetColor(255, 0, 0);

	unsigned int White = GetColor(255, 255, 255);

	unsigned int SelectColor;

	int SelectAmount;

	int SelectNow;

public:

	Menu(int selectamount);

	~Menu();

	vector <const char *> SelectText;

	D3DXVECTOR2 Pos;

	unsigned int FontSize;

	void Update();

	void Draw();

	int GetSelectNow();
};

