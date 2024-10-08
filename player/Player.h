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
#include "deque"
#include <array>
#include <limits>
#include <string>
#include <algorithm>

#include "../constants.h"
#include "../gameLogic/DestroyPacket.h"
#include "../gameLogic/AddPacket.h"
#include "../entities/header/Model/Triangle.h"

/*
Player class. Replaces Camera class.
*/
class Player
{
private:
	// Stores the width and height of the window
	int width;
	int height;

	// Axis-Aligned Bounding Box values
	GLfloat playerMaxX;
	GLfloat playerMaxY;
	GLfloat playerMaxZ;
	GLfloat playerMinX;
	GLfloat playerMinY;
	GLfloat playerMinZ;

	// inventory
	// for tuple, first value is amount, 2nd value is amount
	std::array <std::array<int, 2>, 20> inventoryArray;
	int selectedSlot = -1;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Player movement properties
	float speed = 0.0f;
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);
	float airSpeed = 0.0f;
	float gravity = -9.0f;

	// Camera look speed
	float sensitivity = 100.0f;

	// player status logic
	bool spacePressed = false;
	bool inAir = false;
	bool menu = false;
	bool inventory = false;

	// key Pressed?
	bool pPressed = false;
	bool escPressed = false;
	bool tabPressed = false;


public:
	// Handles camera inputs
	void Inputs(GLFWwindow* window, float delta, std::vector<glm::vec3> blockCords, std::vector<Triangle> playerVerts, std::deque<std::unique_ptr<UpdatePacket>>* updateQue, int posX, int posY);

	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Down = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Camera constructor to set up initial values
	Player(int width, int height, glm::vec3 position);

	// Split movement into inputs and move function for better organization
	void MovePlayer(glm::vec3 displacement);


	glm::vec3 getOrientation();

	// Set player movement for collision detection
	void setPlayerMovement(float frameSpeed, glm::vec3 direction, float newAirSpeed);
	glm::vec3 getDirection();
	float getSpeed();

	// Collision Detection
	/*
	Use broadSweep to filter out unimportant blocks for sweptAABB and reduce computational load
	*/
	std::vector<glm::vec3> broadSweep(std::vector<glm::vec3> blockCords, float delta);
	float sweeptAABB(std::vector<glm::vec3> blockCords, glm::vec3& normalForces, float delta);
	void detectCollison(float delta, std::vector<glm::vec3> blockCords);
	void detectCollisonHelper(float delta, std::vector<glm::vec3> blockCords, glm::vec3 normalForces, float remainingtime);

	// Check if grounded
	void grounded(std::vector<glm::vec3> blockCords);

	// inventory logic
	void addItemToInventory(int blockID, int amount);
	void removeItemFromInventory( int amount, int slot);
	std::array <std::array<int, 2>, 20> getInventory();
	int getSelectedSlot();
	void setSelectedSlot(int index);

	// Ray logic
	// when it finds a block to commti an action to, it appends it to a que of actions to be completed by the chunk managaer
	bool castRayForBlock(GLFWwindow* window, Ray ray, const glm::vec3& blockPosition, const std::vector<Triangle>& triangles);
	int castRayForBlockPlace(GLFWwindow* window, Ray ray, const glm::vec3& blockPosition, std::vector<Triangle> triangles);
	Ray GetMouseRay(GLFWwindow* window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void GetMouseCoordinates(GLFWwindow* window, double& mouseX, double& mouseY);
	glm::mat4 getView();
	glm::mat4 getProjection(float FOVdeg, float nearPlane, float farPlane);

	// update bounding box on move
	void updateBoundingBox();

	// Updates and exports the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);


	// Exports Frustum Planes of player
	std::vector<glm::vec4> extractFrustumPlanes();
	std::vector<glm::vec4> extractFrustumPlanes(const glm::mat4& viewProjectionMatrix);

	// Get menu status
	bool isMenuOpen();
	bool isInventoryOpen();
};

#endif