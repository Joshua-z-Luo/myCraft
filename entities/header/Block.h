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
#include"header/Model/Mesh.h"
#include "../../shaders/EBO.h"
#include "../../shaders/VBO.h"
#include "../../shaders/VAO.h"
#include <utility> 
#include <memory>
#include "../../Texture.h"
#include "header/Model/Triangle.h"
#include "../../player/Player.h"


class Block
{
protected:
    std::unique_ptr<Mesh> mesh;
    int id;
    Vertex baseVertices[24] = {
        // Top face 
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
        { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

        // Bottom face
        { glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

        // Front face
        { glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

        // Right face
        { glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

        // Back face
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },

        // Left face
        { glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f) },
    };
    GLuint indices[36];
	
public:
	Block(GLfloat x, GLfloat y, GLfloat z, int id);

    
    int getID();
    Vertex* getVert();
	glm::vec3 getBlockCords();
	GLfloat x;
	GLfloat y;
	GLfloat z;

	//GLfloat* getVert();
	GLuint* getInd();
    Triangle * getTriangles();

    void createMesh(Texture * texture[2]);
    void drawMesh(Shader& shader, Player& camera);
    

};

