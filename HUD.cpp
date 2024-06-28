#include "HUD.h"
#include "Sprites.h"

CHUD::CHUD(float x, float y) : CUIObject(x, y)
{
	life = 4;
	coin = 0;
	point = 0;
	level = 1;
	time = 000;
	power = 0;

	characterIconType = TYPE_MARIO;

	firstCard = ID_SPRITE_UI_CARD_HUD_EMPTY;
	secondCard = ID_SPRITE_UI_CARD_HUD_EMPTY;
	thirdCard = ID_SPRITE_UI_CARD_HUD_EMPTY;

	levelUI = new CNumberUI(x - 35, y - 4, level, 1);
	coinUI = new CNumberUI(x + 68, y - 4, coin, 2);
	pointUI = new CNumberUI(x + 28, y + 4, point, 7);
	lifeUI = new CNumberUI(x - 35, y + 4, life, 2);
	timeUI = new CNumberUI(x + 68, y + 4, time, 3);

	characterIconUI = new CCharacterIconUI(x + 16 * 2, y + 16 * 2, characterIconType);

	bar_1 = new CIconUI(x - 20, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	bar_2 = new CIconUI(x - 12, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	bar_3 = new CIconUI(x - 4, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	bar_4 = new CIconUI(x + 4, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	bar_5 = new CIconUI(x + 12, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	bar_6 = new CIconUI(x + 20, y - 4, ID_SPRITE_UI_POWER_BAR, false);
	active = new CIconUI(x + 32, y - 4, ID_ANI_UI_POWER_ACTIVE, true);

}

void CHUD::Render()
{
	RenderMainHUD();
	RenderCardHUD();
	RenderNumberInfoHUD();
	RenderIconInfoHUD();
	RenderPowerInfoHUD();
}

void CHUD::RenderMainHUD()
{
	CSprites::GetInstance()->Get(ID_SPRITE_UI_HUD_HOLDER)->Draw(x + 16 * 2 + 1, y + 14);
	CSprites::GetInstance()->Get(ID_SPRITE_UI_MAIN_HUD)->Draw(x, y);
}

void CHUD::RenderCardHUD()
{
	CSprites::GetInstance()->Get(firstCard)->Draw(x + 16 * 6, y);
	CSprites::GetInstance()->Get(secondCard)->Draw(x + 16 * 7.5, y);
	CSprites::GetInstance()->Get(thirdCard)->Draw(x + 16 * 9, y);
}

void CHUD::RenderNumberInfoHUD()
{
	levelUI->Render();
	coinUI->Render();
	pointUI->Render();
	lifeUI->Render();
	timeUI->Render();
}

void CHUD::RenderIconInfoHUD()
{
	characterIconUI->Render();
}

void CHUD::RenderPowerInfoHUD()
{
	switch (power)
	{
	case 6:
		active->Render();
		bar_6->Render();
		case 5:
			bar_5->Render();
			case 4:
				bar_4->Render();
				case 3:
					bar_3->Render();
					case 2:
						bar_2->Render();
						case 1:
							bar_1->Render();
							break;
	default:
		break;
	}
}

void CHUD::SetPosition(float x, float y)
{
	CUIObject::SetPosition(x, y);
	levelUI->SetPosition(x - 35, y - 4);
	coinUI->SetPosition(x + 68, y - 4);
	pointUI->SetPosition(x + 28, y + 4);
	lifeUI->SetPosition(x - 35, y + 4);
	timeUI->SetPosition(x + 68, y + 4);

	characterIconUI->SetPosition(x - 64, y + 5);

	bar_1->SetPosition(x - 20, y - 4);
	bar_2->SetPosition(x - 12, y - 4);
	bar_3->SetPosition(x - 4, y - 4);
	bar_4->SetPosition(x + 4, y - 4);
	bar_5->SetPosition(x + 12, y - 4);
	bar_6->SetPosition(x + 20, y - 4);
	active->SetPosition(x + 32, y - 4);
}