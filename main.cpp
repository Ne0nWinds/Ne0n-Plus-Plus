#include "base.h"

// Todo List:
// - Mouse Input
// - Error Handling

s32 AppMain(void) {
	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(WindowTitle, 1280, 720);

	while (!ShouldWindowClose()) {
		if (WasButtonPressed(mouse_button::LeftMouseButton)) {
			DebugOutput("Left Click!");
		}
		if (WasButtonPressed(mouse_button::RightMouseButton)) {
			DebugOutput("Left Click!");
		}
		if (GetMouseDelta().x > 0.0f) {
			DebugOutput("Mouse Moved Right\n");
		} else if (GetMouseDelta().x < 0.0f) {
			DebugOutput("Mouse Moved Left\n");
		} else {
			DebugOutput("Mouse Stopped\n");
		}
	}

	return 0;
}
