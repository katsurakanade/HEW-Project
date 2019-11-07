#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include <vector>

using namespace std;

typedef enum {

	TEXTURE_INDEX_START,

	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

class GameObject {

private:

public:

	int handle;

	void LoadTexture(const char * name);

	void Draw(int x, int y);

	void Draw(int x, int y, int width, int height,bool use_alpha);

	int GetHandle();

};

extern vector <const char *>TexturePassDict;