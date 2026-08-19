#include "Components/UI/TextMeshScroller.h"
#include "Engine/Events/Context/Renderer/RenderTargetSizeChangedEvent.h"
#include <Components/UI/MenuManager.h>
#include <Core/Context/Systems/Coroutines/CoroutineScheduler.h>
#include <Core/Context/Systems/Rendering/Renderer.h>
#include <Core/Services/Time/Abstractions/ITimeProvider.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Component/UI/TextMesh.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Coroutines/CoroutineHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


TextMeshScroller::TextMeshScroller(ComponentHandle<TextMesh> textMesh, float scrollSpeed)
	: textMesh(textMesh),
	activeTask(nullptr),
	scrollSpeed(scrollSpeed)
{
	Guard::AgainstNull(textMesh, NAME_OF(textMesh));
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

void TextMeshScroller::OnGameObjectActiveStateChangedHandler(const ObjectHandle<GameObject>& obj, bool isActive)
{
	if (activeTask != nullptr && !activeTask->IsDone() && !activeTask->IsCancelled())
	{
		activeTask->Cancel();

		activeTask = nullptr;
	}

	if (isActive)
	{
		activeTask = &GetGameObject()->CoreContext().coroutineScheduler->StartCoroutine(ScrollText());
	}
}

void TextMeshScroller::Init()
{
	menuManager = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<MenuManager>(), NAME_OF(menuManager));

	auto renderer = GetGameObject()->CoreContext().renderer;

	if (renderer != nullptr)
	{
		resolutionTarget = renderer->GetResolutionTarget();
	}
}

Task TextMeshScroller::ScrollText()
{
	if (textMesh == nullptr)
		co_return;

	auto startPos = Vector2F(resolutionTarget.x * 0.5f, resolutionTarget.y);
	auto endPos = Vector2F(resolutionTarget.x * 0.5f, -textMesh->GetWidgetSize().y) ;
	auto textMeshTransform = textMesh->GetGameObject()->GetTransform();

	textMeshTransform->SetWorldPosition(startPos);
	textMesh->SetAnchor(UIAnchor::TOP_CENTER);

	auto t = 0.0f;
	while (t < 1.0f)
	{
		t += GetGameObject()->ServiceContext().frameTimer->DeltaTime() * scrollSpeed;

		auto newPos = Vector2F::Lerp(startPos, endPos, t);

		textMeshTransform->SetWorldPosition(newPos);

		co_await CoroutineHelpers::WaitFrame();
	}

	menuManager->HideAll();
	menuManager->ShowMenu(MenuID::MAIN_MENU);
}