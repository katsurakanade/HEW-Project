#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include <vector>

#define ANIME_CUT_LIMIT 36

using namespace std;

typedef enum {

	TEXTURE_INDEX_START,
	TEXTURE_INDEX_END,
	TEXTURE_INDEX_AIROU,
	TEXTURE_INDEX_ACTION_SUCCESS,
	TEXTURE_INDEX_ACTION_DEFAULT,
	TEXTURE_INDEX_ACTION_FAILED,
	TEXTURE_INDEX_A,
	TEXTURE_INDEX_B,
	TEXTURE_INDEX_C,

	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

class GameObject {

private:

public:

	int Anime_handle[ANIME_CUT_LIMIT];

	int handle;

	void LoadTexture(const char * name);

	void LoadTexture(const char * name,int allcut,int xcut,int ycut,int xsize,int ysize);

	void Draw(int x, int y);

	void Draw(int x, int y, int width, int height,bool use_alpha);

	void Draw(int x, int y, int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	void Draw_Anime(int x,int y,int cut);

	void Gauss_Filter(int param);

	int GetHandle();

};

extern vector <const char *>TexturePassDict;