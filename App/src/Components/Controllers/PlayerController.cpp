#include "Components/Audio/DestroyOnAudioFinished.h"
#include "Components/Controllers/PlayerController.h"
#include "Components/Map/CustomTileMapCollider2D.h"
#include <Constants/AssetPaths.h>
#include <Core/Context/Systems/Graphics/TextureManager.h>
#include <Core/Context/Systems/Input/Actions/InputActionView.h>
#include <CustomEvents/LifeLostEvent.h>
#include <Data/Components/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Collisions/BoxCollider2D.h>
#include <Engine/ECS/Component/Input/PlayerInput.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Events/EventDispatcher.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


PlayerController::PlayerController(std::string_view idleSpriteSource, std::string_view runSpriteSource)
	: startPos(Vector2F::Zero),
	flipState(RenderFlip::NONE),
	idleSpriteSource(idleSpriteSource),
	runSpriteSource(runSpriteSource),
	footContacts(0),
	speed(6.5f),
	jumpImpulse(50.0f),
	yThreshold(0.0f)
{
}

void PlayerController::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	if (!collisionInfo.otherGameObject)
		return;

	auto tileComponent = collisionInfo.otherGameObject->GetComponent<CustomTileMapCollider2D>();

	if (tileComponent == nullptr)
		return;

	++footContacts;

	rigidBody->SetVelocityX(0.0f);
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

void PlayerController::MoveInputHandler(const InputActionView& inputAction)
{
	auto dir = inputAction.ReadValue<Vector2F>();

	rigidBody->SetVelocityX(dir.x * speed);

	// Animation State
	spriteAnimator->PlayAnimation(dir.x != 0.0f ? "Run" : "Idle");
	spriteAnimator->SetFlipState(dir.x < 0.0f ? RenderFlip::HORIZONTAL : RenderFlip::NONE);
}

void PlayerController::JumpInputHandler(const InputActionView& inputAction)
{
	if (!inputAction.IsStarted() || footContacts <= 0)
		return;

	rigidBody->AddImpulse(Vector2F::Up * jumpImpulse);

	// Jump Sound (self-destroys once the clip finishes)
	auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(AssetPaths::Files::PLAYER_JUMP);

	soundSourceObj->AddComponent<DestroyOnAudioFinished>();
}

void PlayerController::Init()
{
	transform = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<Transform>(), NAME_OF(transform));
	rigidBody = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<RigidBody2D>(), NAME_OF(rigidBody));
	spriteAnimator = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<SpriteAnimator>(), NAME_OF(spriteAnimator));
}

void PlayerController::Start()
{
	textureManager = GetGameObject()->CoreContext().textureManager;

	spriteCache =
	{
		textureManager->LoadTexture(idleSpriteSource),
		textureManager->LoadTexture(runSpriteSource),
	};

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

	auto tileRenderer = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<CustomTileMapRenderer2D>(), NAME_OF(tileRenderer));
	
	auto mapFullSize = tileRenderer->GetMapFullSize();

	auto tileRendererPos = tileRenderer->GetGameObject()->GetTransform()->GetWorldPosition();

	yThreshold = tileRendererPos.y + mapFullSize.y + 100.0f; // Add some gap

	auto boxCollider = Guard::AgainstNullAssignment(GetGameObject()->GetComponentInChildren<BoxCollider2D>(), NAME_OF(boxCollider));

	boxCollider->RegisterContactEnterHandler(GetHandle(), EventHelpers::BindFunction(this, &PlayerController::OnContactEnterHandler));
	boxCollider->RegisterContactExitHandler(GetHandle(), EventHelpers::BindFunction(this, &PlayerController::OnContactExitHandler));

	// Input Registration
	auto playerInput = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<PlayerInput>(), NAME_OF(playerInput));

	playerInput->RegisterAction("Default", "Move", GetHandle(), EventHelpers::BindFunction(this, &PlayerController::MoveInputHandler));
	playerInput->RegisterAction("Default", "Jump", GetHandle(), EventHelpers::BindFunction(this, &PlayerController::JumpInputHandler));
}

void PlayerController::Update(float deltaTime)
{
	if (transform->GetWorldPosition().y > yThreshold)
	{
		LoseLife();
	}
}

void PlayerController::LoseLife()
{
	auto* eventDispatcher = Guard::AgainstNullAssignment(GetGameObject()->ServiceContext().eventDispatcher, NAME_OF(eventDispatcher));

	eventDispatcher->SendEvent(std::make_shared<LifeLostEvent>());

	transform->SetWorldPosition(startPos);
}