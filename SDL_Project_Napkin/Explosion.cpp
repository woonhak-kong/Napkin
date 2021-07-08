#include "Explosion.h"

#include <iostream>

#include "CallbackType.h"
#include "Camera.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureID.h"
#include "TextureManager.h"

Explosion::Explosion(int x, int y, int width, int height, ExplosionType type) :
	m_type(type)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(width);
	setHeight(height);

	if(type == ExplosionType::EXPLOSION_SMALL)
	{
		setAnimation(TextureManager::Instance().getAnimation(TextureID::EXPLOSION2));
	}
	else
	{
		setAnimation(TextureManager::Instance().getAnimation(TextureID::EXPLOSION1));
	}
	SoundManager::Instance().playSound(SoundID::ENEMY_EXPLOSION);
}

void Explosion::draw()
{
	switch (m_type)
	{
		case ExplosionType::EXPLOSION_SMALL:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::EXPLOSION2), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 40.0f, 0.0f, 255, SDL_FLIP_NONE, false, [&](CallbackType type) -> void
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
		case ExplosionType::EXPLOSION_BIG:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::EXPLOSION1), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 40.0f, 0.0f, 255, SDL_FLIP_NONE, false, [&](CallbackType type) -> void
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

void Explosion::update()
{
}

void Explosion::clean()
{
}
