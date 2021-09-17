#pragma once

#include "emission.hpp"
#include <vector>

using namespace std;

#ifndef pixel_HPP
#define pixel_HPP

class Pixel {
    public:
        float R;
        float G;
        float B;
        bool impacto;

        Pixel();
        Pixel(float Rgb, float rGb, float rgB);
        Pixel(Emission emision);

        void update(Emission emision);
        void update(float Rgb, float rGb, float rgB);
        void divideTotal(int divisor);
        void multiplicaTotal(float multiplicador);
        void multiplicaTotal(Emission multiplicador);

        bool escero();

        void nuevoImpacto(bool impactoN);
        bool dameImpacto();

        Pixel GammaCurve(float gamma, float max, float m, float c);
};

#endif