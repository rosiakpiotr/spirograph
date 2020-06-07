#include "scene.h"

Scene::Scene(sf::RenderWindow& window, SceneManager* sceneManager)
    : mWindow(&window), mUI(window), mSceneManager(sceneManager)
{
}
