#pragma once
#include<string>
#include <memory>
#include <map>
namespace Renderer {
	class ShaderProgram;
}
using namespace std;


class ResourseManager {
public:
	//передаем путь к екзе файлу из папки дебаг и из него уже будет искаться 
	ResourseManager(const string& executablePath);
	~ResourseManager() = default;
	//запрещаем то что не надо
	ResourseManager(const ResourseManager&) = delete;
	ResourseManager& operator=(const ResourseManager&) = delete; 
	ResourseManager& operator=(ResourseManager&&) = delete;
	ResourseManager(ResourseManager&&) = delete;

	//функция для загрузки шейдеров, передаем вертексный и фрагментый шейдер
	shared_ptr<Renderer::ShaderProgram> loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath);
	shared_ptr<Renderer::ShaderProgram> getShaderProgram(const string& shaderName);
private:
	//получаем файл по строке
	string getFileString(const string& relativeFilePath) const;
	//сохраняем все эти шейдеры в ресурсе менеджера, мап будет хранить строку - название шейдера и указатель на него 
	typedef map<const string, shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_shaderProgram;

	string m_path;
};