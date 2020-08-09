#include "pch.h"
#include "shader.h"

Shader::Shader(	const char* vertexShader, const ShaderCreationMethod vertexMethod,
				const char* fragmentShader, const ShaderCreationMethod fragmentMethod,
				const char* geometryShader, const ShaderCreationMethod geometryMethod)
{
	unsigned int shaders[3];
	shaders[0] = createShader(vertexShader, GL_VERTEX_SHADER, vertexMethod);
	shaders[1] = createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentMethod);
	if(geometryShader != nullptr)
		shaders[2] = createShader(geometryShader, GL_GEOMETRY_SHADER, geometryMethod);


	//linking shaders
	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, shaders[0]);
	glAttachShader(m_shaderProgram, shaders[1]);
	if(geometryShader != nullptr)
		glAttachShader(m_shaderProgram, shaders[2]);

	glLinkProgram(m_shaderProgram);

	//checking for errors
	int success;
	char infoLog[512];

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
		//TODO RED_TODO - wyj¹tek z wiadomoœci¹ infoLog
	}

	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	if (geometryShader != nullptr)
		glDeleteShader(shaders[2]);
}

Shader::~Shader()
{
	glDeleteShader(m_shaderProgram);
}

unsigned int Shader::createShader(const char* shaderData, const GLenum shaderType, const ShaderCreationMethod method)
{
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER && shaderType != GL_GEOMETRY_SHADER)
		return -1;

	//shader source code
	const char* code;

	if (method == ShaderCreationMethod::eShaderFilePath) {
		std::ifstream shaderFile(shaderData, std::ios::in);
		std::string shaderCode;
		

		//getting the size of the file
		shaderFile.seekg(0, std::ios::end);
		size_t size = shaderFile.tellg();

		//setting string size (?)
		shaderCode = std::string(size, ' ');

		//reading file - getting it while content into the string
		shaderFile.seekg(0);
		shaderFile.read(&shaderCode[0], size);

		//getting const char*
		code = shaderCode.c_str();
	} 
	else if (method == ShaderCreationMethod::eShaderSourceCode) {
		code = shaderData;
	}
	//shader compilation
	const auto shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	//checking for errors
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		//TODO RED_TODO - wyj¹tek z wiadomoœci¹ infoLog
	}

	return shader;
}

void Shader::useShader() const
{
	glUseProgram(m_shaderProgram);
}

GLint Shader::getUniformLocation(const std::string& name) const
{
	if (m_uniformsLocations.find(name) != m_uniformsLocations.end())
		return m_uniformsLocations[name];

	GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
	m_uniformsLocations[name] = location;
	return location;
}

void Shader::setInt(const std::string& name, int value) const
{
	GLint location = getUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::setVec3f(const std::string& name, glm::vec3 v) const
{
	GLint location = getUniformLocation(name);
	glUniform3f(location, v.x, v.y, v.z);
}

void Shader::setVec4f(const std::string& name, glm::vec4 v) const
{
	GLint location = getUniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::setMat4(const std::string& name, glm::mat4 matrix) const
{
	GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
