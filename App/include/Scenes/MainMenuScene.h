#pragma once
#include "Scenes/Abstractions/BaseGameScene.h"



class ButtonBlueprint;


class MainMenuScene : public BaseGameScene
{
public:
	MainMenuScene() = default;

	virtual ~MainMenuScene() override = default;


	virtual void Enter() override;
};