#pragma once
#include <Components/GameComponent.h>
#include <Coroutines/Task.h>
#include <EventSystem/DispatchableEvent.h>
#include <Math/Vector2.h>


class TextMesh;
class MenuManager;


class TextMeshScroller : public GameComponent
{
private:
	TextMesh* textMesh;

	MenuManager* menuManager;

	Vector2I resolutionTarget;

	Task* activeTask;

	float scrollSpeed = 0.1f;


	void RenderTargetSizeChangedEventHandlers(std::shared_ptr<DispatchableEvent> dispatchableEvent);


protected:
	void OnGameObjectActiveStateChangedHandler(GameObject* obj, bool isActive) override;


public:
	TextMeshScroller(TextMesh* textMesh, float scrollSpeed = 0.05f);

	virtual ~TextMeshScroller() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	Task ScrollText();
};