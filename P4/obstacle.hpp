#include <vector>
#include "ray.hpp"
#include "emission.hpp"

#ifndef obstacle_HPP
#define obstacle_HPP

using namespace std;

class Obstacle{
    public:
        virtual bool ray_intersect(Ray& rayo, Emission& emite, float& distancia) const = 0;
};

#endif obstacle_HPP