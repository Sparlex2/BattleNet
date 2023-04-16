#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourseManager.h"
//�����
GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
/*
//������, ����� ����������� ��� ������� ��������(3 ����)
const char* vertex_shader =
//������ �������, �� ������ 4.6 => ������ ������� 460
"#version 460\n"
//��������� ������� ��� ������� ������
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
//�������� ���������� �����
"out vec3 color;"
"void main() {"
//��� ��������� ������ �������� ������ ������ ���� ����� �����
"   color = vertex_color;"
//���������� ������� ��������, � ���� ������� 4-�� ������������ ������, � � ����� ������� 3, 4 �������� ��� �������� �����������, �� ���� ��� ��� �� �����
"   gl_Position = vec4(vertex_position, 1.0);"
"}";
//���������� ������
const char* fragment_shader =
"#version 460\n"
//3-� ����������� ������, ������� ��������, �� ������� �������
"in vec3 color;"
//�������� �������� 4-� ������������ ������, �������� �������� ����� ���� ��� 1
"out vec4 frag_color;"
"void main() {"
//����, ����������� ������ ������ �� 4 ������� �� � ��� �� �������� ����� �����(������������)
"   frag_color = vec4(color, 1.0);"
"}";*/
int g_windowSizeX = 640;
int g_windowSizeY = 480;
using namespace std;

//������� ������
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);


}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    //���� ������ ������� ������ �� �� ������� �� ���������
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfwInit failed!" << endl;
        return -1;
    }
    //����������� ������ ���� �� 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    //������� ����
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "EldarAlkash", nullptr, nullptr);
    //���� ���� �� ���� �������� �� �������
    if (!pWindow)
    {
        cout << "glfwCreateWindow FAILED!" << endl;
        glfwTerminate();
        return -1;
    }
    //���������� ������ � ������ ����.
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    /* Make the window's context current */
    //���� ����� ���� ��������� � ��� ���� ������� �������
    glfwMakeContextCurrent(pWindow);

    //������������� ���������� glad
    if (!gladLoadGL()) {
        cout << "Can't load GLAD!" << endl;
        return -1;
    }
    //�������� ������/����������
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    //������ ������ 
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    //���� ����
    glClearColor(1, 0, 1, 0);
    {
        ResourseManager resourseManger(argv[0]);
        auto pDefaultShaderProgram = resourseManger.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            cerr << "cant create shader program: " << "DefaultShader" << endl;

        }
        //��� ����������� ���� ��� �������� �������� � ������ ����������
        GLuint points_vbo = 0;
        //���������� ������ ��� ����������
        glGenBuffers(1, &points_vbo);
        //���������� ������ � ������ �������
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        //��������� ��� ����������� �� ���� ��������� ������ �������� �� ����������
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        //���������� ������ ��� ����������
        glGenBuffers(1, &colors_vbo);
        //���������� ������ � ������ �������
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        //��������� ��� ����������� �� ���� ������ ������ �������� �� ����������
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        //���� ���������, ���� ���� �� �������, ��������� � ������� �� ������

        //������� ���������� �� ������ ������ �����
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //������� ������� ��� �������� ����� � �������
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        //��� ������� �������, �������� ��� �����, ����� ���� ����, ����������� �� ����� �� ���, ��� �������� ��� �� ����� �� ��� ������ ���� �� �������, ���� ������ ���� � ����� �� ��������� ��������� �� ������ �������
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        //������� ������� ��� �������� ����� � �������
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        //��� ������ �������, �������� ��� �����, ����� ���� ����, ����������� �� ����� �� ���, ��� �������� ��� �� ����� �� ��� ������ ���� �� �������, ���� ������ ���� � ����� �� ��������� ��������� �� ������ �������
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        while (!glfwWindowShouldClose(pWindow))
        {
            //���������
            glClear(GL_COLOR_BUFFER_BIT);

            //������ ���������
            //������������ ���������
            pDefaultShaderProgram->use();
            //���������� ��, ��� ����� ����������
            glBindVertexArray(vao);
            //������������ ����� �� ������ � �������� ������� � ��� �� ���������
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /*�������� ������� �������� � ������ ������ */
            glfwSwapBuffers(pWindow);

            /* ����� � ��������� ������� */
            glfwPollEvents();
        }
    }
    //���������� ������ ���������, ������������ ���� ��������
    glfwTerminate();
    return 0;
}