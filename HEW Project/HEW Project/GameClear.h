#pragma once


class GameClear
{
private:

	float TimeCount = SECONDS;

	bool objflag;

public:

	void Init();

	~GameClear();

	void Update();

	void Draw();
};

void Init_GameClear();

