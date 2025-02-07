#pragma once

#include "mesh.h"
#include "image.h"
#include "camera.h"

class Entity {
private:
    Mesh mesh;
    Matrix44 modelMatrix;

public:
    // Constructores
    Entity();
    Entity(const Mesh& m);
    Entity(const Matrix44& mm);
    Entity(const Mesh& m, const Matrix44& mm);

    // Renderizado en wireframe
    void Render(Image* framebuffer, Camera* camera, const Color& color);
};
