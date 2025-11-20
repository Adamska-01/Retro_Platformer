#pragma once
#include "Data/Components/UI/Button/ButtonCallback.h"
#include <Core/Math/Vector2.h>
#include <Engine/Entity/Handles/GameObject/ObjectHandle.h>
#include <Engine/SceneSystem/Scene.h>
#include <functional>
#include <optional>
#include <string_view>



namespace DeadFrame2D::Engine
{
	class ButtonBlueprint;
	class GameObject;
}


class BaseGameScene : public DeadFrame2D::Engine::Scene
{
protected:
	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::ButtonBlueprint> CreateButton(
		const std::string& text, 
		const std::string_view& fontSource, 
		const std::optional<DeadFrame2D::Data::ButtonCallback>& onPressedHandler = std::nullopt, 
		const std::optional<DeadFrame2D::Data::ButtonCallback>& onEnterHandler = std::nullopt);

	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject> CreateText(const std::string& text, const std::string_view& fontSource);
};