#pragma once
#include "Components/GameComponent.h"
#include <Math/Vector2.h>


class Transform;


class ExampleComponent : public GameComponent
{
private:
	Transform* transform;

	Vector2F initialPosition;

	float timeAccumulator;

	float amplitude;

	float frequency;

	float rotationSpeed;


public:
	ExampleComponent(float amplitude, float frequency, float rotationSpeed);

	virtual ~ExampleComponent() override = default;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;
};