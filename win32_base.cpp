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

static u32 PrevControllerState;
static u64 PrevKeyboardState;
static u32 ControllerState;
static u64 KeyboardState;

static inline u32 XInputBitFromButton(button Button) {
	switch (Button) {
		case button::DPadUp: {
			return XINPUT_GAMEPAD_DPAD_UP;
		} break;
		case button::DPadDown: {
			return XINPUT_GAMEPAD_DPAD_DOWN;
		} break;
		case button::DPadLeft: {
			return XINPUT_GAMEPAD_DPAD_LEFT;
		} break;
		case button::DPadRight: {
			return XINPUT_GAMEPAD_DPAD_RIGHT;
		} break;
		case button::Start: {
			return XINPUT_GAMEPAD_START;
		} break;
		case button::Back: {
			return XINPUT_GAMEPAD_BACK;
		} break;
		case button::LeftThumb: {
			return XINPUT_GAMEPAD_LEFT_THUMB;
		} break;
		case button::RightThumb: {
			return XINPUT_GAMEPAD_RIGHT_THUMB;
		} break;
		case button::LeftShoulder: {
			return XINPUT_GAMEPAD_LEFT_SHOULDER;
		} break;
		case button::RightShoulder: {
			return XINPUT_GAMEPAD_RIGHT_SHOULDER;
		} break;
		case button::A: {
			return XINPUT_GAMEPAD_A;
		} break;
		case button::B: {
			return XINPUT_GAMEPAD_B;
		} break;
		case button::X: {
			return XINPUT_GAMEPAD_X;
		} break;
		case button::Y: {
			return XINPUT_GAMEPAD_Y;
		} break;
		case button::Count: {
			return 0;
		}
	}
	return 0;
}

bool IsButtonDown(button Button) {
	u32 XInputButton = XInputBitFromButton(Button);
	return XInputButton & ControllerState;
}
bool IsButtonUp(button Button) {
	u32 XInputButton = XInputBitFromButton(Button);
	return !(XInputButton & ControllerState);
}
bool WasButtonReleased(button Button) {
	u32 XInputButton = XInputBitFromButton(Button);
	bool CurrentlyUp = !(XInputButton & ControllerState);
	bool PreviouslyDown = XInputButton & PrevControllerState;
	return CurrentlyUp & PreviouslyDown;
}
bool WasButtonPressed(button Button) {
	u32 XInputButton = XInputBitFromButton(Button);
	bool CurrentlyDown = XInputButton & ControllerState;
	bool PreviouslyUp = !(XInputButton & PrevControllerState);
	return CurrentlyDown & PreviouslyUp;
}

#undef CreateWindow
void CreateWindow(memory_arena *Arena, const string8 &Title, u32 Width, u32 Height) {

	HMODULE hInstance = GetModuleHandle(0);

	wchar_t *WindowTitle = 0;
	{
		s32 Length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS | MB_PRECOMPOSED, (const char *)Title.Data, Title.Length, 0, 0);
		Assert(Length);
		WindowTitle = (wchar_t *)Push(Arena, Length, sizeof(wchar_t));
		s32 Result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS | MB_PRECOMPOSED, (const char *)Title.Data, Title.Length, WindowTitle, Length * sizeof(wchar_t));
		Assert(Result);
	}

	{
		WNDCLASSW WindowClass = {0};
		WindowClass.lpfnWndProc = WindowProc;
		WindowClass.hInstance	 = hInstance;
		WindowClass.lpszClassName = WindowTitle;
		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClassW(&WindowClass);
	}

	DWORD WindowStyle = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	{
		RECT WindowSize = {0};
		WindowSize.right = (LONG)Width;
		WindowSize.bottom = (LONG)Height;
		AdjustWindowRectEx(&WindowSize, WindowStyle, FALSE, 0);

		u32 AdjustedWidth = WindowSize.right - WindowSize.left;
		u32 AdjustedHeight = WindowSize.bottom - WindowSize.top;

		WindowHandle = CreateWindowExW(
			0,
			WindowTitle,
			WindowTitle,
			WindowStyle | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, AdjustedWidth, AdjustedHeight,
			NULL, NULL, hInstance, NULL
		);
	}


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

		s32 sThumbLX = XinputState.Gamepad.sThumbLX;
		s32 sThumbLY = XinputState.Gamepad.sThumbLY;

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

		PrevControllerState = ControllerState;
		ControllerState = XinputState.Gamepad.wButtons;
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

#ifdef COMPILER_MSVC
extern "C" int _fltused{0x9875};
#endif

void _AppMain() {
	s32 Result = AppMain();
	ExitProcess(Result);
}
