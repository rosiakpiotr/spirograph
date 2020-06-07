#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "scene.h"
#include "spirographscene.h"

using namespace tgui;

class SettingsScene : public Scene
{
public:
    SettingsScene(sf::RenderWindow& window, SceneManager& sceneMgr);

    virtual void handleInput(sf::Event& e);
    virtual void update(sf::Time& deltaTime);
    virtual void render();

    virtual ~SettingsScene() {}

private:

    virtual void build(Gui& gui);

    // Builds UI for adding new arm.
    void newArmPrompt();

    // Builds UI for removing any arm.
    void removeArmPrompt();

    // Method that returns arms parsed from UI's tables.
    std::vector<Arm> mArms;

    void updateListBoxes();
};

#endif // SETTINGSSCENE_H
