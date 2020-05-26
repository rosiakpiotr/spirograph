#ifndef SPIROGRAPHSCENE_H
#define SPIROGRAPHSCENE_H

#include <TGUI/TGUI.hpp>
#include <SFML/Window/Event.hpp>
#include "scene.h"
#include "spirograph.h"

class SpirographScene : public Scene
{
public:
    SpirographScene(RenderWindow& window, SceneManager& sceneMgr, std::vector<Arm> arms);

    virtual void handleInput(Event& e);
    virtual void update(Time& deltaTime);
    virtual void render();

private:

    virtual void build(Gui& gui);

    Spirograph mSpiro;
    float mTimeScale;
};

#endif // SPIROGRAPHSCENE_H
