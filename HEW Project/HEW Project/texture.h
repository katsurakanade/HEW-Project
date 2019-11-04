#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include <vector>

using namespace std;

typedef enum {

	TEXTURE_INDEX_START,

	TEXTURE_INDEX_MAX

}TEXTURE_KEY;


class Texture {

private:

	int handle;

public:


	void Load(const char * name);

	void Draw(int x, int y);

	void Draw(int x, int y, int width, int height,bool use_alpha);


};

extern vector <const char *>TexturePassDict;