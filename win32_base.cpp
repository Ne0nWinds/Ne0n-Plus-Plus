#include "base.h"

#define UNICODE
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <Xinput.h>

// Memory
void ArenaInit(memory_arena *Arena, u64 Size, u64 StartingAddress) {
	constexpr u32 PageSize = 65536;
	u32 ReserveSize = u64_roundup_pw2(Size, PageSize);

	Arena->Start = VirtualAlloc((void *)StartingAddress, ReserveSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	Arena->Offset = Arena->Start;
	Arena->Size = ReserveSize;

	Assert(Arena->Start != NULL);
}
void *Push(memory_arena *Arena, u64 Size, u64 Count) {
	return PushAligned(Arena, Size, Count, 16);
}
void *PushAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment) {
	Assert(u32_popcnt(Alignment) == 1);

	u8 *AlignedOffset = (u8 *)Arena->Offset;
	*(u64 *)&AlignedOffset = u64_roundup_pw2((u64)AlignedOffset, Alignment);

	u8 *NewOffset = AlignedOffset + (Size * Count);
	Assert((u64)(NewOffset - (u8 *)Arena->Start) < Arena->Size);
	Arena->Offset = NewOffset;

	return AlignedOffset;
}
void Pop(memory_arena *Arena, void *Ptr) {
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

enum class scan_code : u32 {
    Escape = 0x01,
    One = 0x02,
    Two = 0x03,
    Three = 0x04,
    Four = 0x05,
    Five = 0x06,
    Six = 0x07,
    Seven = 0x08,
    Eight = 0x09,
    Nine = 0x0A,
    Zero = 0x0B,
    Minus = 0x0C,
    Equals = 0x0D,
    Backspace = 0x0E,
    Tab = 0x0F,
    Q = 0x10,
    W = 0x11,
    E = 0x12,
    R = 0x13,
    T = 0x14,
    Y = 0x15,
    U = 0x16,
    I = 0x17,
    O = 0x18,
    P = 0x19,
    BracketLeft = 0x1A,
    BracketRight = 0x1B,
    Enter = 0x1C,
    ControlLeft = 0x1D,
    A = 0x1E,
    S =0x1F,
    D = 0x20,
    F = 0x21,
    G = 0x22,
    H = 0x23,
    J = 0x24,
    K = 0x25,
    L = 0x26,
    Semicolon = 0x27,
    Apostrophe = 0x28,
    Grave = 0x29,
    ShiftLeft = 0x2A,
    Backslash = 0x2B,
    Z = 0x2C,
    X = 0x2D,
    C = 0x2E,
    V = 0x2F,
    B = 0x30,
    N = 0x31,
    M = 0x32,
    Comma = 0x33,
    Period = 0x34,
    Slash = 0x35,
    ShiftRight = 0x36,
    NumpadMultiply = 0x37,
    AltLeft = 0x38,
    Space = 0x39,
    CapsLock = 0x3A,
    F1 = 0x3B,
    F2 = 0x3C,
    F3 = 0x3D,
    F4 = 0x3E,
    F5 = 0x3F,
    F6 = 0x40,
    F7 = 0x41,
    F8 = 0x42,
    F9 = 0x43,
    F10 = 0x44,
    NumLock = 0x45,
    ScrollLock = 0x46,
    Numpad7 = 0x47,
    Numpad8 = 0x48,
    Numpad9 = 0x49,
    NumpadMinus = 0x4A,
    Numpad4 = 0x4B,
    Numpad5 = 0x4C,
    Numpad6 = 0x4D,
    NumpadPlus = 0x4E,
    Numpad1 = 0x4F,
    Numpad2 = 0x50,
    Numpad3 = 0x51,
    Numpad0 = 0x52,
    NumpadPeriod = 0x53,
    AltPrintScreen = 0x54,
    AngleBracket = 0x56,
    F11 = 0x57,
    F12 = 0x58,
    F13 = 0x64,
    F14 = 0x65,
    F15 = 0x66,
    F16 = 0x67,
    F17 = 0x68,
    F18 = 0x69,
    F19 = 0x6A,
    F20 = 0x6B,
    F21 = 0x6C,
    F22 = 0x6D,
    F23 = 0x6E,
    NumpadEnter = 0xE01C,
    ControlRight = 0xE01D,
    VolumeDown = 0xE02E,
    VolumeUp = 0xE030,
    NumpadDivide = 0xE035,
    PrintScreen = 0xE037,
    AltRight = 0xE038,
    Home = 0xE047,
    ArrowUp = 0xE048,
    PageUp = 0xE049,
    ArrowLeft = 0xE04B,
    ArrowRight = 0xE04D,
    End = 0xE04F,
    ArrowDown = 0xE050,
    PageDown = 0xE051,
    Insert = 0xE052,
    Delete = 0xE053,
    MetaLeft = 0xE05B,
    MetaRight = 0xE05C,
};

inline key KeyFromScanCode(scan_code ScanCode) {
	u32 Value;

	switch (ScanCode) {
		case scan_code::NumpadEnter: {
			Value = (u32)key::NumpadEnter;
		} break;
		case scan_code::ControlRight: {
			Value = (u32)key::ControlRight;
		} break;
		case scan_code::VolumeDown: {
			Value = (u32)key::VolumeDown;
		} break;
		case scan_code::VolumeUp: {
			Value = (u32)key::VolumeUp;
		} break;
		case scan_code::NumpadDivide: {
			Value = (u32)key::NumpadDivide;
		} break;
		case scan_code::PrintScreen: {
			Value = (u32)key::PrintScreen;
		} break;
		case scan_code::AltRight: {
			Value = (u32)key::AltRight;
		} break;
		case scan_code::Home: {
			Value = (u32)key::Home;
		} break;
		case scan_code::ArrowUp: {
			Value = (u32)key::ArrowUp;
		} break;
		case scan_code::PageUp: {
			Value = (u32)key::PageUp;
		} break;
		case scan_code::ArrowLeft: {
			Value = (u32)key::ArrowLeft;
		} break;
		case scan_code::ArrowRight: {
			Value = (u32)key::ArrowRight;
		} break;
		case scan_code::End: {
			Value = (u32)key::End;
		} break;
		case scan_code::ArrowDown: {
			Value = (u32)key::ArrowDown;
		} break;
		case scan_code::PageDown: {
			Value = (u32)key::PageDown;
		} break;
		case scan_code::Insert: {
			Value = (u32)key::Insert;
		} break;
		case scan_code::Delete: {
			Value = (u32)key::Delete;
		} break;
		case scan_code::MetaLeft: {
			Value = (u32)key::MetaLeft;
		} break;
		case scan_code::MetaRight: {
			Value = (u32)key::MetaRight;
		} break;
		default: {
			Value = (u32)ScanCode;
		}
	}

	return (key)Value;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND WindowHandle = NULL;
static bool ShouldClose = false;
static LARGE_INTEGER PerformanceFrequency = {0};

static u32 PrevControllerState;
static u32 ControllerState;
static u128 PrevKeyboardState;
static u128 KeyboardState;

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

	DeferredPop(Arena);

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

	Assert(WindowHandle != NULL);

	{
		BOOL Result = QueryPerformanceFrequency(&PerformanceFrequency);
		Assert(Result);
	}

	{
		RAWINPUTDEVICE RID[1] = {};
		RID[0].usUsagePage = 0x01, // HID_USAGE_PAGE_GENERIC
		RID[0].usUsage = 0x06,
		RID[0].dwFlags = 0,
		RID[0].hwndTarget = WindowHandle;

		UINT Result = RegisterRawInputDevices(RID, array_len(RID), sizeof(RAWINPUTDEVICE));
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
		case WM_INPUT: {
			UINT Size = sizeof(RAWINPUT);
			RAWINPUT RawInput = {0};

			UINT Result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &RawInput, &Size, sizeof(RAWINPUTHEADER));
			if (!Result) {
				Break();
				return 0;
			}

			if (RawInput.header.dwType == RIM_TYPEKEYBOARD) {
				u32 ScanCode = RawInput.data.keyboard.MakeCode;
				bool KeyDown = !(RawInput.data.keyboard.Flags & RI_KEY_BREAK);
				u32 Count = (u32)key::Count;
				Break();
			}

			return 0;
		}
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
// C Runtime BS
extern "C" int _fltused{0x9875};
extern "C" void __std_terminate() { ExitProcess(0); }
extern "C" void __CxxFrameHandler4() { }
#endif

void _AppMain() {
	s32 Result = AppMain();
	ExitProcess(Result);
}
