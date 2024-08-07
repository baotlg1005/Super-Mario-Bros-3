#include "Scene.h"
#include "SaveFile.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->key_handler = NULL;
	this->mainHUD = NULL;
}

void CScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens[0] == "time") {
		if (timeLimit == -1) timeLimit = (float)atof(tokens[1].c_str());
	}

	if (tokens[0] == "background_color") {
		float r = (float)atof(tokens[1].c_str());
		float g = (float)atof(tokens[2].c_str());
		float b = (float)atof(tokens[3].c_str());

		backgroundColor = D3DXCOLOR(r / 255, g / 255, b / 255, 0.0f);
	}

	if (tokens[0] == "cam_limit") {
		if (tokens.size() > 1) camLimitLeft = (float)atof(tokens[1].c_str());
		if (tokens.size() > 2) camLimitRight = (float)atof(tokens[2].c_str());
		if (tokens.size() > 3) camLimitBottom = (float)atof(tokens[3].c_str());
		if (tokens.size() > 4) camLimitTop = (float)atof(tokens[4].c_str());
		if (tokens.size() > 5) camVerticalFreeZone = (float)atof(tokens[5].c_str());
	}

	if (tokens[0] == "level_id") {
		this->level_id = atoi(tokens[1].c_str());
	}
}

void CScene::FreezeScene(ULONGLONG time)
{
	freezeTime = time;
	isFreeze = true;
	freeze_start = GetTickCount64();
}

void CScene::Update(DWORD dt)
{
	if (isFreeze)
	{
		if (loadingStart || loadingEnd) freeze_start = GetTickCount64();
		if (GetTickCount64() - freeze_start > freezeTime)
		{
			isFreeze = false;
			freeze_start = -1;
		}
	}

	if(isSwitchingScene && !loadingEnd)
	{
		CGame::GetInstance()->InitiateSwitchScene(switchSceneID);
		switchSceneID = -1;
	}
}

void CScene::LoadUI() {
	DebugOut(L"[INFO] Start loading UI\n");
	mainHUD = new CHUD(0, 0);

	LPSAVEFILE saveFile = SaveFile::GetInstance();

	mainHUD->SetCoin(saveFile->GetCoin());
	mainHUD->SetScore(saveFile->GetScore());
	mainHUD->SetLife(saveFile->GetLife());
	mainHUD->SetWorld(saveFile->GetWorld());

	mainHUD->SetFirstCard(saveFile->GetCardSlot1());
	mainHUD->SetSecondCard(saveFile->GetCardSlot2());
	mainHUD->SetThirdCard(saveFile->GetCardSlot3());
}

void CScene::UpdateUI(DWORD dt) {
	if (mainHUD == NULL) return;
	LPSAVEFILE saveFile = SaveFile::GetInstance();

	mainHUD->SetCoin(saveFile->GetCoin());
	mainHUD->SetScore(saveFile->GetScore());
	mainHUD->SetLife(saveFile->GetLife());
	mainHUD->SetWorld(saveFile->GetWorld());

	mainHUD->SetFirstCard(saveFile->GetCardSlot1());
	mainHUD->SetSecondCard(saveFile->GetCardSlot2());
	mainHUD->SetThirdCard(saveFile->GetCardSlot3());
}

void CScene::LoadIntro() {
	loadingStart = true;
	loading_start = GetTickCount64();
}

void CScene::LoadOutro() {
	loadingEnd = true;
	loading_end = GetTickCount64();
}


void CScene::RenderLoadingStart() {
	float alpha = (GetTickCount64() - loading_start) / (float)LOADING_START_TIME;

	if (alpha < 0.25f) alpha = 0;

	RenderBlackScreen(1 - alpha);
	if (alpha >= 0.75f) {
		loading_start = -1;
		loadingStart = false;
	}
}

void CScene::RenderLoadingEnd() {
	float alpha = (GetTickCount64() - loading_end) / (float)LOADING_END_TIME;

	if (alpha > 0.75f) {
		alpha = 1;
		loading_end = -1;
		loadingEnd = false;
	}

	RenderBlackScreen(alpha);
}

void CScene::ReadyToSwitchScene(int switchSceneID) {
	this->switchSceneID = switchSceneID;
	isSwitchingScene = true;
	LoadOutro();

	DebugOut(L"[INFO] Ready to switch scene\n");
	DebugOut(L"[INFO] switchSceneID: %d\n", switchSceneID);

}