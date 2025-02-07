#include "entity.h"
#include "camera.h"
#include "image.h"

// Renderiza la entidad en wireframe
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    if (!mesh.GetVertices().size() || !mesh.GetIndices().size() || !camera) return;

    for (size_t i = 0; i < mesh.GetIndices().size(); i += 3) {
        // Obtener los índices del triángulo
        int idx0 = mesh.GetIndices()[i];
        int idx1 = mesh.GetIndices()[i + 1];
        int idx2 = mesh.GetIndices()[i + 2];

        // Obtener los vértices en espacio local
        Vector3 v0 = mesh.GetVertices()[idx0];
        Vector3 v1 = mesh.GetVertices()[idx1];
        Vector3 v2 = mesh.GetVertices()[idx2];

        // Transformar los vértices a espacio mundial
        v0 = modelMatrix * v0;
        v1 = modelMatrix * v1;
        v2 = modelMatrix * v2;

        // Proyectar los vértices con la cámara
        bool negZ = false;
        v0 = camera->ProjectVector(v0, negZ);
        v1 = camera->ProjectVector(v1, negZ);
        v2 = camera->ProjectVector(v2, negZ);

        // Convertir coordenadas de clip space a screen space
        int x0 = (v0.x + 1.0f) * 0.5f * framebuffer->width;
        int y0 = (1.0f - v0.y) * 0.5f * framebuffer->height;
        int x1 = (v1.x + 1.0f) * 0.5f * framebuffer->width;
        int y1 = (1.0f - v1.y) * 0.5f * framebuffer->height;
        int x2 = (v2.x + 1.0f) * 0.5f * framebuffer->width;
        int y2 = (1.0f - v2.y) * 0.5f * framebuffer->height;

        // Dibujar las líneas del triángulo usando DDA
        framebuffer->DrawLineDDA(x0, y0, x1, y1, c);
        framebuffer->DrawLineDDA(x1, y1, x2, y2, c);
        framebuffer->DrawLineDDA(x2, y2, x0, y0, c);
    }
}
