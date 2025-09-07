#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <string_view>


class Map;
struct CollisionInfo;


class Coin : public GameObject
{
private:
	unsigned int score;

	std::string_view spriteSource;


	void OnContactEnterHandler(const CollisionInfo& collisionInfo);


public:
	Coin(Vector2F startPos, std::string_view spriteSource);


	virtual void ConstructGameObject() override;
};