#include "base.h"

#define UNICODE
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <Xinput.h>

// Memory
void ArenaInitCommitAndReserve(memory_arena *Arena, u64 Size, u64 StartingAddress) {
	constexpr u32 PageSize = 65536;
	u32 ReserveSize = u64_roundup_pw2(Size, PageSize);

	Arena->Start = VirtualAlloc((void *)StartingAddress, ReserveSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	Arena->Offset = Arena->Start;
	Arena->Size = ReserveSize;

	Assert(Arena->Start != NULL);
}
void *PushFast(memory_arena *Arena, u64 Size, u64 Count) {
	return PushFastAligned(Arena, Size, Count, 16);
}
void *PushFastAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment) {
	Assert(u32_popcnt(Alignment) == 1);

	u8 *AlignedOffset = (u8 *)Arena->Offset;
	*(u64 *)&AlignedOffset = u64_roundup_pw2((u64)AlignedOffset, Alignment);

	u8 *NewOffset = AlignedOffset + (Size * Count);
	Assert((u64)(NewOffset - (u8 *)Arena->Start) < Arena->Size);
	Arena->Offset = NewOffset;

	return AlignedOffset;
}
void PopFast(memory_arena *Arena, void *Ptr) {
	Assert((u64)Ptr >= (u64)Arena->Start && (u64)Ptr < (u64)Arena->Offset);
	Arena->Offset = Ptr;
}

// Reserve large amount of memory and commit only as necessary
void ArenaReserve(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, void *StartingAddress);
void *PushAndCommit(memory_arena *Arena, u64 Size, u64 Count);
void PopAndDecommit(memory_arena *Arena, void *Ptr);

// Use a linked list of virtual memory pages
void ArenaInitChained(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, void *StartingAddress);
void *PushChained(memory_arena *Arena, u64 Size, u64 Count);
void PopChained(memory_arena *Arena, void *Ptr);

// Windowing

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND WindowHandle = NULL;
static bool ShouldClose = false;
static LARGE_INTEGER PerformanceFrequency = {0};

#undef CreateWindow
void CreateWindow(memory_arena *Arena, const string8 &Title, u32 Width, u32 Height) {

	wchar_t *WindowTitle = 0;
	{
		s32 Length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (const char *)Title.Data, Title.Length, 0, 0);
		Assert(Length);
		WindowTitle = (wchar_t *)Push(Arena, Length, sizeof(wchar_t));
		s32 Result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (const char *)Title.Data, Title.Length, WindowTitle, Length * sizeof(wchar_t));
		Assert(Result);
	}

	HMODULE hInstance = GetModuleHandle(0);
	WNDCLASSW WindowClass = {0};
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance	 = hInstance;
	WindowClass.lpszClassName = WindowTitle;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassW(&WindowClass);

	HWND WindowHandle = CreateWindowExW(
		0,
		WindowTitle,
		WindowTitle,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,
		NULL, NULL, hInstance, NULL
	);

	Pop(Arena, WindowTitle);
	Assert(WindowHandle != NULL);

	{
		BOOL Result = QueryPerformanceFrequency(&PerformanceFrequency);
		Assert(Result);
	}
	
}
void ResizeWindow(u32 Width, u32 Height) {

}
bool ShouldWindowClose() {
	MSG msg;
	while (PeekMessageA(&msg, WindowHandle, 0, 0, PM_REMOVE)) {
		DispatchMessageA(&msg);
	}

	XINPUT_STATE XinputState;
	if (XInputGetState(0, &XinputState) == ERROR_SUCCESS) {
		f32 x = 0.0f, y = 0.0f;

		s16 sThumbLX = XinputState.Gamepad.sThumbLX;
		s16 sThumbLY = XinputState.Gamepad.sThumbLY;

		if (s32_abs(sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			if (sThumbLX < 0) {
				x = (f32)sThumbLX / 32768.0f;
			} else {
				x = (f32)sThumbLX / 32767.0f;
			}
		}

		if (s32_abs(sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			if (sThumbLY < 0) {
				y = (f32)sThumbLY / 32768.0f;
			} else {
				y = (f32)sThumbLY / 32767.0f;
			}
		}
	}

	return ShouldClose;
}
u64 TimerSample() {
	LARGE_INTEGER PerformanceCounter = {0};
	QueryPerformanceCounter(&PerformanceCounter);
	return PerformanceCounter.QuadPart;
}

LRESULT CALLBACK WindowProc(HWND WindowHandle, UINT Msg, WPARAM wParam, LPARAM lParam) {
	
	switch (Msg) {
		case WM_DESTROY:
		case WM_CLOSE:
		case WM_QUIT: {
			ShouldClose = true;
			return 0;
		}
	}

	return DefWindowProcW(WindowHandle, Msg, wParam, lParam);
}
