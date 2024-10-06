#include "pch.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Font.h"
#include "Text.h"
#include "EventManager.h"

Timer::Timer()
{
	_font = ResourceManager::GetInstance()->GetTextFont(L"TextFont01_12x20");
	int a = 0;
}

Timer::~Timer()
{
}

void Timer::Init()
{
	Super::Init();

	unique_ptr<Text> minText = make_unique<Text>();
	minText->SetFont(_font);
	minText->SetPos({ 468, 10 });
	minText->SetLetters(to_string(_minute));
	AddChild(::move(minText));

	unique_ptr<Text> secText = make_unique<Text>();
	secText->SetFont(_font);
	secText->SetPos({ 488, 10 });
	secText->SetLetters(to_string(_second));
	AddChild(::move(secText));

}

void Timer::Update()
{
	float deltaTime = TimeManager::GetInstance()->GetAdjustDeltaTime();
	_sumTime += deltaTime;
	if (_sumTime >= 1.f)
	{
		++_second;
		if (_second > 59)
		{
			_second = 0;
			++_minute;

			EventManager::GetInstance()->AddEvent([this]() {
				unique_ptr<Text> minText = make_unique<Text>();
				minText->SetFont(_font);
				minText->SetPos({ 468, 10 });
				minText->SetLetters(to_string(_minute));

				_children[0] = ::move(minText);
				});
		}

		unique_ptr<Text> secText = make_unique<Text>();
		secText->SetFont(_font);
		secText->SetPos({ 488, 10 });
		secText->SetLetters(to_string(_second));
	
		_children[1] = ::move(secText);

		_sumTime = 0.f;
	}

	Super::Update();
}

void Timer::Render(HDC hdc)
{
	Super::Render(hdc);
}
