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


	// NEED UPDATE
	// CAN'T RETURN AN ARRAY IN C++ ONLY POINTER TO FIRST ELEMENT ITS JOEVER
	GLfloat* getVert();
	GLuint* getInd();
	glm::vec3* getTriangles();

	GLfloat vertices[192];
	GLuint indices[36];
};

