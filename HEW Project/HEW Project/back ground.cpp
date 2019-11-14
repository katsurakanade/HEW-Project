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



static GameObject obj[1];
static int GameFrame;




void BACK_GROUND::BACK_GROUND_Init()
{
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_LUOTIANYI]);

	//�Q�[�����̃t���[����[SECONDS]�̐��l�ɏ���������
	GameFrame = SECONDS;

	GameFrame_pos = 0.0;
	

	GameFrame_spd = 3.0;
	


}


void BACK_GROUND::BACK_GROUND_Update()
{
	GameFrame_pos++;

	if (GameFrame_pos > 100)
	{
		GameFrame_pos--;

	}

}

void BACK_GROUND::BACK_GROUND_Draw()
{
	//�f�o�b�N�p
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�o��:%d�b", stime / 60);


}