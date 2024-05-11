#include "Koopas.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	hide_start = -1;
	restore_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_HIDE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_HIDE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPAS_STATE_HIDE) && (GetTickCount64() - hide_start > KOOPAS_HIDE_TIMEOUT))
	{
		SetState(KOOPAS_STATE_RESTORE);
	}
	if ((state == KOOPAS_STATE_RESTORE) && (GetTickCount64() - restore_start > KOOPAS_RESTORE_TIMEOUT)) {
		SetState(KOOPAS_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (vy == 0 && fallCheckingObject == NULL)
	{
		if (vx < 0)
		{
			fallCheckingObject = new CFallCheckingObject(x - 16, y);
		}
		else
		{
			fallCheckingObject = new CFallCheckingObject(x + 16, y);
			float fall_vx, _;
			fallCheckingObject->GetSpeed(fall_vx, _);
			fallCheckingObject->SetSpeed(-fall_vx, _);
		}
	}

	if (fallCheckingObject != NULL) {
		fallCheckingObject->Update(dt, coObjects);
		
		float _, fallCheckingObject_vy;
		fallCheckingObject->GetSpeed(_, fallCheckingObject_vy);
		if (fallCheckingObject_vy != 0)
		{
			fallCheckingObject->Delete();
			fallCheckingObject = NULL;
			vx = -vx;
		}
	}


}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;
	if (vx > 0)
	{
		aniId = ID_ANI_KOOPAS_FLIP_WALKING;
	}
	if (state == KOOPAS_STATE_HIDE)
	{
		aniId = ID_ANI_KOOPAS_HIDE;
	}
	if (state == KOOPAS_STATE_RESTORE) {
		aniId = ID_ANI_KOOPAS_RESTORE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	if (fallCheckingObject != NULL) {
		fallCheckingObject->Render();
	}
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		break;
	case KOOPAS_STATE_HIDE:
		hide_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_HIDE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_RESTORE:
		restore_start = GetTickCount64();
		break;
	case KOOPAS_STATE_SLIDE:
		break;
	case KOOPAS_STATE_WALKING:
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_HIDE) / 2;

		vx = -KOOPAS_WALKING_SPEED;
		this->ax = 0;
		this->ay = KOOPAS_GRAVITY;
		die_start = -1;
		hide_start = -1;
		restore_start = -1;
		break;
	}
}
