#pragma once
#include <functional>
#include <Management/Scene.h>
#include <memory>
#include <string>


class ButtonBlueprint;


class ExampleScene : public Scene
{
private:
	std::weak_ptr<ButtonBlueprint> CreateButton(const std::string& text, const std::function<void()>& onPressedHandler, const std::function<void()>& onEnterHandler);

	std::weak_ptr<GameObject> CreateText(const std::string& text);


public:
	ExampleScene() = default;

	virtual ~ExampleScene() override = default;


	virtual void Enter() override;
};