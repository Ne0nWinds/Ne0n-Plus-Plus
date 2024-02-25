
#include <d3d11_2.h>
#include <dxgi.h>

void GetErrorMessage(HRESULT HResult);

struct d3d_state {
	ID3D11Device1 *Device;
	ID3D11DeviceContext1 *DeviceContext;
	IDXGIDevice1 *DxgiDevice;
	IDXGISwapChain2 *SwapChain;
	HANDLE SwapChainWaitHandle;
	ID3D11RenderTargetView *FrameBuffer;
};

static d3d_state State = {0};

static void Win32RendererInit(HWND WindowHandle, u32 WindowWidth, u32 WindowHeight) {

	HRESULT HResult = S_OK;

#define HResultAssert() {\
	if (HResult != S_OK) {\
		Break();\
		goto error;\
	}\
}

	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	UINT CreationFlags = 0;
#ifdef _DEBUG
	CreationFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	{
		ID3D11Device *BaseDevice = 0;
		ID3D11DeviceContext *BaseDeviceContext = 0;

		HResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, CreationFlags, FeatureLevels, array_len(FeatureLevels), D3D11_SDK_VERSION, &BaseDevice, 0, &BaseDeviceContext);
		HResultAssert();

		HResult = BaseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext), (void **)&State.DeviceContext);
		HResultAssert();
		BaseDeviceContext->Release();

		HResult = BaseDevice->QueryInterface(__uuidof(ID3D11Device1), (void **)&State.Device);
		HResultAssert();

		HResult = State.Device->QueryInterface(__uuidof(IDXGIDevice1), (void **)&State.DxgiDevice);
		HResultAssert();

		BaseDevice->Release();
	}

	{
		IDXGIFactory2* DxgiFactory = 0;
		IDXGIAdapter *DxgiAdapter = 0;
		HResult = State.DxgiDevice->GetAdapter(&DxgiAdapter);
		HResultAssert();

		DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void **)&DxgiFactory);
		HResultAssert();

		DxgiAdapter->Release();

		DXGI_SWAP_CHAIN_DESC1 SwapChainDesc = {};
		SwapChainDesc.Width = WindowWidth;
		SwapChainDesc.Height = WindowHeight;
		SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 2;
		SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

		IDXGISwapChain1 *SwapChain1 = 0;
		HResult = DxgiFactory->CreateSwapChainForHwnd((struct IUnknown *)State.Device, (HWND)WindowHandle, &SwapChainDesc, 0, 0, &SwapChain1);
		HResultAssert();

		IDXGISwapChain2 *SwapChain2 = 0;
		HResult = SwapChain1->QueryInterface(__uuidof(IDXGISwapChain2), (void **)&SwapChain2);
		State.SwapChain = SwapChain2;
		HResultAssert();

		State.SwapChain->SetMaximumFrameLatency(2);
		State.SwapChainWaitHandle = SwapChain2->GetFrameLatencyWaitableObject();
		Assert(State.SwapChainWaitHandle);

		SwapChain1->Release();
		DxgiAdapter->Release();
	}

	{
		ID3D11Texture2D *Buffer = 0;
		HRESULT HResult = 0;

		HResult = State.SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&Buffer);
		HResultAssert();

		HResult = State.Device->CreateRenderTargetView((struct ID3D11Resource *)Buffer, 0, &State.FrameBuffer);
		HResultAssert();
		Assert(State.FrameBuffer);
		Buffer->Release();
	}

	return;
error:
	GetErrorMessage(HResult);
	return;
}


#undef HResultAssert

void GetErrorMessage(HRESULT HResult) {
	LPTSTR ErrorText = NULL;
	FormatMessage(
	   // use system message tables to retrieve error text
	   FORMAT_MESSAGE_FROM_SYSTEM
	   // allocate buffer on local heap for error text
	   | FORMAT_MESSAGE_ALLOCATE_BUFFER
	   // Important! will fail otherwise, since we're not 
	   // (and CANNOT) pass insertion parameters
	   | FORMAT_MESSAGE_IGNORE_INSERTS,  
	   NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   HResult,
	   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	   (LPTSTR)&ErrorText,  // output 
	   0, // minimum size for output buffer
	   NULL
	); 
	OutputDebugStringW(L"\n");
	OutputDebugStringW(ErrorText);
}

static v4 BackgroundColor = 0;

void ClearBackground(v3 Color) {
	BackgroundColor = v4(Color, 1.0f);
}

void Draw() {
	State.SwapChain->Present(1, 0);
	State.DeviceContext->OMSetRenderTargets(1, &State.FrameBuffer, NULL);
	WaitForSingleObjectEx(State.SwapChainWaitHandle, 1000, true);
	State.DeviceContext->ClearRenderTargetView(State.FrameBuffer, (f32 *)&BackgroundColor);
}

u32 CreateTextureFromImage(image Image) {

	return 1;
}
void BlitTexture(u32 Texture) {

}
void DeleteTexture(u32 Texture) {

}
void PushMatrix(m2 Matrix) {

}
void PopMatrix() {


}
