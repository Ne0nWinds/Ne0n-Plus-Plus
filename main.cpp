#define _DEBUG
#define PLATFORM_WIN32
#include "base.h"

int main(void) {
	volatile f32 a_x = 1.0f;
	volatile f32 a_y = 2.0f;
	volatile f32 a_z = 3.25f;
	volatile f32 a_w = 5.0f;

	v2 a = { 1, 1 };
	volatile v2 Result = v2_normalize(a);

	return 0;
}
