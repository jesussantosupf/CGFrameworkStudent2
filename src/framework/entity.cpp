#include "entity.h"
#include "camera.h"

// Constructores
Entity::Entity(const Mesh& m) : mesh(m), modelMatrix(Matrix44()) {}

Entity::Entity(const Matrix44& mm) : mesh(), modelMatrix(mm) {}

Entity::Entity(const Mesh& m, const Matrix44& mm) : mesh(m), modelMatrix(mm) {}

// Método Render basado en el enunciado
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    if (!mesh.GetVertices().size() || !camera) return;

    for (const auto& vertex : mesh.GetVertices()) {
        Vector3 worldVertex = modelMatrix * vertex;
        bool negZ = false;
        Vector3 screenVertex = camera->ProjectVector(worldVertex, negZ);

        if (!negZ) {
            int x = (screenVertex.x + 1.0f) * 0.5f * framebuffer->width;
            int y = (1.0f - screenVertex.y) * 0.5f * framebuffer->height;
            framebuffer->SetPixel(x, y, c);
        }
    }
}
