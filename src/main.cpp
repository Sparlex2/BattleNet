#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_windowSizeX = 640;
int g_windowSizeY = 480;
using namespace std;

//опредет высоту
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);


}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    //если нажата клавиша эскейп то мы выходим из программы
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
   //минимальная версия опен гл 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    //создаем окно
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "EldarAlkash", nullptr, nullptr);
    //если окно не было созданно мы выходим
    if (!pWindow)
    {
        cout << "glfwCreateWindow FAILED!" << endl;
        glfwTerminate(); 
        return -1;
    }
    //каллбекает ширину и длинну окна.
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);

    /* Make the window's context current */
    //окон может быть несколько и тут надо текущее ебануть
    glfwMakeContextCurrent(pWindow);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    //инициализация библиотеки glad
	if(!gladLoadGL()){
		cout << "Can't load GLAD!";
		return -1;
	}
    //рендерер опенгл/видеокарта
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    //версия опенгл 
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    //цвет фона
	glClearColor(0, 1, 0, 1);

    //цикл отрисовки, пока окно не закрыто, рендеринг и рисовка на экране
    while (!glfwWindowShouldClose(pWindow))
    {
        //рендеринг
        glClear(GL_COLOR_BUFFER_BIT);

        /*Поменять местами передний и задний буфера */
        glfwSwapBuffers(pWindow);

        /* Опрос и обработка событий */
        glfwPollEvents();
    }
    //завершение работы программы, освобождение всех ресурсов
    glfwTerminate();
    return 0;
}