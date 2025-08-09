#pragma once
#include "Tbx/PluginAPI/RegisterPlugin.h"

namespace JIM
{
    class JIMAssetLoaderPlugin : public Tbx::ITextureLoaderPlugin, public Tbx::IShaderLoaderPlugin
    {
    public:
        JIMAssetLoaderPlugin() = default;
        ~JIMAssetLoaderPlugin() override = default;

        void OnLoad() override;
        void OnUnload() override;

        Tbx::Texture LoadTexture(const std::string& filename) override;
        Tbx::Shader LoadShader(const std::string& filename) override;
    };

    TBX_REGISTER_PLUGIN(JIMAssetLoaderPlugin);
}