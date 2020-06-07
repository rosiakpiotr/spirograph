#ifndef SPIROGRAPHSCENE_H
#define SPIROGRAPHSCENE_H

#include <TGUI/TGUI.hpp>
#include <SFML/Window/Event.hpp>
#include "scene.h"
#include "spirograph.h"

class SpirographScene : public Scene
{
public:
    SpirographScene(sf::RenderWindow& window, SceneManager& sceneMgr, std::vector<Arm> arms);

    virtual void handleInput(sf::Event& e);
    virtual void update(sf::Time& deltaTime);
    virtual void render();

private:

    virtual void build(Gui& gui);

    Spirograph mSpiro;
    float mTimeScale;
};

#endif // SPIROGRAPHSCENE_H
