#include "effect.h"

GameObject eft[3];
//static int g_eft;

void effEct::Init()
{

	

	eft[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_EFFECT]);
	eft[0].Object.Pos.x = 300;
	eft[0].Object.Pos.y = 500;
	eft[0].Object.Scale.x = 0.3;//‘å‚«‚³
	eft[0].Object.Scale.y = 0.3;
	

	


}

void effEct::Update()
{

	eft[0] = a;

	a++;
	

	eft[0].Delay_Move.GetDelayTimer(0, 2.0, 500.0f, 500.0f);

	eft[0].SetDelayFlag(1);     //ˆÚ“®‚Ìƒtƒ‰ƒO


}

void effEct::Draw()
{
	/*for (int i = 0; i < g_EFFECT.size(); i++) {
		g_EFFECT[i].Draw();
	}*/

	eft[0].Draw();
}

effEct::effEct()
{
}

effEct::~effEct()
{
}


