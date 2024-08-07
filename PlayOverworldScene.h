#pragma once
#include "Scene.h"

#include "OW_GameObject.h"
#include "OW_MapHolder.h"

#include "OW_Mario.h"
#include "OW_Path.h"
#include "OW_Terrain.h"
#include "OW_Portal.h"
#include "OW_Point.h"
#include "OW_Boss.h"


class CPlayOverworldScene : public CScene
{
protected:
	LPOWGAMEOBJECT player;
	COWMapHolder* mapHolder;
	vector<LPOWGAMEOBJECT> pathObjs;
	vector<LPOWGAMEOBJECT> terrainObjs;
	vector<LPOWGAMEOBJECT> portalObjs;
	vector<LPOWGAMEOBJECT> pointObjs;
	COWBoss* boss;

	void _ParseSection_OBJECTS(string line);

public:
	CPlayOverworldScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Unload();

	virtual void LoadSave();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void LoadUI();

	virtual void Clear() {};

	virtual LPOWGAMEOBJECT GetOWPlayer() { return player; }

	virtual void RenderBlackScreen(float alpha);
};

typedef CPlayOverworldScene* LPPLAYOVERWORLDSCENE;

