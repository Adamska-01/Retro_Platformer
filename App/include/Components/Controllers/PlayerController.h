#pragma once
#include <array>
#include <Core/Math/Vector2.h>
#include <Engine/Components/GameComponent.h>
#include <Engine/Entity/ComponentHandle.h>
#include <memory>
#include <SDL.h>
#include <string_view>


namespace DeadFrame2D::Core
{
	class RuntimeInputAction;
}

namespace DeadFrame2D::Engine
{
	class Transform;
	class RigidBody2D;
	class SpriteAnimator;
}

namespace DeadFrame2D::Data
{
	struct CollisionInfo;
}


class PlayerController : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(PlayerController, DeadFrame2D::Engine::GameComponent);


private:
	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::Transform> transform;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::RigidBody2D> rigidBody;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::SpriteAnimator> spriteAnimator;

	DeadFrame2D::Core::Vector2F startPos;

	SDL_RendererFlip flipState;

	std::array<std::shared_ptr<SDL_Texture>, 2> spriteCache;

	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;

	int footContacts;

	float speed;

	float jumpImpulse;

	float yThreshold;


	void OnContactEnterHandler(const DeadFrame2D::Data::CollisionInfo& collisionInfo);

	void OnContactExitHandler(const DeadFrame2D::Data::CollisionInfo& collisionInfo);


	void MoveInputHandler(const DeadFrame2D::Core::RuntimeInputAction& inputAction);

	void JumpInputHandler(const DeadFrame2D::Core::RuntimeInputAction& inputAction);


public:
	PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource);

	virtual ~PlayerController() override = default;


	void Init() override;

	void Start() override;

	void Update(float deltaTime) override;


	void LoseLife();
};