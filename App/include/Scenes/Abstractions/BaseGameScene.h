#pragma once
#include "Data/Components/UI/Button/ButtonCallback.h"
#include <Engine/ECS/Entity/Object/Handle/ObjectHandle.h>
#include <Engine/ECS/System/Scene/Scene.h>
#include <optional>
#include <string>
#include <string_view>



namespace DF2D::Engine
{
	class ButtonBlueprint;
	class GameObject;
}


class BaseGameScene : public DF2D::Engine::Scene
{
protected:
	DF2D::Engine::ObjectHandle<DF2D::Engine::ButtonBlueprint> CreateButton(
		const std::string& text, 
		const std::string_view& fontSource, 
		const std::optional<DF2D::Data::ButtonCallback>& onPressedHandler = std::nullopt,
		const std::optional<DF2D::Data::ButtonCallback>& onEnterHandler = std::nullopt);

	DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> CreateText(const std::string& text, const std::string_view& fontSource);
};