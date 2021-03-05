#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



int main() {
	glfwInit();

	// Window setup 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Shaders", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shaders
	Shader ourShader("shader.vert","shader.frag");

	

	// Rectangle
	
	float vertices[] = {
		// positions			// colors		    // texture coords
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// bottom left
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f	// top left
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	// Vertex array object 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Vertex buffer object 

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element buffer object 
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex attribute 
	// Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// Tex Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	// Texture 
	//	Generate  texture1
	unsigned int texture1;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//	Set parameter 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// Flipping Image Y-Axis 
	stbi_set_flip_vertically_on_load(true);
	//	Loading file for texture1 
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture1" << std::endl;
	}
	
	//	Generate  texture2
	unsigned int texture2;

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//	Set parameter 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//	Loading file for texture2 
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture2" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	ourShader.setInt("texture1",0);

	ourShader.setInt("texture2", 1);
	// Viewport setup 
	glViewport(0, 0, 800, 600);

	
	
	while (!glfwWindowShouldClose(window)) {
		

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		

		
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	

	// Terminate 
	glfwTerminate();

	

	return 0;
}



	

	
