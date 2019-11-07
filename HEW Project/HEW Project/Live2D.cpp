
#include "Live2D.h"
#include <vector>
#include <algorithm>

vector <const char *>Live2DModelPassDict = {
	"asset/Live2D/Hiyori/Hiyori.model3.json"
};

Live2D::Live2D() {

	Pos.x = 0;
	Pos.y = 0;

	Zoom.x = 1.0f;
	Zoom.y = 1.0f;

	MotionGroup = "Idle";
	MotionIndex = 0;

}

Live2D::~Live2D() {

	Live2D_DeleteModel(handle);

}

void Live2D::LoadModel(const char * name) {
	
	try {
		throw Live2D_LoadModel(name);
	}

	catch(int data){
		
		if (data > 0) {
			handle = data;
		}
		else {
			MessageBox(GetHWND(), "Live2Dモデル読み込みエラー", "警告！", MB_ICONWARNING);
		}
	}
}

void Live2D::Draw() {

	Live2D_Model_Update(handle, SECONDS);

	Live2D_Model_SetTranslate(handle, Pos.x, Pos.y);

	Live2D_Model_SetExtendRate(handle, Zoom.x, Zoom.y);

	if (Live2D_Model_IsMotionFinished(handle)) {
		Live2D_Model_StartMotion(handle, MotionGroup, MotionIndex);
	}

	Live2D_RenderBegin();

	Live2D_Model_Draw(handle);

	Live2D_RenderEnd();
}

void Live2D::SetMontionIndex(int index) {
	MotionIndex = index;
}

void Live2D::SetMontionGroup(const char *name) {
	MotionGroup = name;
}

int Live2D::GetMotionIndex() {
	return MotionIndex;
}

const char * Live2D::GetMontionGroup() {
	return MotionGroup;
}
