#pragma once
#include <endstone/plugin/plugin.h>

namespace ExamplePlugin {

class PluginDescriptionBuilderImpl : public endstone::detail::PluginDescriptionBuilder {
public:
    PluginDescriptionBuilderImpl() {
        prefix      = "CppExamplePlugin";
        description = "C++ example plugin for Endstone servers";
        website     = "https://github.com/ZMBlocks/ES-Example";
        authors     = {"Endstone Developers <hello@endstone.dev>"};
    }
};

class Entry : public endstone::Plugin {
public:
    static Entry* getInstance();

    void onLoad() override;

    void onEnable() override;

    void onDisable() override;

    endstone::PluginDescription const& getDescription() const override;

private:
    PluginDescriptionBuilderImpl mBuilder;
    endstone::PluginDescription  mDescription = mBuilder.build("cpp_example", "0.4.0");
};
} // namespace ExamplePlugin