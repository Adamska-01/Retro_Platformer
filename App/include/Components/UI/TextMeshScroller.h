#pragma once
#include <Core/Coroutines/Task.h>
#include <Core/Math/Vector2.h>
#include <Engine/Components/GameComponent.h>
#include <Engine/EngineEvents/DispatchableEvent.h>


namespace DeadFrame2D::Engine
{
	class TextMesh;
}

class MenuManager;


class TextMeshScroller : public DeadFrame2D::Engine::GameComponent
{
private:
	DeadFrame2D::Engine::TextMesh* textMesh;

	MenuManager* menuManager;

	DeadFrame2D::Core::Vector2I resolutionTarget;

	DeadFrame2D::Core::Task* activeTask;

	float scrollSpeed = 0.1f;


	void RenderTargetSizeChangedEventHandlers(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);


protected:
	void OnGameObjectActiveStateChangedHandler(DeadFrame2D::Engine::GameObject* obj, bool isActive) override;


public:
	TextMeshScroller(DeadFrame2D::Engine::TextMesh* textMesh, float scrollSpeed = 0.05f);

	virtual ~TextMeshScroller() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	DeadFrame2D::Core::Task ScrollText();
};