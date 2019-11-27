#pragma once
#include <vector>
#include <algorithm>
#include "DxLib.h"
#include "main.h"
#include "GameObject.h"

class BackGround
{
private:

	vector <GameObject> BG_Vector;

	int index;

	float Speed;

public:

	void Init();

	void Update();

	void Draw();

	BackGround();

	~BackGround();

	void SetSpeed(float value);
	
	float GetSpeed();
};

