#pragma once
#include "Scene.h"

class UI;

class StatUpgradeScene : public Scene
{
	using Super = Scene;
public:
	StatUpgradeScene();
	virtual ~StatUpgradeScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AtkUpgradeButton();
};

