#pragma once
#include "Scene.h"

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//bool CanGo(Vec2Int cellpos);
	//Vec2 ConvertPos(Vec2Int cellPos);

};
