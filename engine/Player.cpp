#include "Player.h"

Player::Player(Map* _map) {
    pos = {0,0};
    map = _map;
}

Player::Player(const Player &p) {
    pos = p.pos;
    angle = p.angle;
    map = p.map;
}

Player &Player::operator=(const Player &p) {
    pos = p.pos;
    angle = p.angle;
    map = p.map;
    return *this;
}

Player::~Player() {

}

Vector2 Player::getPos() const {
    return pos;
}

void Player::setPos(Vector2 _pos) {
    pos = _pos;
}

void Player::setPos(float x, float y) {
    pos = {x, y};
}

Player::Player(Vector2 _pos, Map* _map) {
    pos = _pos;
    map = _map;
}

Player::Player(Vector2 _pos, float _angle, Map* _map) {
    pos = _pos;
    angle = _angle;
    map = _map;
}

float Player::getAngle() const {
    return angle;
}

void Player::setAngle(float _angle) {
    angle = _angle;
}

float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float _speed) {
    speed = _speed;
}

void Player::move() {
    auto map_data = map->getData();
    double radians = degToRad(angle);
    if(IsKeyDown(KEY_W))
    {
        double dx = speed * cos(radians);
        double dy = speed * sin(radians);
        Vector2 temp_pos, temp_pos_cell;
        temp_pos.x = pos.x + fapprox(dx) + PLAYER_RADIUS * cos(radians);
        temp_pos.y = pos.y + fapprox(dy) + PLAYER_RADIUS * sin(radians);
        temp_pos_cell.x = temp_pos.x / CELL_SIZE;
        temp_pos_cell.y = temp_pos.y / CELL_SIZE;
        if(map_data[temp_pos_cell.y][temp_pos_cell.x] == '_')
        {
            pos.x += fapprox(dx);
            pos.y += fapprox(dy);
        }

    }

    if(IsKeyDown(KEY_S))
    {
        double dx = speed * cos(radians);
        double dy = speed * sin(radians);
        Vector2 temp_pos, temp_pos_cell;
        temp_pos.x = pos.x - fapprox(dx) - PLAYER_RADIUS * cos(radians);
        temp_pos.y = pos.y - fapprox(dy) - PLAYER_RADIUS * sin(radians);
        temp_pos_cell.x = temp_pos.x / CELL_SIZE;
        temp_pos_cell.y = temp_pos.y / CELL_SIZE;
        if(map_data[temp_pos_cell.y][temp_pos_cell.x] == '_')
        {
            pos.x -= fapprox(dx);
            pos.y -= fapprox(dy);
        }
    }


    if(IsKeyDown(KEY_A))
        angle -= angle_speed;
    if(IsKeyDown(KEY_D))
        angle += angle_speed;
    clampAngle(angle);

    cell_x = pos.x / CELL_SIZE;
    cell_y = pos.y / CELL_SIZE;

}

float Player::getFOV() const {
    return FOV;
}

void Player::setFOV(float _fov) {
    FOV = _fov;
}

float Player::getRaysNumber() const {
    return rays_number;
}

void Player::setRaysNumber(float r) {
    rays_number = r;
}
