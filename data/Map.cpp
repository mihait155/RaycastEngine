#include "Map.h"
#include <iostream>

vector<std::string> Map::getData() {
    return map_data;
}

Map::Map() {
}

Map::Map(const Map &m) {
    map_data = m.map_data;
}

Map &Map::operator=(const Map &m) {
    this->map_data = m.map_data;
    return *this;
}

void Map::initData() {

}

char Map::getCell(int x, int y) {
    try
    {
        if(x < 0 || y < 0) return '#';
        if(y >= map_data.size() - 1) return '#';
        if(x >= map_data[y].length() - 1) return '#';
        return map_data[x][y];
    }
    catch(exception& e)
    {
        return '#';
    }
    return '#';

}
