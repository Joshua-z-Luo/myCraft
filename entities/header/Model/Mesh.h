#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"../Texture.h"
#include"../shaders/shaderClass/shaderClass.h"
#include"../shaders/VAO.h"
#include"../shaders/VBO.h"
#include"../shaders/EBO.h"
#include"../player/player.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader, Player& camera);
};
#endif