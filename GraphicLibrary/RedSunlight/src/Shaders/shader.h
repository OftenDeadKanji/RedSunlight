#pragma once

enum class ShaderCreationMethod {
	SHADER_FILE_PATH,
	SHADER_SOURCE_CODE
};

class Shader
{
public:
	Shader(	const char* vertexShaderPath,				ShaderCreationMethod vertexMethod, 
			const char* fragmentShaderPath,				ShaderCreationMethod fragmentMethod, 
			const char* geometryShaderPath = nullptr,	ShaderCreationMethod geometryMethod = ShaderCreationMethod::SHADER_FILE_PATH);

	void useShader();

	void setInt(const std::string& name, int) const;
	void setVec3f(const std::string& name, glm::vec3) const;
	void setVec4f(const std::string& name, glm::vec4) const;
	void setMat4(const std::string& name, glm::mat4) const;
private:
	unsigned int createShader(const char* path, GLenum shaderType, ShaderCreationMethod method);
	GLint getUniformLocation(const std::string& name) const;

	GLuint m_shaderProgram;
	mutable std::unordered_map<std::string, GLint> m_uniformsLocations;
};

