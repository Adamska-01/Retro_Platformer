#include "Components/UI/TextMeshScroller.h"
#include <Components/UI/MenuManager.h>
#include <Core/Framerate/FrameTimer.h>
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <Core/SubSystems/Systems/Renderer.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/UI/TextMesh.h>
#include <Engine/EngineEvents/Events/SubSystems/Renderer/RenderTargetSizeChangedEvent.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Coroutines/CoroutineHelpers.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


TextMeshScroller::TextMeshScroller(TextMesh* textMesh, float scrollSpeed)
	: textMesh(textMesh),
	menuManager(nullptr),
	activeTask(nullptr),
	scrollSpeed(scrollSpeed)
{
	Guard::AgainstNull(textMesh, NAME_OF(textMesh));

	resolutionTarget = Renderer::GetResolutionTarget();
}

TextMeshScroller::~TextMeshScroller()
{
}

void TextMeshScroller::RenderTargetSizeChangedEventHandlers(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	auto renderTargetSizeChangeEvent = DispatchableEvent::SafeCast<RenderTargetSizeChangedEvent>(dispatchableEvent);

	if (renderTargetSizeChangeEvent == nullptr)
		return;

	resolutionTarget = renderTargetSizeChangeEvent->renderTargetSize;
}

void TextMeshScroller::OnGameObjectActiveStateChangedHandler(GameObject* obj, bool isActive)
{
	if (activeTask != nullptr && !activeTask->IsDone() && !activeTask->IsCancelled())
	{
		activeTask->Cancel();

		activeTask = nullptr;
	}

	if (isActive)
	{
		activeTask = &CoroutineScheduler::StartCoroutine(ScrollText());
	}
}

void TextMeshScroller::Init()
{
	menuManager = SceneManager::FindObjectOfType<MenuManager>();

	Guard::AgainstNull(menuManager, NAME_OF(menuManager));
}

void TextMeshScroller::Start()
{

}

void TextMeshScroller::Update(float deltaTime)
{

}

void TextMeshScroller::Draw()
{

}

Task TextMeshScroller::ScrollText()
{
	if (textMesh == nullptr)
		co_return;

	auto startPos = Vector2F(resolutionTarget.x * 0.5f, resolutionTarget.y);
	auto endPos = Vector2F(resolutionTarget.x * 0.5f, -textMesh->GetWidgetSize().y) ;
	auto textMeshTransform = textMesh->GetGameObject().lock()->GetTransform();

	textMeshTransform->SetWorldPosition(startPos);
	textMesh->SetAnchor(UIAnchor::TOP_CENTER);

	auto t = 0.0f;
	while (t < 1.0f)
	{
		t += FrameTimer::DeltaTime() * scrollSpeed;

		auto newPos = Vector2F::Lerp(startPos, endPos, t);

		textMeshTransform->SetWorldPosition(newPos);

		co_await WaitFrame();
	}

	menuManager->HideAll();
	menuManager->ShowMenu(MenuID::MAIN_MENU);
}