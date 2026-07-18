#pragma once
#include <array>
#include <Core/Math/Vector2.h>
#include <Data/Systems/Graphics/TextureID.h>
#include <Data/Systems/Rendering/RenderFlip.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <string_view>


namespace DF2D::Core
{
	class InputActionView;
	class TextureManager;
}

namespace DF2D::Engine
{
	class Transform;
	class RigidBody2D;
	class SpriteAnimator;
}

namespace DF2D::Data
{
	struct CollisionInfo;
}


class PlayerController : public DF2D::Engine::GameComponent
{
	TYPE_INFO(PlayerController, DF2D::Engine::GameComponent);


private:
	DF2D::Engine::ComponentHandle<DF2D::Engine::Transform> transform;

	DF2D::Engine::ComponentHandle<DF2D::Engine::RigidBody2D> rigidBody;

	DF2D::Engine::ComponentHandle<DF2D::Engine::SpriteAnimator> spriteAnimator;

	DF2D::Core::TextureManager* textureManager = nullptr;

	DF2D::Core::Vector2F startPos;

	DF2D::Data::RenderFlip flipState;

	std::array<DF2D::Data::TextureID, 2> spriteCache{};

	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;

	int footContacts;

	float speed;

	float jumpImpulse;

	float yThreshold;


	void OnContactEnterHandler(const DF2D::Data::CollisionInfo& collisionInfo);

	void OnContactExitHandler(const DF2D::Data::CollisionInfo& collisionInfo);


	void MoveInputHandler(const DF2D::Core::InputActionView& inputAction);

	void JumpInputHandler(const DF2D::Core::InputActionView& inputAction);


public:
	PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource);

	virtual ~PlayerController() override = default;


	void Init() override;

	void Start() override;

	void Update(float deltaTime) override;


	void LoseLife();
};
