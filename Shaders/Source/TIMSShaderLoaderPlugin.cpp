#include "TIMSShaderLoaderPlugin.h"
#include "Tbx/Debug/Asserts.h"
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace Tbx::Plugins::JIMS
{
    /////////////// LOADER /////////////////////

    bool TIMSShaderLoaderPlugin::CanLoad(const std::filesystem::path& filepath) const
    {
        return filepath.extension() == ".vert" ||
               filepath.extension() == ".frag";
    }

    Ref<Shader> TIMSAssetLoaderPlugin::LoadShader(const std::filesystem::path& filepath)
    {
        // Get shader type from extension
        ShaderType shaderType;
        if (filepath.extension() == ".vert")
        {
            shaderType = ShaderType::Vertex;
        }
        else if (filepath.extension() == ".frag")
        {
            shaderType = ShaderType::Fragment;
        }
        else
        {
            TBX_ASSERT(false, "JIMS: Invalid shader file extension at {}!", filepath.string());
            return nullptr;
        }

        // Load and validate shader
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file)
        {
            TBX_ASSERT(false, "JIMS: Failed to load text file at {}!", filepath.string());
            return {};
        }

        // Load shader file from disc
        std::string shaderSource;
        {
            std::ostringstream shaderFileContent;
            contents << file.rdbuf();
            file.close();
            shaderSource = contents.str();
        }
        if (shaderSource.empty())
        {
            TBX_ASSERT(false, "JIMS: Failed to load shader file at {}!", filepath.string());
            return nullptr;
        }

        // Create tbx in memory shader and return it
        auto shader = FactoryPlugin<TIMSShader>::Create(shaderSource, shaderType);
        return shader;
    }
}
