#include "base.h"

// Todo List:
// - Mouse Input
// - Error Handling

s32 AppMain(void) {
	memory_arena Arena = {0};
	ArenaInit(&Arena, MB(256), TB(8));

	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(&Arena, WindowTitle, 1280, 720);

	while (!ShouldWindowClose(&Arena)) {
		bool k = IsKeyDown(key::Space);
		if (k) {
			Break();
		}
	}

	return 0;
}
