#pragma once
#include <endstone/plugin/plugin.h>

namespace ChunkLeakFix {

class PluginDescriptionBuilderImpl : public endstone::detail::PluginDescriptionBuilder {
public:
    PluginDescriptionBuilderImpl() {
        prefix      = "ChunkLeakFix";
        description = "Addresses the issue of chunks remaining loaded after players leave.";
        website     = "https://github.com/ZMBlocks/ES-ChunkLeakFix";
        authors     = {"啥也不会的子沐呀 <limulu10@163.com>"};
    }
};

class Entry : public endstone::Plugin {
public:
    static Entry* getInstance();

    endstone::PluginDescription const& getDescription() const override { return mDescription; }

private:
    PluginDescriptionBuilderImpl mBuilder;
    endstone::PluginDescription  mDescription = mBuilder.build("chunk_leak_fix", "1.1.0");
};
} // namespace ChunkLeakFix