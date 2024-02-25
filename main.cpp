#include "base.h"

// Todo List:
// - Error Handling
// - Graphics API
// - Assets
// - Random

static constexpr u32 Width = 1280;
static constexpr u32 Height = 720;

s32 AppMain(void) {
	
	constexpr string8 WindowTitle = u8"¿Qué?";
	CreateWindow(WindowTitle, Width, Height);

	u32 Texture = 0;

	while (!ShouldWindowClose()) {

		ClearBackground(v3(0.25f, 0.125f, 0.125f));

		/*
		image Image = CreateImage(&TempArena, Width, Height, format::R32B32G32A32_F32);

		v4 *ImageData = (v4 *)Image.Data;
		for (u32 y = 0; y < Height; ++y) {
			for (u32 x = 0; x < Width; ++x) {
				ImageData[y * Width + x] = v4(1.0f, 0.0f, 0.0f, 0.0f);
			}
		}

		DeleteTexture(Texture);
		Texture = CreateTextureFromImage(Image);
		Pop(ImageData);

		PushMatrix(m2::Identity());
		BlitTexture(Texture);
		PopMatrix(); */

		Draw();
	}

	return 0;
}
