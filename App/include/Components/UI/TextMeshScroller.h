#pragma once
#include <Core/Context/Systems/Coroutines/Task.h>
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <Engine/ECS/System/Events/DispatchableEvent.h>


namespace DF2D::Engine
{
	class TextMesh;
}

class MenuManager;


class TextMeshScroller : public DF2D::Engine::GameComponent
{
	TYPE_INFO(TextMeshScroller, DF2D::Engine::GameComponent);


private:
	DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> textMesh;

	DF2D::Engine::ComponentHandle<MenuManager> menuManager;

	DF2D::Core::Vector2I resolutionTarget;

	DF2D::Core::Task* activeTask;

	float scrollSpeed = 0.1f;


	void RenderTargetSizeChangedEventHandlers(std::shared_ptr<DF2D::Engine::DispatchableEvent> dispatchableEvent);


protected:
	void OnGameObjectActiveStateChangedHandler(const DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject>& obj, bool isActive) override;


public:
	TextMeshScroller(DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> textMesh, float scrollSpeed = 0.05f);

	virtual ~TextMeshScroller() override;


	virtual void Init() override;


	DF2D::Core::Task ScrollText();
};