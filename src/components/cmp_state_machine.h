#pragma once
#include <ecm.h>
#include <unordered_map>
#include <string>

class State {
public:
    virtual ~State() = default;
    virtual void execute(Entity*, double) noexcept = 0;
};

class StateMachineComponent : public Component {
private:
    std::unordered_map<std::string, std::shared_ptr<State>> _states;
    std::shared_ptr<State> _currentState;
    std::string _currentStateName = std::string();

public:
    void update(double) override;
    void render() override {}
    
    explicit StateMachineComponent(Entity* p);
    StateMachineComponent() = delete;

    void addState(const std::string&, std::shared_ptr<State>) noexcept;
    std::shared_ptr<State> getState(const std::string&) const noexcept;
    void removeState(const std::string&) noexcept;
    void changeState(const std::string&) noexcept;
    const std::string& currentState() const { return _currentStateName; }
};