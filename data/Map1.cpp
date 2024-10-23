#include "Map1.h"

// Map data for this map
void Map1::initData() {
    map_data.emplace_back("#####################");
    map_data.emplace_back("#_____________#_____#");
    map_data.emplace_back("#_____________#_____#");
    map_data.emplace_back("#_____________#######");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#___________________#");
    map_data.emplace_back("#####################");
}

Map1::Map1() {

}

Map1::Map1(const Map1 &m) {
    map_data = m.map_data;
}

Map1 &Map1::operator=(const Map1 &m) {
    map_data = m.map_data;
    return *this;
}
