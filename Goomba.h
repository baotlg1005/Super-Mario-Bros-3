#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 12
#define GOOMBA_BBOX_HEIGHT_DIE 5

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_KNOCKOUT 300

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	bool isKnockOut = false;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { 
		if(state == GOOMBA_STATE_WALKING) return 1;
		return 0;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
	virtual void TakeDamage(bool isKnockOut = false);
};