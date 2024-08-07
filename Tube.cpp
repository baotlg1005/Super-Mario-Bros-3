#include "Tube.h"
#include "Sprites.h"
#include "Textures.h"
#include "AssetIDs.h"
#include "Mario.h"

CTube::CTube(float x, float y, int length, BOOLEAN isUpsideDown, int type)
	: CGameObject(x, y)
{
	this->length = length;
	this->isUpsideDown = isUpsideDown;
	this->type = type;
}

void CTube::RenderInViewport(int spriteId, float x, float y)
{
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	float min_x = cam_x - 16;
	float max_x = cam_x + game->GetBackBufferWidth() + 16;

	if (x >= min_x && x <= max_x)
		CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}

void CTube::Render()
{
	float xx = x;
	float yy = y;
	int leftSpriteId = ID_SPRITE_TUBE_BODY_LEFT + type * 100;
	int rightSpriteId = ID_SPRITE_TUBE_BODY_RIGHT + type * 100;

	for (int i = 0; i < length - 1; i++) {
		RenderInViewport(leftSpriteId, xx, yy);
		RenderInViewport(rightSpriteId, xx + 16, yy);
		if(isUpsideDown)
			yy += 16;
		else
			yy -= 16;
	}

	leftSpriteId = ID_SPRITE_TUBE_MOUTH_LEFT + type * 100;
	rightSpriteId = ID_SPRITE_TUBE_MOUTH_RIGHT + type * 100;
	

	RenderInViewport(leftSpriteId, xx, yy);
	RenderInViewport(rightSpriteId, xx + 16, yy);

	//RenderBoundingBox();

}

void CTube::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 8;
	b = y + 8;
	r = l + 32;
	t = b - length * 16;

	if (isUpsideDown) {
		t = y - 8;
		b = t + length * 16;
	
	}

}

void CTube::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = l + rect.right / 2;
	float yy = b - length * 16 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}