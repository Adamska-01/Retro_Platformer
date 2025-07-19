#pragma once
#include "Components/AI/Abstractions/AIBehavior.h"


class GroundAIBehavior : public AIBehavior
{
private:
	bool movingLeft;
	
	float speed;


public:
	GroundAIBehavior();


	void Update(SimpleAI* ai, float deltaTime) override;
};