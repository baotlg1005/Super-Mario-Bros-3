#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "ParaGoomba.h"
#include "Koopas.h"
#include "Plant.h"
#include "FireBall.h"

#include "Mushroom.h"
#include "Leaf.h"
#include "Coin.h"

#include "QuestionBlock.h"
#include "Button.h"
#include "Brick.h"
#include "SpawnCheck.h"

#include "Collision.h"


CMario::CMario(float x, float y) : CGameObject(x, y)
{
	isSitting = false;
	lookingRight = true;

	wantWhip = false;
	wantJump = false;
	wantReleaseJump = false;
	wantFloat = false;
	wantFly = false;

	isGearing = false;
	isRunning = false;
	isMovingRight = false;
	isMovingLeft = false;
	isFlying = false;

	maxVx = 0.0f;
	maxVy = MARIO_MAX_FALL_SPEED;
	decayVx = MARIO_WALK_DECAY;
	ax = 0.0f;
	ay = MARIO_GRAVITY;

	level = SaveFile::GetInstance()->GetMarioLevel();
	untouchable = 0;

	untouchable_start = -1;
	kick_start = -1;
	whip_start = -1;
	float_start = -1;
	gear_start = -1;
	flying_start = -1;
	switch_delay_start = -1;

	isOnPlatform = false;
	gearUpState = 0;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = min(vy + ay * dt, maxVy);

	MovingBehavior(dt);
	JumpingBehavior();

	if (koopasPickedUp != NULL) PickUpBehavior();

	if (level == MARIO_LEVEL_RACOON) RacoonBehavior();
	wantFloat = false;
	wantWhip = false;
	wantFly = false;

	TimeChecking();

	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CMario::MovingBehavior(DWORD dt) {

	if (isMovingRight == isMovingLeft) {
		SetState(MARIO_STATE_IDLE);
		if (lookingRight)
			vx = max(vx - decayVx * dt, 0.0f);
		else
			vx = min(vx - decayVx * dt, 0.0f);
	}
	else if (isMovingRight) {
		lookingRight = true;
		
		if(isGearing) SetState(MARIO_STATE_GEAR_RIGHT);
		else SetState(MARIO_STATE_WALK_RIGHT);

		if(vx < MARIO_WALKING_SPEED)
			vx = vx + MARIO_ACCEL_WALK * dt;
		else 
			vx = vx + MARIO_ACCEL_GEAR * dt;

		if (vx > maxVx) vx = maxVx;
	}
	else if (isMovingLeft) {
		lookingRight = false;

		if (isGearing) SetState(MARIO_STATE_GEAR_LEFT);
		else SetState(MARIO_STATE_WALK_LEFT);

		vx = vx - MARIO_ACCEL_WALK * dt;

		if (vx < maxVx) vx = maxVx;
	}

	if (abs(vx) >= MARIO_GEARING_SPEED) {
		if(gear_start == -1) gear_start = GetTickCount64();
	}

}

void CMario::PickUpBehavior() {
	if (!wantPickUp) {
		koopasPickedUp->SetState(KOOPAS_STATE_SLIDE);
		float koopas_x, koopas_y;
		koopasPickedUp->GetPosition(koopas_x, koopas_y);
		if (koopas_x < x)
			koopasPickedUp->SetSpeed(-KOOPAS_SLIDE_SPEED, 0);
		else
			koopasPickedUp->SetSpeed(KOOPAS_SLIDE_SPEED, 0);

		koopasPickedUp->SetIsPickedUp(false);
		koopasPickedUp = NULL;
	}

	if (koopasPickedUp != NULL) {
		if (koopasPickedUp->GetState() == KOOPAS_STATE_WALKING) {
			koopasPickedUp->SetIsPickedUp(false);
			koopasPickedUp = NULL;
		}
		else {
			int offset = 12;
			if (!lookingRight)
				offset *= -1;
			koopasPickedUp->SetPosition(x + offset, y);
		}
	}
}

void CMario::RacoonBehavior() {
	if (wantWhip) SetState(MARIO_STATE_WHIP);
	
	if(!isFlying && wantFloat) SetState(MARIO_STATE_FLOAT);

	//DebugOut(L"---isOnPlatform: %d, isFlying: %d, wantFly: %d--- \n", isOnPlatform, isFlying, wantFly);
	if(!isOnPlatform && isFlying && wantFly) SetState(MARIO_STATE_FLY);
}

void CMario::JumpingBehavior() {
	if (isOnPlatform && wantJump) {
		SetState(MARIO_STATE_JUMP);
		if (level == MARIO_LEVEL_RACOON && gearUpState == 6) {
			isFlying = true;
			maxVy = MARIO_MAX_FALL_SPEED / 5;
			flying_start = GetTickCount64();
		}
	}
	if (wantReleaseJump) SetState(MARIO_STATE_RELEASE_JUMP);

	wantJump = false;
	wantReleaseJump = false;

}

void CMario::TimeChecking() {
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if( !isFlying && gear_start != -1 && GetTickCount64() - gear_start > MARIO_GEAR_UP_TIME)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED && isOnPlatform) {
			gearUpState += 1;
			if (gearUpState > 6) gearUpState = 6;
			else gear_start = GetTickCount64();
		}
		else {
			gearUpState -= 1;
			if (gearUpState <= 0) {
				gearUpState = 0;
				gear_start = -1;
			}
			else gear_start = GetTickCount64();
		}
	}

	if (flying_start != -1 && GetTickCount64() - flying_start > MARIO_FLYING_TIME)
	{
		isFlying = false;
		maxVy = MARIO_MAX_FALL_SPEED;
		flying_start = -1;
	}
}

#pragma region COLLISION
void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if(vy < 0) isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) Landed();
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CSpawnCheck*>(e->obj))
		OnCollisionWithSpawnCheck(e);
	else if (dynamic_cast<CMushroom*>(e->obj)) 
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
		
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);


	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0 || state == MARIO_STATE_WHIP)
	{
		if (goomba->GetState() == GOOMBA_STATE_DIE) return;
		//check is para goomba
		if (dynamic_cast<CParaGoomba*>(goomba))
		{
			CParaGoomba* paraGoomba = dynamic_cast<CParaGoomba*>(goomba);
			if (paraGoomba->IsHaveWing())
				paraGoomba->BreakWing();
			else if (goomba->GetState() != GOOMBA_STATE_DIE)
				goomba->SetState(GOOMBA_STATE_DIE);
		}
		else if (goomba->GetState() != GOOMBA_STATE_DIE)
			goomba->SetState(GOOMBA_STATE_DIE);

		if (e->ny < 0) vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{ 
		if(goomba->GetState() != GOOMBA_STATE_DIE)
			TakingDamage();
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	int type;
	koopas->GetType(type);

	if (koopas == koopasPickedUp) return;

	if (koopas->GetState() == KOOPAS_STATE_HIDE || koopas->GetState() == KOOPAS_STATE_REVIVE) {

		if (wantPickUp) {
			koopasPickedUp = koopas;
			koopasPickedUp->SetIsPickedUp(true);
			return;
		}

		koopas->SetState(KOOPAS_STATE_SLIDE);

		float koopas_x, koopas_y;
		koopas->GetPosition(koopas_x, koopas_y);
		if (koopas_x < x)
			koopas->SetSpeed(-KOOPAS_SLIDE_SPEED, 0);
		else
			koopas->SetSpeed(KOOPAS_SLIDE_SPEED, 0);

	}
	else {
		if (e->ny < 0 || state == MARIO_STATE_WHIP) {
			if (type == KOOPAS_TYPE_WING) {
				koopas->SetType(KOOPAS_TYPE_GREEN);
			}
			else if (koopas->GetState() == KOOPAS_STATE_WALKING)
			{
				koopas->SetState(KOOPAS_STATE_HIDE);
			}
			else if (koopas->GetState() == KOOPAS_STATE_SLIDE)
			{
				koopas->SetState(KOOPAS_STATE_HIDE);
			}
			if (e->ny < 0) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else {
			if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_SLIDE)
			{
				TakingDamage();
			}
		}
	}
}	

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	TakingDamage();
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireBall = dynamic_cast<CFireBall*>(e->obj);
	TakingDamage();
	fireBall->Delete();
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SaveFile::GetInstance()->AddCoin(1);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* portal = dynamic_cast<CPortal*>(e->obj);
	if (portal->IsMainPortal())
	{
		portalCanUse = portal;
	}
	else
	{
		portalCanUse = nullptr;
	}
}

void CMario:: OnCollisionWithSpawnCheck(LPCOLLISIONEVENT e)
{
	//delete spawn check
	e->obj->Delete();
	DebugOut(L"---Collision with spawn check---- \n");

}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (level == MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_BIG;

		SaveFile::GetInstance()->SetMarioLevel(level);

		y -= (float)(MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;

		CGame::GetInstance()->GetCurrentScene()->FreezeScene(400);
		isMovingLeft = isMovingRight = false;
		freezeId = ID_ANI_MARIO_SMALL_TO_BIG_RIGHT;
		if (!lookingRight) freezeId += 10;

	}

	mushroom->Delete();
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	level = MARIO_LEVEL_RACOON;

	SaveFile::GetInstance()->SetMarioLevel(level);

	CGame::GetInstance()->GetCurrentScene()->FreezeScene(400);
	isMovingLeft = isMovingRight = false;
	freezeId = ID_ANI_MARIO_SMOKE;

	leaf->Delete();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e) {
	if (e->ny <= 0) return;

	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);
	if (questionBlock->GetState() == QBLOCK_STATE_IDLE) {
		questionBlock->SetState(QBLOCK_STATE_BOUND_UP);
		if (questionBlock->GetRewardType() == REWARD_COIN) {
			SaveFile::GetInstance()->AddCoin(1);
		}
		questionBlock->GetReward();
	}
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* button = dynamic_cast<CButton*>(e->obj);
	button->Pressing();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (!brick->IsBreakable()) return;

	if (e->ny < 0) return;
	
	if(e->ny > 0) brick->Breaking();

	if(state == MARIO_STATE_WHIP)
	{
		brick->Breaking();
	}


}

void CMario::TakingDamage() {

	if (untouchable == 0)
	{
		int freezeTime = 400;
		isMovingLeft = isMovingRight = false;

		if(level == MARIO_LEVEL_RACOON)
		{
			level = MARIO_LEVEL_BIG;
			freezeId = ID_ANI_MARIO_SMOKE;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;

			freezeId = ID_ANI_MARIO_BIG_TO_SMALL_RIGHT;
			if (!lookingRight) freezeId += 10;

			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			DebugOut(L">>> Mario DIE >>> \n");
			freezeId = ID_ANI_MARIO_DIE;
			freezeTime = 10000;
			SetState(MARIO_STATE_DIE);
		}

		CGame::GetInstance()->GetCurrentScene()->FreezeScene(freezeTime);
	}
}

void CMario::Landed()
{
	isOnPlatform = true;
	isFlying = false;
	maxVy = MARIO_MAX_FALL_SPEED;
}
#pragma endregion


int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
		if(!lookingRight) aniId += 10;
	}
	else
		if (isSitting)
		{
			aniId = ID_ANI_MARIO_SIT_RIGHT;
			if (!lookingRight) aniId += 10;
			aniId -= 10000;
		}
		else
			if (vx == 0)
			{
				aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				if (!lookingRight) aniId += 10;
			}
			else if (vx > 0)
			{
				if (ax < 0) {
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				}
				else if (gearUpState == 6)
					aniId = ID_ANI_MARIO_SMALL_RUN_RIGHT;
				else if (vx > MARIO_WALKING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_GEARING_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALK_RIGHT;

			}
			else // vx < 0
			{
				if (ax > 0) {
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				}
				else if (gearUpState == 6)
					aniId = ID_ANI_MARIO_SMALL_RUN_LEFT;
				else if (vx < -MARIO_WALKING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_GEARING_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALK_LEFT;
			}

	if (koopasPickedUp != NULL)
	{
		if (!isOnPlatform) {
			aniId = ID_ANI_MARIO_SMALL_PICK_UP_JUMP_RIGHT;
			if (!lookingRight) aniId += 10;
		}
		else {
			if (vx == 0) {
				aniId = ID_ANI_MARIO_SMALL_PICK_UP_IDLE_RIGHT;
				if (!lookingRight) aniId += 10;
			}
			else {
				aniId = ID_ANI_MARIO_SMALL_PICK_UP_WALK_RIGHT;
				if (!lookingRight) aniId += 10;
			}
		}
	}

	if (state == MARIO_STATE_KICK) {
		aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		if (!lookingRight) aniId += 10;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	aniId = GetAniIdSmall();

	if (
		(level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACOON)
		&& (aniId == ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT || aniId == ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT)
		)
	{
		if (!isOnPlatform && vy > 0) aniId += 1000;
		else if (gearUpState == 6) aniId += 100;

	}

	if (level == MARIO_LEVEL_BIG) aniId += 10000;
	if (level == MARIO_LEVEL_RACOON) aniId += 20000;

	if (isFlying) {
		if (vy < 0) aniId = ID_ANI_RACOON_MARIO_FLY_RIGHT;
		else aniId = ID_ANI_RACOON_MARIO_GLIDE_RIGHT;

		if (!lookingRight) aniId += 10;
	}


	if (state == MARIO_STATE_WHIP) {
		aniId = ID_ANI_RACOON_MARIO_WHIP_RIGHT;
		if (!lookingRight) aniId += 10;
	}

	if (state == MARIO_STATE_FLOAT) {
		aniId = ID_ANI_RACOON_MARIO_FLOAT_RIGHT;
		if (!lookingRight) aniId += 10;
	}

	if (state == MARIO_STATE_DIE) {
		aniId = ID_ANI_MARIO_DIE;
	}

	if (untouchable == 1 &&
		((GetTickCount64() - untouchable_start) % 100 >= 0 && (GetTickCount64() - untouchable_start) % 100 <= 30)) {
		CSprites::GetInstance()->Get(ID_SPRITE_MARIO_UNTOUCHABLE)->Draw(x, y);
	}

	else animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUN_RIGHT: {
		if (isSitting) break;
		break;
	}
	case MARIO_STATE_RUN_LEFT: {
		if (isSitting) break;
		break;
	}
	case MARIO_STATE_GEAR_RIGHT: {
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		decayVx = MARIO_RUN_DECAY;
		break;
	}
	case MARIO_STATE_GEAR_LEFT: {
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		decayVx = -MARIO_RUN_DECAY;
		break;
	}
	case MARIO_STATE_WALK_RIGHT: {
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		decayVx = MARIO_WALK_DECAY;
		break;
	}
	case MARIO_STATE_WALK_LEFT: {
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		decayVx = -MARIO_WALK_DECAY;
		break;
	}
	case MARIO_STATE_JUMP: {
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (gearUpState == 6)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	}
	case MARIO_STATE_RELEASE_JUMP: {
		if(vy < -MARIO_QUICK_JUMP_SPEED_Y)
			vy = -MARIO_QUICK_JUMP_SPEED_Y;
		break;
	}
	case MARIO_STATE_SIT: {
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_SIT_RELEASE: {
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_IDLE: {
		maxVx = 0;
		break;
	}
	case MARIO_STATE_DIE: {
		vy = -MARIO_JUMP_SPEED_Y;
		vx = 0;
		ax = 0;
		break;
	}
	case MARIO_STATE_KICK: {
		if (kick_start != -1) break;
		kick_start = GetTickCount64();
		break;
	}
	case MARIO_STATE_WHIP: {
		if (whip_start != -1) break;
		whip_start = GetTickCount64();
		break;
	}
	case MARIO_STATE_FLOAT: {
		maxVy = MARIO_MAX_FALL_SPEED / 5;
		if (float_start != -1) break;
		float_start = GetTickCount64();
		break;
	}
	case MARIO_STATE_FLY: {
		vy = -MARIO_FLY_SPEED_Y;
		break;
	}
	}

	if (GetTickCount64() - kick_start < MARIO_KICK_TIME) {
		state = MARIO_STATE_KICK;	
	}
	else kick_start = -1;

	if (GetTickCount64() - whip_start < MARIO_WHIP_TIME) {
		state = MARIO_STATE_WHIP;
	}
	else whip_start = -1;

	if (GetTickCount64() - float_start < MARIO_FLOAT_TIME) {
		state = MARIO_STATE_FLOAT;	
	}
	else {
		maxVy = MARIO_MAX_FALL_SPEED;
		float_start = -1;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
		if (state == MARIO_STATE_WHIP)
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}

}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (float)(MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;

	SaveFile::GetInstance()->SetMarioLevel(level);
}


void CMario::UpdateOnFreeze(DWORD dt) {
	if (state == MARIO_STATE_DIE) {
		vy = min(vy + ay * dt, maxVy);
		y += vy * dt;
	}

	if (switch_delay_start != -1) {
		int dir_x, dir_y;
		portalCanUse->GetDirection(dir_x, dir_y);
		x += 0.05f * dir_x * dt;
		y += 0.05f * dir_y * dt;
	}

	if (switch_delay_start != -1 && GetTickCount64() - switch_delay_start >= 500) {
		portalCanUse->SwitchScene();
		switch_delay_start = -1;
	}

}

void CMario::RenderOnFreeze() {
	CAnimations::GetInstance()->Get(freezeId)->Render(x, y);
}

void CMario::StartSwitchingScene() {
	CGame::GetInstance()->GetCurrentScene()->FreezeScene(1100);
	switch_delay_start = GetTickCount64();

	freezeId = ID_ANI_MARIO_SMALL_STRAIGHT;
	if(level == MARIO_LEVEL_BIG) freezeId += 100;
	if(level == MARIO_LEVEL_RACOON) freezeId += 200;
}
