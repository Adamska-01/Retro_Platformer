#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/SceneSystem/Scene.h>
#include <functional>
#include <memory>
#include <string_view>


class ButtonBlueprint;
class GameObject;


class BaseGameScene : public Scene
{
protected:
	std::weak_ptr<ButtonBlueprint> CreateButton(const std::string& text, const std::string_view& fontSource, const std::function<void()>& onPressedHandler, const std::function<void()>& onEnterHandler);

	std::weak_ptr<GameObject> CreateText(const std::string& text, const std::string_view& fontSource);

	std::function<void()> MakeAudioPlayAndDestroyCallback(
		const std::string_view& audioPath,
		const Vector2F& position,
		float volume,
		bool isMusic,
		bool loop,
		float destroyDelaySeconds);
};