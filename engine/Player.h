#ifndef RAYCASTENGINE_PLAYER_H
#define RAYCASTENGINE_PLAYER_H
#include "raylib.h"
#include "../data/Constants.h"
#include "../data/Map.h"
#include <iostream>
#include <cmath>
#include "EngineUtils.h"

class Player {
private:
    Vector2 pos;
    float angle = 270;
    float speed = 5;
    float angle_speed = 2;

    float FOV = 80;

    float rays_number = FOV;

    int cell_x, cell_y;

    Map* map;


public:
    explicit Player(Map* _map);
    explicit Player(Vector2 _pos, Map* _map);
    Player(Vector2 _pos, float _angle, Map* _map);
    Player(const Player& p);
    Player& operator=(const Player& p);
    ~Player();

    Vector2 getPos() const;
    void setPos(Vector2 _pos);
    void setPos(float x, float y);

    float getAngle() const;
    void setAngle(float _angle);

    float getSpeed() const;
    void setSpeed(float _speed);

    float getFOV() const;
    void setFOV(float _fov);

    float getRaysNumber() const;
    void setRaysNumber(float r);

    void move();

};


#endif //RAYCASTENGINE_PLAYER_H
