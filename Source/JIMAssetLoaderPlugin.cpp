#include "JIMAssetLoaderPlugin.h"
#include <Tbx/Debug/Debugging.h>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace JIMS
{
    /////////////// LOADER /////////////////////

    bool JIMSAssetLoaderPlugin::CanLoad(const std::filesystem::path& filepath) const
    {
        if (filepath.extension() == ".png" ||
            filepath.extension() == ".jpg" ||
            filepath.extension() == ".jpeg" ||
            filepath.extension() == ".vert" ||
            filepath.extension() == ".frag" ||
            filepath.extension() == ".txt")
        {
            return true;
        }
        return false;
    }

    Tbx::Texture JIMSAssetLoaderPlugin::LoadTexture(const std::filesystem::path& filepath)
    {
        // Load texture with stbimg
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filepath.string().c_str(), &width, &height, &channels, 0);
        
        // Ensure texture loaded correctly
        if (!data)
        {
            TBX_ASSERT(false, "Failed to load texture file at {}!", filepath.string());
            return Tbx::Texture();
        }

        // Allocate and copy into vector
        size_t dataSize = static_cast<size_t>(width) * height * channels;
        std::vector<unsigned char> pixelData(dataSize);
        std::memcpy(pixelData.data(), data, dataSize);

        // Create tbx in memory texture and return it
        auto texture = Tbx::Texture(
            Tbx::Size(width, height),
            Tbx::TextureWrap::Repeat,
            Tbx::TextureFilter::Nearest,
            channels == 4 ? Tbx::TextureFormat::RGBA : Tbx::TextureFormat::RGB,
            pixelData);

        // Free the stb data
        stbi_image_free(data);

        return texture;
    }

    Tbx::Shader JIMSAssetLoaderPlugin::LoadShader(const std::filesystem::path& filepath)
    {
        // Get shader type from extension
        Tbx::ShaderType shaderType;
        if (filepath.extension() == ".vert")
        {
            shaderType = Tbx::ShaderType::Vertex;
        }
        else if (filepath.extension() == ".frag")
        {
            shaderType = Tbx::ShaderType::Fragment;
        }
        else
        {
            TBX_ASSERT(false, "Invalid shader file extension at {}!", filepath.string());
            return Tbx::Shader();
        }

        // Load and validate shader
        auto shaderSource = LoadText(filepath);
        if (shaderSource.Value.empty())
        {
            TBX_ASSERT(false, "Failed to load shader file at {}!", filepath.string());
            return Tbx::Shader();
        }

        // Create tbx in memory shader and return it
        auto shader = Tbx::Shader(shaderSource.Value, shaderType);
        return shader;
    }

    Tbx::Text JIMSAssetLoaderPlugin::LoadText(const std::filesystem::path& filepath)
    {
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file)
        {
            TBX_ASSERT(false, "Failed to load text file at {}!", filepath.string());
            return {};
        }

        std::ostringstream contents;
        contents << file.rdbuf();
        file.close();

        return Tbx::Text(contents.str());
    }
}
