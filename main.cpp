#include "base.h"

s32 AppMain(void) {
	memory_arena Arena = {0};
	ArenaInitCommitAndReserve(&Arena, MB(256), TB(8));

	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(&Arena, WindowTitle, 1280, 720);

	while (!ShouldWindowClose()) {

	}

	return 0;
}
