#ifndef RAYCASTENGINE_ENGINEUTILS_H
#define RAYCASTENGINE_ENGINEUTILS_H
#include <cmath>

// Custom approximation function, needed to correctly display stuff; raylib draw functions can't take floats
inline int fapprox(float val) {
    if(val - (int)val >= 0.5)
        return (int)val+1;
    else return (int)val;
}

inline int fapprox(double val) {
    if(val - (int)val >= 0.5)
        return (int)val+1;
    else return (int)val;
}

// Degrees to radians conversion
inline double degToRad(double angleInDegrees)
{
    return (angleInDegrees) * M_PI / 180.0;
}


template <typename T>
inline void clampAngle(T& angle)
{
    if(angle >= 361)
        angle = 0;
    if(angle < 0)
        angle = 360;
}

#endif //RAYCASTENGINE_ENGINEUTILS_H
