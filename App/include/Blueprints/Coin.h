#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <string_view>


class Map;

namespace DeadFrame2D::Data
{
	struct CollisionInfo;
}


class Coin : public DeadFrame2D::Engine::GameObject
{
private:
	unsigned int score;

	std::string_view spriteSource;


	void OnContactEnterHandler(const DeadFrame2D::Data::CollisionInfo& collisionInfo);


public:
	Coin(DeadFrame2D::Core::Vector2F startPos, std::string_view spriteSource);


	virtual void ConstructGameObject() override;
};