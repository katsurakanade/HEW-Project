#include <d3dx9.h>
//#include "debugPrintf.h"
#include "mydirect3d.h"
#include "texture.h"
#include "DxLib.h"
#include <algorithm>

vector <const char *>TexturePassDict = {
	"C:/syashin/back ground.jpg",
};

void Texture::Load(const char * name) {

	handle = LoadGraph(name);
}

void Texture::Draw(int x,int y) {

	DrawGraph(x, y, this->handle, true);
}

void Texture::Draw(int x, int y, int width, int height, bool use_alpha) {

	DrawExtendGraph(x, y, width, height, this->handle ,use_alpha);
}

