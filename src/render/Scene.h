#include "../geometry/SceneObject.h"
#include "Camera.h"
#include "Renderer.h"

#ifndef SCENE_H
#define SCENE_H

struct Scene {
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<SceneObject>> objects;

    Camera camera;

    Float4 sky_light_dir;

    Scene(const Camera &camera);

    void render(std::unique_ptr<Framebuffer> &buffer) const;
};
#endif
