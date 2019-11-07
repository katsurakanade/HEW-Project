#include "Menu.h"
#include "input.h"

Menu::Menu(int selectamount)
{
	SelectAmount = selectamount;

	SelectNow = 0;
}

Menu::~Menu()
{

}

void Menu::Update() {

	if (keyboard.IsTrigger(DIK_DOWNARROW) && SelectNow < (SelectAmount - 1)) {
		SelectNow++;
	}

	else if (keyboard.IsTrigger(DIK_UPARROW) && SelectNow > 0) {
		SelectNow--;
	}

}

void Menu::Draw() {

	SetFontSize(FontSize);

	for (int i = 0; i < SelectAmount; i++) {

		if (i == SelectNow) {
			SelectColor = Red;
		}

		else {
			SelectColor = White;
		}

		DrawFormatString(Pos.x, Pos.y + i  * (100.0f), SelectColor, SelectText[i]);
	}

}

int Menu::GetSelectNow() {
	return SelectNow;
}