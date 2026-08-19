#pragma once
#include "Data/Components/Animation/SpriteAnimationProperties.h"
#include "Data/Components/Physics/BodyDefinition2D.h"
#include <string_view>


struct EnemyConfig
{
	std::string_view spriteSource;

	bool canFly = false;

	float characterSize = 32.0f;

	float gravityScale = 1.0f;

	DF2D::Data::SpriteAnimationProperties idleAnimProperty;

	DF2D::Data::BodyDefinition2D bodyDefinition;
};