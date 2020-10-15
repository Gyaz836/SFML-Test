#include "Application.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"

Application::Application()
    : mWindow(std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 900), "Application", sf::Style::Titlebar | sf::Style::Close))
    , mPlayer(std::make_unique<Player>())
    , mContext(*mWindow, mTextures, mFonts, *mPlayer)
    , mStateStack(mContext)
{
    registerStates();
    ImGui::SFML::Init(*mWindow);

    mStateStack.pushState(States::ID::Title);
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
}

void Application::run()
{
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow->isOpen()) {
        updateDeltaTime();
        timeSinceLastUpdate += fullFrameDeltaTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }
        ImGui::SFML::Update(*mWindow, fullFrameDeltaTime);
        draw();
    }
}

void Application::updateDeltaTime()
{
    fullFrameDeltaTime = deltaClock.restart();
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        mStateStack.handleEvent(event);

        if (event.type == sf::Event::EventType::KeyPressed) {
            handlePlayerInput(event.key.code, true);
        }
        if (event.type == sf::Event::EventType::KeyReleased) {
            handlePlayerInput(event.key.code, false);
        }

        if (event.type == sf::Event::Closed) {
            mWindow->close();
        }
    }
}

void Application::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
    case sf::Keyboard::Key::Tilde:
    {
        if (isPressed && consoleReleased) {
            consoleOpened = !consoleOpened;
            consoleReleased = false;
        }
        if (!isPressed) {
            consoleReleased = true;
        }
    }
    default:
        break;
    }
}

void Application::update(sf::Time dt)
{
    processInput();

    mStateStack.update(dt);

    if (mStateStack.isEmpty()) {
        mWindow->close();
    }
}

void Application::draw()
{
    mWindow->clear();

    mStateStack.draw();

    if (consoleOpened) {
        ImGui::Begin("Console");

        ImGui::Checkbox("Show Settings", &settingsOpened);

        ImGui::End();
    }

    if (settingsOpened) {
        ImGui::Begin("Settings");

        ImGui::End();
    }

    ImGui::SFML::Render(*mWindow);

    mWindow->display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::ID::Title);
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<GameState>(States::ID::Game);
    mStateStack.registerState<PauseState>(States::ID::Pause);
    mStateStack.registerState<SettingsState>(States::ID::Settings);
}
