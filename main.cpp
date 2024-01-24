#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"Texture.h"
#include"shaders/shaderClass/shaderClass.h"
#include"shaders/VAO.h"
#include"shaders/VBO.h"
#include"shaders/EBO.h"
#include"player/Camera.h"
#include"player/Player.h"

#include"entities/header/Block.h"
#include "entities/header/Map.h"
#include "gameLogic/UpdatePacket.h"

#include "constants.h"

#include"entities/header/Mesh.h"



const unsigned int width = 800;
const unsigned int height = 800;

GLfloat x = 0;
GLfloat y = 0;
GLfloat z = 0;


Vertex vertices[] =
{
	// Top face
	{glm::vec3(x - 0.5f, z + 0.5f, y - 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y - 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y + 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z + 0.5f, y + 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

	// Bottom face
	{glm::vec3(x - 0.5f, z - 0.5f, y + 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x + 0.5f, z - 0.5f, y + 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z - 0.5f, y - 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z - 0.5f, y - 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

	// Front face
	{glm::vec3(x - 0.5f, z - 0.5f, y + 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x + 0.5f, z - 0.5f, y + 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y + 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z + 0.5f, y + 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

	// Right face
	{glm::vec3(x + 0.5f, z - 0.5f, y + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x + 0.5f, z - 0.5f, y - 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y - 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

	// Back face
	{glm::vec3(x + 0.5f, z - 0.5f, y - 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x - 0.5f, z - 0.5f, y - 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z + 0.5f, y - 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x + 0.5f, z + 0.5f, y - 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

	// Left face
	{glm::vec3(x - 0.5f, z - 0.5f, y + 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(x - 0.5f, z - 0.5f, y - 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z + 0.5f, y - 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(x - 0.5f, z + 0.5f, y + 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLint indices[] =
{
	// Top face
	16, 17, 18, 18, 19, 16,

	// Front face
	0, 1, 2, 2, 3, 0,

	// Left face
	12, 13, 14, 14, 15, 12,

	// Back face
	4, 5, 6, 6, 7, 4,

	// Right face
	8, 9, 10, 10, 11, 8,

	// Bottom face
	20, 21, 22, 22, 23, 20
};

Vertex lightVertices[] =
{
	// Updated coordinates to make the light block 0.5 times in size
	Vertex{glm::vec3(-0.5f, -0.5f,  0.5f)},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f)},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f)},
	Vertex{glm::vec3(0.5f, -0.5f,  0.5f)},
	Vertex{glm::vec3(-0.5f,  0.5f,  0.5f)},
	Vertex{glm::vec3(-0.5f,  0.5f, -0.5f)},
	Vertex{glm::vec3(0.5f,  0.5f, -0.5f)},
	Vertex{glm::vec3(0.5f,  0.5f,  0.5f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "MyCraft"
	GLFWwindow* window = glfwCreateWindow(width, height, "MyCraft", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Texture data

	Texture textures[]
	{
		Texture(("textures/grass.png"), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture(("textures/grass.png"), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture texturesBrick[]
	{
		Texture(("textures/brick.png"), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture(("textures/brick.png"), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	// Initalize map on heap
	Map* map = new Map(1);
	map->addChunk(0);
	map->loadMap();
	//std::vector<GLfloat> vect = map->getVerts();
	//std::vector<GLuint> indi =->getInds();


	// Store mesh data in vectors for the mesh
	//std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	//std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex1(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create block mesh
	//Mesh block(verts, ind, tex);




	// Shader for light cube
	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, tex1);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(2.0f, 20.0f, 2.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	

	
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	// x z y
	Player camera(width, height, glm::vec3(0.0f, 50.0f, 0.0f));

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	int posX = 0;
	int posY = 0;

	std::deque<UpdatePacket> updateQue;
	std::vector<glm::vec3> playerVerts;

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	std::vector<glm::vec3> blockCords = map->getBlockCordinates();
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		bool updateFlag = false;
		while (updateQue.size() > 0) {
			UpdatePacket target = updateQue[0];
			glm::vec3 deleteBlock = target.getTargetBlock();

			map->removeBlockFromChunk(target.getChunkX(), target.getChunkY(), deleteBlock.x, deleteBlock.y, deleteBlock.z);
			updateQue.pop_front();
			updateFlag = true;
		}


		int newX = static_cast<int>(round((camera.Position.x - 16) / Constants::CHUNK_SIZE));
		int newY = static_cast<int>(round((camera.Position.z - 16) / Constants::CHUNK_SIZE));
		if (newX != posX || newY != posY) {

			//fprintf(stdout, "%d %d \n", newX, newY);
			map->playerPositionCord(newX, newY);
			map->addChunk(-1);
			map->printChunks();
			posX = newX;
			posY = newY;
			updateFlag = true;
		}

		if (updateFlag == true) {
			map->updateMap(0, 0);
			blockCords = map->getBlockCordinates();
		}
		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "MyCraft - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}

		// Specify the color of the background
		glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// update current position of player hitbox
		camera.updateBoundingBox();
		// Handles camera inputs
		// Collision self contained with player class.
		if (updateFlag != true) {
			playerVerts = map->getPlayerChunk(camera.Position);
			camera.Inputs(window, timeDiff, blockCords, &playerVerts, &updateQue, posX, posY);
		}
		//%TODO: Player is gets stuck in blocks when a frame where new chunks must be loaded occurs.
		// Why is this happening? We get the new block coordinates on chunk updates, so collision should carry over?
		// Current work around is to NOT update the players position during a chunk loading frame.
		
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(90.0f, 0.1f, 100.0f);


		// Draws different meshes
		// ok not drawing the block apparently jsut ruins the shader, no block no shader
		//block.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);
		map->drawMap(shaderProgram, camera);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}