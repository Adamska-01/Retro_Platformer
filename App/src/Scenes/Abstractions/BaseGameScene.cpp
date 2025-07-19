#pragma once
#include "Constants/CommonColors.h"
#include "Scenes/Abstractions/BaseGameScene.h"
#include <Blueprints/Audio/AudioClipBlueprint.h>
#include <Blueprints/UI/ButtonBlueprint.h>
#include <Components/UI/TextMesh.h>
#include <Coroutines/CoroutineScheduler.h>
#include <Models/Blueprints/UI/ButtonBlueprintModel.h>
#include <Models/Components/UI/ButtonComponentModel.h>
#include <Models/Components/UI/TextMeshComponentModel.h>


std::weak_ptr<ButtonBlueprint> BaseGameScene::CreateButton(const std::string& text, const std::string_view& fontSource, const std::function<void()>& onPressedHandler, const std::function<void()>& onEnterHandler)
{
	ButtonBlueprintModel buttonConfiguration =
	{
		ButtonComponentModel
		{
			.onPressedHandler = onPressedHandler,
			.onEnterHandler = onEnterHandler,
			.buttonSize = Vector2F{ 275.0f, 80.0f }
		},
		TextMeshComponentModel
		{
			.fontSource = fontSource,
			.text = text,
			.textColor = CommonColors::YELLOW,
			.fontSize = 100,
			.textObjectInitialScale = Vector2F(0.25f, 0.25f),
			.isCentered = true
		}
	};

	return GameObject::Instantiate<ButtonBlueprint>(buttonConfiguration);
}

std::weak_ptr<GameObject> BaseGameScene::CreateText(const std::string& text, const std::string_view& fontSource)
{
	auto textMeshObject = GameObject::Instantiate<GameObject>();

	textMeshObject.lock()->AddComponent<TextMesh>(TextMeshComponentModel
		{
			.fontSource = fontSource,
			.text = text,
			.textColor = SDL_Color(255, 132, 31),
			.fontSize = 100,
			.textObjectInitialScale = Vector2F(0.25f, 0.25f),
			.isCentered = false
		});

	return textMeshObject;
}

std::function<void()> BaseGameScene::MakeAudioPlayAndDestroyCallback(const std::string_view& audioPath, const Vector2F& position, float volume, bool isMusic, bool loop, float destroyDelaySeconds)
{
	return [=]()
		{
			auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
				audioPath,
				position,
				volume,
				isMusic,
				loop);

			CoroutineScheduler::StartCoroutine(soundSourceObj.lock()->Destroy(destroyDelaySeconds));
		};
}