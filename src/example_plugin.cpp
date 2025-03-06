#include "example_plugin.h"

namespace ExamplePlugin {

Entry* Entry::getInstance() {
    static Entry* instance;
    if (!instance) instance = new Entry();
    return instance;
}

void Entry::onLoad() { getLogger().info("onLoad is called"); }

void Entry::onEnable() { getLogger().info("onEnable is called"); }

void Entry::onDisable() { getLogger().info("onDisable is called"); }

endstone::PluginDescription const& Entry::getDescription() const { return mDescription; }

} // namespace ExamplePlugin

#if defined(WIN32) || defined(_WIN32)
#define EXPORT_ENTRY_POINT __declspec(dllexport)
#else
#define EXPORT_ENTRY_POINT __attribute__((visibility("default")))
#endif

extern "C" [[maybe_unused]] EXPORT_ENTRY_POINT endstone::Plugin* init_endstone_plugin() {
    return ExamplePlugin::Entry::getInstance();
}