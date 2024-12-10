#ifndef INPUT_SERVICE_H
#define INPUT_SERVICE_H

#include "Service.h"
#include "raylib.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

/**
 * Tracks all user input, which is then retrieved by the screens
 */
class InputService : public Service<InputService>
{
public:
    /**
     * Setting up the keys to watch, so that only the keys that might get pressed are being watched
     */
    void setKeysToWatch(std::vector<KeyboardKey> keysToWatch, std::vector<MouseButton> mouseButtonsToWatch)
    {
        this->watchedKeys.clear();
        this->keysPressed.clear();

        for (int i = 0; i < keysToWatch.size(); i++)
        {
            this->watchedKeys.insert(keysToWatch[i]);
            this->keysPressed[keysToWatch[i]] = false;
        }

        setMouseButtonsToWatch(mouseButtonsToWatch);
    }

    /**
     * Checks if a button has been pressed
     * The flow:
     * 1. Screen constructor: Announce which keys to watch
     * 2. StateService loop: Check keys, store the result
     * 3. Screen logic: If pressed, execute logic
     */
    void checkKeys()
    {
        for (auto key : watchedKeys)
        {
            keysPressed[key] = false;
            if (IsKeyPressed(key))
            {
                keysPressed[key] = true;
            }
        }
        for (auto button : watchedMouseButtons)
        {
            mouseButtonsPressed[button] = false;
            if (IsMouseButtonPressed(button))
            {
                mouseButtonsPressed[button] = true;
            }
        }
    }

    bool isKeyPressed(KeyboardKey key)
    {
        return keysPressed[key];
    }

    bool isMouseButtonPressed(MouseButton button)
    {
        return mouseButtonsPressed[button];
    }

private:
    std::unordered_set<KeyboardKey> watchedKeys;
    std::unordered_map<KeyboardKey, bool> keysPressed;
    std::unordered_set<MouseButton> watchedMouseButtons;
    std::unordered_map<MouseButton, bool> mouseButtonsPressed;

    void setMouseButtonsToWatch(std::vector<MouseButton> mouseButtonsToWatch)
    {
        this->watchedMouseButtons.clear();
        this->mouseButtonsPressed.clear();

        for (int i = 0; i < mouseButtonsToWatch.size(); i++)
        {
            this->watchedMouseButtons.insert(mouseButtonsToWatch[i]);
            this->mouseButtonsPressed[mouseButtonsToWatch[i]] = false;
        }
    }
};

#endif