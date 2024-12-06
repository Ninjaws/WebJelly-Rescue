#include "MainScreen.h"
#include "AssetService.h"
#include <iostream>

MainScreen::MainScreen() {
    assetDir = "assets";
    font1 = LoadFontEx((assetDir+"/Fonts/Reckoner_Bold.ttf").c_str(), 100,0,0);
    SetTextureFilter(font1.texture, TEXTURE_FILTER_BILINEAR);
    font2 = LoadFont((assetDir+"/Fonts/Sansation.ttf").c_str());
    SetTextureFilter(font2.texture, TEXTURE_FILTER_BILINEAR);
    dimTitle = MeasureTextEx(font1, "Jelly sadsdsdsdrescue", 100,0);
    dimSub = MeasureTextEx(font2, "Press Entsder to continue", 30,0);
    dimHead = MeasureTextEx(font2, "Made by Ian Vink", 20,0);
    bg = LoadMusicStream((assetDir+"/Audio/Music/Crash_WarpRoomTheme.ogg").c_str());
    bg.looping = true;
    SetMasterVolume(1.0f);
    SetMusicVolume(bg,1.0f);
    PlayMusicStream(bg);
}

MainScreen::~MainScreen() {
    UnloadMusicStream(bg);
    UnloadFont(font1);
    UnloadFont(font2);
}

void MainScreen::step() {
    draw();
    logic();
}

void MainScreen::logic() {
    // if(IsKeyPressed(KEY_ENTER)) {
    //     std::cout << "Next screen!" << std::endl;
    // }
}

void MainScreen::draw() {
        UpdateMusicStream(bg);
        BeginDrawing();
        ClearBackground(BLACK);                
        DrawTextEx(font2,"Made by Ian Vink", {((float)GetScreenWidth()-dimHead.x)/1.2f, (float(GetScreenHeight()-dimHead.y)/6.0f)}, 20, 0, WHITE);
        DrawTextEx(font1,"Jelly rescue", {((float)GetScreenWidth()-dimTitle.x)/2.0f, (float(GetScreenHeight()-dimTitle.y)/2.0f)}, 100,0, {255,25,25,255});
        DrawTextEx(font2,"Press Enter to continue", {((float)GetScreenWidth()-dimSub.x)/2.0f, (float(GetScreenHeight()-dimSub.y)/1.5f)}, 30, 0, WHITE);
        EndDrawing();
}