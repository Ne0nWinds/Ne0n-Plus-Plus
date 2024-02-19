#include "base.h"

s32 AppMain(void) {
	memory_arena Arena = {0};
	ArenaInitCommitAndReserve(&Arena, MB(256), TB(8));

	constexpr char8 str[] = u8"¿Qué?";
	CreateWindow(&Arena, string8((char8 *)str), 1280, 720);

	while (!ShouldWindowClose()) {

	}

	return 0;
}
