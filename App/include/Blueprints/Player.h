#pragma once
#include <GameObject.h>
#include <Math/Vector2.h>
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