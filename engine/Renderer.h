#ifndef RAYCASTENGINE_RENDERER_H
#define RAYCASTENGINE_RENDERER_H
#include "../data/Map.h"
#include <string>
#include <raylib.h>
#include <iostream>
#include <vector>>
#include "Player.h"
#include "EngineUtils.h"

class Renderer {
private:
    Vector2 startFOV={0,0}, endFOV={0,0};
    float startAngle = 0;
    vector<float> ray_lengths;
    float wall_scale_factor = 0.3;

public:
    void drawMinimap(Map* map);
    void drawPlayerMinimap(Player* player);
    void drawPlayerFOV(Player* player);
    void drawCameraPlane(Player* player);
    void shootRaysConic(Player* player, Map* map);
    void shootRaysPlane(Player* player, Map* map); // not needed anymore
    void renderWorld(Player* player);
};


#endif //RAYCASTENGINE_RENDERER_H
