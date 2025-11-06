#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <string_view>


namespace DeadFrame2D::Data
{
	struct CollisionInfo;
}


class Key : public DeadFrame2D::Engine::GameObject
{
private:
	DeadFrame2D::Core::Vector2F startPos;

	int score = 100;

	std::string_view spriteSource;

	
	void OnContactEnterHandler(const DeadFrame2D::Data::CollisionInfo& collisionInfo);


public:
	Key(DeadFrame2D::Core::Vector2F startPos, std::string_view spriteSource);


	virtual void ConstructGameObject() override;
};