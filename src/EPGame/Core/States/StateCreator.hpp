#ifndef STATE_CREATOR_HPP
#define STATE_CREATOR_HPP

#include "../GameState.hpp"
#include "Gameplay.hpp"

#include <unordered_map>

enum class States {
    GAMEPLAY
};

//Abstract Factory of States
class StateCreator {  
    public:
        StateCreator() = default;
        virtual ~StateCreator() = default;
        virtual std::unique_ptr<GameState> createState(PEngine* ctx) = 0;
};

template<typename TState>
class TStateCreator : public StateCreator {
    public:
        TStateCreator(){}
        ~TStateCreator(){}
        std::unique_ptr<GameState> createState(PEngine* ctx) override {
            return std::make_unique<TState>(ctx);
        }
};

inline std::unordered_map<States, std::unique_ptr<StateCreator>> initStateFacts(){
    std::unordered_map<States, std::unique_ptr<StateCreator>> Facts;
    Facts[States::GAMEPLAY] = std::make_unique<TStateCreator<GamePlay>>();
    return Facts;
}

#endif