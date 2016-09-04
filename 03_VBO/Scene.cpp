#include "Scene.hpp"
#include <glm/glm.hpp>
#include <iostream>

using  namespace std;
const GLuint kPositionIndex = 0;
const GLuint kColorIndex = 1;

GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,  // Top Right
	0.5f, -0.5f, 0.0f,  // Bottom Right
	-0.5f, -0.5f, 0.0f,  // Bottom Left
	-0.5f, 0.5f, 0.0f   // Top Left 
};
GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3,  // First Triangle
	1, 2, 3   // Second Triangle
};
const GLfloat color[] = {
	1.0f, 0.0f, 0.0f, 1.0f
};


void CreateApplicationInstance() {
	new Sample();
}


bool Sample::initialize() {
	const char vertexShaderSource[]{ R"(
		#version 300 es
		layout(location = 0) in vec4 a_position;
		layout(location = 1) in vec4 a_color;
		smooth out vec4 v_color;
		void main() {
			gl_Position = a_position;
			v_color = a_color;
		}
	)"};
	const char fragmentShaderSource[]{ R"(
		#version 300 es
		precision mediump float;
		smooth in vec4 v_color;
		layout(location = 0) out vec4 color;
		void main() {
			color = v_color;
		}
	)" };

	VertexShader vertexShader{ vertexShaderSource };
	FragmentShader fragmentShader{ fragmentShaderSource };
	_program = new Program{ vertexShader, fragmentShader };

	glViewport(0, 0, this->getWindowWidth(), this->getWindowHeight());
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	CreateVBO();
	return true;
}


void Sample::finalize() {
}


void Sample::update(float dt) {

}


void Sample::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	_program->use();
	if (GetUseVAO()){
		glBindVertexArray(m_VAO);
		cout << "USE VAO" << endl;
	}
	if (m_IBO){
		cout << "USE IBO" << endl;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else{
		cout << "USE VBO" << endl;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glDrawArrays(GL_TRIANGLES, 0, 4);
	}
	glBindVertexArray(0);
	
	glFlush();
}


Sample::Sample() :Application("VBO Window", 400, 400)
{

}

Sample::~Sample()
{

	glDisableVertexAttribArray(kPositionIndex);
	glDisableVertexAttribArray(kColorIndex);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	if (_program) {
		delete _program;
		_program = nullptr;
	}
}

void Sample::CreateVBO()
{
	if (GetUseVAO())
	{
		//VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
	}
	// ======== 创建并绑定VBO
	if (m_VBO == 0)
	{
		glGenBuffers(1, &m_VBO);
	}
	// 0. 复制顶点数组到缓冲中提供给OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//设置顶点属性指针
	glEnableVertexAttribArray(kPositionIndex);
	glVertexAttribPointer(kPositionIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	// 
	glVertexAttrib4f(kColorIndex, 0.0, 0.5, 1.0, 1.0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ========= 创建并绑定IBO
	if (m_IBO == 0)
	{
		glGenBuffers(1, &m_IBO);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
