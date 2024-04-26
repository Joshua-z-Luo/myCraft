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
#include "gameLogic/DestroyPacket.h"

#include "constants.h"

#include"entities/header/Model/Mesh.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

/*
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
};*/

Vertex lightVertices[] =
{
	// Updated coordinates to make the light block 0.5 times in size
	Vertex{glm::vec3(-0.5f, -0.5f,  0.5f)},
	Vertex{glm::vec3(-0.5f, -0.50, -0.5f)},
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

const unsigned int width = 1200;
const unsigned int height = 800;

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
	//make window unresizable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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



	// Temporary Texture data
	// Want to move this into map in future.
	/**/
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

	// Store mesh data in vectors for the mesh
	//std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	//std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	// Shader for light cube
	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(2.0f, 15.0f, 2.0f);
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
	

	// ----------------------------- Menu (ImGui) -----------------------------------------------------------------------------------------------------
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Set button color to grey
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Set hover color to light grey

	// add scaled fonts
	ImFontAtlas* fontAtlas = io.Fonts;
	fontAtlas->AddFontFromFileTTF("libraries/include/mygui/misc/fonts/ProggyTiny.ttf", 16.0f);
	fontAtlas->AddFontFromFileTTF("libraries/include/mygui/misc/fonts/ProggyTiny.ttf", 40.0f);


	// ----------------------------- Game Logic -----------------------------------------------------------------------------------------------

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Initalize map
	Map* map = new Map(1);
	map->addChunk(0);
	map->loadMap();

	// Creates camera object
	// x z y
	Player camera(width, height, glm::vec3(10.0f, 50.0f, 10.0f));

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	int posX = 0;
	int posY = 0;

	std::deque<std::unique_ptr<UpdatePacket>> updateQue;
	std::vector<Triangle> playerVerts;

	// Gets block coordinates for detection logic
	std::vector<glm::vec3> blockCords = map->getBlockCordinates();


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		// Update que
		// %TODO: change in future to only due X number of actions per frame for performance purposes.
		bool updateFlag = false;
		if (updateQue.size() > 0) {
			printf("%d \n", updateQue[0]->getActionID());
			switch (updateQue[0]->getActionID()) {
			case 1:
				// Delete Block
				glm::vec3 deleteBlock = updateQue[0]->conductAction();

				//add block to inventory
				// 1. get destryoed blockid, (might need to get a return value from removeBlockFromChunk)
				// 2. call addBlockToInventory from player class
				camera.addItemToInventory(map->removeBlockFromChunk(0, 0, deleteBlock.x, deleteBlock.y, deleteBlock.z), 1);
				break;

			case 2:
				// Add Block
				glm::vec3 addBlock = updateQue[0]->conductAction();
				// % TODO IMPLEMENT A WAY TO FETCH THE BLOCK ID. MIGHT NEED NEW METHOD IN UpdatePacket
				// 1. FIX SELECTABLES (CAN ONLY SELECT slot IF BLOCK AMOUNT < THEN MAX OF STACK). 
				// 2. PLACE BLOCK IF SELECTED IN INVENTORY 
				// 3. REMOVE BLOCK FROM INVENTORY ONCE PLACED
				map->addBlockToChunk(0, 0, addBlock.x, addBlock.y, addBlock.z, 1);
				break;

			case 3:

				break;
			default:
				printf(" no update \n");
			}

			updateQue.pop_front();
			updateFlag = true;
		}

		// World Logic
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
		// Update que
		// % TODO: Chunks should not be all loading in one frame, this causes stutters.
		// Chunk loading should be done block by block via the update que.
		if (updateFlag == true) {
			map->updateMap(0, 0);
			blockCords = map->getBlockCordinates();
		}

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



		// update current position of player hitbox
		camera.updateBoundingBox();
		// Handles camera inputs
		// Collision self contained with player class.
		if (updateFlag != true) {
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			view = camera.getView();
			projection = camera.getProjection(90.0f, 0.1f, 10.0f);
			// verticies of visable blocks
			playerVerts = map->getPlayerChunk(camera.Position, camera.extractFrustumPlanes(projection * view));

			// controls
			camera.Inputs(window, timeDiff, blockCords, playerVerts, &updateQue, posX, posY);
		}
		//playerVerts = map->getPlayerChunk(camera.Position);
		//camera.Inputs(window, timeDiff, blockCords, &playerVerts, &updateQue, posX, posY);
		//%TODO: Player is gets stuck in blocks when a frame where new chunks must be loaded occurs.
		// Why is this happening? We get the new block coordinates on chunk updates, so collision should carry over?
		// Current work around is to NOT update the players position during a chunk loading frame.
		
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(90.0f, 0.1f, 100.0f);

		// Specify the color of the background
		glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draws different meshes
		// ok not drawing the block apparently jsut ruins the shader, no block no shader
		light.Draw(lightShader, camera);
		map->drawMap(shaderProgram, camera);

		// Menu elements
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (camera.isInventoryOpen()) {
			ImGui::SetNextWindowSize(ImVec2(800, 400));
			ImGui::SetNextWindowPos(ImVec2(200, 200)); 
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
			ImGui::Begin("Inventory", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

				ImGui::PushFont(fontAtlas->Fonts[1]);
				ImGui::Text("Inventory");
				ImGui::PopFont();

				ImGui::Columns(2, nullptr, false);

				std::array <std::array<int, 2>, 20> inventoryArray = camera.getInventory(); 

				for (int i = 0; i < inventoryArray.size(); i++) {


					// Render selectable or empty text
					if (inventoryArray[i][1] == -1) {
						ImGui::Text("Empty Slot");
					}
					else {
						// %TODO Selectable not reacting to clicks sometimes.
						if (ImGui::Selectable((
							"Block: " + std::to_string(inventoryArray[i][1]) + " "
							+ "Amount: " + std::to_string(inventoryArray[i][0]))
							.c_str(), (camera.getSelectedSlot() == i))) 
							{

								printf("Item %d clicked!\n", i);
								camera.setSelectedSlot(i); // set selected state if clicked
							}
					}
					ImGui::NextColumn();
				}

			ImGui::End();
			ImGui::PopStyleColor();
		}

		if (camera.isMenuOpen()) {
			// Draw a black translucent overlay
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(io.DisplaySize);
			ImGui::SetNextWindowBgAlpha(0.7f);
			ImGui::Begin("Overlay", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
			ImGui::End();

			ImVec2 windowSize = ImVec2(200, 100);
			ImGui::SetNextWindowSize(windowSize); // Set window size to 400x300
			ImGui::SetNextWindowPos(ImVec2(500, 400)); // Set window position to (100, 100)
			ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

				// Calculate position for centering button
				ImVec2 buttonSize(150, 50); // button size
				ImVec2 buttonPosition = ImVec2((windowSize.x - buttonSize.x) * 0.5f, (windowSize.y - buttonSize.y) * 0.5f); // Find center
				// Set cursor position to center the button
				ImGui::SetCursorPos(buttonPosition);

				if (ImGui::Button("Exit Game", buttonSize)) {
					// break out of game loop
					break;
				}
		
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		//printf("x %f, y %f z %f \n", camera.Position.x, camera.Position.y, camera.Position.z);

	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();

	//cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}