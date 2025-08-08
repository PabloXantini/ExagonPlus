#include "Shader33.hpp"

void ShaderGL33::load(const std::vector<ShaderPartData>& parts){
    unsigned int vertexShader = 0, fragmentShader = 0, geometryShader = 0;
    for(const auto& part : parts){
        const char* glslCode = part.glslCode.c_str();
        switch(part.part){
            case ShaderPart::VERTEX:
                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &glslCode, nullptr);
                glCompileShader(vertexShader);
                checkCompileErrors(vertexShader, "VERTEX");
                break;
            case ShaderPart::FRAGMENT:
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &glslCode, nullptr);
                glCompileShader(fragmentShader);
                checkCompileErrors(fragmentShader, "FRAGMENT");
                break;
            case ShaderPart::GEOMETRY:
                geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometryShader, 1, &glslCode, nullptr);
                glCompileShader(geometryShader);
                checkCompileErrors(geometryShader, "GEOMETRY");
                break;
        }
    }
    // Shader Program
    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertexShader);
    glAttachShader(ShaderProgramID, fragmentShader);
    if(geometryShader!=0) glAttachShader(ShaderProgramID, geometryShader);
    glLinkProgram(ShaderProgramID);
    checkCompileErrors(ShaderProgramID, "PROGRAM");
    // Free resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(geometryShader!=0){
        glDeleteShader(geometryShader);
    }
}

void ShaderGL33::checkCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if (type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
void ShaderGL33::use(){
    glUseProgram(ShaderProgramID);
}

void ShaderGL33::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), (int)value); 
}

void ShaderGL33::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value); 
}

void ShaderGL33::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value); 
}

void ShaderGL33::setVec2(const std::string &name, const glm::vec2 &value) const { 
    glUniform2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]); 
}

void ShaderGL33::setVec2(const std::string &name, float x, float y) const { 
    glUniform2f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y); 
}

void ShaderGL33::setVec2(const std::string &name, const Vec2f &vec2) const {
    glUniform2f(glGetUniformLocation(ShaderProgramID, name.c_str()), vec2.X, vec2.Y);
}

void ShaderGL33::setVec3(const std::string &name, const glm::vec3 &value) const { 
    glUniform3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]); 
}

void ShaderGL33::setVec3(const std::string &name, float x, float y, float z) const { 
    glUniform3f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z); 
}

void ShaderGL33::setVec3(const std::string &name, const Vec3f &vec3) const {
    glUniform3f(glGetUniformLocation(ShaderProgramID, name.c_str()), vec3.X, vec3.Y, vec3.Z);
}
    
void ShaderGL33::setVec4(const std::string &name, const glm::vec4 &value) const { 
    glUniform4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]); 
}
    
void ShaderGL33::setVec4(const std::string &name, float x, float y, float z, float w) const { 
    glUniform4f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z, w); 
}
    
void ShaderGL33::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderGL33::setMat2(const std::string &name, const Mat2f &mat) const {

    glUniformMatrix2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat.mat2x2[0][0]);
}
    
void ShaderGL33::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderGL33::setMat3(const std::string &name, const Mat3f &mat) const {

    glUniformMatrix3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat.mat3x3[0][0]);
}
    
void ShaderGL33::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderGL33::setMat4(const std::string &name, const Mat4f &mat) const {
    
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat.mat4x4[0][0]);
}

void ShaderGL33::kill(){
    glDeleteProgram(ShaderProgramID);
}