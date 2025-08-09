#include "JIMAssetLoaderPlugin.h"

namespace JIM
{
    void JIMAssetLoaderPlugin::OnLoad()
    {
        // Do nothing
    }

    void JIMAssetLoaderPlugin::OnUnload()
    {
        // Do nothing
    }

    Tbx::Texture JIMAssetLoaderPlugin::LoadTexture(const std::string& filename)
    {
        return Tbx::Texture();
    }

    Tbx::Shader JIMAssetLoaderPlugin::LoadShader(const std::string& filename)
    {
        return Tbx::Shader();
    }
}
