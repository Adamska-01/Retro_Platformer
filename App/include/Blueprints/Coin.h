#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <string_view>


class Map;

namespace DF2D::Data
{
	struct CollisionInfo;
}


class Coin : public DF2D::Engine::GameObject
{
private:
	DF2D::Core::Vector2F startPos;

	unsigned int score;

	std::string_view spriteSource;


	void OnContactEnterHandler(const DF2D::Data::CollisionInfo& collisionInfo);


public:
	Coin(DF2D::Core::Vector2F startPos, std::string_view spriteSource);
};