#pragma once
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>


namespace DF2D::Engine
{
	class AudioSource;
}


class DestroyOnAudioFinished : public DF2D::Engine::GameComponent
{
	TYPE_INFO(DestroyOnAudioFinished, DF2D::Engine::GameComponent);


private:
	DF2D::Engine::ComponentHandle<DF2D::Engine::AudioSource> audioSource;


public:
	DestroyOnAudioFinished();

	virtual ~DestroyOnAudioFinished() override;


	virtual void Init() override;

	virtual void Update(float deltaTime) override;
};