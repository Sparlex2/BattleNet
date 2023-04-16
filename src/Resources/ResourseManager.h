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
	//�������� ���� � ���� ����� �� ����� ����� � �� ���� ��� ����� �������� 
	ResourseManager(const string& executablePath);
	~ResourseManager() = default;
	//��������� �� ��� �� ����
	ResourseManager(const ResourseManager&) = delete;
	ResourseManager& operator=(const ResourseManager&) = delete; 
	ResourseManager& operator=(ResourseManager&&) = delete;
	ResourseManager(ResourseManager&&) = delete;

	//������� ��� �������� ��������, �������� ���������� � ���������� ������
	shared_ptr<Renderer::ShaderProgram> loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath);
	shared_ptr<Renderer::ShaderProgram> getShaderProgram(const string& shaderName);
private:
	//�������� ���� �� ������
	string getFileString(const string& relativeFilePath) const;
	//��������� ��� ��� ������� � ������� ���������, ��� ����� ������� ������ - �������� ������� � ��������� �� ���� 
	typedef map<const string, shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_shaderProgram;

	string m_path;
};