#include "base.h"

// Todo List:
// - Mouse Input
// - Error Handling

s32 AppMain(void) {
	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(WindowTitle, 1280, 720);

	while (!ShouldWindowClose()) {
		bool b;
		b = IsKeyDown(key::Q);
		if (b) {
			DebugOutput("Q\n");
		}
	}

	return 0;
}
