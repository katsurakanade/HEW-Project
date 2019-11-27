#include "BackGround.h"

BackGround::BackGround()
{

}


BackGround::~BackGround()
{

}

void BackGround::Init() {

	GameObject tmp[3];

	for (int i = 0; i < 3; i++) {
		tmp[i].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
		tmp[i].Object.Pos.x = -640 + (i * 1280);
		tmp[i].Object.Pos.y = 720 / 2;
		tmp[i].Object.Scale = D3DXVECTOR2(0.70, 0.70);
		BG_Vector.push_back(tmp[i]);
	}

	Speed = 1.0f;

}

void BackGround::Update() {

	for (int i = 0; i < BG_Vector.size(); i++) {

		BG_Vector[i].Object.Pos.x -= Speed;
		
		if (BG_Vector[i].Object.Pos.x <= -640) {

			BG_Vector[i].Destroy();
		
			if (BG_Vector[i].handle != -1) {
				GameObject tmp;
				tmp.LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
				tmp.Object.Pos.x = (1280 * 3) - 640;
				tmp.Object.Pos.y = 720 / 2;
				tmp.Object.Scale = D3DXVECTOR2(0.70, 0.70);
				BG_Vector.push_back(tmp);
			}

			BG_Vector[i].handle = -1;
		}

	}

}

void BackGround::Draw() {

	for (int i = 0; i < BG_Vector.size(); i++) {
		BG_Vector[i].Draw();
	}
}

void BackGround::SetSpeed(float value) {

	Speed = value;

}

float BackGround::GetSpeed() {
	return Speed;
}