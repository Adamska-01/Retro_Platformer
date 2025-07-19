#include "Components/UI/TextMeshScroller.h"
#include <Components/Transform.h>
#include <Components/UI/MenuManager.h>
#include <Components/UI/TextMesh.h>
#include <EventSystem/Events/SubSystems/Renderer/RenderTargetSizeChangedEvent.h>
#include <GameObject.h>
#include <Management/SceneManager.h>
#include <SubSystems/Renderer.h>
#include <Tools/FrameTimer.h>
#include <Tools/Helpers/Coroutines/CoroutineHelpers.h>
#include <Tools/Helpers/Guards.h>


TextMeshScroller::TextMeshScroller(TextMesh* textMesh, float scrollSpeed)
	: textMesh(textMesh),
	menuManager(nullptr),
	activeTask(nullptr),
	scrollSpeed(scrollSpeed)
{
	Tools::Helpers::GuardAgainstNull(textMesh, "TextMesh is nullptr in TextMeshScroller");

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

	Tools::Helpers::GuardAgainstNull(menuManager, "Failed to get menuManager from TextMeshScroller");
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

		co_await Tools::Helpers::Coroutines::WaitFrame();
	}

	menuManager->HideAll();
	menuManager->ShowMenu(MenuID::MAIN_MENU);
}