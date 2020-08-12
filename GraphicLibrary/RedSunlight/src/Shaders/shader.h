#pragma once

enum class RED_API ShaderCreationMethod {
	eShaderFilePath,
	eShaderSourceCode
};

class RED_API Shader
{
public:
	Shader(ShaderCreationMethod method, const char* vertexShader, const char* fragmentShader, const char* geometryShader = nullptr);
	~Shader();
	void useShader() const;

	void setInt(const std::string& name, int) const;
	void setVec3f(const std::string& name, const glm::vec3&) const;
	void setVec4f(const std::string& name, const glm::vec4&) const;
	void setMat4(const std::string& name, const glm::mat4&) const;
private:
	static unsigned int createShader(const char* shaderData, GLenum shaderType, ShaderCreationMethod method);
	void linkShaders(unsigned int shaders[], bool withGeometryShader);
	GLint getUniformLocation(const std::string& name) const;

	GLuint m_shaderProgram;
	mutable std::unordered_map<std::string, GLint> m_uniformsLocations;
};

