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

class Block
{
protected:
	
public:
	Block(GLfloat x, GLfloat y, GLfloat z);

	glm::vec3 getBlockCords();
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat* getVert();
	GLuint* getInd();
	glm::vec3* getTriangles();

	GLfloat vertices[64];
	GLuint indices[36];
};

