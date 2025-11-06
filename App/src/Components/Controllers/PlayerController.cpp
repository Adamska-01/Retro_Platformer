#include "Components/Controllers/PlayerController.h"
#include "Components/Map/CustomTileMapCollider2D.h"
#include <Constants/AssetPaths.h>
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <Core/SubSystems/Systems/Input/Input.h>
#include <Core/SubSystems/Systems/TextureManager.h>
#include <CustomEvents/LifeLostEvent.h>
#include <Data/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Collisions/BoxCollider2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


PlayerController::PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource)
	: startPos(Vector2F::Zero),
	flipState(SDL_RendererFlip::SDL_FLIP_NONE),
	idleSpriteSource(idleSpriteSource),
	runSpriteSource(runSpriteSource),
	footContacts(0),
	speed(6.5f),
	jumpImpulse(50.0f),
	yThreshold(0.0f)
{
	spriteCache =
	{
		TextureManager::LoadTexture(idleSpriteSource),
		TextureManager::LoadTexture(runSpriteSource),
	};
}

void PlayerController::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	if (!collisionInfo.otherGameObject)
		return;

	auto tileComponent = collisionInfo.otherGameObject->GetComponent<CustomTileMapCollider2D>();

	if (tileComponent == nullptr)
		return;

	++footContacts;
}

void PlayerController::OnContactExitHandler(const CollisionInfo& collisionInfo)
{
	if (!collisionInfo.otherGameObject)
		return;

	auto tileComponent = collisionInfo.otherGameObject->GetComponent<CustomTileMapCollider2D>();

	if (tileComponent == nullptr)
		return;

	--footContacts;
}

void PlayerController::Move()
{
	auto xDir = 0.0f;

	if (Input::IsButtonHeld(PlayerInputSlot::PLAYER_1, "Left"))
	{
		xDir += -1.0f;
	}
	if (Input::IsButtonHeld(PlayerInputSlot::PLAYER_1, "Right"))
	{
		xDir += 1.0f;
	}

	rigidBody->SetVelocityX(xDir * speed);
}

void PlayerController::Jump()
{
	if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Jump") && footContacts > 0)
	{
		rigidBody->AddImpulse(Vector2F::Up * jumpImpulse);

		// Jump Sound
		auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(AssetPaths::Files::PLAYER_JUMP);

		CoroutineScheduler::StartCoroutine(soundSourceObj->Destroy(1.0f));
	}
}

void PlayerController::AnimationState()
{
	auto xVel = rigidBody->GetVelocity().x;

	auto animationName = xVel != 0.0f ? "Run" : "Idle";
	auto flipState = xVel < 0.0f ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	spriteAnimator->PlayAnimation(animationName);
	spriteAnimator->SetFlipState(flipState);
}

void PlayerController::Init()
{
	transform = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<Transform>(), NAME_OF(transform));
	rigidBody = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<RigidBody2D>(), NAME_OF(rigidBody));
	spriteAnimator = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<SpriteAnimator>(), NAME_OF(spriteAnimator));
}

void PlayerController::Start()
{
	auto idleAnim = SpriteAnimationProperties
	{
		.name = "Idle",
		.spriteSource = idleSpriteSource,
		.columnCount = 8,
		.rowCount = 1,
		.animSpeed = 6.0f,
		.loop = true
	};

	auto runAnim = SpriteAnimationProperties
	{
		.name = "Run",
		.spriteSource = runSpriteSource,
		.columnCount = 8,
		.rowCount = 1,
		.animSpeed = 10.0f,
		.loop = true
	};

	spriteAnimator->AddAnimation(idleAnim);
	spriteAnimator->AddAnimation(runAnim);

	startPos = transform->GetWorldPosition();

	auto boxCollider = GetGameObject()->GetComponent<BoxCollider2D>();

	auto tileRenderer = SceneManager::FindObjectOfType<CustomTileMapRenderer2D>();
	
	auto mapFullSize = tileRenderer->GetMapFullSize();

	auto tileRendererPos = tileRenderer->GetGameObject()->GetTransform()->GetWorldPosition();

	yThreshold = tileRendererPos.y + mapFullSize.y + 100.0f; // Add some gap

	if (boxCollider == nullptr)
		return;

	boxCollider->RegisterContactEnterHandler(EventHelpers::BindFunction(this, &PlayerController::OnContactEnterHandler), reinterpret_cast<uintptr_t>(this));
	boxCollider->RegisterContactExitHandler(EventHelpers::BindFunction(this, &PlayerController::OnContactExitHandler), reinterpret_cast<uintptr_t>(this));
}

void PlayerController::Update(float deltaTime)
{
	Move();
	Jump();
	AnimationState();

	if (transform->GetWorldPosition().y > yThreshold)
	{
		LoseLife();
	}
}

void PlayerController::LoseLife()
{
	EventDispatcher::SendEvent(std::make_shared<LifeLostEvent>());

	transform->SetWorldPosition(startPos);
}