#include "PauseState.h"

#include "imgui.h"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
{

}

void PauseState::draw()
{
    auto windowSize = getContext().window->getSize();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos({ 0, 0 });

    ImGuiWindowFlags menuFlags =
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse |
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration;

    ImGui::Begin("Pause", nullptr, menuFlags);

    ImGui::SetWindowFontScale(10.f);

    auto textSize = ImGui::CalcTextSize("Paused");

    ImGui::Dummy({ 0.f, textSize.y / 3.f });

    ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2.f);

    ImGui::Text("Paused");

    textSize.y /= 1.3f;
    textSize.x /= 1.3f;

    ImGui::SetWindowFontScale(7.f);
    ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2.f);
    if (ImGui::Button("Resume", textSize)) {
        requestStackPop();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SetWindowFontScale(5.f);
    ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2.f);
    if (ImGui::Button("Main Menu", textSize)) {
        requestStackClear();
        requestStackPush(States::ID::Menu);
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SetWindowFontScale(7.f);
    ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2.f);
    if (ImGui::Button("Exit", textSize)) {
        requestStackClear();
    }

    ImGui::End();
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) {
        requestStackPop();
    }
    return false;
}
