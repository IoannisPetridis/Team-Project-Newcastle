#pragma once
#include "RendererBase.h"
#include "PS4MemoryAware.h"

#include <gnm.h>
#include <gnmx\fetchshaderhelper.h>

#include <..\samples\sample_code\graphics\api_gnm\toolkit\allocators.h>
#include <..\samples\sample_code\graphics\api_gnm\toolkit\stack_allocator.h>
#include <..\samples\sample_code\graphics\api_gnm\toolkit\toolkit.h>
#include "PS4Frame.h"
#include "PS4Texture.h"
#include "PS4Input.h"
#include "Camera.h"

class Camera;

using namespace sce;
using namespace Gnmx;
using namespace Gnmx::Toolkit;

enum MemoryLocation {
	GARLIC,
	ONION,
	MEMORYMAX
};

struct PS4ScreenBuffer  {
	//colour buffer
	sce::Gnm::RenderTarget		colourTarget;
	//depth buffer
	sce::Gnm::DepthRenderTarget depthTarget;

	//uint width;
	//uint height;
	//sce::Gnmx::Toolkit::Timers   m_timers; ?????
};

class PS4Shader;
class PS4Mesh;

class PS4RendererBase : 
	public RendererBase, public PS4MemoryAware
{
public:
	PS4RendererBase();
	~PS4RendererBase();

	void UpdateScene(float dt)	override;
	void RenderScene()			override;
	void SwapBuffers()			override;

protected:
	void	SwapScreenBuffer();
	void	SwapCommandBuffer();

private:
	void	InitialiseMemoryAllocators();
	void	InitialiseVideoSystem();
	void	InitialiseGCMRendering();

	void	DestroyMemoryAllocators();
	void	DestroyVideoSystem();
	void	DestroyGCMRendering();

	void	SetRenderBuffer(PS4ScreenBuffer*buffer, bool clearColour, bool clearDepth, bool clearStencil);
	void	ClearBuffer(bool colour, bool depth, bool stencil);

	PS4ScreenBuffer* GenerateScreenBuffer(uint width, uint height, bool colour = true, bool depth = true, bool stencil = false);


	void DrawMesh(PS4Mesh& mesh);
	void DrawSky(PS4Mesh& mesh);


protected:
	int currentGPUBuffer;

	const int _MaxCMDBufferCount;

//VIDEO SYSTEM VARIABLES
	int videoHandle;		//Handle to video system

//SCREEN BUFFER VARIABLES
	const int			_bufferCount;	//How many screen buffers should we have
	int					currentScreenBuffer;
	int					prevScreenBuffer;
	PS4ScreenBuffer**	screenBuffers;	//Pointer to our screen buffers
//Memory Allocation
	const int _GarlicMemory;
	const int _OnionMemory;

	sce::Gnmx::Toolkit::StackAllocator	stackAllocators[MEMORYMAX];

	//default shader
	PS4Shader*	defaultShader;
	PS4Shader*	SkyboxShader;
	PS4Mesh*	defaultMesh;
	PS4Mesh*	defaultMesh_2;
	PS4Texture* sky;
	PS4Mesh*	quad;

	PS4Texture* defaultTexture;

	//Individual Frames
	PS4Frame*	frames;

	int framesSubmitted;

	//Per frame pointers...
	PS4ScreenBuffer*		currentPS4Buffer;  //Pointer to whichever buffer we're currently using...
	Gnmx::GnmxGfxContext*	currentGFXContext;

	PS4Frame*				currentFrame;
protected:
	PS4Input input = PS4Input();
	Matrix4 projMatrix;		//Projection matrix
	Matrix4 modelMatrix;	//Model matrix. NOT MODELVIEW
	Matrix4 viewMatrix;		//View matrix
	Matrix4 textureMatrix;	//Texture matrix
	Camera* camera;
};

