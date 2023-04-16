#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourseManager.h"
//место
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
//шейдер, будет запускаться для каждого вертекса(3 раза)
const char* vertex_shader =
//версия шейдера, тк опенгл 4.6 => весрия шейдера 460
"#version 460\n"
//указываем позицию где шейдеру искать
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
//выходная переменная цвета
"out vec3 color;"
"void main() {"
//для вертексов делаем значения цветов короче надо пусть будет
"   color = vertex_color;"
//обозночает позицию вертекса, в этой функции 4-ех компонентный вектор, а в нашем векторе 3, 4 параметр это параметр перспективы, он пока что там не нужен
"   gl_Position = vec4(vertex_position, 1.0);"
"}";
//фрагментый шейдер
const char* fragment_shader =
"#version 460\n"
//3-х компонентый вектор, входной параметр, из прошлой функции
"in vec3 color;"
//выходной параметр 4-х компонентный вектор, выходной параметр может быть ток 1
"out vec4 frag_color;"
"void main() {"
//цвет, приходиться делать вектор из 4 значени тк у нас не указанно число альфа(прозрачность)
"   frag_color = vec4(color, 1.0);"
"}";*/
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

int main(int argc, char** argv)
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
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    /* Make the window's context current */
    //окон может быть несколько и тут надо текущее ебануть
    glfwMakeContextCurrent(pWindow);

    //инициализация библиотеки glad
    if (!gladLoadGL()) {
        cout << "Can't load GLAD!" << endl;
        return -1;
    }
    //рендерер опенгл/видеокарта
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    //версия опенгл 
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    //цвет фона
    glClearColor(1, 0, 1, 0);
    {
        ResourseManager resourseManger(argv[0]);
        auto pDefaultShaderProgram = resourseManger.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            cerr << "cant create shader program: " << "DefaultShader" << endl;

        }
        //всю необходимую инфу для шейдоров передаем в память видеокарты
        GLuint points_vbo = 0;
        //генерируем буффер под переменную
        glGenBuffers(1, &points_vbo);
        //подключаем буффер и делаем текущим
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        //заполняем его информацией то есть позициями нашего вертекса на видеокарту
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        //генерируем буффер под переменную
        glGenBuffers(1, &colors_vbo);
        //подключаем буффер и делаем текущим
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        //заполняем его информацией то есть цветом нашего вертекса на видеокарту
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        //цикл отрисовки, пока окно не закрыто, рендеринг и рисовка на экране

        //говорим видеокарте че делать откуда брать
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //создаем позиции для векторов цвета и позиции
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        //для нулевой позиции, передаем три числа, числа типа флот, нармировать не хотим тк уже, шаг смещения нам не нужен тк все данные идут по порядку, если данные идут с каким то начальным смещением от начала массива
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        //создаем позиции для векторов цвета и позиции
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        //для первой позиции, передаем три числа, числа типа флот, нармировать не хотим тк уже, шаг смещения нам не нужен тк все данные идут по порядку, если данные идут с каким то начальным смещением от начала массива
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        while (!glfwWindowShouldClose(pWindow))
        {
            //рендеринг
            glClear(GL_COLOR_BUFFER_BIT);

            //делаем отрисовку
            //использовать программу
            pDefaultShaderProgram->use();
            //подключаем то, что хотим отрисовать
            glBindVertexArray(vao);
            //отрисовываем какую то фигуру с нулевого индекса и кол во вертексов
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /*Поменять местами передний и задний буфера */
            glfwSwapBuffers(pWindow);

            /* Опрос и обработка событий */
            glfwPollEvents();
        }
    }
    //завершение работы программы, освобождение всех ресурсов
    glfwTerminate();
    return 0;
}