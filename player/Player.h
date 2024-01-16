#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

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



/*
Player class. Replaces Camera class.
*/
class Player
{
public:
	// Axis-Aligned Bounding Box values
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

	// Player movement properties
	float speed = 5.0f;
	float airSpeed = 0.0f;
	float gravity = -9.0f;
	
	// Camera look speed
	float sensitivity = 100.0f;

	// player status logic
	bool inAir = true;
	bool spacePressed = false;

	// REPLACE inAir WITH COLLISION LOGIC IN FUTURE
	glm::vec3 collision = glm::vec3(0.0f, 0.0f, 0.0f);

	// Camera constructor to set up initial values
	Player(int width, int height, glm::vec3 position);

	void setCollision(float x, float y, float z);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

	// Split movement into inputs and move function for better organization
	void MovePlayer(float frameSpeed, glm::vec3 direction);

	// Handles camera inputs
	void Inputs(GLFWwindow* window, double delta);

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