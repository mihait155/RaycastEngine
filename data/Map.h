#ifndef RAYCASTENGINE_MAP_H
#define RAYCASTENGINE_MAP_H
#include <vector>
#include <string>
using namespace std;

class Map {
protected:
    vector<std::string> map_data;
public:
    Map();
    Map(const Map& m);
    Map& operator=(const Map& m);

    vector<std::string> getData();
    char getCell( int x, int y);
    virtual void initData();

};


#endif //RAYCASTENGINE_MAP_H
