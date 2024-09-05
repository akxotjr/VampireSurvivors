#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
	using Super = Scene;
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void GoToLobbyScene();
};

