#include "SettingsState.h"

#include "imgui.h"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context)
{

}

void SettingsState::draw()
{
    auto windowSize = getContext().window->getSize();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos({ 0, 0 });

    ImGuiWindowFlags menuFlags =
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse |
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration;

    ImGui::Begin("Settings", nullptr, menuFlags);

    if (ImGui::Button("Back")) {
        requestStackClear();
        requestStackPush(States::ID::Menu);
    }

    ImGui::End();
}

bool SettingsState::update(sf::Time dt)
{
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    return true;
}
