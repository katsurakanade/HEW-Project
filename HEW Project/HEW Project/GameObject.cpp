#include <d3dx9.h>
#include "mydirect3d.h"
#include "GameObject.h"
#include "DxLib.h"
#include <algorithm>

vector <const char *>TexturePassDict = {
	"C:/Users/katsu/source/repos/katsurakanade/HEW-Project/HEW Project/HEW Project/asset/texture/start.png",

};

void GameObject::LoadTexture(const char * name) {

	handle = LoadGraph(name);
}

void GameObject::Draw(int x,int y) {

	DrawGraph(x, y, this->handle, true);
}

void GameObject::Draw(int x, int y, int width, int height, bool use_alpha) {

	DrawExtendGraph(x, y, width, height, this->handle ,use_alpha);
}

int GameObject::GetHandle() {
	return handle;
}