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



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{
	// Front face
   -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,   0.0f, 0.0f, // 0 - Bottom-left
	0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,   1.0f, 0.0f, // 1 - Bottom-right
	0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,   1.0f, 1.0f, // 2 - Top-right
   -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,   0.0f, 1.0f, // 3 - Top-left

   // Back face
  -0.5f, -0.5f, -0.5f,  0.92f, 0.86f, 0.76f,   0.0f, 0.0f, // 4 - Bottom-left
   0.5f, -0.5f, -0.5f,  0.92f, 0.86f, 0.76f,   1.0f, 0.0f, // 5 - Bottom-right
   0.5f,  0.5f, -0.5f,  0.92f, 0.86f, 0.76f,   1.0f, 1.0f, // 6 - Top-right
  -0.5f,  0.5f, -0.5f,  0.92f, 0.86f, 0.76f,   0.0f, 1.0f, // 7 - Top-left

  // Right face
  0.5f, -0.5f,  0.5f,  0.76f, 0.45f, 0.12f,   0.0f, 0.0f, // 8 - Bottom-front
  0.5f, -0.5f, -0.5f,  0.76f, 0.45f, 0.12f,   1.0f, 0.0f, // 9 - Bottom-back
  0.5f,  0.5f, -0.5f,  0.76f, 0.45f, 0.12f,   1.0f, 1.0f, // 10 - Top-back
  0.5f,  0.5f,  0.5f,  0.76f, 0.45f, 0.12f,   0.0f, 1.0f, // 11 - Top-front

  // Left face
 -0.5f, -0.5f,  0.5f,  0.76f, 0.45f, 0.12f,   0.0f, 0.0f, // 12 - Bottom-front
 -0.5f, -0.5f, -0.5f,  0.76f, 0.45f, 0.12f,   1.0f, 0.0f, // 13 - Bottom-back
 -0.5f,  0.5f, -0.5f,  0.76f, 0.45f, 0.12f,   1.0f, 1.0f, // 14 - Top-back
 -0.5f,  0.5f,  0.5f,  0.76f, 0.45f, 0.12f,   0.0f, 1.0f, // 15 - Top-front

 // Top face
-0.5f,  0.5f,  0.5f,  0.67f, 0.87f, 0.50f,   0.0f, 0.0f, // 16 - Front-left
 0.5f,  0.5f,  0.5f,  0.67f, 0.87f, 0.50f,   1.0f, 0.0f, // 17 - Front-right
 0.5f,  0.5f, -0.5f,  0.67f, 0.87f, 0.50f,   1.0f, 1.0f, // 18 - Back-right
-0.5f,  0.5f, -0.5f,  0.67f, 0.87f, 0.50f,   0.0f, 1.0f, // 19 - Back-left

// Bottom face
-0.5f, -0.5f,  0.5f,  0.98f, 0.76f, 0.45f,   0.0f, 0.0f, // 20 - Front-left
 0.5f, -0.5f,  0.5f,  0.98f, 0.76f, 0.45f,   1.0f, 0.0f, // 21 - Front-right
 0.5f, -0.5f, -0.5f,  0.98f, 0.76f, 0.45f,   1.0f, 1.0f, // 22 - Back-right
-0.5f, -0.5f, -0.5f,  0.98f, 0.76f, 0.45f,   0.0f, 1.0f  // 23 - Back-left
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20
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



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Link VBO for texture coordinates
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

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
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}