#pragma once
#include "Tbx/Plugins/Plugin.h"
#include "Tbx/Assets/AssetLoaders.h"

namespace Tbx::Plugins::JIMS
{
    class JIMSAssetLoaderPlugin final
        : public Plugin
        , public ITextureLoader
        , public IShaderLoader
        , public ITextLoader
    {
    public:
        JIMSAssetLoaderPlugin(Ref<EventBus> eventBus) {}

        bool CanLoad(const std::filesystem::path& filepath) const final;
        Texture LoadTexture(const std::filesystem::path& filepath) final;
        Shader LoadShader(const std::filesystem::path& filepath) final;
        Text LoadText(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(JIMSAssetLoaderPlugin);
}