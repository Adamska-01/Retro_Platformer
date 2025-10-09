#pragma once
#include "Data/Animation/SpriteAnimationProperties.h"
#include <Data/Physics/BodyDefinition2D.h>
#include <string_view>


struct EnemyConfig
{
	std::string_view spriteSource;

	bool canFly = false;

	float characterSize = 32.0f;

	float gravityScale = 1.0f;

	DeadFrame2D::Data::SpriteAnimationProperties idleAnimProperty;

	DeadFrame2D::Data::BodyDefinition2D bodyDefinition;
};