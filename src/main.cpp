#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

int main(void)
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

    /* Make the window's context current */
    //���� ����� ���� ��������� � ��� ���� ������� �������
    glfwMakeContextCurrent(pWindow);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    //������������� ���������� glad
	if(!gladLoadGL()){
		cout << "Can't load GLAD!";
		return -1;
	}
    //�������� ������/����������
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    //������ ������ 
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    //���� ����
	glClearColor(0, 1, 0, 1);

    //���� ���������, ���� ���� �� �������, ��������� � ������� �� ������
    while (!glfwWindowShouldClose(pWindow))
    {
        //���������
        glClear(GL_COLOR_BUFFER_BIT);

        /*�������� ������� �������� � ������ ������ */
        glfwSwapBuffers(pWindow);

        /* ����� � ��������� ������� */
        glfwPollEvents();
    }
    //���������� ������ ���������, ������������ ���� ��������
    glfwTerminate();
    return 0;
}