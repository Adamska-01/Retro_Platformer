#include "Components/Audio/DestroyOnAudioFinished.h"
#include "Components/UI/MenuFunctions.h"
#include "Components/UI/MenuManager.h"
#include "Scenes/MainGameScene.h"
#include "Scenes/MainMenuScene.h"
#include <Constants/AssetPaths.h>
#include <Core/Services/Events/EventManager.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/System/Scene/SceneManager.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;


void MenuFunctions::MakeAudioPlayAndDestroyCallback(const std::string_view& audioPath, const Vector2F& position, float volume, bool isMusic, bool loop)
{
	auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
		audioPath,
		position,
		volume,
		isMusic,
		loop);

	// A looping clip is caller-managed; a one-shot self-destroys once it finishes
	if (!loop)
	{
		soundSourceObj->AddComponent<DestroyOnAudioFinished>();
	}
}

ButtonCallback MenuFunctions::LoadMenu()
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false);

			SceneManager::LoadScene<MainMenuScene>();
		}
	};
}

ButtonCallback MenuFunctions::LoadGame()
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false);

			SceneManager::LoadScene<MainGameScene>();
		}
	};
}

ButtonCallback MenuFunctions::ShowCredits(const ComponentHandle<MenuManager>& menuManager)
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this, menuManager]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false);

			menuManager->HideAll();

			menuManager->ShowMenu(MenuID::CREDITS_MENU);
		}
	};
}

ButtonCallback MenuFunctions::ExitGame()
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false);

			GetGameObject()->ServiceContext().eventManager->RequestQuit();
		}
	};
}

ButtonCallback MenuFunctions::SelectUI()
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::SELECT_UI, Vector2F::Zero, 0.5f, false, false);
		}
	};
}