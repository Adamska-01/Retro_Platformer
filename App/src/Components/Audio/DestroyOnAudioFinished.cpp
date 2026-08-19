#include "Components/Audio/DestroyOnAudioFinished.h"
#include <Engine/ECS/Component/Audio/AudioSource.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Utilities/Debugging/Guards.h>


using namespace DF2D::Engine;
using namespace DF2D::Utilities;


DestroyOnAudioFinished::DestroyOnAudioFinished()
{
}

DestroyOnAudioFinished::~DestroyOnAudioFinished()
{
}

void DestroyOnAudioFinished::Init()
{
	audioSource = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<AudioSource>(), NAME_OF(audioSource));
}

void DestroyOnAudioFinished::Update(float deltaTime)
{
	if (audioSource->IsPlaying())
		return;

	GetGameObject()->Destroy();
}