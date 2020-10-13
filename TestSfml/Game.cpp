#include "Game.h"

#include <string>
#include <iostream>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

Game::Game()
    : window(std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 900), "ImGui + SFML = <3", sf::Style::Titlebar | sf::Style::Close))
    , mWorld(*window)
{
    window->setFramerateLimit(300);
    ImGui::SFML::Init(*window);
}

Game::~Game()
{
    ImGui::SFML::Shutdown();
}

void Game::run()
{
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window->isOpen()) {
        updateDeltaTime();
        timeSinceLastUpdate += fullFrameDeltaTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }
        ImGui::SFML::Update(*window, fullFrameDeltaTime);
        render();
    }
}

void Game::updateDeltaTime()
{
    fullFrameDeltaTime = deltaClock.restart();
    /*system("cls");
    std::cout << deltaTime.asSeconds();*/
}

void Game::updateSFMLEvents()
{
    while (window->pollEvent(sfEvent)) {
        ImGui::SFML::ProcessEvent(sfEvent);

        switch (sfEvent.type)
        {
        case sf::Event::KeyPressed:
        {
            handlePlayerInput(sfEvent.key.code, true);
            break;
        }
        case sf::Event::KeyReleased:
        {
            handlePlayerInput(sfEvent.key.code, false);
            break;
        }
        case sf::Event::Closed:
        {
            window->close();
            break;
        }
        default:
            break;
        }
    }
}

void Game::update(sf::Time dt)
{
    updateSFMLEvents();
    mWorld.update(dt);
}

void Game::render()
{
    window->clear();

    if (consoleOpened) {
        ImGui::Begin("Console");

        ImGui::Checkbox("Show Settings", &settingsOpened);

        ImGui::End();
    }

    if (settingsOpened) {
        ImGui::Begin("Settings");

        ImGui::End();
    }

    //ImGui::Begin("Player parameters");
    //ImGui::Text(("Player Pos : " + std::to_string(mPlayer->getPosition().x) + " " + std::to_string(mPlayer->getPosition().y)).c_str());

    //ImGui::DragFloat("Player Speed", &playerSpeed);
    //ImGui::DragFloat("Player size", &playerSize);

    //ImGui::ShowDemoWindow(&pOpen);

    //ImGui::End();

    mWorld.draw();

    ImGui::SFML::Render(*window);
    window->display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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
    case sf::Keyboard::Key::W:
    {
        break;
    }
    case sf::Keyboard::Key::S:
    {
        break;
    }
    case sf::Keyboard::Key::D:
    {
        break;
    }
    case sf::Keyboard::Key::A:
    {
        break;
    }
    default:
        break;
    }
}
