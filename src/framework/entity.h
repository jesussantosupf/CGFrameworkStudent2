#pragma once

#include "mesh.h"
#include "image.h"

class Entity {
private:
    Mesh mesh;
    Matrix44 modelMatrix;

public:
    // Constructores corregidos
    Entity() {}
    Entity(const Mesh& m);
    Entity(const Matrix44& mm);
    Entity(const Mesh& m, const Matrix44& mm);

    // Método de renderizado sin "Entity::"
    void Render(Image* framebuffer, Camera* camera, const Color& c);
};
