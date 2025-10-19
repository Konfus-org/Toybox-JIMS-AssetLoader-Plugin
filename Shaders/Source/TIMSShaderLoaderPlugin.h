#pragma once
#include "Tbx/Plugins/Plugin.h"
#include "Tbx/Assets/AssetLoaders.h"

namespace Tbx::Plugins::JIMS
{
    struct TIMSShader : public Shader, public IProductOfPluginFactory
    {
        using Shader::Shader;
    };

    class TIMSShaderLoaderPlugin final
        : public IShaderLoader
        , public FactoryPlugin<TIMSShader>
    {
    public:
        TIMSShaderLoaderPlugin(Ref<EventBus> eventBus) {}
        bool CanLoad(const std::filesystem::path& filepath) const final;
        Ref<Shader> LoadShader(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(TIMSShaderLoaderPlugin);
}