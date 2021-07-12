#pragma once

#ifndef emission_HPP
#define emission_HPP

using namespace std;

struct Emission{
    float red;
    float green;
    float blue;

    Emission();
    Emission(float Ered, float Egreen, float Eblue);
    void getEmision(float& Rred, float& Rgreen, float& Rblue);

    Emission operator*(Emission e2) const;
    Emission operator*(float difusion) const;
    Emission operator/(float e) const;
};

#endif