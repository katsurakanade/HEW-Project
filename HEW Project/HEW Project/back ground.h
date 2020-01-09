#pragma once
#define BACK_GROUND_WIDTH 3840
#define BACK_GROUND_HEIGHT  1080
#define BACK_GROUND_MAX 100
#include <stdbool.h>
#include <stdio.h>

class BACK_GROUND
{
public:

	BACK_GROUND();	//コンストラクタ

	~BACK_GROUND();


	void BACK_GROUND_Init();
	void BACK_GROUND_Update();
	void BACK_GROUND_Draw();
	

	static BACK_GROUND bg[BACK_GROUND_MAX];

	
	

	static int GameFrame;//
	static int g_GameFrame;

	bool flag = false;//
	int num = GameFrame;//



	bool isUse;
	

	float GameFrame_spd;
	

	GameObject GOB;//オブジェクト

};