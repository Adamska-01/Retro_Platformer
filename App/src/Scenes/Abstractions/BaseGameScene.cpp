#pragma once
#include "Constants/CommonColors.h"
#include "Scenes/Abstractions/BaseGameScene.h"
#include <Core/Context/Systems/Coroutines/CoroutineScheduler.h>
#include <Data/Blueprints/UI/Button/ButtonBlueprintModel.h>
#include <Data/Blueprints/UI/Button/ButtonComponentModel.h>
#include <Data/Blueprints/UI/Text/TextMeshComponentModel.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Blueprints/UI/ButtonBlueprint.h>
#include <Engine/ECS/Component/UI/TextMesh.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>


using namespace DF2D::Constants;
using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;


ObjectHandle<ButtonBlueprint> BaseGameScene::CreateButton(const std::string& text, const std::string_view& fontSource, const std::optional<ButtonCallback>& onPressedHandler, const std::optional<ButtonCallback>& onEnterHandler)
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

ObjectHandle<GameObject> BaseGameScene::CreateText(const std::string& text, const std::string_view& fontSource)
{
	auto textMeshObject = GameObject::Instantiate<GameObject>();

	textMeshObject->AddComponent<TextMesh>(TextMeshComponentModel
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