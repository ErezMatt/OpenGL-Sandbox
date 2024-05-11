#include "Shader.h"

Shader::Shader():
	shader{0}
{
}

Shader::~Shader()
{
    clear();
}

void Shader::createFromString(const std::string& vertexCode, const std::string& fragmentCode)
{
    create(vertexCode, fragmentCode);
}

void Shader::createFromFile(const std::string& vertexLocation, const std::string& fragmentLocation)
{
    std::string vertexString = readFile(vertexLocation);
    std::string fragmentString = readFile(fragmentLocation);
    create(vertexString, fragmentString);

}

std::string Shader::readFile(const std::string& fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cout << "File read failed";
        return "";
    }
    std::string line = "";

    while (std::getline(fileStream, line))
    {  
        content.append(line + "\n");
    }
    fileStream.close();

    return content;
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
    glUniform1i(getUniformLocation(name), v0);
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    glUniform1f(getUniformLocation(name), v0);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setLight(const Light& light)
{
    glm::vec3 color = light.getColor();

    SetUniform3f("light.color", color.x, color.y, color.z);
    SetUniform1f("light.ambientIntensity", light.getAmbientIntensity());
}

void Shader::setDirectionalLight(const DirectionalLight& light)
{
    glm::vec3 color = light.getColor();
    glm::vec3 direction = light.getDiection();

    SetUniform3f("directionalLight.base.color", color.x, color.y, color.z);
    SetUniform1f("directionalLight.base.ambientIntensity", light.getAmbientIntensity());
    SetUniform3f("directionalLight.direction", direction.x, direction.y, direction.z);
    SetUniform1f("directionalLight.base.diffuseIntensity", light.getDiffuseIntensity());
}

void Shader::setPointLights(const std::vector<std::unique_ptr<PointLight>> const& pLights)
{
    int lightCount = pLights.size();
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    
    SetUniform1i("pointLightCount", lightCount);

    for (size_t i = 0; i < lightCount; i++) {
        glm::vec3 color = pLights[i]->getColor();
        glm::vec3 position = pLights[i]->getPosition();
        
        std::string uniformName = "pointLights[" + std::to_string(i) + "].";

        SetUniform3f(uniformName + "base.color", color.x, color.y, color.z);
        SetUniform1f(uniformName + "base.ambientIntensity", pLights[i]->getAmbientIntensity());
        SetUniform3f(uniformName + "position", position.x, position.y, position.z);
        SetUniform1f(uniformName + "base.diffuseIntensity", pLights[i]->getDiffuseIntensity());

        SetUniform1f(uniformName + "exponent", pLights[i]->getExponent());
        SetUniform1f(uniformName + "linear", pLights[i]->getLinear());
        SetUniform1f(uniformName + "constant", pLights[i]->getConstant());
    }
}

void Shader::setSpotLights(const std::vector<std::unique_ptr<SpotLight>> const& sLights)
{
    int lightCount = sLights.size();
    if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;


    SetUniform1i("spotLightCount", lightCount);

    for (size_t i = 0; i < lightCount; i++) {
        glm::vec3 color = sLights[i]->getColor();
        glm::vec3 position = sLights[i]->getPosition();
        glm::vec3 direction = sLights[i]->getDirection();

        std::string uniformName = "spotLights[" + std::to_string(i) + "].";

        SetUniform3f(uniformName + "base.base.color", color.x, color.y, color.z);
        SetUniform1f(uniformName + "base.base.ambientIntensity", sLights[i]->getAmbientIntensity());
        SetUniform3f(uniformName + "base.position", position.x, position.y, position.z);
        SetUniform1f(uniformName + "base.base.diffuseIntensity", sLights[i]->getDiffuseIntensity());

        SetUniform1f(uniformName + "base.exponent", sLights[i]->getExponent());
        SetUniform1f(uniformName + "base.linear", sLights[i]->getLinear());
        SetUniform1f(uniformName + "base.constant", sLights[i]->getConstant());

        SetUniform3f(uniformName + "direction", direction.x, direction.y, direction.z);
        SetUniform1f(uniformName + "edge", sLights[i]->getCalculationEdge());

    }
}

int Shader::getUniformLocation(const std::string& name)
{
    if (auto foundLocation = uniformLocationCache.find(name); foundLocation != uniformLocationCache.end())
        return foundLocation->second;

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1)
        std::cout << "Warning " << name;

    uniformLocationCache[name] = location;
    return location;
}

void Shader::use() const
{
    glUseProgram(shader);
}

void Shader::unbind() const
{
    glUseProgram(0);
}
void Shader::clear()
{
    if (shader != 0) {
        glDeleteProgram(shader);
        shader = 0;
    }
}

void Shader::create(const std::string& vertexCode, const std::string& fragmentCode)
{
    shader = glCreateProgram();

    compile(shader, vertexCode, GL_VERTEX_SHADER);
    compile(shader, fragmentCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shader);
    glValidateProgram(shader);
}

void Shader::compile(GLuint program, const std::string& shadetCode, GLenum shaderType)
{
    GLuint id = glCreateShader(shaderType);
    const char* src = shadetCode.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return;
    }

    glAttachShader(program, id);
}
