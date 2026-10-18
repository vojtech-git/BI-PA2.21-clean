#pragma once

namespace domain::config {
    namespace player {
        inline constexpr float kInitialBombCooldown = 2.0f;
        inline constexpr float kMinBombCooldown = 0.5f;
        inline constexpr float kInvulnerabilityDuration = 2.0f;
        inline constexpr uint32_t kInitialExplosionSize = 1;
    }

    namespace bonus {
        inline constexpr float kFreezeDuration = 3.0f;
        inline constexpr float kLevitationDuration = 5.0f;
        inline constexpr float kCooldownReduction = 0.3f;
        inline constexpr int kHealthBonus = 1;
        inline constexpr uint32_t kExplosionBonus = 1;
    }

    namespace bomb {
        inline constexpr float kDetonationDuration = 3.5f;
    }

    namespace smoke {
        inline constexpr float kSmokeDuration = 2.0f;
    }

    namespace ghost {
        inline constexpr float kMoveInterval = 1.0f;
    }
}