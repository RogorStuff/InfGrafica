#include "material.hpp"
#include "pixel.hpp"

Material Emitter() {
    return Material {
            .type = EMITTER
    };
}

Material Reflector(Pixel &kd, Pixel &ks, const float s, Pixel &kdPhong, Pixel &ksPhong) {
    return Material {
            .type = REFLECTOR,
            .reflectance = {.kd = kd, .ks = ks, .kdPhong = kdPhong, .ksPhong = ksPhong, .s = s}
    };
}

Material Phong(const Pixel &kdPhong, const Pixel &ksPhong, const float s) {
    return Reflector(Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0), s, kdPhong, ksPhong);
}

Material Diffuse(const Pixel &k) {
    return Phong(k, Pixel(0.0,0.0,0.0), 1);
}

Material Delta(const Pixel &kd, const Pixel &ks) {
    return Reflector(kd, ks, 1, Pixel(0.0,0.0,0.0), Pixel(0.0,0.0,0.0));
}

Material Refractor(const Pixel &kd) {
    return Delta(kd, Pixel(0.0,0.0,0.0));
}

Material Specular(const Pixel &ks) {
    return Delta(Pixel(0.0,0.0,0.0), ks);
}