#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <string_view>


class Player : public DF2D::Engine::GameObject
{
private:
	DF2D::Core::Vector2F startPos;

	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;


public:
	Player(DF2D::Core::Vector2F startPos, std::string_view idleSpriteSource, std::string_view runSpriteSource);

	~Player();
};