#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPlatform::RenderBoundingBox()
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

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPlatform::Render()
{

	if (length <= 0) return; 
	if (spriteIdBegin == -1) return;

	if(length == 1)
	{
		CSprites::GetInstance()->Get(this->spriteIdBegin)->Draw(x, y);
		return;
	}


	if (this->isVertical) {
		float yy = y;
		CSprites* s = CSprites::GetInstance();

		s->Get(this->spriteIdBegin)->Draw(x, yy);
		yy += this->cellHeight;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(x, yy);
			yy += this->cellHeight;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(x, yy);
	}
	else {
		float xx = x; 
		CSprites * s = CSprites::GetInstance();

		s->Get(this->spriteIdBegin)->Draw(xx, y);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(xx, y);
			xx += this->cellWidth;
		}
		if (length>1)
			s->Get(this->spriteIdEnd)->Draw(xx, y);

	}
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->isVertical) {
		float cellHeight_div_2 = this->cellHeight / 2;
		l = x - this->cellWidth / 2;
		t = y - cellHeight_div_2;
		r = l + this->cellWidth;
		b = t + this->cellHeight * this->length;
	}
	else {
		float cellWidth_div_2 = this->cellWidth / 2;
		l = x - cellWidth_div_2;
		t = y - this->cellHeight / 2;
		r = l + this->cellWidth * this->length;
		b = t + this->cellHeight;
	}
}

int CPlatform::IsDirectionColliable(float nx, float ny)
{
	if (!isDirectionColliable) return 1;
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}