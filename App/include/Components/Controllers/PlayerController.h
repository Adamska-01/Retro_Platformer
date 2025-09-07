#pragma once
#include <array>
#include <Core/Math/Vector2.h>
#include <Engine/Components/GameComponent.h>
#include <memory>
#include <SDL.h>
#include <string_view>


class Transform;
class RigidBody2D;
class SpriteAnimator;
struct CollisionInfo;


class PlayerController : public GameComponent
{
private:
	Transform* transform;

	RigidBody2D* rigidBody;

	SpriteAnimator* spriteAnimator;

	Vector2F startPos;

	SDL_RendererFlip flipState;

	std::array<std::shared_ptr<SDL_Texture>, 2> spriteCache;

	std::string_view idleSpriteSource;

	std::string_view runSpriteSource;

	int footContacts;

	float speed;

	float jumpImpulse;

	float yThreshold;


	void OnContactEnterHandler(const CollisionInfo& collisionInfo);

	void OnContactExitHandler(const CollisionInfo& collisionInfo);

	void Move();

	void Jump();

	void AnimationState();


public:
	PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource);

	virtual ~PlayerController() override = default;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void LoseLife();
};