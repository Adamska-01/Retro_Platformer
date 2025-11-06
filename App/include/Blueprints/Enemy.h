#pragma once
#include "Data/Entities/EnemyConfig.h"
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>


class Enemy : public DeadFrame2D::Engine::GameObject
{
private:
	EnemyConfig enemyConfig;

	DeadFrame2D::Core::Vector2F startPos;


public:
	Enemy(DeadFrame2D::Core::Vector2F startPos, const EnemyConfig& enemyConfig);


	virtual void ConstructGameObject() override;
};