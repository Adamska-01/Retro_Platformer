#pragma once
#include "Data/Entities/EnemyConfig.h"
#include <GameObject.h>
#include <Math/Vector2.h>
#include <string_view>


class Enemy : public GameObject
{
private:
	EnemyConfig enemyConfig;


public:
	Enemy(Vector2F startPos, const EnemyConfig& enemyConfig);


	virtual void ConstructGameObject() override;
};