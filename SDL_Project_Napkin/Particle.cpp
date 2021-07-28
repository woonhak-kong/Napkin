#include "Particle.h"

#include "Camera.h"
#include "TextureID.h"
#include "TextureManager.h"
#include "Scene.h"

Particle::Particle(int x, int y, int width, int height, ParticleType type) :
	m_type(type)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(width);
	setHeight(height);

	switch (m_type)
	{
		case ParticleType::TRINKLE:
			setAnimation(TextureManager::Instance().getAnimation(TextureID::TRINKLE));
			break;

		case ParticleType::HIT:
			setAnimation(TextureManager::Instance().getAnimation(TextureID::HIT_PARTICLE));
			break;
	}
}

Particle::~Particle()
{
}

void Particle::draw()
{
	switch (m_type)
	{
		case ParticleType::TRINKLE:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::TRINKLE), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getWidth(), 0.5f, 0.0f, 255, SDL_FLIP_NONE, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}

				});
			break;
		case ParticleType::HIT:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::HIT_PARTICLE), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getWidth(), 0.5f, 0.0f, 255, SDL_FLIP_NONE, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}

				});
			break;
		default:
			break;
	}
}

void Particle::update()
{
}

void Particle::clean()
{
}
