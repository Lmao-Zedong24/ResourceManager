#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : m_id()
{
}

Texture::~Texture()
{
    this->Delete();
}

void Texture::Initialize(const std::string& p_fileName)
{
    m_fileName = p_fileName;
}

void Texture::OpenGlSetup()
{
    SetTexture(m_fileName);
}

bool Texture::SetTexture(const std::string& p_fileName)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load((TexturePath + p_fileName).c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }

    std::cout << "Failed to load texture" << std::endl;
    if (stbi_failure_reason())
        std::cout << stbi_failure_reason();
    stbi_image_free(data);
    return false;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &m_id);
}
