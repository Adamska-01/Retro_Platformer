#pragma once
#include "Scenes/Abstractions/BaseGameScene.h"
#include <Engine/Entity/GameObject.h>
#include <memory>


class ButtonBlueprint;


class MainGameScene : public BaseGameScene
{
private:
	std::weak_ptr<GameObject> CreateText(const std::string& text);

	MenuBase* CreateEndScreen(std::string menuTitle, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	MenuBase* CreateHUD();


public:
	MainGameScene() = default;

	virtual ~MainGameScene() override = default;


	virtual void Enter() override;
};