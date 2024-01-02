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
#include"Camera.h"

#include"entities/header/Block.h"
#include "entities/header/Map.h"



const unsigned int width = 800;
const unsigned int height = 800;


// Vertices coordinate
/*
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.25f, 0.0f,  0.25f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.25f, 0.0f, -0.25f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.25f, 0.0f, -0.25f,     0.83f, 0.70f, 0.44f,	5.0f, 5.0f,
	 0.25f, 0.0f,  0.25f,     0.83f, 0.70f, 0.44f,	0.0f, 5.0f,
	-0.25f, 0.5f,  0.25f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.25f, 0.5f, -0.25f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.25f, 0.5f, -0.25f,     0.83f, 0.70f, 0.44f,	5.0f, 5.0f,
	 0.25f, 0.5f,  0.25f,     0.83f, 0.70f, 0.44f,	0.0f, 5.0f,
	 -0.25f + 1, 0.0f,  0.25f + 1,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.25f + 1, 0.0f, -0.25f + 1,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.25f + 1, 0.0f, -0.25f + 1,     0.83f, 0.70f, 0.44f,	5.0f, 5.0f,
	 0.25f + 1, 0.0f,  0.25f + 1,     0.83f, 0.70f, 0.44f,	0.0f, 5.0f,
	-0.25f + 1, 0.5f,  0.25f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.25f + 1, 0.5f, -0.25f + 1,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.25f + 1, 0.5f, -0.25f + 1,     0.83f, 0.70f, 0.44f,	5.0f, 5.0f,
	 0.25f + 1, 0.5f,  0.25f + 1,     0.83f, 0.70f, 0.44f,	0.0f, 5.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7,
	0, 7, 3,
	0, 4, 7,
	3, 6, 2,
	3, 7, 6,
	1, 6, 2,
	1, 5, 6,
	1, 0, 4,
	1, 4, 5,

	0 + 8, 1 + 8, 2 + 8,
	0 + 8, 2 + 8, 3 + 8,
	4 + 8, 5 + 8, 6 + 8,
	4 + 8, 6 + 8, 7 + 8 ,
	0 + 8, 7 + 8, 3 + 8,
	0 + 8, 4 + 8, 7 + 8,
	3 + 8, 6 + 8, 2 + 8,
	3 + 8, 7 + 8, 6 + 8,
	1 + 8, 6 + 8, 2 + 8,
	1 + 8, 5 + 8, 6 + 8,
	1 + 8, 0 + 8, 4 + 8,
	1 + 8, 4 + 8, 5 + 8,
};*/
/*
GLfloat * vertices;

// Indices for vertices order
GLuint * indices;
void buildCubes(int layers) {

	// Number of blocks
	int num = (layers * 2 + 1);
	num = pow(num, 2);
	int count = 0;

	//Allocate memory
	vertices = (GLfloat *) malloc(sizeof(GLfloat) * 64 * num);
	indices = (GLuint*) malloc(sizeof(GLuint) * 48 * num);

	//Origin Index
	GLfloat posInd = 0.25f;
	GLfloat negInd = -0.25f;

	// Generate blocks
	for (int i = 0; i < layers; i++) {
		if (i == 0){
			// Generate initial block
		}

		else {
			// Generate based on the position of a previously added outer layer block
			// Then add the corner blocks.
		}

	}
}
*/
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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");



	/* using raw pointers
	GLfloat* vecArr = new GLfloat[vec.size()];
	GLuint* indArr = new GLuint[ind.size()];
	std::copy(vec.begin(), vec.end(), vecArr);
	std::copy(ind.begin(), ind.end(), indArr);
	*/ 


	/*
	fprintf(stdout, "%d\n", vec.size());
	fprintf(stdout, "%d\n", ind.size());
	fprintf(stdout, "%d\n", sizeof(vecArr));
	fprintf(stdout, "%d\n", sizeof(indArr));
	fprintf(stdout, "%d\n", sizeof(block.vertices));
	fprintf(stdout, "%d\n", sizeof(block.indices));
	*/

	Map map(100, 100);
	//Block block(0, 0, 0);
	//Block block2(0.5, 0.5, 0);
	//map.addBlock(&block);
	//map.addBlock(&block2);
	std::vector<GLfloat> vec = map.getVerts();
	std::vector<GLuint> ind = map.getInds();

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	//fprintf(stdout, "%d\n", map.getNumBlocks() * 64 * 4);
	//fprintf(stdout, "%d\n", map.getNumBlocks() * 36 * 4);

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vec.data(), vec.size() * sizeof(GLfloat));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(ind.data(), ind.size() * sizeof(GLuint));

	// Links VBO attributes such as coordinates and colors to VAO
	// Do I only need to do this once if I follow th same format?
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Dynamic addition of block
	//VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	//VBO1.updateData(block2.vertices, sizeof(block2.vertices));
	// Generates Element Buffer Object and links it to indices
	//EBO1.UpdateData(block2.indices, sizeof(block2.indices));

	// THIS REMOVES THE SHIT :(

	//SOLUTIONS 
	// CREATE A MAP CLASS THAT HOLDS A VECTOR OF ALL BLOCKS SO YOU CAN ADD, TRACK, REMOVE BLOCKS AND SEND TO VAO
	//



	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

	Texture dirtTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	dirtTex.texUnit(shaderProgram, "tex0", 0);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	map.genHeightMap(0, 0);
	map.generateRandomMap();
	vec = map.getVerts();
	ind = map.getInds();

	VBO1.updateData(vec.data(), vec.size() * sizeof(GLfloat));
	EBO1.UpdateData(ind.data(), ind.size() * sizeof(GLuint));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "YoutubeOpenGL - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		dirtTex.Bind();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, map.getNumBlocks() * 36, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	dirtTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}