#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{

}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);								  
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); 
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);			  
	::DeleteObject(prev);

	TimeManager::GetInstance()->Init();
	InputManager::GetInstance()->Init(hwnd);
	SceneManager::GetInstance()->Init();

	//ResourceManager::GetInstance()->Init(hwnd, fs::path(L"C:\\Users\\UserK\\Desktop\\Project_VampireSurvivors\\VampireSurvivors\\Resources"));
	ResourceManager::GetInstance()->Init(hwnd, fs::path(L"C:\\Users\\matae\\source\\repos\\akxotjr\\VampireSurvivals\\VampireSurvivals\\Resources"));
	SceneManager::GetInstance()->ChangeScene(SceneType::StatUpgradeScene);
}

void Game::Update()
{
	TimeManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
}

void Game::Render()
{
	SceneManager::GetInstance()->Render(_hdcBack);

	uint32 fps = TimeManager::GetInstance()->GetFps();
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	{
		POINT mousePos = InputManager::GetInstance()->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(_hdcBack, 600, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	//// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}