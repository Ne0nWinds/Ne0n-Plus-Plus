#include "base.h"

s32 AppMain(void) {
	memory_arena Arena = {0};
	ArenaInit(&Arena, MB(256), TB(8));

	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(&Arena, WindowTitle, 1280, 720);

	u32 count = (u32)key::Count;

	while (!ShouldWindowClose()) {
		bool k = WasKeyReleased(key::Space);
		if (k) {
			Break();
		}
	}

	return 0;
}
