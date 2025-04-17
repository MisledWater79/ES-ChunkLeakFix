#include "Entry.h"
#include <glacie/memory/Hook.h>

namespace ChunkLeakFix {

#if defined(_WIN32) || defined(_WIN64)
GLACIE_AUTO_INSTANCE_HOOK(
    OnPlayerLeftHook,
    "48 85 D2 0F 84 ?? ?? ?? ?? 48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? "
    "?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44 88 44 24",
    void,
    void* player,
    bool  skipMessage
) {
    origin(player, skipMessage);
    if (!player) return;
    auto& level      = glacie::memory::dAccess<void*>(player, 472);    // Actor::mLevel
    auto* manager    = glacie::memory::virtualCall<void*>(level, 381); // ServerLevel::_getMapDataManager
    auto& allMapData = glacie::memory::dAccess<std::unordered_map<long long, std::unique_ptr<void*>>>(
        manager,
        112
    ); // MapDataManager::mUnk8ad806
    for (auto& [id, data] : allMapData) {
        auto& trackedEntities = glacie::memory::dAccess<std::vector<std::shared_ptr<void*>>>(data.get(), 96);
        std::erase_if(trackedEntities, [&player](std::shared_ptr<void*>& ptr) {
            static auto* getOrCreateUniqueIDFunc =
                SIGNATURE_CALL("40 53 48 83 EC ?? 4C 8B 51 ?? BB ?? ?? ?? ?? 8B 51", long long, void*); // Actor::getOrCreateUniqueID
            return glacie::memory::dAccess<long long>(ptr.get(), 0x8) == getOrCreateUniqueIDFunc(player);
        });
    }
}
#else

// Linux

#endif

Entry* Entry::getInstance() {
    static Entry* instance;
    if (!instance) instance = new Entry();
    return instance;
}

} // namespace ChunkLeakFix


extern "C" [[maybe_unused]] ENDSTONE_EXPORT endstone::Plugin* init_endstone_plugin() {
    return ChunkLeakFix::Entry::getInstance();
}