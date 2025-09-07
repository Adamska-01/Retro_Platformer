#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
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