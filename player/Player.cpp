#include"Player.h"

Player::Player(int width, int height, glm::vec3 position)
{
	Player::width = width;
	Player::height = height;
	Position = position;
	updateBoundingBox();
}

void Player::setCollision(float x, float y, float z)
{
	collision = glm::vec3(x, z, y);
}

void Player::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}


void Player::MovePlayer(glm::vec3 displacement)
{
	Position += displacement;
}

void Player::setPlayerMovement(float frameSpeed, glm::vec3 direction, float newAirSpeed)
{
	Direction = direction;
	speed = frameSpeed;
	airSpeed = newAirSpeed;
	fprintf(stdout, "setting: %f %f \n", Direction.y, airSpeed);
}

glm::vec3 Player::getDirection()
{
	return Direction;
}

float Player::getSpeed()
{
	return speed;
}

std::vector<glm::vec3> Player::broadSweep(std::vector<glm::vec3> blockCords)
{
	bool flag = false;
	std::vector<glm::vec3> result;
	for (int i = blockCords.size() - 1; i >= 0; i--) {
		glm::vec3 block = blockCords[i];
		if (playerMinX + (Direction.x * speed) <= block.x + Constants::BLOCK_SIZE && playerMaxX + (Direction.x * speed) >= block.x) {
			if (playerMinZ + (Direction.z * speed) <= block.y + Constants::BLOCK_SIZE && playerMaxZ + (Direction.z * speed) >= block.y) {
				// Check if in Air
				
				/*
				if (playerMinY + (Direction.y * airSpeed) <= block.z + (Constants::BLOCK_SIZE * 2) && playerMaxY + (Direction.y * airSpeed) >= block.z + Constants::BLOCK_SIZE) {
					result.push_back(block);
				}*/
				if (playerMinY + (Direction.y * airSpeed) <= block.z + (Constants::BLOCK_SIZE) && playerMaxY + (Direction.y * airSpeed) >= block.z) {
					result.push_back(block);
				}
			}
		}
		blockCords.pop_back();
	}
	return result;
}

float Player::sweeptAABB(std::vector<glm::vec3> blockCords)
{
	float minTime = 1.1f;
	int minBlock = NULL;
	bool groundBlock = false;

	float xInvEntry;
	float xInvExit;
	float yInvEntry;
	float yInvExit;
	float zInvEntry;
	float zInvExit;


	float xEntry, yEntry, zEntry;
	float xExit, yExit, zExit;


	float entryTime;
	float exitTime;

	glm::vec3 normal;

	for (int i = 0; i < blockCords.size(); i++) {
		glm::vec3 block = blockCords[i];
		if (Direction.x * speed > 0.0f)
		{
			xInvEntry = block.x - (playerMaxX);
			xInvExit = (block.x + Constants::BLOCK_SIZE) - playerMinX;
		}
		else
		{
			xInvEntry = (block.x + Constants::BLOCK_SIZE) - playerMinX;
			xInvExit = block.x - (playerMaxX);
		}

		if (Direction.z * speed > 0.0f)
		{
			yInvEntry = block.y - (playerMaxZ);
			yInvExit = (block.y + Constants::BLOCK_SIZE) - playerMinZ;
		}
		else
		{
			yInvEntry = (block.y + Constants::BLOCK_SIZE) - playerMinZ;
			yInvExit = block.y - (playerMaxZ);
		}
		
		if (Direction.y * airSpeed > 0.0f)
		{
			zInvEntry = block.z - (playerMaxY);
			zInvExit = (block.z + Constants::BLOCK_SIZE) - playerMinY;
		}
		else
		{
			zInvEntry = (block.z + Constants::BLOCK_SIZE) - playerMinY;
			zInvExit = block.z - (playerMaxY);
		}
		
		// 2nd step
		if (Direction.x * speed == 0.0f)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / (Direction.x * speed);
			xExit = xInvExit / (Direction.x * speed);
		}

		if (Direction.z * speed == 0.0f)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / (Direction.z * speed);
			yExit = yInvExit / (Direction.z * speed);
		}
		
		if (Direction.y * airSpeed == 0.0f)
		{
			zEntry = -std::numeric_limits<float>::infinity();
			zExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			zEntry = zInvEntry / (Direction.y * airSpeed);
			zExit = zInvExit / (Direction.y * airSpeed);
		}
		

		entryTime = std::max(xEntry, yEntry);
		entryTime = std::max(entryTime, zEntry);
		exitTime = std::min(xExit, yExit);
		exitTime = std::min(exitTime, zExit);


		if (entryTime <= exitTime && (xEntry >= 0.0f || yEntry >= 0.0f || zEntry >= 0.0f) && xEntry <= 1.0f && yEntry <= 1.0f && zEntry <= 1.0f)
		{
			// Track minimum collision time
			if (entryTime < minTime) {
				minTime = entryTime;

				// Check if we collision is on top of block
				// if so, toggle ground block
				if (zEntry >= 0.0f) {
					groundBlock = true;
				}
				else {
					groundBlock = false;
				}

				// For testing purposes
				minBlock = i;
			}
		}

	}
	if (minBlock != NULL) {
		glm::vec3 small = blockCords[minBlock];
	}
	if (groundBlock == true) {
		inAir = false;
	}
	else {
		inAir = true;
	}
	return minTime;

}



void Player::Inputs(GLFWwindow* window, double delta, std::vector<glm::vec3> blockCords)
{
	// Binds speed to real time not frames per second.
	speed = 0.0f;
	float newAirSpeed = 0.0f;
	glm::vec3 movementVector(0.0f, 0.0f, 0.0f);
	float frameSpeed = delta * 5.0f;

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		movementVector += glm::vec3(Orientation.x, 0.0f, Orientation.z);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		movementVector += -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		movementVector += -glm::vec3(Orientation.x, 0.0f, Orientation.z);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{	
		movementVector += glm::normalize(glm::cross(Orientation, Up));
	}
	
	// Jump logic
	
	if (spacePressed == false && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inAir == false)
	{
		spacePressed = true;
		inAir = true;
		airSpeed = 15.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spacePressed = false;
	}
	/*
	if (inAir == true) {
		float velocityChange = delta * gravity;
		newAirSpeed = (airSpeed + velocityChange) * delta;
		if (newAirSpeed < -2.0f) {
			newAirSpeed = -2.0f;
		}	
	
		if (newAirSpeed > 0.0f) {
			movementVector += Up;
		}
		else if (newAirSpeed < 0.0f) {
			movementVector += Down;
		}
		
	}
	else{
		newAirSpeed = 0.0f;
	}
	*/


	setPlayerMovement(frameSpeed, movementVector, abs(newAirSpeed));


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}
		 
		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}


	std::vector<glm::vec3> broadPhase = broadSweep(blockCords);
	float collisiontime = sweeptAABB(broadPhase);
	// calculate movement
	glm::vec3 displacement = speed * Direction;
	displacement.y = airSpeed * Direction.y;
	displacement = displacement * collisiontime;
	//fprintf(stdout, "displace: %f \n", displacement.y);
	fprintf(stdout, "inAir: %d %f\n", inAir, airSpeed);


	MovePlayer(displacement);


}

void Player::GetMouseCoordinates(GLFWwindow* window, double& mouseX, double& mouseY)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);
}


bool Player::castRayForBlock(GLFWwindow* window, Ray ray, const glm::vec3& blockPosition, const std::vector<glm::vec3>& triangles)
{

	for (int i = 0; i < triangles.size(); i += 3)
	{
		glm::vec3 v0 = triangles[i];
		glm::vec3 v1 = triangles[i + 1];
		glm::vec3 v2 = triangles[i + 2];

		//glm::vec3 v0 = triangles[i] + blockPosition;
		//glm::vec3 v1 = triangles[i + 1] + blockPosition;
		//glm::vec3 v2 = triangles[i + 2] + blockPosition;

		float t;
		if (ray.rayIntersectsBlock(v0, v1, v2, t))
		{
			// Intersection found with this triangle
			return true;
		}
	}

	// No intersection with any triangle
	return false;
}

Ray Player::GetMouseRay(GLFWwindow* window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	double mouseX, mouseY;
	GetMouseCoordinates(window, mouseX, mouseY);

	// Convert mouse coordinates to normalized device coordinates
	float x = (2.0f * mouseX) / width - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / height;

	glm::mat4 inverseProjection = glm::inverse(projectionMatrix);
	glm::mat4 inverseView = glm::inverse(viewMatrix);

	glm::vec4 rayClip = glm::vec4(x, y, -1.0, 1.0);
	glm::vec4 rayEye = inverseProjection * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

	glm::vec4 rayWorld = inverseView * rayEye;
	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

	return Ray(Position, rayDirection);
}

glm::mat4 Player::getView()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(Position, Position + Orientation, Up);
	return view;
}

glm::mat4 Player::getProjection(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	return projection;
}

void Player::updateBoundingBox()
{
	//fprintf(stdout, "%f %f %f \n", playerMaxX, Position.x, Position.x + Constants::BLOCK_SIZE);
	playerMaxX = Position.x + Constants::PLAYER_WIDTH;
	playerMaxY = Position.y;
	playerMaxZ = Position.z + Constants::PLAYER_WIDTH;
	playerMinX = Position.x - Constants::PLAYER_WIDTH;
	playerMinY = Position.y - Constants::BLOCK_SIZE;
	playerMinZ = Position.z - Constants::PLAYER_WIDTH;
}
