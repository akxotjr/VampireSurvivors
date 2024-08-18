#include "pch.h"
#include "GravityCannon.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "FlipbookActor.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "Player.h"


GravityCannon::GravityCannon()
{
	_flipbook = ResourceManager::GetInstance()->GetFlipbook(L"FB_GravityCannon");
}

GravityCannon::~GravityCannon()
{
}

void GravityCannon::Init()
{
	SetCooltime(3.f);
	SetDamage();
}

void GravityCannon::Update()
{
    auto it = _skillObjectsAndDurations.begin();
    while (it != _skillObjectsAndDurations.end())
    {
        Vec2 pos = it->first->GetPos();
        Vec2 destPos = it->first->GetDestPos();

        if (pos == destPos)
        {
            float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
            it->second += deltaTime;

            if (it->second >= _skillDuration)
            {
                GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
                scene->RemoveActor(it->first);

                // 요소를 제거하고, 반복자를 업데이트
                it = _skillObjectsAndDurations.erase(it);
                continue;
            }
        }
        else
        {
            Vec2 dir = it->first->GetDir();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
            float moveSpeed = 2.f;

            float curDist = (destPos - pos).Length();

            // 근접했을 때 destPos 로 설정
            if (curDist < moveSpeed)
            {
                it->first->SetPos(destPos);
            }
            else
            {
                it->first->SetPos(pos + dir * moveSpeed);
            }
        }

        // 다음 요소로 이동
        ++it;
    }
}

void GravityCannon::Use(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _coolTime)
	{
		FlipbookActor* gravitycannon = new FlipbookActor();
		gravitycannon->SetFlipbook(_flipbook);
		gravitycannon->SetStartPos(GetOwner()->GetPos());
		gravitycannon->SetPos(GetOwner()->GetPos());
		gravitycannon->SetLayer(LAYER_UNDERSKILL);
		gravitycannon->SetDestPos(GetRandomDestPos());

		GameScene* gamescene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		gamescene->AddActor(gravitycannon);

		Skill::AddSkillObjectAndDuration(gravitycannon, 0.f);
		_sumTime = 0.f;
	}
}

void GravityCannon::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

Vec2 GravityCannon::GetRandomDestPos()
{
	Vec2 pos = GetOwner()->GetPos();

	::random_device rd;
	::mt19937 gen(rd());

	::uniform_real_distribution<float> theta_dist(0.f, 2.f * PI);
	float theta = theta_dist(gen);

	Vec2 destPos;
	destPos.x = pos.x + _dist * cos(theta);
	destPos.y = pos.y + _dist * sin(theta);

	return destPos;
}
