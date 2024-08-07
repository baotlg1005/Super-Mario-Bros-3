#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "CoinEffect.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"


CQuestionBlock::CQuestionBlock(float x, float y, int reward_type) : CGameObject(x, y)
{
	this->boundPosY = y - 8;
	this->idlePosY = y;
	this->reward_type = reward_type;
	SetState(QBLOCK_STATE_IDLE);
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if(state == QBLOCK_STATE_BOUND_UP)
	{
		if (y <= boundPosY)
		{
			y = boundPosY;
			GetReward();
			SetState(QBLOCK_STATE_BOUND_DOWN);
		}
	}
	else if (state == QBLOCK_STATE_BOUND_DOWN)
	{
		if (y >= idlePosY)
		{
			y = idlePosY;
			SetState(QBLOCK_STATE_EMPTY);
		}
	}

	CGameObject::Update(dt);
}

void CQuestionBlock::Render()
{
	int aniId = ID_ANI_QUESTION_BLOCK_HIT;

	if (state == QBLOCK_STATE_IDLE)
		aniId = ID_ANI_QUESTION_BLOCK;

	if (reward_type == REWARD_1UP) {
		aniId = ID_ANI_BRICK_BREAKABLE_HIT;

		if (state == QBLOCK_STATE_IDLE)
			aniId = ID_ANI_BRICK_BREAKABLE;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_BBOX_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QBLOCK_STATE_BOUND_UP:
			vy = -QBLOCK_BOUND_SPEED;
			break;
		case QBLOCK_STATE_BOUND_DOWN:
			vy = QBLOCK_BOUND_SPEED;
			break;
		case QBLOCK_STATE_EMPTY:
			vy = 0;
			break;

	}
}

void CQuestionBlock::GetReward()
{
	switch (reward_type)
	{
	case REWARD_COIN:
		SpawnCoinEffect();
		break;
	case REWARD_1UP:
		Spawn1Up();
		break;
	case REWARD_POWERUP:
		int level;
		CGameObject* playerObj = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		CMario* player = dynamic_cast<CMario*>(playerObj);
		
		player->GetLevel(level);

		DebugOut(L"[INFO] Mario level: %d\n", level);

		if (level == MARIO_LEVEL_SMALL)
		{
			SpawnMusroom();
		}
		else
		{
			SpawnLeaf();
		}
		break;

	}
}

void CQuestionBlock::SpawnCoinEffect() {
	CEffectObject* coinEffect = new CCoinEffect(x, y - 16);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddEffect(coinEffect);
	SaveFile::GetInstance()->AddCoin(1);
}

void CQuestionBlock::SpawnMusroom()
{
	CMushroom* mushroom = new CMushroom(x, y);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, OBJECT_TYPE_MUSHROOM);
}
void CQuestionBlock::SpawnLeaf()
{
	CLeaf* leaf = new CLeaf(x, y - 16);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(leaf, OBJECT_TYPE_LEAF);
}
void CQuestionBlock::Spawn1Up()
{
	CMushroom* mushroom = new CMushroom(x, y, true);
	dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, OBJECT_TYPE_MUSHROOM);
}