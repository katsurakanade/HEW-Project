#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "DxLib.h"
#include <time.h>
#include "back ground.h"





BACK_GROUND::BACK_GROUND()
{

}

BACK_GROUND::~BACK_GROUND()
{

}




void BACK_GROUND::BACK_GROUND_Init()
{

	



	bg[0].GOB.LoadTexture(TexturePassDict[TEXTURE_INDEX_LUOTIANYI]);
	bg[1].GOB.LoadTexture(TexturePassDict[TEXTURE_INDEX_LUOTIANYI]);
	
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		bg[i].isUse = false;

	}
	

	bg[0].GOB.Object.Pos.x = 500;
	bg[0].GOB.Object.Pos.y = 500;
	bg[1].GOB.Object.Pos.x = 3840;
	bg[1].GOB.Object.Pos.y = 500;
	
	bg[0].GOB.Object.Pos.x = GameFrame;
	
	bg[1].GOB.Object.Pos.x = g_GameFrame;


	


}


void BACK_GROUND::BACK_GROUND_Update()
{
	

	while (0)
	{
		GameFrame--;
		bg[0].isUse = true;
		if (GameFrame < 330)
		{
			g_GameFrame--;
			bg[1].isUse = true;
			if (g_GameFrame < 980)
			{
				bg[0].isUse = false;
			}


			
		}

	 }






















}

void BACK_GROUND::BACK_GROUND_Draw()
{
	//obj[0].Draw();
	//obj[1].Draw();

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		if (bg[i].isUse == true)
		{
			bg[i].GOB.Draw();
		}
	}
	
		
	DrawFormatString(0, 0, GetColor(255, 255, 255), "経過:%d秒", GameFrame);//デバック用

	
}