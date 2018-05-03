#include "MyUtil/Shader.h"
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "MyUtil/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

int windowHeight = 900, windowWidth = 900;
float imageSize = 1, mixPara = 0.2;
float verPos[][3] = {
	//�ϵ���
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	//�µ���
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f };
float vertices[] = {
	////�ϵ���
	//0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f, imageSize, 0.0f,
	//0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, imageSize, imageSize,
	//-0.5f, -0.5f, 0.5f,1.0f, 0.0f, 0.0f,0.0f, imageSize,     
	//-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,          
	////�µ���
	//0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, imageSize, 0.0f,     
	//0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,imageSize, imageSize,
	//-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,0.0f, imageSize,     
	//-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f,          

	//ʹ����������
	//λ��				                           ��ɫ	   				����
	//��1������
	verPos[0][0], verPos[0][1], verPos[0][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[1][0], verPos[1][1], verPos[1][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[2][0], verPos[2][1], verPos[2][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[3][0], verPos[3][1], verPos[3][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           // ���Ͻ�
	//��2������
	verPos[7][0], verPos[7][1], verPos[7][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[6][0], verPos[6][1], verPos[6][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[5][0], verPos[5][1], verPos[5][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[4][0], verPos[4][1], verPos[4][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           // ���Ͻ�
	//��3������
	verPos[0][0], verPos[0][1], verPos[0][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[4][0], verPos[4][1], verPos[4][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[5][0], verPos[5][1], verPos[5][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[1][0], verPos[1][1], verPos[1][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           // ���Ͻ�
	//��4������
	verPos[1][0], verPos[1][1], verPos[1][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[5][0], verPos[5][1], verPos[5][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[6][0], verPos[6][1], verPos[6][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[2][0], verPos[2][1], verPos[2][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           // ���Ͻ�
	//��5������
	verPos[2][0], verPos[2][1], verPos[2][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[6][0], verPos[6][1], verPos[6][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[7][0], verPos[7][1], verPos[7][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[3][0], verPos[3][1], verPos[3][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           // ���Ͻ�
	//��6������
	verPos[3][0], verPos[3][1], verPos[3][2], 1.0f, 0.0f, 0.0f,  imageSize, 0.0f,      // ���Ͻ�
	verPos[7][0], verPos[7][1], verPos[7][2], 1.0f, 0.0f, 0.0f,  imageSize, imageSize, // ���½�
	verPos[4][0], verPos[4][1], verPos[4][2], 1.0f, 0.0f, 0.0f,  0.0f, imageSize,      // ���½�
	verPos[0][0], verPos[0][1], verPos[0][2], 1.0f, 0.0f, 0.0f,  0.0f, 0.0f            // ���Ͻ�
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	//ʹ�ÿո�ֹͣ����
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//ʹ�����·�������������С
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		imageSize *= 1.005f;
		for (int i = 0; i < 6; ++i) {
			vertices[6 + i * 32] = vertices[14 + i * 32] = vertices[15 + i * 32] = vertices[23 + i * 32] = imageSize;
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		imageSize /= 1.005f;
		for (int i = 0; i < 6; ++i) {
			vertices[6 + i * 32] = vertices[14 + i * 32] = vertices[15 + i * 32] = vertices[23 + i * 32] = imageSize;
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	//ʹ�����ҷ��������mix����
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		mixPara += 0.005f;
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		mixPara -= 0.005f;
	}
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		system("pause");
		return -1;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	//texture
	vector<char*>imgs;
	imgs.push_back((char*)"src/imgs/img0.jpg");
	imgs.push_back((char*)"src/imgs/img1.jpg");
	unsigned int texture[2];
	for(int i = 0; i < 2; ++i){
		//����ͼƬ
		int width, height, nrChannels;
		unsigned char * data = stbi_load(imgs[i], &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture[i]);

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		//���û��ơ����˷�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//���������ͼƬ��������
		if(data){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else{
			std::cout << "error:fail to load texture" << endl;
		}
		//�ͷ��ڴ�
		stbi_image_free(data);
	}

	//��ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	unsigned int tv[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��1������
		1, 2, 3,

		4, 5, 7,
		5, 6, 7
	}; 
	vector<unsigned int> indices(tv, tv + 6);
	for (int i = 1; i <= 5; ++i) {
		for (int j = 0; j < 6; ++j) {
			indices.push_back(indices[j] + 4 * i);
			cout << indices[indices.size() - 1] << '\t';
		}
		cout << endl;
	}

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	vector<Shader>shaders;
	GLchar vertexFile[] = "src/MyUtil/vertex.hlsl", fragmentFile[] = "src/MyUtil/fragment.hlsl";
	shaders.push_back(*(new Shader(vertexFile, fragmentFile)));
	shaders.push_back(*(new Shader(vertexFile, fragmentFile)));

	//������Ԫ����ɫ����ϵ����
	for(int i = 0; i < shaders.size(); ++i){
		shaders[i].use();
		glUniform1i(glGetUniformLocation(shaders[i].ID, "ourTexture0"), 0);
		shaders[i].setInt("ourTexture1", 1);
	}

	//�۲����
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.4f, 0.4f, -2.0f));

	//ͶӰ����
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float timeValue = glfwGetTime();

		//ģ�;���
		vector<glm::mat4>models;
		glm::mat4 *tempTrans = new glm::mat4(1.0f);
		*tempTrans = glm::rotate(*tempTrans, glm::radians(timeValue * 40), glm::vec3(1.0f, 0.0f, 0.0f));
		*tempTrans = glm::rotate(*tempTrans, glm::radians(timeValue * 40), glm::vec3(0.0f, 1.0f, 0.0f));
		*tempTrans = glm::translate(*tempTrans, glm::vec3(0.0f, 0.0f, -3.0f));
		*tempTrans = glm::rotate(*tempTrans, glm::radians(timeValue * 40), glm::vec3(1.0f, 0.0f, 0.0f));
		models.push_back(*tempTrans);

		tempTrans = new glm::mat4(1.0f);
		*tempTrans = glm::translate(*tempTrans, glm::vec3(0.0f, 0.0f, -4.0f));
		float rot = sin(timeValue * 4) + 2;
		*tempTrans = glm::scale(*tempTrans, glm::vec3(rot, rot, rot));
		*tempTrans = glm::rotate(*tempTrans, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		*tempTrans = glm::rotate(*tempTrans, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		*tempTrans = glm::rotate(*tempTrans, glm::radians(timeValue * 40), glm::vec3(0.0f, 1.0f, 0.0f));
		models.push_back(*tempTrans);

		for(int i = 0; i < shaders.size(); ++i){
			shaders[i].use();
			//����������ͼ�Ļ��ֵ
			shaders[i].setFloat("mixPara", mixPara);

			//��ɫ��ʱ��仯
			float colorTime = timeValue * 10;
			vector<float>nowColor;
	        nowColor.push_back((sin(colorTime) / 2.0f) + 0.5f);
	        nowColor.push_back((sin(colorTime/4) / 2.0f) + 0.5f);
	        nowColor.push_back((sin(colorTime/2) / 2.0f) + 0.5f);
			shaders[i].set4f("ourColor", nowColor[0], nowColor[1], nowColor[2], 1.0f);

			//����ȥ�任����
			shaders[i].setMat4("model", models[i]);
			shaders[i].setMat4("view", view);
			shaders[i].setMat4("projection", projection);

			glBindVertexArray(VAO);

			//��������0������Ԫ
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[0]);

			//��������1������Ԫ
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture[1]);

			glBindVertexArray(VAO);

			//����ָ����ʽȡ�������ݲ�������Ⱦ
			//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
			int xx = 6;
			glDrawElements(GL_TRIANGLES, xx * 6, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
		}

		//����Ⱦ����
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
    return 0;
}
