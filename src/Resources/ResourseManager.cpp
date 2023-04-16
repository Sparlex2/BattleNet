#include "ResourseManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;
ResourseManager::ResourseManager(const string& executablePath) {
	//нам надо найти позицию последнего / либо \ второй слеш используется на линуксе, то есть мы идем с конца и находит слеш и заносим его в переменную фаунд
	size_t found = executablePath.find_last_of("/\\");
	//берем сабстр до этой позиции, то есть с нуля идем до последнего слеша 
	m_path = executablePath.substr(0, found);
}
string ResourseManager::getFileString(const string& relativeFilePath) const
{
	//создаем переменную в которой открываем файл
	ifstream f;
	//открываем файл бинарным кодом
	f.open(m_path + "/" + relativeFilePath, ios::in | ios::binary);
	//если файл не открылся выводим ошибку
	if (!f.is_open()){
		cerr << "Failed to open file: " << relativeFilePath << endl;
		return string{};
	}
	//если файл открылся мы считываем весь текст
	stringstream buffer;
	//считываем бинарный текст
	buffer << f.rdbuf();
	//ретерним обычный текст
	return buffer.str();
}
//функция загрузки шейдера
shared_ptr<Renderer::ShaderProgram> ResourseManager::loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath) 
{
	//создаем вертексный и фрагментный шейдер и получаем их через ссылку на них
	string vertexString = getFileString(vertexPath);
	//есди ничего не передалось в файл соответственно у нас нету шейдера, мы выводим ошибку
	if (vertexString.empty()) {
		cerr << "No vertex shader" << endl;
		return nullptr;
	}
	string fragmentString = getFileString(fragmentPath);
	//если ничего не передалось в файл соответственно у нас нету шейдера, мы выводим ошибку
	if (fragmentString.empty()) {
		cerr << "No fragment shader!" << endl;
		return nullptr;
	}

	//добавляем шейдеры в наш мэп
	shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderProgram.emplace(shaderName, make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled()) {
		return newShader;
	}
	cerr << "Cant load shader program!\n" << "Vertex: " << vertexPath << "\n" << "Fragment: " << fragmentPath << endl;
	return nullptr; 
}
shared_ptr<Renderer::ShaderProgram> ResourseManager::getShaderProgram(const string& shaderName) {
	//ищем шейдер по имени, если находим то возвращаем его если нет то возвращаем ничего
	ShaderProgramMap::const_iterator it = m_shaderProgram.find(shaderName);
	//если имена не совпадают, то ретерним шейдерную программу
	if (it != m_shaderProgram.end()) {
		return it->second;
	}
	cerr << "Cant find shader program: " << shaderName << endl;
	return nullptr;
}