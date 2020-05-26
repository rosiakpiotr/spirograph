#include <TGUI/TGUI.hpp>
#include <memory>
#include "spirograph.h"
#include "settingsscene.h"

using namespace sf;
using namespace tgui;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Spirograph!"); 
    window.setFramerateLimit(60);

    SceneManager sceneManager;
    sceneManager.setCurrentScene(std::make_shared<SettingsScene>(window, sceneManager));

    Clock clock;
    while (window.isOpen())
    {
        auto currentScene = sceneManager.getCurrentScene();

        Event e;

        // Delta from frame to frame render time.
        Time elapsed = clock.restart();

        while (window.pollEvent(e))
        {
            // This gets triggered when user presses close button on window.
            if (e.type == Event::Closed)
            {
                window.close();
            }

            // Pass occurred event to current scene.
            currentScene->handleInput(e);
        }

        // Update logic of current scene.
        currentScene->update(elapsed);

        window.clear();
        currentScene->render();
        window.display();
    }

    return 0;
}
