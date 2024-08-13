#pragma once
#include "Scene.h"


class LobbyScene : public Scene
{
	using Super = Scene;
public:
	LobbyScene();
	virtual ~LobbyScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);


};

