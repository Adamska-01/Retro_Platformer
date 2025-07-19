#pragma once
#include <GameObject.h>
#include <Math/Vector2.h>
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