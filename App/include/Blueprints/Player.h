#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <SDL.h>
#include <string_view>


class Transform;


class Player : public GameObject
{
private:
	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;


public:
	Player(Vector2F startPos, std::string_view idleSpriteSource, std::string_view runSpriteSource);
	
	~Player();
	

	virtual void ConstructGameObject() override;
};