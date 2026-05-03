#pragma once
#include "Data/Entities/EnemyConfig.h"
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>


class Enemy : public DF2D::Engine::GameObject
{
private:
	EnemyConfig enemyConfig;

	DF2D::Core::Vector2F startPos;


public:
	Enemy(DF2D::Core::Vector2F startPos, const EnemyConfig& enemyConfig);


	virtual void ConstructGameObject() override;
};