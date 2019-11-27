#pragma once
#include "main.h"
#include "GameObject.h"
#include "ActionSlot.h"

class ActionAffect
{

private:

	float timer;

public:

	GameObject *self;

	bool OutFlag = false;

	void Update();

	ActionAffect(int value);

	~ActionAffect();

	void Draw_Affect();

};

