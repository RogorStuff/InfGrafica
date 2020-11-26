#ifndef material_HPP
#define material_HPP

enum MATERIAL_TYPE {
    EMITTER,
    REFLECTOR
};

struct Reflectance {
    const Pixel kd; // Refraction (delta BTDF)
    const Pixel ks; // Specular (delta BRDF)
    const Pixel kdPhong; //Phong BRDF
    const Pixel ksPhong; // Phong BRDF
    const float s; // Shininess
};

/**
 * EMMITER
 * Light area
 *
 * REFLECTOR
 * Reflector material
 * Perfect Diffuse material: kd = 0 AND ks = 0 AND ksPhong = kdPhong
 * Perfect Phong material: kd = 0 AND ks = 0
 * Perfect Delta material: kdPhong = 0 AND ksPhong = 0
 * Perfect Refractor material: ks = 0 AND kdPhong = 0 AND ksPhong = 0
 * Perfect Specular material: kd = 0 AND kdPhong = 0 AND ksPhong = 0
 */
typedef struct {
    const MATERIAL_TYPE type;
    const Reflectance reflectance;
} Material;

/**
 * Creates an emmiter material
 * @return the emmiter as material
 */
Material Emitter();

/**
 * Creates a Reflector material
 * @return the Reflector material
 */
Material Reflector(const Pixel &kd, const Pixel &ks, float s, const Pixel &kdPhong, const Pixel &ksPhong);

/**
 * Creates a perfect Phong material
 * @return the perfect Phong material
 */
Material Phong(const Pixel &kdPhong, const Pixel &ksPhong, float s);

/**
 * Creates a perfect diffuse Delta material
 * @return the perfect diffuse Delta material
 */
Material Diffuse(const Pixel &k);

/**
 * Creates a perfect Delta material
 * @return the perfect Delta material
 */
Material Delta(const Pixel &kd, const Pixel &ks);

/**
 * Creates a perfect Refractor material
 * @return the perfect Refractor material
 */
Material Refractor(const Pixel &kd);

/**
 * Creates a perfect Specular material
 * @return the perfect Specular material
 */
Material Specular(const Pixel &ks);

#endif