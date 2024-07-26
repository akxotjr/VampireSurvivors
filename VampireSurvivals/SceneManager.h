#pragma once

#include "Scene.h"

class SceneManager
{
public:
	~SceneManager() = default;

	static SceneManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = make_unique<SceneManager>();
		}
		return instance.get();
	}

	void Init();
	void Update();
	void Render(HDC hdc);

	//void Clear();

	void ChangeScene(SceneType sceneType);
	unique_ptr<Scene>& GetCurrentScene() { return _scene; }

private:
	SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	friend std::unique_ptr<SceneManager> std::make_unique<SceneManager>();

private:
	static unique_ptr<SceneManager> instance;

	unique_ptr<Scene> _scene = nullptr;
	SceneType _sceneType = SceneType::None;

	//public:
		//Vec2 GetCameraPos() { return _cameraPos; }
		//void SetCameraPos(Vec2 pos) { _cameraPos = pos; }

	//private:
		//Vec2 _cameraPos = { 400, 300 };
};

