#include "raylib.h"
#include <string>
#include "data/Map.h"
#include "data/Map1.h"
#include "engine/Renderer.h"
#include "engine/Player.h"

int main()
{
    // Initialization
    Renderer renderer;
    
    Map1* map = new Map1;
    map->initData();

    Player player({screenWidth/2, screenHeight/2}, map);


    InitWindow(screenWidth, screenHeight, wName.c_str());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        player.move();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        // DRAW HERE

        renderer.shootRaysConic(&player, map);
        renderer.renderWorld(&player);
        renderer.drawMinimap(map);
        renderer.drawPlayerMinimap(&player);
        renderer.drawPlayerFOV(&player);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    delete map;
    return 0;
}
