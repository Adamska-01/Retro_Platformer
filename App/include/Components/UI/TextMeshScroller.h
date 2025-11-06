#pragma once
#include <Core/Coroutines/Task.h>
#include <Core/Math/Vector2.h>
#include <Engine/Components/GameComponent.h>
#include <Engine/EngineEvents/DispatchableEvent.h>
#include <Engine/Entity/ComponentHandle.h>


namespace DeadFrame2D::Engine
{
	class TextMesh;
}

class MenuManager;


class TextMeshScroller : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(TextMeshScroller, DeadFrame2D::Engine::GameComponent);


private:
	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> textMesh;

	DeadFrame2D::Engine::ComponentHandle<MenuManager> menuManager;

	DeadFrame2D::Core::Vector2I resolutionTarget;

	DeadFrame2D::Core::Task* activeTask;

	float scrollSpeed = 0.1f;


	void RenderTargetSizeChangedEventHandlers(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);


protected:
	void OnGameObjectActiveStateChangedHandler(const DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject>& obj, bool isActive) override;


public:
	TextMeshScroller(DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> textMesh, float scrollSpeed = 0.05f);

	virtual ~TextMeshScroller() override;


	virtual void Init() override;


	DeadFrame2D::Core::Task ScrollText();
};