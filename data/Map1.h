#ifndef RAYCASTENGINE_MAP1_H
#define RAYCASTENGINE_MAP1_H
#include "Map.h"

class Map1 : public Map {
public:
    Map1();
    Map1(const Map1& m);
    Map1& operator=(const Map1& m);

    void initData() override;
};


#endif //RAYCASTENGINE_MAP1_H
