#include "settingsscene.h"

SettingsScene::SettingsScene(RenderWindow& window, SceneManager& sceneMgr)
    : Scene(window, &sceneMgr)
{
    build(mUI);
}

void SettingsScene::build(Gui& gui)
{
    Button::Ptr cornerButton = Button::create("Start");
    cornerButton->setPosition(1100, 30);
    gui.add(cornerButton);

    Button::Ptr newArmTrigger = Button::create(L"Dodaj ramię");
    newArmTrigger->setPosition(1100, 90);
    gui.add(newArmTrigger);

    Button::Ptr removeArmTrigger = Button::create(L"Usuń ramię");
    removeArmTrigger->setPosition(1100, 150);
    gui.add(removeArmTrigger);

    Label::Ptr tabLeftTop = Label::create("Ramie");
    tabLeftTop->setPosition(100, 150);
    tabLeftTop->setTextColor(sf::Color::White);
    gui.add(tabLeftTop);

    Label::Ptr tabMidTop = Label::create(L"Długość");
    tabMidTop->setPosition(385, 150);
    tabMidTop->setTextColor(sf::Color::White);
    gui.add(tabMidTop);

    Label::Ptr tabRightTop = Label::create(L"Prędkość obrotowa(rad/s)");
    tabRightTop->setPosition(670, 150);
    tabRightTop->setTextColor(sf::Color::White);
    gui.add(tabRightTop);

    HorizontalLayout::Ptr panel = HorizontalLayout::create();
    panel->setPosition(100, 175);
    panel->setSize(850, 500);
    panel->setRatio(0, 0.5);
    panel->setRatio(1, 2);
    panel->setRatio(2, 2);
    gui.add(panel);

    // ListBox with numbers of arms.
    ListBox::Ptr listLeft = ListBox::create();
    listLeft->setSize(20, listLeft->getSize().y);
    panel->add(listLeft, "listLeft");

    // ListBox displaying lengths of arms.
    ListBox::Ptr listMid = ListBox::create();
    panel->add(listMid, "listMid");

    // ListBox displaying angular speeds of arms.
    ListBox::Ptr listRight = ListBox::create();
    panel->add(listRight, "listRight");

    /* Setting actions on user events */

    // Set action on corner button press.
    cornerButton->connect("pressed", [this]
    {
        mSceneManager->setCurrentScene(std::make_shared<SpirographScene>(*mWindow, *mSceneManager, mArms));
    });

    newArmTrigger->connect("pressed", &SettingsScene::newArmPrompt, this);
    removeArmTrigger->connect("pressed", &SettingsScene::removeArmPrompt, this);
}

void SettingsScene::newArmPrompt()
{
    ChildWindow::Ptr childWindow = mUI.get<ChildWindow>("childWindow");

    // Proceed only if there is no child window added.
    if (childWindow == nullptr)
    {
        childWindow = ChildWindow::create();
        childWindow->setSize(600, 400);
        childWindow->setPosition(360, 160);

        Label::Ptr lenLabel = Label::create(L"Długość"); // 70 width
        lenLabel->setPosition(300 - 1.63 * lenLabel->getSize().x, 55);
        lenLabel->setTextColor(sf::Color::Black);
        childWindow->add(lenLabel);

        EditBox::Ptr lenEdit = EditBox::create();
        lenEdit->setSize(110, 30);
        lenEdit->setPosition(bindLeft(lenLabel) - 0.2 * 110, 90);
        lenEdit->setInputValidator(EditBox::Validator::UInt);
        childWindow->add(lenEdit, "lenEdit");

        Label::Ptr angSpeedLabel = Label::create(L"Prędkość obrotowa(rad/s)"); // 230 width
        angSpeedLabel->setPosition(300 + 0.30 * angSpeedLabel->getSize().x, 55);
        angSpeedLabel->setTextColor(sf::Color::Black);
        childWindow->add(angSpeedLabel);

        EditBox::Ptr angSpeedEdit = EditBox::create();
        angSpeedEdit->setSize(110, 30);
        angSpeedEdit->setPosition(bindLeft(angSpeedLabel) + 0.5 * 110, 90);
        angSpeedEdit->setInputValidator(EditBox::Validator::Float);
        childWindow->add(angSpeedEdit, "angSpeedEdit");

        // Let user choose index if there are any existing arms.
        if (!mArms.empty())
        {
            Label::Ptr indexLabel = Label::create(L"Kolejność"); // 100 width
            indexLabel->setPosition(250, 195);
            indexLabel->setTextColor(sf::Color::Black);
            childWindow->add(indexLabel);

            ListBox::Ptr indexList = ListBox::create();
            indexList->setSize(75, 100);
            indexList->setPosition(255, 230);
            for (size_t i = 0; i < mArms.size() + 1; i++)
            {
                indexList->addItem(to_string(i + 1));
            }
            indexList->setSelectedItemByIndex(mArms.size());
            childWindow->add(indexList, "listIndex");
        }

        Button::Ptr cancelTrig = Button::create("Anuluj");
        cancelTrig->setSize(135, 30);
        cancelTrig->setPosition(300 - 1.5 * cancelTrig->getSize().x, 340);
        cancelTrig->setTextSize(16);
        childWindow->add(cancelTrig);

        Button::Ptr applyTrig = Button::create(L"Zatwierdź");
        applyTrig->setSize(135, 30);
        applyTrig->setPosition(300 + 0.5 * applyTrig->getSize().x, 340);
        applyTrig->setTextSize(16);
        childWindow->add(applyTrig);

        mUI.add(childWindow, "childWindow");

        // Setting actions on button events.
        cancelTrig->connect("pressed", &Gui::remove, &mUI, childWindow); // [&]{ mUI.remove(childWindow); });
        applyTrig->connect("pressed", [this, childWindow]
        {

            auto list = mUI.get<ListBox>("listIndex", true);
            auto lenEdit = mUI.get<EditBox>("lenEdit", true);
            auto angSpeedEdit = mUI.get<EditBox>("angSpeedEdit", true);
            int moveBy = 0;

            if (list != nullptr)
            {
                moveBy = list->getSelectedItemIndex();
            }

            std::string lenStr = lenEdit->getText().toAnsiString();
            std::string angSpeedStr = angSpeedEdit->getText().toAnsiString();

            if (!lenStr.empty() && !angSpeedStr.empty())
            {
                int length = std::stoi(lenStr);
                float angularSpeed = std::stof(angSpeedStr);

                mArms.insert(mArms.begin() + moveBy, Arm(length, angularSpeed));
                updateListBoxes();
            }

            mUI.remove(childWindow);
        });
    }
}

void SettingsScene::removeArmPrompt()
{
    ChildWindow::Ptr childWindow = mUI.get<ChildWindow>("childWindow");

    // Proceed only if there is no child window added.
    if (childWindow == nullptr)
    {
        childWindow = ChildWindow::create();
        childWindow->setSize(600, 400);
        childWindow->setPosition(360, 160);

        ListBox::Ptr indexList = ListBox::create();
        indexList->setSize(75, 100);
        indexList->setPosition(255, 230);
        for (size_t i = 0; i < mArms.size(); i++)
        {
            indexList->addItem(to_string(i + 1));
        }
        indexList->setSelectedItemByIndex(mArms.size());
        childWindow->add(indexList, "listIndex");

        Button::Ptr cancelTrig = Button::create("Anuluj");
        cancelTrig->setSize(135, 30);
        cancelTrig->setPosition(300 - 1.5 * cancelTrig->getSize().x, 340);
        cancelTrig->setTextSize(16);
        childWindow->add(cancelTrig);

        Button::Ptr applyTrig = Button::create(L"Zatwierdź");
        applyTrig->setSize(135, 30);
        applyTrig->setPosition(300 + 0.5 * applyTrig->getSize().x, 340);
        applyTrig->setTextSize(16);
        childWindow->add(applyTrig);

        mUI.add(childWindow, "childWindow");

        applyTrig->connect("pressed", [this, childWindow]
        {
            auto list = mUI.get<ListBox>("listIndex", true);
            int selected = list->getSelectedItemIndex();
            // Remove selected item.
            mArms.erase(mArms.begin() + selected);
            mUI.remove(childWindow);
            updateListBoxes();
        });

        cancelTrig->connect("pressed", &Gui::remove, &mUI, childWindow);
    }

}

void SettingsScene::updateListBoxes()
{
    auto listLeft = mUI.get<ListBox>("listLeft", true);
    auto listMid = mUI.get<ListBox>("listMid", true);
    auto listRight = mUI.get<ListBox>("listRight", true);

    listLeft->removeAllItems();
    listMid->removeAllItems();
    listRight->removeAllItems();

    int i = 0;
    for (auto& a : mArms)
    {
        listLeft->addItem(to_string(++i));
        listMid->addItem(to_string(a.getLength()));
        listRight->addItem(to_string(a.getRotationSpeed()));
    }
}

void SettingsScene::handleInput(Event& e)
{
    if (e.type == Event::MouseMoved)
    {
        //printf("%d, %d\n", e.mouseMove.x, e.mouseMove.y);
    }

    mUI.handleEvent(e);
}

void SettingsScene::render()
{
    mUI.draw();
}

void SettingsScene::update(Time& deltaTime)
{
    // Nothing to update in this scene.
}
