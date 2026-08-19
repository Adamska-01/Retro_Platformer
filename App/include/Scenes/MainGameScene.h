#pragma once
#include "Scenes/Abstractions/BaseGameScene.h"
#include <Engine/ECS/Entity/Object/Core/GameObject.h>


class MenuBase;


class MainGameScene : public BaseGameScene
{
private:
	DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> CreateText(const std::string& text);

	DF2D::Engine::ComponentHandle<MenuBase> CreateEndScreen(std::string menuTitle, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	DF2D::Engine::ComponentHandle<MenuBase> CreateHUD();


public:
	MainGameScene() = default;

	virtual ~MainGameScene() override = default;


	virtual void Enter() override;
};