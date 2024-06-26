#pragma once
#include "OW_GameObject.h"
#include "AssetIDs.h"

class COWPath: public COWGameObject {
protected:
	bool isVertical;
	bool haveCoin;
	bool haveTurn;
public:
	COWPath(float x, float y, bool canGoIn, bool isVertical, bool haveCoin, bool haveTurn);
	void Render();
};