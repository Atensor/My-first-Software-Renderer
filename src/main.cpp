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

constexpr int WIDTH{800}, HEIGHT{600};
constexpr int RENDER_WIDTH{800}, RENDER_HEIGHT{600};

int main() {
	// ========================================================================
	// Window init
	// ========================================================================
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init Failed: " << SDL_GetError() << "\n";

		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Software Renderer", WIDTH, HEIGHT,
	                                      SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';

		SDL_Quit();
		return 1;
	}
	SDL_MaximizeWindow(window);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

	if (!renderer) {
		std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';

		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                                         SDL_TEXTUREACCESS_STREAMING,
	                                         RENDER_WIDTH, RENDER_HEIGHT);

	if (!texture) {
		std::cerr << "SDL_CreateTexture failed: " << SDL_GetError() << '\n';

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// ========================================================================
	// ImGui init
	// ========================================================================
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGuiIO &io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	if (!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer)) {
		std::cerr << "ImGui SDL3 initialization failed\n";
		return 1;
	}

	if (!ImGui_ImplSDLRenderer3_Init(renderer)) {
		std::cerr << "ImGui SDL renderer initialization failed\n";
		return 1;
	}

	// ========================================================================
	// Renderer init
	// ========================================================================
	std::unique_ptr<Framebuffer> buffer =
	    std::make_unique<Framebuffer>(RENDER_WIDTH, RENDER_HEIGHT);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(
	    Camera(1.0f, Float2{(float)RENDER_WIDTH, (float)RENDER_HEIGHT}));
	scene->sky_light_dir = Float3(1, -1, -1);
	scene->use_lighting = true;

	for (const auto &entry : std::filesystem::directory_iterator("models/")) {
		/*
		if (entry == std::filesystem::path("models/Dragon.obj"))
		    continue;
		*/
		scene->meshes.emplace_back(
		    std::make_unique<Mesh>(Obj::parse_obj(entry.path())));
	}

	// Cube Object
	auto cube = Mesh::find_mesh(scene->meshes, "cube");
	if (cube != nullptr) {
		scene->objects.emplace_back(
		    std::make_unique<SceneObject>(SceneObject(cube)));

		scene->objects.back()->normals_as_color = true;
		scene->objects.back()->translate = Float3{-2, 0, 5};
		scene->objects.back()->rotate.x = 45.0f;
		scene->objects.back()->rotate.y = -35.0f;
		scene->objects.back()->scalar = 0.8f;

		scene->objects.back()->draw = false;
	} else {
		printf("Cube didn't load!");
	}

	// Monkey object
	auto suzanne = Mesh::find_mesh(scene->meshes, "suzanne");
	if (suzanne != nullptr) {
		scene->objects.emplace_back(
		    std::make_unique<SceneObject>(SceneObject(suzanne)));

		scene->objects.back()->color = Float3(
		    0.3921568627450980f, 0.5843137254901961f, 0.9294117647058824f);
		scene->objects.back()->translate = Float3{0.5f, 0, 3};
		scene->objects.back()->rotate.x = 180.0f;

		scene->objects.back()->draw = false;
	} else {
		printf("Suzanne didn't load!");
	}

	auto dragon = Mesh::find_mesh(scene->meshes, "dragon");
	if (dragon != nullptr) {
		scene->objects.emplace_back(
		    std::make_unique<SceneObject>(SceneObject(dragon)));

		scene->objects.back()->color = Float3(
		    0.3921568627450980f, 0.5843137254901961f, 0.9294117647058824f);
		scene->objects.back()->translate.z = 5.0f;
		scene->objects.back()->scalar = 0.02f;
		scene->objects.back()->rotate.x = 180.0f;

		scene->objects.back()->draw = true;
	} else {
		printf("Dragon didn't load!");
	}

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

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

		ImGui::Begin("Meshes");

		ImGui::Text("Loaded Meshes");
		ImGui::Separator();

		for (size_t i = 0; i < scene->meshes.size(); i++) {
			Mesh *mesh = scene->meshes.at(i).get();

			if (ImGui::TreeNode(mesh->name.c_str())) {
				ImGui::Text("%s", mesh->name.c_str());

				ImGui::Separator();

				ImGui::Text("Mesh Info");

				ImGui::Text("Vertices: %zu", mesh->positions.size());
				ImGui::Text("Faces: %zu", mesh->faces.size());

				std::string button_str = "Create new " + mesh->name;
				if (ImGui::Button(button_str.c_str())) {
					scene->objects.emplace_back(
					    std::make_unique<SceneObject>(SceneObject(mesh)));
				}
				ImGui::TreePop();
			}
		}

		// ---- Scene list ----
		ImGui::Text("Scene Objects");
		ImGui::Separator();

		ImGui::Checkbox("use Lighting", &scene->use_lighting);

		ImGui::Checkbox("use culling", &scene->use_culling);

		ImGui::Checkbox("Draw normals", &scene->draw_normals);

		ImGui::Separator();

		for (size_t i = 0; i < scene->objects.size(); ++i) {
			SceneObject *object = scene->objects[i].get();

			std::string name = object->mesh->name + std::to_string(i);

			if (ImGui::TreeNode(name.c_str())) {
				ImGui::Text("Inspector");
				ImGui::Separator();

				ImGui::Checkbox("Draw Object", &object->draw);

				ImGui::Checkbox("Use normals as color",
				                &object->normals_as_color);

				ImGui::Text("Position");
				ImGui::DragFloat3("##position", &object->translate.x, 0.1f);

				ImGui::Text("Rotation");
				ImGui::DragFloat3("##rotation", &object->rotate.x, 0.1f);

				ImGui::Text("Scale");
				ImGui::DragFloat("##scale", &object->scalar, 0.001f);

				ImGui::Text("Color");
				ImGui::ColorEdit3("##color", &object->color.r);

				ImGui::Separator();

				if (ImGui::Button("Delete")) {
					scene->objects.erase(scene->objects.begin() + i);
				}
				ImGui::TreePop();
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
		                  RENDER_WIDTH * sizeof(uint32_t));

		ImGui::Begin("Renderer");

		ImGui::Image((ImTextureID)texture, ImVec2(RENDER_WIDTH, RENDER_HEIGHT));

		ImGui::End();

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
