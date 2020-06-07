#include "spirographscene.h"

SpirographScene::SpirographScene(sf::RenderWindow& window, SceneManager& sceneMgr,
                                 std::vector<Arm> arms)
    : Scene(window, &sceneMgr), mSpiro(sf::Vector2f(1280 / 2.f, 720 / 2.f), arms), mTimeScale(1)
{
    build(mUI);
}

void SpirographScene::build(Gui& gui)
{
    Button::Ptr settingsTrigger = Button::create("Ustawienia");
    settingsTrigger->setPosition(25, 30);
    mUI.add(settingsTrigger);

    Button::Ptr startStopTrigger = Button::create("Start/stop");
    startStopTrigger->setPosition(25, 100);
    mUI.add(startStopTrigger);

    Button::Ptr showHideTrigger = Button::create(L"Pokaż/schowaj");
    showHideTrigger->setPosition(25, 170);
    mUI.add(showHideTrigger);

    settingsTrigger->connect("pressed", [this]{
        mSceneManager->setCurrentScene(mSceneManager->getPreviousScene());
    });

    startStopTrigger->connect("pressed", [this]{
        mSpiro.setRunning(!mSpiro.getRunning());
    });

    showHideTrigger->connect("pressed", [this]{
        mSpiro.setVisible(!mSpiro.getVisibility());
    });
}

void SpirographScene::handleInput(sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        float delta = 5;

        if (e.key.code == sf::Keyboard::Up)
        {
            if (mTimeScale + delta < 128)
            {
                mTimeScale += delta;
            }
        }
        else if (e.key.code == sf::Keyboard::Down)
        {
            if (mTimeScale - delta > 0)
            {
                mTimeScale -= delta;
            }
        }
    }

    mUI.handleEvent(e);
}

void SpirographScene::render()
{
    mWindow->draw(mSpiro);
    mUI.draw();
}

void SpirographScene::update(sf::Time& deltaTime)
{
    deltaTime *= mTimeScale;
    mSpiro.tick(deltaTime);
}
