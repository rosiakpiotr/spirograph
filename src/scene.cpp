#include "scene.h"

Scene::Scene(RenderWindow& window, SceneManager* sceneManager)
    : mWindow(&window), mUI(window), mSceneManager(sceneManager)
{
}
