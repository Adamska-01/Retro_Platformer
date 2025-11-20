#include "Components/UI/MenuFunctions.h"
#include "Components/UI/MenuManager.h"
#include "Scenes/MainGameScene.h"
#include "Scenes/MainMenuScene.h"
#include <Constants/AssetPaths.h>
#include <Core/CoreEvents/EventManager.h>
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;


void MenuFunctions::MakeAudioPlayAndDestroyCallback(const std::string_view& audioPath, const Vector2F& position, float volume, bool isMusic, bool loop, float destroyDelaySeconds)
{
	auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
		audioPath,
		position,
		volume,
		isMusic,
		loop);

	CoroutineScheduler::StartCoroutine(soundSourceObj->Destroy(destroyDelaySeconds));
}

DeadFrame2D::Data::ButtonCallback MenuFunctions::LoadMenu()
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);

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
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);

			SceneManager::LoadScene<MainGameScene>();
		}
	};
}

DeadFrame2D::Data::ButtonCallback MenuFunctions::ShowCredits(const ComponentHandle<MenuManager>& menuManager)
{
	return ButtonCallback
	{
		.handle = GetHandle(),
		.callback = [this, menuManager]()
		{
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);

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
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);

			EventManager::SendSystemEvent(SDL_EventType::SDL_QUIT);
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
			MakeAudioPlayAndDestroyCallback(AssetPaths::Files::SELECT_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);
		}
	};
}