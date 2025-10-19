#pragma once
#include "Tbx/Plugins/Plugin.h"
#include "Tbx/Assets/AssetLoaders.h"

namespace Tbx::Plugins::JIMS
{
    struct TIMSText : public Text, public IProductOfPluginFactory
    {
        using Text::Text;
    };

    class TIMSTextLoaderPlugin final
        : public ITextureLoader
        , public IShaderLoader
        , public ITextLoader
        , public FactoryPlugin<TIMSTexture>
        , public FactoryPlugin<TIMSShader>
        , public FactoryPlugin<TIMSText>
    {
    public:
        TIMSTextLoaderPlugin(Ref<EventBus> eventBus) {}
        bool CanLoad(const std::filesystem::path& filepath) const final;
        Ref<Text> LoadText(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(TIMSTextLoaderPlugin);
}