#include "services/StateService.h"

int main()
{
    StateService& stateService = StateService::getInstance();
    stateService.setScreenSize({640,544});
    stateService.startGame();
    return 0;
}
