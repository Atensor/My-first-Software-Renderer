#include "SceneObject.h"

SceneObject::SceneObject(Mesh *mesh)
    : mesh(mesh), translate(Float4(0, 0, 0, 1)), scalar(1.0f), rotate_x(0.0f),
      rotate_y(0.0f), normals_as_color(false), draw(true),
      color(Float4(1, 1, 1, 1)) {}

SceneObject::~SceneObject() = default;

std::array<Vertex, 3> SceneObject::get_Face_Vertices(int i) const {
    return std::array<Vertex, 3>{
        Vertex{mesh->vertices.at(mesh->faces.at(i).vertex_index.at(0) - 1),
               mesh->normals.at(mesh->faces.at(i).normal_index.at(0) - 1),
               Float4(0, 0, 0, 1), 1.0f},
        Vertex{mesh->vertices.at(mesh->faces.at(i).vertex_index.at(1) - 1),
               mesh->normals.at(mesh->faces.at(i).normal_index.at(1) - 1),
               Float4(0, 0, 0, 1), 1.0f},
        Vertex{mesh->vertices.at(mesh->faces.at(i).vertex_index.at(2) - 1),
               mesh->normals.at(mesh->faces.at(i).normal_index.at(2) - 1),
               Float4(0, 0, 0, 1), 1.0f}};
}

std::array<Float2, 3> SceneObject::get_Face_Texture_Coordinates(int i) const {
    return std::array<Float2, 3>{
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(0) - 1),
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(1) - 1),
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(2) - 1)};
}

Matrix4 SceneObject::get_translation_matrix() const {
    return Transform::translate(translate);
}

Matrix4 SceneObject::get_rotation_matrix() const {
    return Transform::rotate_y(rotate_y) * Transform::rotate_x(rotate_x);
}

Matrix4 SceneObject::get_scalar_matrix() const {
    return Transform::scale(scalar);
}
