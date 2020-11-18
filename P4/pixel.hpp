#include "emission.hpp"

using namespace std;

#ifndef pixel_HPP
#define pixel_HPP

class Pixel {
    public:
        float R;
        float G;
        float B;

        Pixel();
        Pixel(float Rgb, float rGb, float rgB);
        Pixel(Emission emision);

        void update(Emission emision);
        void update(float Rgb, float rGb, float rgB);
        void divideTotal(int divisor);
        Pixel GammaCurve(float gamma, float max, float m, float c);
};

#endif pixel_HPP