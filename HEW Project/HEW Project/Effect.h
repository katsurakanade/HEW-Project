#include "GameObject.h"
#include <vector>
#include <algorithm>
#include "DxLib.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include <math.h>




class effEct
{

public:

	bool IsDraw;     // �`��t���O


	void Init();

	void Update();

	void Draw();

	effEct();
	
	~effEct();



};
