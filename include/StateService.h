#ifndef STATE_SERVICE_H
#define STATE_SERVICE_H

#include "Screen.h"
#include "ScreenState.h"
#include <iostream>
#include <memory>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

class StateService
{
private:
    std::unique_ptr<Screen> currentScreen;

    static StateService* instance;
    // StateService() {}

    // StateService() = default;
    // friend StateService* StateService::getInstance();
    StateService()
    {
        std::cout << "Singleton instance created."
                  << std::endl;
    }

    // Private destructor to prevent external deletion
    ~StateService()
    {
        std::cout << "Singleton instance destroyed."
                  << std::endl;
    }
    
public:
    StateService(const StateService&) = delete;
    StateService& operator=(const StateService&) = delete;
    // ~StateService() = default;
    // StateService(const StateService &) = delete;
    // StateService &operator=(const StateService &) = delete;

    //  StateService&  myStateService = StateService::instance(); 
    // StateService(const StateService&) = delete;
    // StateService& operator=(const StateService&) = delete;

    // static StateService* getInstance();

    //     static std::shared_ptr<StateService> getInstance() {
    //     static std::shared_ptr<StateService> instance = std::make_shared<StateService>();
    //     return instance;
    // }
    static StateService& getInstance()
     {
        if (instance == nullptr) {
            instance = new StateService();
        }
        return *instance;
    }

    // static StateService* getInstance();

    // {
    //     if (!instance)
    //     {
    //         instance = std::make_unique<StateService>(); // This works because of the friend declaration
    //     }
    //     return instance.get(); // Return the raw pointer of the unique_ptr
    // }

    void setScreen(ScreenState screen);
    Screen *getScreen();

    void gameloop();
};

// StateService* StateService::instance = nullptr;

// std::unique_ptr<StateService> StateService::instance = nullptr;

#endif