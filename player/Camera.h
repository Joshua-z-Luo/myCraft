#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"../shaders/shaderClass/shaderClass.h"
#include "Ray.h"
#include "vector"

#include "../constants.h"

class Camera
{
public:
	// Axis-Aligned Bounding Box
	GLfloat playerMaxX;
	GLfloat playerMaxY;
	GLfloat playerMaxZ;
	GLfloat playerMinX;
	GLfloat playerMinY;
	GLfloat playerMinZ;


	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
	
	// when it finds a block to commti an action to, it appends it to a que of actions to be completed by the chunk managaer
	bool castRayForBlock(GLFWwindow* window, Ray ray, const glm::vec3& blockPosition, const std::vector<glm::vec3>& triangles);
	Ray GetMouseRay(GLFWwindow* window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void GetMouseCoordinates(GLFWwindow* window, double& mouseX, double& mouseY);
	glm::mat4 getView();
	glm::mat4 getProjection(float FOVdeg, float nearPlane, float farPlane);

	// update bounding box on move
	void updateBoundingBox();

};


#endif