#include "obj/Obj.h"
#include "render/Renderer.h"
#include "render/Scene.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include <stdint.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Failed: " << SDL_GetError() << "\n";

        return 1;
    }

    constexpr int WIDTH{800}, HEIGHT{600};
    SDL_Window *window =
        SDL_CreateWindow("Software Rasterizer", WIDTH, HEIGHT, 0);

    if (!window) {
        std::cerr << SDL_GetError() << "\n";

        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Texture *texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    std::unique_ptr<Framebuffer> buffer =
        std::make_unique<Framebuffer>(WIDTH, HEIGHT);

    std::unique_ptr<Scene> scene = std::make_unique<Scene>(
        Camera(1.0f, Float2{(float)WIDTH, (float)HEIGHT}));
    scene->sky_light_dir = Float4(1, -1, -1, 0);
    scene->use_lighting = true;

    // Cube Object
    scene->meshes.emplace_back(
        std::make_unique<Mesh>(Obj::parse_obj("Cube.obj")));
    scene->objects.emplace_back(
        std::make_unique<SceneObject>(SceneObject(scene->meshes.back().get())));

    scene->objects.back()->normals_as_color = true;
    scene->objects.back()->translate = Float4{-2, 0, 5, 0};
    scene->objects.back()->rotate_x = 45.0f;
    scene->objects.back()->rotate_y = -35.0f;
    scene->objects.back()->scalar = 0.8f;

    scene->objects.back()->draw = true;

    // Monkey object
    scene->meshes.emplace_back(
        std::make_unique<Mesh>(Obj::parse_obj("monkey.obj")));
    scene->objects.emplace_back(
        std::make_unique<SceneObject>(SceneObject(scene->meshes.back().get())));

    scene->objects.back()->color = Float4(
        0.3921568627450980f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);
    scene->objects.back()->translate = Float4{0.5f, 0, 3, 0};
    scene->objects.back()->rotate_x = 180.0f;
    scene->objects.back()->rotate_y = 0.0f;

    scene->objects.back()->draw = true;

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Meshes");

        ImGui::Text("Scene Objects");
        ImGui::Separator();

        static int selected = -1;

        // ---- Scene list ----
        for (int i = 0; i < scene->objects.size(); i++) {

            char label[64];
            std::snprintf(label, sizeof(label), "Mesh %d", i);

            if (ImGui::Selectable(label, selected == i)) {
                selected = i;
            }
        }

        ImGui::Checkbox("use Lighting", &scene->use_lighting);

        ImGui::Checkbox("use culling", &scene->use_culling);

        ImGui::Checkbox("Draw normals", &scene->draw_normals);

        ImGui::Separator();

        // ---- Inspector ----
        if (selected >= 0 && selected < scene->objects.size()) {

            SceneObject *obj = scene->objects[selected].get();

            ImGui::Text("Inspector");
            ImGui::Separator();

            ImGui::Checkbox("Draw Object", &obj->draw);

            ImGui::Checkbox("Use normals as color", &obj->normals_as_color);

            ImGui::Text("Transform");

            ImGui::DragFloat3("Position", &obj->translate.x, 0.1f);

            ImGui::DragFloat("Scale", &obj->scalar, 0.1f);

            ImGui::DragFloat2("Rotation", &obj->rotate_x, 0.1f);

            ImGui::Separator();

            ImGui::Text("Mesh Info");

            if (obj->mesh) {
                ImGui::Text("Vertices: %zu", obj->mesh->vertices.size());
                ImGui::Text("Faces: %zu", obj->mesh->faces.size());
            } else {
                ImGui::Text("No mesh assigned");
            }

            ImGui::Separator();

            if (ImGui::Button("Delete")) {
                scene->objects.erase(scene->objects.begin() + selected);
                selected = -1;
            }
        }

        ImGui::End();

        ImGui::Begin("Performance");

        // ---- FPS / frame timing ----
        float deltaTime = ImGui::GetIO().DeltaTime;
        float fps = 1.0f / deltaTime;

        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Frame Time: %.3f ms", deltaTime * 1000.0f);

        // ---- optional: scene stats ----
        ImGui::Separator();

        ImGui::Text("Objects: %zu", scene->objects.size());

        // If you have mesh stats:
        size_t triangles = 0;
        for (auto &obj : scene->objects) {
            if (obj->mesh)
                triangles += obj->mesh->faces.size();
        }

        ImGui::Text("Triangles: %zu", triangles);

        ImGui::End();

        ImGui::Begin("Camera");

        ImGui::DragFloat3("Position", &scene->camera.pos.x, 0.1f);

        ImGui::DragFloat2("Rotation", &scene->camera.rotate_x, 0.1f);

        ImGui::DragFloat3("Sky Light dir", &scene->sky_light_dir.x, 0.1f);

        ImGui::End();

        scene->render(buffer);

        SDL_UpdateTexture(texture, nullptr, buffer->buffer,
                          WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
        buffer->clear();
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
