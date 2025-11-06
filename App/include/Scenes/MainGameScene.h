#pragma once
#include "Scenes/Abstractions/BaseGameScene.h"
#include <Engine/Entity/GameObject.h>
#include <memory>


class MainGameScene : public BaseGameScene
{
private:
	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject> CreateText(const std::string& text);

	DeadFrame2D::Engine::ComponentHandle<MenuBase> CreateEndScreen(std::string menuTitle, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	DeadFrame2D::Engine::ComponentHandle<MenuBase> CreateHUD();


public:
	MainGameScene() = default;

	virtual ~MainGameScene() override = default;


	virtual void Enter() override;
};