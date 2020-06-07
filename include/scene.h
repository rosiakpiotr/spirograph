#ifndef SCENE_H
#define SCENE_H

#include <TGUI/Gui.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

using namespace tgui;

struct SceneManager;

class Scene
{
public:

    virtual void handleInput(sf::Event& e) = 0;
    virtual void update(sf::Time& deltaTime) = 0;
    virtual void render() = 0;

    virtual ~Scene() {}

protected:

    // Override this method to create TGUI's user interface.
    virtual void build(Gui& gui) = 0;

    // Constructor is protected.
    Scene(sf::RenderWindow& window, SceneManager* sceneMgr);

    sf::RenderWindow* mWindow;
    Gui mUI;
    SceneManager* mSceneManager;
};

struct SceneManager
{
    SceneManager(std::shared_ptr<Scene> firstScene)
        : currentScene(firstScene)
    {
    }
    SceneManager()
    {
    }

    void setCurrentScene(std::shared_ptr<Scene> scene)
    {
        previousScene = currentScene;
        currentScene = scene;
    }

    auto getCurrentScene()
    {
        return currentScene;
    }

    auto getPreviousScene()
    {
        return previousScene;
    }

private:

    std::shared_ptr<Scene> currentScene;
    std::shared_ptr<Scene> previousScene;
};

#endif // SCENE_H
