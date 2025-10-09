#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <string_view>


class Player : public DeadFrame2D::Engine::GameObject
{
private:
	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;


public:
	Player(DeadFrame2D::Core::Vector2F startPos, std::string_view idleSpriteSource, std::string_view runSpriteSource);

	~Player();


	virtual void ConstructGameObject() override;
};