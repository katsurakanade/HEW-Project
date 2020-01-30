#include "ActionAffect.h"

static const float InitPosY = 600;

ActionAffect::ActionAffect(int value)
{

	self = new GameObject;
	
	switch (value)
	{
	case ACTIONSLOT_OVER:
		self->LoadTexture(TexturePassDict[TEXTURE_INDEX_OVER]);
		self->Object.Scale.x = 0.5;
		self->Object.Scale.y = 0.5;
		break;
	case ACTIONSLOT_GREAT:
		self->LoadTexture(TexturePassDict[TEXTURE_INDEX_GREAT]);
		self->Object.Scale.x = 1.1;
		self->Object.Scale.y = 1.1;
		break;
	case ACTIONSLOT_GOOD:
		self->LoadTexture(TexturePassDict[TEXTURE_INDEX_GOOD]);
		self->Object.Scale.x = 0.3;
		self->Object.Scale.y = 0.3;
		break;
	case ACTIONSLOT_BAD:
		self->LoadTexture(TexturePassDict[TEXTURE_INDEX_BAD]);
		self->Object.Scale.x = 0.7;
		self->Object.Scale.y = 0.7;
		break;
	}

	self->Object.Pos.x = (rand() % 201) + 800;
	self->Object.Pos.y = InitPosY;
}

ActionAffect::~ActionAffect()
{
	self->Destroy();
	self->~GameObject();
}

void ActionAffect::Update() {

	
	if (self->Object.Pos.y > InitPosY - 50.0) {
		self->Object.Pos.y -= 5.0f;
	}

	if (self->Object.Pos.y <= InitPosY - 50.0) {
		timer += SECONDS;
	}

	if (timer > 0.1f) {
		self->Object.Pos.x -= 30.0f;
	}

	if (self->Object.Pos.x < -200) {
		OutFlag = true;
		this->~ActionAffect();
	}
	
}

void ActionAffect::Draw_Affect() {

	if (!OutFlag) {
		self->Draw();
	}

}


