#ifndef StateStack_h__
#define StateStack_h__

#include <vector>
#include <map>
#include <functional>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "State.h"

class StateStack : private sf::NonCopyable
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear,
    };

    StateStack(State::Context context);

    template <typename T>
    void registerState(States::ID state);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID state);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID state);
    void applyPendingChanges();

    struct PendingChange
    {
        Action action;
        States::ID state;
    };

    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;
    State::Context mContext;
    std::map<States::ID, std::function<State::Ptr()>> mFactories;
};

template <typename T>
void StateStack::registerState(States::ID state)
{
    mFactories[state] = [this]()
    {
        return std::make_unique<T>(*this, mContext);
    };
}

#endif // StateStack_h__
