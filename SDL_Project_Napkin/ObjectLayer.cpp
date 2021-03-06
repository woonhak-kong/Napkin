#include "ObjectLayer.h"

void ObjectLayer::draw()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

void ObjectLayer::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

std::vector<GameObject*>* ObjectLayer::getGameObjects()
{
	return &m_gameObjects;
}
