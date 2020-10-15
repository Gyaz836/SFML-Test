#include "MenuState.h"

#include "imgui.h"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
{

}

void MenuState::draw()
{
    auto windowSize = getContext().window->getSize();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos({ 0, 0 });

    ImGuiWindowFlags menuFlags =
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse |
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration;

    unsigned int entriesCount = static_cast<unsigned int>(MenuEntries::Count);

    sf::Vector2u buttonSize(windowSize.x / 2, windowSize.y / entriesCount / 3);
    float spaceSize = (windowSize.y - buttonSize.y * entriesCount) / (entriesCount + 1.f);

    ImGui::Begin("Menu", nullptr, menuFlags);

    ImGui::SetWindowFontScale(4.f);

    ImGui::Dummy({ 0.f, spaceSize });

    ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2.f); 
    if (ImGui::Button("Play", buttonSize))
    {
        requestStackPop();
        requestStackPush(States::ID::Game);
    }

    ImGui::Dummy({ 0.f, spaceSize });

    ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2.f);
    if (ImGui::Button("Settings", buttonSize))
    {
        requestStackPop();
        requestStackPush(States::ID::Settings);
    }

    ImGui::Dummy({ 0.f, spaceSize });

    ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2.f);
    if (ImGui::Button("Exit", buttonSize))
    {
        requestStackPop();
    }

    ImGui::End();
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    return true;
}
