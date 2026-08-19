#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <string_view>


namespace DF2D::Data
{
	struct CollisionInfo;
}


class Key : public DF2D::Engine::GameObject
{
private:
	DF2D::Core::Vector2F startPos;

	int score = 100;

	std::string_view spriteSource;

	
	void OnContactEnterHandler(const DF2D::Data::CollisionInfo& collisionInfo);


public:
	Key(DF2D::Core::Vector2F startPos, std::string_view spriteSource);
};