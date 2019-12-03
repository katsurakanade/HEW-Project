#include "GameObject.h"
#include <vector>
#include <algorithm>
#include "DxLib.h"
#include "main.h"
#include "game.h"
#include "input.h"

class effEct
{

public:


	void Init();

	void Update();

	void Draw();

	effEct();
	
	~effEct();

	float spd = 1.0f;



};
