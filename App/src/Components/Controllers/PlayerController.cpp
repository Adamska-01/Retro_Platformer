#include "Components/Controllers/PlayerController.h"
#include "Components/Map/CustomTileMapCollider2D.h"
#include <Blueprints/Audio/AudioClipBlueprint.h>
#include <Components/Collisions/BoxCollider2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/SpriteAnimator.h>
#include <Components/Transform.h>
#include <Constants/AssetPaths.h>
#include <Coroutines/CoroutineScheduler.h>
#include <CustomEvents/LifeLostEvent.h>
#include <Data/Collision/CollisionInfo.h>
#include <GameObject.h>
#include <SubSystems/Input/Input.h>
#include <SubSystems/TextureManager.h>
#include <Tools/Helpers/EventHelpers.h>
#include <Tools/Helpers/Guards.h>
#include <Management/SceneManager.h>


PlayerController::PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource)
	: transform(nullptr),
	rigidBody(nullptr),
	spriteAnimator(nullptr),
	startPos(Vector2F::Zero),
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
	if (collisionInfo.otherGameObject.expired())
		return;

	auto tileComponent = collisionInfo.otherGameObject.lock()->GetComponent<CustomTileMapCollider2D>();

	if (tileComponent == nullptr)
		return;

	++footContacts;
}

void PlayerController::OnContactExitHandler(const CollisionInfo& collisionInfo)
{
	if (collisionInfo.otherGameObject.expired())
		return;

	auto tileComponent = collisionInfo.otherGameObject.lock()->GetComponent<CustomTileMapCollider2D>();

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

		CoroutineScheduler::StartCoroutine(soundSourceObj.lock()->Destroy(1.0f));
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
	transform = OwningObject.lock()->GetComponent<Transform>();
	rigidBody = OwningObject.lock()->GetComponent<RigidBody2D>();
	spriteAnimator = OwningObject.lock()->GetComponent<SpriteAnimator>();

	Tools::Helpers::GuardAgainstNull(transform, "Failed to get Transform from OwningObject");
	Tools::Helpers::GuardAgainstNull(rigidBody, "Failed to get RigidBody2D from OwningObject");
	Tools::Helpers::GuardAgainstNull(spriteAnimator, "Failed to get SpriteAnimator from OwningObject");
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

	auto boxCollider = OwningObject.lock()->GetComponent<BoxCollider2D>();

	auto tileRenderer = SceneManager::FindObjectOfType<CustomTileMapRenderer2D>();
	
	auto mapFullSize = tileRenderer->GetMapFullSize();

	auto tileRendererPos = tileRenderer->GetGameObject().lock()->GetTransform()->GetWorldPosition();

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

	auto pos = transform->GetWorldPosition();

	if (pos.y > yThreshold)
	{
		LoseLife();
	}
}

void PlayerController::Draw()
{

}

void PlayerController::LoseLife()
{
	EventDispatcher::SendEvent(std::make_shared<LifeLostEvent>());

	transform->SetWorldPosition(startPos);
}