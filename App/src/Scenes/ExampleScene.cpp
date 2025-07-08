#include "Blueprints/ExampleBlueprint.h"
#include "Scenes/ExampleScene.h"
#include <Blueprints/UI/ButtonBlueprint.h>
#include <Components/Rendering/ImageScroller.h>
#include <Components/Transform.h>
#include <Components/UI/Button.h>
#include <Components/UI/Canvas.h>
#include <Components/UI/Layout/VerticalLayoutGroup.h>
#include <Components/UI/TextMesh.h>
#include <Constants/CommonColors.h>
#include <Management/SceneManager.h>
#include <Math/Vector2.h>
#include <SubSystems/Events/EventManager.h>
#include <SubSystems/Renderer.h>


std::weak_ptr<ButtonBlueprint> ExampleScene::CreateButton(const std::string& text, const std::function<void()>& onPressedHandler, const std::function<void()>& onEnterHandler)
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
			.text = text,
			.textColor = CommonColors::YELLOW,
			.fontSize = 100,
			.textObjectInitialScale = Vector2F(0.35f, 0.25f),
			.isCentered = true
		}
	};

	return GameObject::Instantiate<ButtonBlueprint>(buttonConfiguration);
}

std::weak_ptr<GameObject> ExampleScene::CreateText(const std::string& text)
{
	auto textMeshObject = GameObject::Instantiate<GameObject>();

	textMeshObject.lock()->AddComponent<TextMesh>(TextMeshComponentModel
		{
			.text = text,
			.textColor = CommonColors::ORANGE,
			.fontSize = 100,
			.textObjectInitialScale = Vector2F(0.4f, 0.4f),
			.isCentered = true
		});

	return textMeshObject;
}

void ExampleScene::Enter()
{
	auto renderTargetSize = Renderer::GetResolutionTarget();

	// Canvas
	auto canvasObject = GameObject::Instantiate<GameObject>();
	canvasObject.lock()->AddComponent<Canvas>();

	// Text
	auto title = CreateText("Example Scene");
	title.lock()->GetTransform()->SetWorldPosition({ renderTargetSize.x * 0.5f, renderTargetSize.y * 0.1f });
	
	auto layoutTitle = CreateText("UI Example\n ");

	auto gameObjectTitle = CreateText("GameObject Example\n ");
	gameObjectTitle.lock()->GetTransform()->SetWorldPosition({ renderTargetSize.x * 0.7f, renderTargetSize.y * 0.4f });

	// Buttons
	auto continueButton = CreateButton("Click Me!", []() {}, []() {});
	auto quitButton = CreateButton("Quit", []() { EventManager::SendSystemEvent(SDL_EventType::SDL_QUIT); }, []() {});

	// Navigation
	continueButton.lock()->GetComponent<Button>()->SetNavigableDownElement(quitButton.lock()->GetComponent<Button>());
	quitButton.lock()->GetComponent<Button>()->SetNavigableUpElement(continueButton.lock()->GetComponent<Button>());

	// Layout
	auto layout = GameObject::Instantiate<GameObject>();
	layout.lock()->AddComponent<VerticalLayoutGroup>(20.0f, LayoutPadding());
	layout.lock()->GetComponent<Transform>()->SetWorldPosition({ renderTargetSize.x * 0.3f, renderTargetSize.y * 0.5f });

	layout.lock()->AddChildGameObject(layoutTitle);
	layout.lock()->AddChildGameObject(continueButton);
	layout.lock()->AddChildGameObject(quitButton);

	canvasObject.lock()->AddChildGameObject(layout);


	// Blueprint
	auto blueprintExample = GameObject::Instantiate<ExampleBlueprint>(Vector2F(renderTargetSize.x * 0.7f, renderTargetSize.y * 0.55f));
}
