#include "raylib.h"
#include "Screen.h"
#include "TitleScreen.h"
#include "StateService.h"
#include <iostream>


int main(void)
{
    StateService& stateService = StateService::getInstance();
    stateService.setScreenSize({640,544});
    stateService.startGame();
    // std::cout << "StateService instance: " << service << std::endl;
  
    return 0;
}