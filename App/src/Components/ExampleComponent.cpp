#include "Components/ExampleComponent.h"
#include <Components/Transform.h>
#include <GameObject.h>
#include <Tools/Helpers/Guards.h>


ExampleComponent::ExampleComponent(float amplitude, float frequency, float rotationSpeed)
	: transform(nullptr),
	initialPosition(Vector2F::Zero),
	timeAccumulator(0.0f),
	amplitude(amplitude),
	frequency(frequency),
	rotationSpeed(rotationSpeed)
{
}

void ExampleComponent::Init()
{
	transform = OwningObject.lock()->GetComponent<Transform>();

	Tools::Helpers::GuardAgainstNull(transform, "ExampleComponent::Init: Transform not found from ExampleComponent.");
}

void ExampleComponent::Start()
{
	initialPosition = transform->GetWorldPosition();
}

void ExampleComponent::Update(float deltaTime)
{
	timeAccumulator += deltaTime;
	timeAccumulator = std::fmod(timeAccumulator, 1000.0f);

	transform->RotateByDegrees(rotationSpeed * deltaTime);

	auto offset = std::sin(timeAccumulator * MathConstants::PI * frequency) * amplitude;

	transform->SetWorldPosition(Vector2F(initialPosition.x + offset, initialPosition.y));
}

void ExampleComponent::Draw()
{

}