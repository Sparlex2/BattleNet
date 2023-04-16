#include "ResourseManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;
ResourseManager::ResourseManager(const string& executablePath) {
	//��� ���� ����� ������� ���������� / ���� \ ������ ���� ������������ �� �������, �� ���� �� ���� � ����� � ������� ���� � ������� ��� � ���������� �����
	size_t found = executablePath.find_last_of("/\\");
	//����� ������ �� ���� �������, �� ���� � ���� ���� �� ���������� ����� 
	m_path = executablePath.substr(0, found);
}
string ResourseManager::getFileString(const string& relativeFilePath) const
{
	//������� ���������� � ������� ��������� ����
	ifstream f;
	//��������� ���� �������� �����
	f.open(m_path + "/" + relativeFilePath, ios::in | ios::binary);
	//���� ���� �� �������� ������� ������
	if (!f.is_open()){
		cerr << "Failed to open file: " << relativeFilePath << endl;
		return string{};
	}
	//���� ���� �������� �� ��������� ���� �����
	stringstream buffer;
	//��������� �������� �����
	buffer << f.rdbuf();
	//�������� ������� �����
	return buffer.str();
}
//������� �������� �������
shared_ptr<Renderer::ShaderProgram> ResourseManager::loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath) 
{
	//������� ���������� � ����������� ������ � �������� �� ����� ������ �� ���
	string vertexString = getFileString(vertexPath);
	//���� ������ �� ���������� � ���� �������������� � ��� ���� �������, �� ������� ������
	if (vertexString.empty()) {
		cerr << "No vertex shader" << endl;
		return nullptr;
	}
	string fragmentString = getFileString(fragmentPath);
	//���� ������ �� ���������� � ���� �������������� � ��� ���� �������, �� ������� ������
	if (fragmentString.empty()) {
		cerr << "No fragment shader!" << endl;
		return nullptr;
	}

	//��������� ������� � ��� ���
	shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderProgram.emplace(shaderName, make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled()) {
		return newShader;
	}
	cerr << "Cant load shader program!\n" << "Vertex: " << vertexPath << "\n" << "Fragment: " << fragmentPath << endl;
	return nullptr; 
}
shared_ptr<Renderer::ShaderProgram> ResourseManager::getShaderProgram(const string& shaderName) {
	//���� ������ �� �����, ���� ������� �� ���������� ��� ���� ��� �� ���������� ������
	ShaderProgramMap::const_iterator it = m_shaderProgram.find(shaderName);
	//���� ����� �� ���������, �� �������� ��������� ���������
	if (it != m_shaderProgram.end()) {
		return it->second;
	}
	cerr << "Cant find shader program: " << shaderName << endl;
	return nullptr;
}