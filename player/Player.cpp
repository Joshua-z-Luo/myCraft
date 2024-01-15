#include"Player.h"


Player::Player(int width, int height, glm::vec3 position)
{
	Player::width = width;
	Player::height = height;
	Position = position;
	updateBoundingBox();
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


void Player::MovePlayer(float frameSpeed, glm::vec3 direction)
{
	Position += frameSpeed * direction;
}



void Player::Inputs(GLFWwindow* window, double delta)
{
	// Binds speed to real time not frames per second.
	float frameSpeed = delta * speed;

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		MovePlayer(frameSpeed, glm::vec3(Orientation.x, 0.0f, Orientation.z));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MovePlayer(frameSpeed, -glm::normalize(glm::cross(Orientation, Up)));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		MovePlayer(frameSpeed, -glm::vec3(Orientation.x, 0.0f, Orientation.z));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{	
		MovePlayer(frameSpeed, glm::normalize(glm::cross(Orientation, Up)));
	}

	// Jump logic
	if (spacePressed == false && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inAir == false)
	{
		spacePressed = true;
		inAir = true;
		airSpeed = 10.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spacePressed = false;
	}

	if (inAir == true) {
		float velocityChange = delta * gravity;
		airSpeed = (airSpeed + velocityChange);
		if (airSpeed < -1.0f) {
			airSpeed = -1.0f;
		}
		fprintf(stdout, "%f \n", airSpeed);
		MovePlayer(airSpeed * delta, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else {
		airSpeed = 0.0f;
	}


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
	playerMaxY = Position.y + Constants::PLAYER_WIDTH;
	playerMaxZ = Position.z;
	playerMinX = Position.x - Constants::PLAYER_WIDTH;
	playerMinY = Position.y - Constants::PLAYER_WIDTH;
	playerMinZ = Position.z - Constants::BLOCK_SIZE - Constants::BLOCK_SIZE;
}
