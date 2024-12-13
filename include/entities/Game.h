#ifndef GAME_H
#define GAME_H

#include "entities/Map.h"
#include "entities/Background.h"
#include "services/StateService.h"
#include "services/AudioService.h"
#include "services/MapService.h"
#include "services/InputService.h"
#include "services/GameService.h"
#include "entities/Player.h"
#include "entities/Text.h"
#include "entities/Bullet.h"
#include "entities/PBullet.h"

class Game
{
public:
    Game()
    {
        GameService::getInstance().resetGame();

        TextureWrapper wrapper1 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME1), {GetScreenWidth() * 2.0f, (float)GetScreenHeight()}, {0, 0});
        wrapper1.setSourceRect({0, 0, wrapper1.getSize().x, wrapper1.getSize().y});
        TextureWrapper wrapper2 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME2), {864.0f, (float)GetScreenHeight()}, {wrapper1.getSize().x, 0.0});
        wrapper2.setSourceRect({0, 200, wrapper2.getSize().x, 200 + wrapper2.getSize().y});
        TextureWrapper wrapper3 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME3), {1792.0f, (float)GetScreenHeight()}, {wrapper1.getSize().x + wrapper2.getSize().x, 0.0});
        wrapper3.setSourceRect({64, 200, 64 + wrapper3.getSize().x, 200 + wrapper3.getSize().y});

        std::vector<TextureWrapper> wrappers;
        wrappers.push_back(wrapper1);
        wrappers.push_back(wrapper2);
        wrappers.push_back(wrapper3);
        this->background = Background(wrappers);
        this->map = Map();
        MapService::getInstance().setMap(this->map);

        Vector2 screenSize = StateService::getInstance().getScreenSize();
        Camera2D camera = {0};
        camera.offset = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Set offset to center
        camera.target = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Initially at the center of the world
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        // this->camera = camera;
        GameService::getInstance().setCamera(camera);
        this->player = Player();
        this->player.setPosition({200, 350});
        this->crosshair = TextureWrapper(AssetService::getInstance().getSprite(ESprite::CROSSHAIR), {15, 15}, {0, 0}, {0, 0, 15, 15});

        initPauseScreen();
        initGameOverScreen();

        InputService::getInstance().setKeysToWatch({KEY_A, KEY_W, KEY_S, KEY_D, KEY_ENTER}, {MOUSE_BUTTON_LEFT});
        AudioService::getInstance().setMusic(EMusic::GAME);
        AudioService::getInstance().playMusic();
    }

    ~Game()
    {
    }

    void logic()
    {
        this->crosshair.setPosition(GetMousePosition());

        if (GameService::getInstance().isPaused())
        {
            pausedLogic();
            return;
        }
        else if (GameService::getInstance().isGameOver())
        {
            gameOverLogic();
            return;
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {
            GameService::getInstance().setPaused(true);
            AudioService::getInstance().pauseMusic();
            return;
        }
 
        GameService::getInstance().bulletLogic();

        this->player.logic();
        if (this->player.getTexture().getPosition().x > (StateService::getInstance().getScreenSize().x / 2.0f))
        {
            GameService::getInstance().getCamera().offset = {(StateService::getInstance().getScreenSize().x / 2.0f) + ((StateService::getInstance().getScreenSize().x / 2.0f) - this->player.getTexture().getPosition().x), StateService::getInstance().getScreenSize().y / 2.0f};
        }
    }

    void draw()
    {
        BeginDrawing();
        BeginMode2D(GameService::getInstance().getCamera());

        this->background.draw();

        // std::vector<PBullet> pbs = GameService::getInstance().getPlayerBullets();
        // for (int i = 0; i < GameService::getInstance().getPlayerBullets().size(); i++)
        // {
        //     GameService::getInstance().getPlayerBullets()[i].draw();
        // }
        GameService::getInstance().drawBullets();
        this->map.draw();
        this->player.draw();

        EndMode2D();

        if (GameService::getInstance().isPaused())
        {
            drawPaused();
        }
        else if (GameService::getInstance().isGameOver())
        {
            drawGameOver();
        }
        drawCrosshair();
        EndDrawing();
    }

private:
    // Camera2D camera;
    Background background;
    Map map;
    Player player;
    TextureWrapper crosshair;

    std::vector<Text> pauseScreenButtons;
    int hoveredPauseScreenButton = 0;

    Text gameOverText;
    std::vector<Text> gameOverScreenButtons;
    int hoveredGameOverScreenButton = 0;

    // std::vector<PBullet> playerBullets;

    // bool isPaused = false;
    // bool isGameOver = false;

    // std::vector<Enemy> enemies
    // std::vector<Create> crates
    // std::vector<EBullet> enemyBullets
    // std::vector<Jelly> jellies
    // std::vector<Ammo> ammo
    // std::vector<Healthpack> healthpacks
    // Powerup powerup

    void initPauseScreen()
    {
        const int TOP_GAP = 100;
        const int BOTTOM_GAP = 50;
        const int AMNT_OF_BUTTONS = 4;
        const int TOTAL_SPACE = GetScreenHeight() - (TOP_GAP + BOTTOM_GAP);
        const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;

        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            Text txt = Text("Continue", EFont::SANSATION, 30, 0, WHITE);
            pauseScreenButtons.push_back(txt);
        }
        pauseScreenButtons[0].setColor(RED);
        pauseScreenButtons[1].setText("Save Game");
        pauseScreenButtons[2].setText("Quit to Main Menu");
        pauseScreenButtons[3].setText("Quit to Desktop");

        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            pauseScreenButtons[i].setPosition({(float)(GetScreenWidth() - pauseScreenButtons[i].getDimensions().x) / 2.0f, (float)TOP_GAP + SPACE_PER_ITEM * i});
        }
    }

    void initGameOverScreen()
    {
        this->gameOverText = Text("Game Over", EFont::SANSATION, 60, 0, WHITE);
        this->gameOverText.setPosition({(float)(GetScreenWidth() - gameOverText.getDimensions().x) / 2.0f, (float)(GetScreenHeight() - gameOverText.getDimensions().y) / 3.0f});

        const int TOP_POS = GetScreenHeight() / 1.8;
        const int X_GAP = 90;
        const int AMNT_OF_BUTTONS = 2;
        const int TOTAL_SPACE = GetScreenWidth() - (X_GAP + X_GAP);
        const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;
        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            Text txt = Text("Play Again", EFont::SANSATION, 30, 0, GRAY);
            gameOverScreenButtons.push_back(txt);
        }
        gameOverScreenButtons[0].setColor(WHITE);
        gameOverScreenButtons[1].setText("Quit to Main Menu");
        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            gameOverScreenButtons[i].setPosition({(float)X_GAP + SPACE_PER_ITEM * i, (float)TOP_POS});
        }
    }

    void pausedLogic()
    {
        if (InputService::getInstance().isKeyPressed(KEY_S) || InputService::getInstance().isKeyPressed(KEY_W))
        {
            pauseScreenButtons[hoveredPauseScreenButton].setColor(WHITE);
            /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
            hoveredPauseScreenButton = ((hoveredPauseScreenButton - (InputService::getInstance().isKeyPressed(KEY_S) ? -1 : 1)) + pauseScreenButtons.size()) % pauseScreenButtons.size();
            pauseScreenButtons[hoveredPauseScreenButton].setColor(RED);
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {

            std::string selectedButton = pauseScreenButtons[hoveredPauseScreenButton].getText();

            if (selectedButton == "Continue")
            {
                GameService::getInstance().setPaused(false);
                AudioService::getInstance().playMusic();
            }
            else if (selectedButton == "Save Game")
            {
            }
            else if (selectedButton == "Quit to Main Menu")
                StateService::getInstance().setScreen(EScreen::MAIN);
            else if (selectedButton == "Quit to Desktop")
                StateService::getInstance().setScreen(EScreen::CLOSE);
        }
    }

    void gameOverLogic()
    {
        if (InputService::getInstance().isKeyPressed(KEY_D) || InputService::getInstance().isKeyPressed(KEY_A))
        {
            gameOverScreenButtons[hoveredGameOverScreenButton].setColor(GRAY);
            /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
            hoveredGameOverScreenButton = ((hoveredGameOverScreenButton - (InputService::getInstance().isKeyPressed(KEY_D) ? -1 : 1)) + gameOverScreenButtons.size()) % gameOverScreenButtons.size();
            gameOverScreenButtons[hoveredGameOverScreenButton].setColor(WHITE);
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {
            std::string selectedButton = gameOverScreenButtons[hoveredGameOverScreenButton].getText();

            if (selectedButton == "Play Again")
            {
                StateService::getInstance().setScreen(EScreen::GAME);
            }
            else if (selectedButton == "Quit to Main Menu")
            {
                StateService::getInstance().setScreen(EScreen::MAIN);
            }
            GameService::getInstance().setGameOver(false);
        }
    }

    void shootLogic()
    {
    }

    void drawPaused()
    {
        // 100, 100, 255, 60
        DrawRectangle(0, 0, StateService::getInstance().getScreenSize().x, StateService::getInstance().getScreenSize().y, {0, 0, 255, 100});
        if (pauseScreenButtons.size() > 0)
        {
            for (int i = 0; i < pauseScreenButtons.size(); i++)
            {
                pauseScreenButtons[i].draw();
            }
        }
    }

    void drawGameOver()
    {
        DrawRectangle(0, 0, StateService::getInstance().getScreenSize().x, StateService::getInstance().getScreenSize().y, {255, 0, 0, 100});

        gameOverText.draw();

        for (int i = 0; i < gameOverScreenButtons.size(); i++)
        {
            gameOverScreenButtons[i].draw();
        }
    }

    void drawCrosshair()
    {
        DrawTextureEx(this->crosshair.getTexture(), GetMousePosition(), 0, 1.2f, RED);
        // DrawTexturePro(
        //     this->crosshair.getTexture(),
        //     this->crosshair.getSourceRect(),
        //     {GetMousePosition().x, GetMousePosition().y, GetMousePosition().x+this->crosshair.getSize().x, GetMousePosition().y+this->crosshair.getSize().y},
        //     {this->crosshair.getSize().x/2.0f, this->crosshair.getSize().y/2.0f},
        //     0,
        //     WHITE);
    }
};

#endif