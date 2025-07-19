#pragma once
#include "Components/AI/Abstractions/AIBehavior.h"


class FlyingAIBehavior : public AIBehavior
{
private:
	float minDistance;

	float speed;


public:
	FlyingAIBehavior();


	void Update(SimpleAI* ai, float deltaTime) override;
};
