#include "Renderer.h"
#include <cmath>
#include "../data/Constants.h"
#include <iostream>

void Renderer::drawMinimap(Map* map) {
    auto map_data = map->getData();
    for(int i=0;i<map_data.size();i++) {
        for(int j=0;j<map_data[i].length();j++) {
            if(map_data[i][j] == '#')
                DrawRectangleLines(MINIMAP_OFFSET_X + (5 + j*CELL_SIZE) * MINIMAP_SCALE,
                                   MINIMAP_OFFSET_Y + (5 + i*CELL_SIZE) * MINIMAP_SCALE,
                                   CELL_SIZE*MINIMAP_SCALE,
                                   CELL_SIZE*MINIMAP_SCALE, WHITE);
        }
    }

}

void Renderer::drawPlayerMinimap(Player *player) {
    Vector2 p = player->getPos();
    // Draw the player
    DrawCircle(MINIMAP_OFFSET_X + (int)p.x * MINIMAP_SCALE,
               MINIMAP_OFFSET_Y + (int)p.y * MINIMAP_SCALE,
               PLAYER_RADIUS * MINIMAP_SCALE, WHITE);

    // Draw a line indicating where the player looks
    int line_size = 100;
    int line_x = fapprox(p.x + line_size * cos(degToRad(player->getAngle())));
    int line_y = fapprox(p.y + line_size * sin(degToRad(player->getAngle())));

    DrawLine(MINIMAP_OFFSET_X + (int)p.x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + (int)p.y * MINIMAP_SCALE,
             MINIMAP_OFFSET_X + (int)line_x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + (int)line_y * MINIMAP_SCALE, RED);
    

}

// Deprecated
void Renderer::drawCameraPlane(Player *player) {
    Vector2 p = player->getPos();
    float cameraPlaneAngle = player->getAngle();
    for(int i=1;i<=90;i++) {
        cameraPlaneAngle++;
        clampAngle(cameraPlaneAngle);
    }
    int line_size = player->getRaysNumber();
    int line_start_x = fapprox(p.x - line_size/2 * cos(degToRad(cameraPlaneAngle)));
    int line_start_y = fapprox(p.y - line_size/2 * sin(degToRad(cameraPlaneAngle)));
    int line_end_x = fapprox(p.x + line_size/2 * cos(degToRad(cameraPlaneAngle)));
    int line_end_y = fapprox(p.y + line_size/2 * sin(degToRad(cameraPlaneAngle)));

    DrawLine(MINIMAP_OFFSET_X + line_start_x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + line_start_y * MINIMAP_SCALE,
             MINIMAP_OFFSET_X + line_end_x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + line_end_y * MINIMAP_SCALE, PINK);


}

void Renderer::drawPlayerFOV(Player *player) {
    Vector2 p = player->getPos();

    Vector2 f1, f2;
    int line_size = 100;

    float lowerAngle = player->getAngle();
    float upperAngle = player->getAngle();
    for(int i=1;i<=player->getFOV()/2;i++)
    {
        lowerAngle--;
        clampAngle(lowerAngle);
        upperAngle++;
        clampAngle(upperAngle);
    }

    startAngle = lowerAngle;

    f1.x = fapprox(p.x + line_size * cos(degToRad(lowerAngle)));
    f1.y = fapprox(p.y + line_size * sin(degToRad(lowerAngle)));
    f2.x = fapprox(p.x + line_size * cos(degToRad(upperAngle)));
    f2.y = fapprox(p.y + line_size * sin(degToRad(upperAngle)));

    startFOV = f1;
    endFOV = f2;

    DrawLine(MINIMAP_OFFSET_X + (int)p.x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + (int)p.y * MINIMAP_SCALE,
             MINIMAP_OFFSET_X + f1.x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + f1.y * MINIMAP_SCALE, GREEN);
    DrawLine(MINIMAP_OFFSET_X + (int)p.x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + (int)p.y * MINIMAP_SCALE,
             MINIMAP_OFFSET_X + f2.x * MINIMAP_SCALE,
             MINIMAP_OFFSET_Y + f2.y * MINIMAP_SCALE, GREEN);
}


// Deprecated - Shoot rays from a camera plane
// This needed no correction for the fisheye effect, but the conic way is the classic way of doing it
void Renderer::shootRaysPlane(Player *player, Map *map) {
    auto map_data = map->getData();
    ray_lengths.clear();
    Vector2 p = player->getPos();
    int ray_max_length = 5000;

    float planeAngle = player->getAngle();
    for(int i=1;i<=90;i++) {
        planeAngle++;
        clampAngle(planeAngle);
    }

    int planeOffset = -player->getRaysNumber();

    // Iterating through all rays
    for(int i=1;i<=player->getRaysNumber()*2;i++) {
        planeOffset++;
        Vector2 ray_start, ray_end;

        ray_start.x = fapprox(p.x + planeOffset/2 * cos(degToRad(planeAngle)));
        ray_start.y = fapprox(p.y + planeOffset/2 * sin(degToRad(planeAngle)));

        int ray_length = 0;
        ray_end.x = fapprox(ray_start.x + ray_length * cos(degToRad(player->getAngle())));
        ray_end.y = fapprox(ray_start.y + ray_length * sin(degToRad(player->getAngle())));

        int raycell_y = ray_end.y / CELL_SIZE;
        int raycell_x = ray_end.x / CELL_SIZE;
        while(map_data[raycell_y][raycell_x] != '#' && ray_length <= ray_max_length) {
            ray_length += 3;
            ray_end.x = fapprox(ray_start.x + ray_length * cos(degToRad(player->getAngle())));
            ray_end.y = fapprox(ray_start.y + ray_length * sin(degToRad(player->getAngle())));
            raycell_y = ray_end.y / CELL_SIZE;
            raycell_x = ray_end.x / CELL_SIZE;

        }

        DrawLine(MINIMAP_OFFSET_X + (int)ray_start.x * MINIMAP_SCALE,
                 MINIMAP_OFFSET_Y + (int)ray_start.y * MINIMAP_SCALE,
                 MINIMAP_OFFSET_X + (int)ray_end.x * MINIMAP_SCALE,
                 MINIMAP_OFFSET_Y + (int)ray_end.y * MINIMAP_SCALE, BLUE);
        ray_lengths.push_back(ray_length);

    }

}

// Shoot rays in a cone shape
void Renderer::shootRaysConic(Player *player, Map *map) {
    auto map_data = map->getData();
    ray_lengths.clear();
    Vector2 p = player->getPos();
    int ray_max_length = 5000;

    float angleDiffPerRay = player->getFOV() / player->getRaysNumber();

    float lastAngle = startAngle;

    // Going through all rays
    for(int i=1;i<=player->getRaysNumber();i++)
    {
        float current_length = 0;
        // Adding degrees to the ray angle
        for(int j=0;j<angleDiffPerRay;j++)
            lastAngle++, clampAngle(lastAngle);

        Vector2 ray;
        ray.x = p.x + current_length * cos(degToRad(lastAngle));
        ray.y = p.y + current_length * sin(degToRad(lastAngle));

        int raycell_y = ray.y / CELL_SIZE;
        int raycell_x = ray.x / CELL_SIZE;

        while(map_data[raycell_y][raycell_x] != '#' && current_length <= ray_max_length) {
            current_length += 3;
            ray.x = p.x + current_length * cos(degToRad(lastAngle));
            ray.y = p.y + current_length * sin(degToRad(lastAngle));
            raycell_y = ray.y / CELL_SIZE;
            raycell_x = ray.x / CELL_SIZE;

        }
        DrawLine(MINIMAP_OFFSET_X + p.x * MINIMAP_SCALE,
                 MINIMAP_OFFSET_Y + p.y * MINIMAP_SCALE,
                 MINIMAP_OFFSET_X + ray.x * MINIMAP_SCALE,
                 MINIMAP_OFFSET_Y + ray.y * MINIMAP_SCALE, BLUE);
        ray_lengths.push_back(current_length);
    }
}

void Renderer::renderWorld(Player* player) {
    int wall_segments = ray_lengths.size(); // The number of wall segments
    if(wall_segments == 0) return;

    int wall_segment_size = screenWidth / wall_segments; // The size of a wall segment
    float projectionPlaneDistance = screenWidth / (2 * tan(player->getFOV() / 2)) * wall_scale_factor; // Distance to projection plane

    float angleDifference = player->getFOV() / wall_segments; // Difference between FOV angles

    for(int i = 0; i < ray_lengths.size(); i++) {
        float angle = (-player->getFOV()/2 +(i*angleDifference));
        float true_length = ray_lengths[i] * cos(degToRad(angle));

        // Calculate wall height inversely proportional to the ray length
        float wallHeight = (screenHeight / true_length) * projectionPlaneDistance;

        // Calculate the center of the screen
        int screenCenter = screenHeight / 2;

        // Determine the upper and lower bounds of the wall segment
        int upperWallBorder = screenCenter - wallHeight / 2;
        int lowerWallBorder = screenCenter + wallHeight / 2;

        // Clip values to ensure they don't go off-screen
        upperWallBorder = std::max(0, upperWallBorder);
        lowerWallBorder = std::min(screenHeight, lowerWallBorder);

        // Draw the four lines representing the wall slice
        // Upper horizontal line
        DrawLine(i * wall_segment_size, upperWallBorder,
                 i * wall_segment_size + wall_segment_size, upperWallBorder, WHITE);
        // Lower horizontal line
        DrawLine(i * wall_segment_size, lowerWallBorder,
                 i * wall_segment_size + wall_segment_size, lowerWallBorder, WHITE);
        // Left vertical line
        DrawLine(i * wall_segment_size, upperWallBorder,
                 i * wall_segment_size, lowerWallBorder, WHITE);
        // Right vertical line
        DrawLine(i * wall_segment_size + wall_segment_size, upperWallBorder,
                 i * wall_segment_size + wall_segment_size, lowerWallBorder, WHITE);
    }
}

