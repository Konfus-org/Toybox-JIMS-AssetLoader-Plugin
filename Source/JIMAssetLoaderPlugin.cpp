#include "JIMAssetLoaderPlugin.h"
#include <Tbx/Debug/Debugging.h>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace JIM
{
    std::shared_ptr<Tbx::Texture> JIMAssetLoaderPlugin::LoadTexture(const std::string& filepath)
    {
        // Load texture with stbimg
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
        
        // Ensure texture loaded correctly
        if (!data)
        {
            TBX_ASSERT(false, "Failed to load texture file at {}!", filepath);
            return std::shared_ptr<Tbx::Texture>(new Tbx::Texture(), [this](Tbx::Texture* texture) { DeleteTexture(texture); });
        }

        // Allocate and copy into vector
        size_t dataSize = static_cast<size_t>(width) * height * channels;
        std::vector<unsigned char> pixelData(dataSize);
        std::memcpy(pixelData.data(), data, dataSize);

        // Create tbx in memory texture and return it
        auto* texture = new Tbx::Texture(
            Tbx::Size(width, height),
            channels == 4 ? Tbx::TextureFormat::RGBA : Tbx::TextureFormat::RGB,
            pixelData);

        // Free the stb data
        stbi_image_free(data);

        return std::shared_ptr<Tbx::Texture>(texture, [this](Tbx::Texture* texture) { DeleteTexture(texture); });
    }

    std::shared_ptr<Tbx::Shader> JIMAssetLoaderPlugin::LoadShader(const std::string& filepath)
    {
        // Load and validate shader
        auto shaderSource = LoadTextFile(filepath);
        if (shaderSource.empty())
        {
            TBX_ASSERT(false, "Failed to load shader file at {}!", filepath);
            return std::shared_ptr<Tbx::Shader>(new Tbx::Shader(), [this](Tbx::Shader* shader) { DeleteShader(shader); });
        }

        // Create tbx in memory shader and return it
        auto* shader = new Tbx::Shader(shaderSource, std::filesystem::path(filepath).extension() == ".vert" ? Tbx::ShaderType::Vertex : Tbx::ShaderType::Fragment);
        return std::shared_ptr<Tbx::Shader>(shader, [this](Tbx::Shader* shader) { DeleteShader(shader); });
    }

    std::string JIMAssetLoaderPlugin::LoadTextFile(const std::string& filepath)
    {
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file)
        {
            TBX_ASSERT(false, "Failed to load text file at {}!", filepath);
            return {};
        }
        
        std::ostringstream contents;
        contents << file.rdbuf(); 
        file.close();

        return contents.str();
    }

    void JIMAssetLoaderPlugin::DeleteTexture(Tbx::Texture* texture)
    {
        delete texture;
    }

    void JIMAssetLoaderPlugin::DeleteShader(Tbx::Shader* shader)
    {
        delete shader;
    }
}
