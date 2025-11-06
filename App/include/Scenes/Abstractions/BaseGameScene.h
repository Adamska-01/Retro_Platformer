#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/Handles/GameObject/ObjectHandle.h>
#include <Engine/SceneSystem/Scene.h>
#include <functional>
#include <string_view>


namespace DeadFrame2D::Engine
{
	class ButtonBlueprint;
	class GameObject;
}


class BaseGameScene : public DeadFrame2D::Engine::Scene
{
protected:
	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::ButtonBlueprint> CreateButton(const std::string& text, const std::string_view& fontSource, const std::function<void()>& onPressedHandler, const std::function<void()>& onEnterHandler);

	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject> CreateText(const std::string& text, const std::string_view& fontSource);

	std::function<void()> MakeAudioPlayAndDestroyCallback(
		const std::string_view& audioPath,
		const DeadFrame2D::Core::Vector2F& position,
		float volume,
		bool isMusic,
		bool loop,
		float destroyDelaySeconds);
};