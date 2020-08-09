#pragma once

enum class ShaderCreationMethod {
	eShaderFilePath,
	eShaderSourceCode
};

class Shader
{
public:
	Shader(	const char* vertexShader,				ShaderCreationMethod vertexMethod, 
			const char* fragmentShader,				ShaderCreationMethod fragmentMethod, 
			const char* geometryShader = nullptr,	ShaderCreationMethod geometryMethod = ShaderCreationMethod::eShaderFilePath);
	~Shader();
	void useShader() const;

	void setInt(const std::string& name, int) const;
	void setVec3f(const std::string& name, glm::vec3) const;
	void setVec4f(const std::string& name, glm::vec4) const;
	void setMat4(const std::string& name, glm::mat4) const;
private:
	static unsigned int createShader(const char* shaderData, GLenum shaderType, ShaderCreationMethod method);
	GLint getUniformLocation(const std::string& name) const;

	GLuint m_shaderProgram;
	mutable std::unordered_map<std::string, GLint> m_uniformsLocations;
};

