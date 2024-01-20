#pragma once

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <tuple>
#include <vector>
#include"header/Mesh.h"

class Block
{
protected:
	
public:
	Block(GLfloat x, GLfloat y, GLfloat z);


	// NEED UPDATE
	// CAN'T RETURN AN ARRAY IN C++ ONLY POINTER TO FIRST ELEMENT ITS JOEVER
	GLfloat* getVert();
	GLuint* getInd();
	glm::vec3* getTriangles();

	GLfloat vertices[192];
    std::vector<Vertex> verticesAdjusted;
    Vertex baseVertices[24] = {
        // Top face
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
        { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

            // Bottom face
        { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

            // Front face
        { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

            // Right face
        { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

            // Back face
        { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

            // Left face
        { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },
    };
	GLuint indices[36];
};

