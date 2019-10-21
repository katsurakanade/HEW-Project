#include "GameObject.h"
#include "texture.h"
#include "sprite.h"

GameObject::GameObject(TextureIndex texture) {

	width = Texture_GetWidth(texture);
	height = Texture_GetHeight(texture);
	Texture = texture;

	pos.x = 0.0f;
	pos.y = 0.0f;
}

void GameObject::Draw() {

	if (this != NULL) {
		if (!Display_Hide) {
			Sprite_Draw(Texture, pos.x, pos.y);
		}
	}
}

void GameObject::SetHide(bool hide) {

	Display_Hide = hide;
}
