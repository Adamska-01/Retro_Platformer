#pragma once
#include "GameObject.h"
#include "Math/Vector2.h"
#include <string_view>


struct CollisionInfo;


class Key : public GameObject
{
private:
	int score = 100;

	std::string_view spriteSource;

	
	void OnContactEnterHandler(const CollisionInfo& collisionInfo);


public:
	Key(Vector2F startPos, std::string_view spriteSource);


	virtual void ConstructGameObject() override;
};