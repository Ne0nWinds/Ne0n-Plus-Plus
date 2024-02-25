#define UNICODE
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <Xinput.h>

#undef CreateWindow
#undef ZeroMemory

#include "base.h"

#ifdef RENDERAPI_D3D11
#pragma comment(lib, "d3d11.lib")
#include "d3d11_api.h"
#else
#include "opengl_api.h"
#endif

static inline wchar_t *WideStringFromString8(const string8 &String) {
	s32 Length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS | MB_PRECOMPOSED, (const char *)String.Data, String.Length + 1, 0, 0);
	if (Length == 0) {
		Break();
		return 0;
	}
	wchar_t *Result = (wchar_t *)Push(sizeof(wchar_t));
	Length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS | MB_PRECOMPOSED, (const char *)String.Data, String.Length + 1, Result, Length * sizeof(wchar_t));
	if (Length == 0) {
		Break();
		Pop(Result);
		return 0;
	}
	return Result;
	return 0;
}

void DebugOutput(const string8 &String) {
	wchar_t *WideString = WideStringFromString8(String);
	OutputDebugStringW(WideString);
	Pop((void *)WideString);
}

// Memory
void ArenaInit(memory_arena *Arena, u64 Size, u64 StartingAddress) {
	constexpr u32 PageSize = 65536;
	u32 ReserveSize = u64_roundup_pw2(Size, PageSize);

	Arena->Start = VirtualAlloc((void *)StartingAddress, ReserveSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	Arena->Offset = Arena->Start;
	Arena->Size = ReserveSize;

	Assert(Arena->Start != NULL);
}
void *ArenaPush(memory_arena *Arena, u64 Size) {
	return ArenaPushAligned(Arena, Size, 16);
}
void *ArenaPushAligned(memory_arena *Arena, u64 Size, u32 Alignment) {
	Assert(u32_popcnt(Alignment) == 1);

	u8 *AlignedOffset = (u8 *)Arena->Offset;
	*(u64 *)&AlignedOffset = u64_roundup_pw2((u64)AlignedOffset, Alignment);

	u8 *NewOffset = AlignedOffset + Size;
	Assert((u64)(NewOffset - (u8 *)Arena->Start) < Arena->Size);
	Arena->Offset = NewOffset;

	return AlignedOffset;
}
void ArenaPop(memory_arena *Arena, void *Ptr) {
	Assert((u64)Ptr >= (u64)Arena->Start && (u64)Ptr <= (u64)Arena->Offset);
	Arena->Offset = Ptr;
}

memory_arena TempArena;

void *Push(u64 Size) {
	return ArenaPush(&TempArena, Size);
}
void *PushAligned(u64 Size, u32 Alignment) {
	return ArenaPushAligned(&TempArena, Size, Alignment);
}
void Pop(void *Ptr) {
	ArenaPop(&TempArena, Ptr);
}

// Windowing

// Based on ANSI layout
enum class scan_code : u32 {
    Escape = 0x1,
	One = 0x2,
	Two = 0x3,
	Three = 0x4,
	Four = 0x5,
	Five = 0x6,
	Six = 0x7,
	Seven = 0x8,
	Eight = 0x9,
	Nine = 0xA,
	Zero = 0xB,
	Minus = 0xC,
	Plus = 0xD,
	Backspace = 0xE,
	Tab = 0xF,
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
	LeftBracket = 0x1A,
	RightBracket = 0x1B,
	Enter = 0x1C,
	LeftControl = 0x1D,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	Semicolon = 0x27,
	Quote = 0x28,
	GraveAccent = 0x29,
	LeftShift = 0x2A,
	Pipe = 0x2B,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	Comma = 0x33,
	Period = 0x34,
	QuestionMark = 0x35,
	RightShift = 0x36,
	NumpadMultiply = 0x37,
	LeftAlt = 0x38,
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
	Pause = 0x45,
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
	_Unused = 0x55,
	OEM10 = 0x56,
	F11 = 0x57,
	F12 = 0x58,
	LeftWindows = 0xE05B,
	RightAlt = 0xE038,
	RightWindows = 0xE05C,
	Menu = 0xE05D,
	RightControl = 0xE01D,
	Insert = 0xE052,
	Home = 0xE047,
	PageUp = 0xE049,
	Delete = 0xE053,
	End = 0xE04F,
	PageDown = 0xE051,
	ArrowUp = 0xE048,
	ArrowLeft = 0xE04B,
	ArrowDown = 0xE050,
	ArrowRight = 0xE04D,
	NumLock = 0x45,
	NumpadForwardSlash = 0xE035,
	NumpadEnter = 0xE01C,
};

inline key KeyFromScanCode(scan_code ScanCode) {
	u32 Value = 0;

	if ((u32)ScanCode <= 0x58) {
		Value = (u32)ScanCode;
	}

	if ((u32)ScanCode & 0xE000) {
		switch (ScanCode) {
			case scan_code::LeftWindows: {
				Value = (u32)key::LeftWindows;
			} break;
			case scan_code::RightAlt: {
				Value = (u32)key::RightAlt;
			} break;
			case scan_code::RightWindows: {
				Value = (u32)key::RightWindows;
			} break;
			case scan_code::Menu: {
				Value = (u32)key::Menu;
			} break;
			case scan_code::RightControl: {
				Value = (u32)key::RightControl;
			} break;
			case scan_code::Insert: {
				Value = (u32)key::Insert;
			} break;
			case scan_code::Home: {
				Value = (u32)key::Home;
			} break;
			case scan_code::PageUp: {
				Value = (u32)key::PageUp;
			} break;
			case scan_code::Delete: {
				Value = (u32)key::Delete;
			} break;
			case scan_code::End: {
				Value = (u32)key::End;
			} break;
			case scan_code::PageDown: {
				Value = (u32)key::PageDown;
			} break;
			case scan_code::ArrowUp: {
				Value = (u32)key::ArrowUp;
			} break;
			case scan_code::ArrowLeft: {
				Value = (u32)key::ArrowLeft;
			} break;
			case scan_code::ArrowDown: {
				Value = (u32)key::ArrowDown;
			} break;
			case scan_code::ArrowRight: {
				Value = (u32)key::ArrowRight;
			} break;
			case scan_code::NumLock: {
				Value = (u32)key::NumLock;
			} break;
			case scan_code::NumpadForwardSlash: {
				Value = (u32)key::NumpadForwardSlash;
			} break;
			case scan_code::NumpadEnter: {
				Value = (u32)key::NumpadEnter;
			} break;
		}
	}

	return (key)Value;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND WindowHandle = NULL;
static bool ShouldClose = false;
static LARGE_INTEGER PerformanceFrequency = {0};

// Use transition count?
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

bool IsButtonDown(key Key) {
	u128 BitPosition = SetBit(0, (u32)Key);
	return KeyboardState & BitPosition;
}
bool IsButtonUp(key Key) {
	u128 BitPosition = SetBit(0, (u32)Key);
	return !(KeyboardState & BitPosition);
}
bool WasButtonReleased(key Key) {
	u128 BitPosition = SetBit(0, (u32)Key);
	bool CurrentlyUp = !(KeyboardState & BitPosition);
	bool PreviouslyDown = (PrevKeyboardState & BitPosition);
	return CurrentlyUp & PreviouslyDown;
}
bool WasButtonPressed(key Key) {
	u128 BitPosition = SetBit(0, (u32)Key);
	bool CurrentlyDown = KeyboardState & BitPosition;
	bool PreviouslyUp = !(PrevKeyboardState & BitPosition);
	return CurrentlyDown & PreviouslyUp;
}

static v2 MouseDelta;
static s32 MouseWheelDelta;
static u32 PrevMouseButtonState;
static u32 MouseButtonState;

v2 GetMouseDelta() {
	return MouseDelta;
}
s32 GetMouseWheelDelta() {
	return MouseWheelDelta;
}
bool IsButtonDown(mouse_button Button) {
	return MouseButtonState & (u32)Button;
}
bool IsButtonUp(mouse_button Button) {
	return !(MouseButtonState & (u32)Button);
}
bool WasButtonReleased(mouse_button Button) {
	bool CurrentlyUp = !(MouseButtonState & (u32)Button);
	bool PreviouslyDown = PrevMouseButtonState & (u32)Button;
	return CurrentlyUp & PreviouslyDown;
}
bool WasButtonPressed(mouse_button Button) {
	bool CurrentlyDown = MouseButtonState & (u32)Button;
	bool PreviouslyUp = !(PrevMouseButtonState & (u32)Button);
	return CurrentlyDown & PreviouslyUp;
}

void CreateWindow(const string8 &Title, u32 Width, u32 Height) {

	DeferredPop(&TempArena);

	HMODULE hInstance = GetModuleHandle(0);

	wchar_t *WindowTitle = WideStringFromString8(Title);

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
		RAWINPUTDEVICE RID[2] = {};
		RID[0].usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
		RID[0].usUsage = 0x06; // KEYBOARD
		RID[0].dwFlags = 0;
		RID[0].hwndTarget = WindowHandle;

		RID[1].usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
		RID[1].usUsage = 0x02; // MOUSE
		RID[1].dwFlags = 0;
		RID[1].hwndTarget = WindowHandle;

		UINT Result = RegisterRawInputDevices(RID, array_len(RID), sizeof(RAWINPUTDEVICE));
		Assert(Result);
	}

	{
		Win32RendererInit(WindowHandle, Width, Height);
	}
}
void ResizeWindow(u32 Width, u32 Height) {

}
bool ShouldWindowClose() {
	DeferredPop(&TempArena);

	PrevControllerState = ControllerState;
	PrevKeyboardState = KeyboardState;
	PrevMouseButtonState = MouseButtonState;
	MouseDelta = 0;
	MouseWheelDelta = 0;

	MSG Message;
	while (PeekMessage(&Message, WindowHandle, 0, 0, PM_REMOVE)) {
		DispatchMessage(&Message);
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

		ControllerState = XinputState.Gamepad.wButtons;
	}

	HWND ActiveWindow = GetActiveWindow();
	if (ActiveWindow != WindowHandle) {
		PrevControllerState = 0;
		ControllerState = 0;
		PrevKeyboardState = 0;
		KeyboardState = 0;
		MouseButtonState = 0;
		MouseWheelDelta = 0;
		MouseDelta = 0;
	}

	return ShouldClose;
}

u64 TimerSample() {
	LARGE_INTEGER PerformanceCounter = {0};
	QueryPerformanceCounter(&PerformanceCounter);
	return PerformanceCounter.QuadPart;
}

f64 TimestampToSeconds(u64 *Timestamp) {
	return (f64)*Timestamp / (f64)PerformanceFrequency.QuadPart;
}

LRESULT CALLBACK WindowProc(HWND WindowHandle, UINT Msg, WPARAM wParam, LPARAM lParam) {
	
	switch (Msg) {
		case WM_INPUT: {
			RAWINPUT Input = {0};
			u32 Size = sizeof(RAWINPUT);
			UINT Result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &Input, &Size, sizeof(RAWINPUTHEADER));
			if (!Result) { return 0; }
			switch (Input.header.dwType) {
				case RIM_TYPEKEYBOARD: {
					RAWKEYBOARD Keyboard = Input.data.keyboard;
					u32 MakeCode = Keyboard.MakeCode;
					if (Keyboard.Flags & RI_KEY_E0) {
						MakeCode |= 0xE000;
					}
					scan_code ScanCode = (scan_code)MakeCode;
					bool KeyDown = !(Keyboard.Flags & RI_KEY_BREAK);
					u32 Count = (u32)key::Count;
					key Key = KeyFromScanCode(ScanCode);

					if (KeyDown) {
						KeyboardState = SetBit(KeyboardState, (u32)Key);
					} else {
						KeyboardState = ClearBit(KeyboardState, (u32)Key);
					}
				} break;
				case RIM_TYPEMOUSE: {
					RAWMOUSE Mouse = Input.data.mouse;
					if (Mouse.usFlags == MOUSE_MOVE_RELATIVE) {
						s64 LastX = Mouse.lLastX;
						s64 LastY = Mouse.lLastY;
						MouseDelta.x = (f32)LastX;
						MouseDelta.y = (f32)LastY;
					} else {
						// I presume this only happens on RDP or weird situations like that?
						Break();
					}

					u32 ButtonFlags = Mouse.usButtonFlags;
					if (ButtonFlags & RI_MOUSE_BUTTON_1_DOWN) {
						MouseButtonState |= (u32)mouse_button::LeftMouseButton;
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_1_UP) {
						MouseButtonState &= ~((u32)mouse_button::LeftMouseButton);
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_2_DOWN) {
						MouseButtonState |= (u32)mouse_button::RightMouseButton;
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_2_UP) {
						MouseButtonState &= ~((u32)mouse_button::RightMouseButton);
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_3_DOWN) {
						MouseButtonState |= (u32)mouse_button::MiddleMouseButton;
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_3_UP) {
						MouseButtonState &= ~((u32)mouse_button::MiddleMouseButton);
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_4_DOWN) {
						MouseButtonState |= (u32)mouse_button::XButton1;
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_4_UP) {
						MouseButtonState &= ~((u32)mouse_button::XButton1);
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_5_DOWN) {
						MouseButtonState |= (u32)mouse_button::XButton2;
					}
					if (ButtonFlags & RI_MOUSE_BUTTON_5_UP) {
						MouseButtonState &= ~((u32)mouse_button::XButton2);
					}
				} break;
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
	ArenaInit(&TempArena, MB(64), TB(8));
	s32 Result = AppMain();
	ExitProcess(Result);
}
