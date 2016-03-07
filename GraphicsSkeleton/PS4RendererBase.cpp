#pragma once
#include "PS4RendererBase.h"
#include <video_out.h>	//Video System
#include "PS4Shader.h"
#include "PS4Mesh.h"
#include <gnmx\basegfxcontext.h>
#include "OBJMesh.h"

PS4RendererBase::PS4RendererBase()
	:
	_MaxCMDBufferCount(3),
	  _bufferCount(3),
	  _GarlicMemory(1024 * 1024 * 512),
	  _OnionMemory( 1024 * 1024 * 256)
{
	framesSubmitted		 = 0;
	currentGPUBuffer	 = 0;
	currentScreenBuffer	 = 0;
	prevScreenBuffer	= 0;

	currentScreenBuffer = NULL;
	currentGFXContext	= NULL;

	InitialiseMemoryAllocators();

	InitialiseGCMRendering();
	InitialiseVideoSystem();

	SkyboxShader = PS4Shader::GenerateShader(
		"/app0/SkyboxVertex.sb",
		"/app0/SkyboxPixel.sb"
	);

	defaultShader = PS4Shader::GenerateShader(
		"/app0/VertexShader.sb",
		"/app0/PixelShader.sb"
		);
	camera = new Camera(0.0f, 0.0f, Vector4(0, 0, 0, 0));
	//defaultMesh		= PS4Mesh::GenerateTriangle();
	quad = PS4Mesh::GenerateQuad();
	defaultMesh =	new OBJMesh("/app0/sphereMinimal2.obj");
	defaultTexture	= PS4Texture::LoadTextureFromFile("/app0/doge.gnf");
	sky = PS4Texture::LoadTextureFromFile("/app0/texture/skyBox/sky_pos_x.gnf");
	SwapBuffers();
}


PS4RendererBase::~PS4RendererBase()
{
	DestroyGCMRendering();
	DestroyVideoSystem();
	DestroyMemoryAllocators();
}

void	PS4RendererBase::InitialiseVideoSystem() {
	screenBuffers = new PS4ScreenBuffer*[_bufferCount];

	for (int i = 0; i < _bufferCount; ++i) {
		screenBuffers[i] = GenerateScreenBuffer(1920, 1080);
	}

	//Now we can open up the video port
	videoHandle		= sceVideoOutOpen(0, SCE_VIDEO_OUT_BUS_TYPE_MAIN, 0, NULL);

	SceVideoOutBufferAttribute attribute;
	sceVideoOutSetBufferAttribute(&attribute,
		SCE_VIDEO_OUT_PIXEL_FORMAT_B8_G8_R8_A8_SRGB,
		SCE_VIDEO_OUT_TILING_MODE_TILE,
		SCE_VIDEO_OUT_ASPECT_RATIO_16_9,
		screenBuffers[0]->colourTarget.getWidth(),
		screenBuffers[0]->colourTarget.getHeight(),
		screenBuffers[0]->colourTarget.getPitch()
	);

	void* bufferAddresses[_bufferCount];

	for (int i = 0; i < _bufferCount; ++i) {
		bufferAddresses[i] = screenBuffers[i]->colourTarget.getBaseAddress();
	}

	sceVideoOutRegisterBuffers(videoHandle, 0, bufferAddresses, _bufferCount, &attribute);
}

void	PS4RendererBase::InitialiseGCMRendering() {
	frames = (PS4Frame*)onionAllocator.allocate(sizeof(PS4Frame) * _MaxCMDBufferCount, alignof(PS4Frame));

	for (int i = 0; i < _MaxCMDBufferCount; ++i) {
		new (&frames[i])PS4Frame();
	}

	sce::Gnmx::Toolkit::Allocators allocators = sce::Gnmx::Toolkit::Allocators(onionAllocator, garlicAllocator, ownerHandle);
	Gnmx::Toolkit::initializeWithAllocators(&allocators);
}

void	PS4RendererBase::InitialiseMemoryAllocators() {
	stackAllocators[GARLIC].init(SCE_KERNEL_WC_GARLIC, _GarlicMemory);
	stackAllocators[ONION ].init(SCE_KERNEL_WB_ONION , _OnionMemory);

	this->garlicAllocator   = Gnmx::Toolkit::GetInterface(&stackAllocators[GARLIC]);
	this->onionAllocator	= Gnmx::Toolkit::GetInterface(&stackAllocators[ONION]);
	Gnm::registerOwner(&ownerHandle, "PS4RendererBase");
}
                          
PS4ScreenBuffer*	PS4RendererBase::GenerateScreenBuffer(uint width, uint height, bool colour, bool depth, bool stencil) {
	PS4ScreenBuffer* buffer = new PS4ScreenBuffer();

	if (colour) {
		Gnm::DataFormat format = Gnm::kDataFormatB8G8R8A8UnormSrgb;
		Gnm::TileMode	tileMode;
		GpuAddress::computeSurfaceTileMode(&tileMode, GpuAddress::kSurfaceTypeColorTargetDisplayable, format, 1);

		const Gnm::SizeAlign colourAlign = buffer->colourTarget.init(width, height, 1, format, tileMode,
			Gnm::kNumSamples1, Gnm::kNumFragments1, NULL, NULL);

		void *colourMemory = stackAllocators[GARLIC].allocate(colourAlign);

		Gnm::registerResource(nullptr, ownerHandle, colourMemory, colourAlign.m_size,
			"Colour", Gnm::kResourceTypeDepthRenderTargetBaseAddress, 0);

		buffer->colourTarget.setAddresses(colourMemory, NULL, NULL);
	}

	if (depth) {
		Gnm::DataFormat depthFormat = Gnm::DataFormat::build(Gnm::kZFormat32Float);
		Gnm::TileMode	depthTileMode;

		GpuAddress::computeSurfaceTileMode(&depthTileMode, GpuAddress::kSurfaceTypeDepthOnlyTarget, depthFormat, 1);

		Gnm::StencilFormat stencilFormat = (stencil ? Gnm::kStencil8 : Gnm::kStencilInvalid);

		void* stencilMemory = 0;
		Gnm::SizeAlign stencilAlign;

		const Gnm::SizeAlign depthAlign = buffer->depthTarget.init(width, height, depthFormat.getZFormat(), stencilFormat, depthTileMode,
			Gnm::kNumFragments1, stencil ? &stencilAlign : 0, 0);

		void *depthMemory = stackAllocators[GARLIC].allocate(depthAlign);

		Gnm::registerResource(nullptr, ownerHandle, depthMemory, depthAlign.m_size,
			"Depth", Gnm::kResourceTypeDepthRenderTargetBaseAddress, 0);


		if (stencil) {
			stencilMemory = stackAllocators[GARLIC].allocate(stencilAlign);

			Gnm::registerResource(nullptr, ownerHandle, stencilMemory, stencilAlign.m_size,
				"Stencil", Gnm::kResourceTypeDepthRenderTargetBaseAddress, 0);
		}

		buffer->depthTarget.setAddresses(depthMemory, stencilMemory);
	}

	return buffer;
}

void PS4RendererBase::DestroyMemoryAllocators() {

}

void	PS4RendererBase::DestroyGCMRendering() {
	//onionAllocator->release(frames);
}

void	PS4RendererBase::DestroyVideoSystem() {
	for (int i = 0; i < _bufferCount; ++i) {
		delete screenBuffers[i];
	}
	delete[] screenBuffers;

	sceVideoOutClose(videoHandle);
}

void PS4RendererBase::UpdateScene(float dt)	{
	input.Poll();

	if (input.GetButtonDown(0)) { //triangle
		//std::cout << "0 BUTTON" << std::endl;

		std::cout << input.GetAxis(0).x << "   " << input.GetAxis(0).y << '\n';

	}
	if (input.GetButton(1)) { //circle
		std::cout << "1 BUTTON" << std::endl;
	}
	if (input.GetButton(2)) { // X
		std::cout << "2 BUTTON" << std::endl;
	}
	if (input.GetButton(3)) { //squre
		std::cout << "3 BUTTON" << std::endl;
	}
	if (input.GetButton(4)) { //L2
		std::cout << "4 BUTTON" << std::endl;
	}
	if (input.GetButton(5)) { //R2
		std::cout << "5 BUTTON" << std::endl;
	}
	if (input.GetButton(6)) { //L1
		std::cout << "6 BUTTON" << std::endl;
	}
	if (input.GetButton(7)) { //R1
		std::cout << "7 BUTTON" << std::endl;
	}
	if (input.GetButton(8)) { //left anlgo press
		std::cout << "8 BUTTON" << std::endl;
	}
	if (input.GetButton(9)) { //right anlgo press
		std::cout << "9 BUTTON" << std::endl;
	}
	if (input.GetButton(10)) { //up
		std::cout << "10 BUTTON" << std::endl;
	}
	if (input.GetButton(11)) { //right
		std::cout << "11 BUTTON" << std::endl;
	}
	if (input.GetButton(12)) { //down
		std::cout << "12 BUTTON" << std::endl;
	}
	if (input.GetButton(13)) { //left
		std::cout << "13 BUTTON" << std::endl;
	}
	//if (input.GetAxis(0).x) { //R1
	//	std::cout << "12 BUTTON" << std::endl;
	//}
	//if (input.GetAxis(0)) { //R1
	//	std::cout << "12 BUTTON" << std::endl;
	//}


	camera->UpdateCamera(dt, &input);
}

void PS4RendererBase::RenderScene()			{
	currentFrame->StartFrame();	

	currentGFXContext->waitUntilSafeForRendering(videoHandle, currentGPUBuffer);
	SetRenderBuffer(currentPS4Buffer, true, true, true);
	
	SkyboxShader->SubmitShaderSwitch(*currentGFXContext);

	//Primitive Setup State
	Gnm::PrimitiveSetup primitiveSetup;
	primitiveSetup.init();
	primitiveSetup.setCullFace(Gnm::kPrimitiveSetupCullFaceNone);
	primitiveSetup.setFrontFace(Gnm::kPrimitiveSetupFrontFaceCcw);
	//primitiveSetup.setPolygonMode()
	currentGFXContext->setPrimitiveSetup(primitiveSetup);

	//Screen Access State
	Gnm::DepthStencilControl dsc;
	dsc.init();
	dsc.setDepthControl(Gnm::kDepthControlZWriteEnable, Gnm::kCompareFuncAlways);
	dsc.setDepthEnable(false);
	currentGFXContext->setDepthStencilControl(dsc);
	currentGFXContext->setupScreenViewport(0, 0, currentPS4Buffer->colourTarget.getWidth(), currentPS4Buffer->colourTarget.getHeight(), 0.5f, 0.5f);

	Gnm::Sampler trilinearSampler;
	trilinearSampler.init();
	trilinearSampler.setMipFilterMode(Gnm::kMipFilterModeLinear);

	//trilinearSampler.set
	trilinearSampler.setXyFilterMode(Gnm::kFilterModeBilinear, Gnm::kFilterModeBilinear);

	currentGFXContext->setTextures(Gnm::kShaderStagePs, 0, 1, &defaultTexture->GetAPITexture());
	currentGFXContext->setSamplers(Gnm::kShaderStagePs, 0, 1, &trilinearSampler);
	
	//DrawSky(*quad);

	//DrawMesh(*quad);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	defaultShader->SubmitShaderSwitch(*currentGFXContext);

	//Primitive Setup State
	primitiveSetup.init();
	primitiveSetup.setCullFace(Gnm::kPrimitiveSetupCullFaceNone);
	primitiveSetup.setFrontFace(Gnm::kPrimitiveSetupFrontFaceCcw);
	//primitiveSetup.setPolygonMode()
	currentGFXContext->setPrimitiveSetup(primitiveSetup);

	//Screen Access State
	dsc.init();
	dsc.setDepthControl(Gnm::kDepthControlZWriteEnable, Gnm::kCompareFuncLessEqual);
	dsc.setDepthEnable(true);
	currentGFXContext->setDepthStencilControl(dsc);
	currentGFXContext->setupScreenViewport(0, 0, currentPS4Buffer->colourTarget.getWidth(), currentPS4Buffer->colourTarget.getHeight(), 0.5f, 0.5f);

	trilinearSampler.init();
	trilinearSampler.setMipFilterMode(Gnm::kMipFilterModeLinear);

	//trilinearSampler.set
	trilinearSampler.setXyFilterMode(Gnm::kFilterModeBilinear, Gnm::kFilterModeBilinear);

	currentGFXContext->setTextures(Gnm::kShaderStagePs, 0, 1, &defaultTexture->GetAPITexture());
	currentGFXContext->setSamplers(Gnm::kShaderStagePs, 0, 1, &trilinearSampler);


	DrawMesh(*defaultMesh);




	currentFrame->EndFrame();

	framesSubmitted++;
}

float rad = 0.0f;

void PS4RendererBase::DrawMesh(PS4Mesh& mesh) {	
	rad += 0.01;

	projMatrix = Matrix4::perspective(0.78f, (float)currentPS4Buffer->colourTarget.getWidth() / (float)currentPS4Buffer->colourTarget.getHeight(), 1.0f, 5000.0f);

	viewMatrix = camera->BuildViewMatrix();

	Matrix4* modelViewProj = (Matrix4*)currentGFXContext->allocateFromCommandBuffer(sizeof(Matrix4), Gnm::kEmbeddedDataAlignment4);
	modelMatrix = Matrix4::translation(Vector3(0, 0, -5)) * Matrix4::rotationZ(rad);


	modelViewProj[0] = projMatrix * viewMatrix * modelMatrix;
	//*modelViewProj = modelMatrix*viewMatrix*projMatrix;

	modelViewProj[1] = modelMatrix;

	Gnm::Buffer constantBuffer;
	constantBuffer.initAsConstantBuffer(modelViewProj, sizeof(Matrix4));
	constantBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK


	Matrix4* identityMat = (Matrix4*)currentGFXContext->allocateFromCommandBuffer(sizeof(Matrix4), Gnm::kEmbeddedDataAlignment4);
	*identityMat = Matrix4::rotationX(rad);

	Gnm::Buffer constantBufferA;
	constantBufferA.initAsConstantBuffer(identityMat, sizeof(Matrix4)*2);
	constantBufferA.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

	int indexA = defaultShader->GetConstantBuffer("ShaderConstants");
	int indexB = defaultShader->GetConstantBuffer("MoreShaderConstants");

	currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, indexA, 1, &constantBuffer);
	//currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, indexB, 1, &constantBufferA);
	currentGFXContext->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &constantBuffer);

	mesh.SubmitDraw(*currentGFXContext, Gnm::ShaderStage::kShaderStageVs);
}

void PS4RendererBase::DrawSky(PS4Mesh& mesh) {
	

	projMatrix = Matrix4::perspective(0.78f, (float)currentPS4Buffer->colourTarget.getWidth() / (float)currentPS4Buffer->colourTarget.getHeight(), 1.0f, 5000.0f);
	viewMatrix = camera->BuildViewMatrix();
	//modelMatrix.identity();
	modelMatrix = Matrix4::translation(Vector3(0, 0, -5)) * Matrix4::rotationZ(rad);



	Matrix4* modelViewProj = (Matrix4*)currentGFXContext->allocateFromCommandBuffer(sizeof(Matrix4)*4, Gnm::kEmbeddedDataAlignment4);

	

	modelViewProj[0] = modelMatrix;
	modelViewProj[1] = viewMatrix;
	modelViewProj[2] = projMatrix;
	modelViewProj[3] = projMatrix * viewMatrix * modelMatrix;

	Gnm::Buffer constantBuffer;
	constantBuffer.initAsConstantBuffer(modelViewProj, sizeof(Matrix4)*4);
	constantBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK


	Matrix4* identityMat = (Matrix4*)currentGFXContext->allocateFromCommandBuffer(sizeof(Matrix4), Gnm::kEmbeddedDataAlignment4);
	*identityMat = projMatrix * viewMatrix * modelMatrix;

	Gnm::Buffer constantBufferA;
	constantBufferA.initAsConstantBuffer(identityMat, sizeof(Matrix4)*4);
	constantBufferA.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

	int indexA = SkyboxShader->GetConstantBuffer("ShaderConstants");
	int indexB = SkyboxShader->GetConstantBuffer("MoreShaderConstants");

	currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, indexA, 1, &constantBuffer);
	//currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, indexB, 1, &constantBufferA);
	currentGFXContext->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &constantBuffer);

	mesh.SubmitDraw(*currentGFXContext, Gnm::ShaderStage::kShaderStageVs);
}

void PS4RendererBase::SwapBuffers()			{
	SwapScreenBuffer();
	SwapCommandBuffer();
}

void	PS4RendererBase::SwapScreenBuffer() {
	prevScreenBuffer	= currentScreenBuffer;
	currentScreenBuffer = (currentScreenBuffer + 1) % _bufferCount;
	sceVideoOutSubmitFlip(videoHandle, prevScreenBuffer, SCE_VIDEO_OUT_FLIP_MODE_VSYNC, 0);

	currentPS4Buffer = screenBuffers[currentScreenBuffer];
}

void	PS4RendererBase::SwapCommandBuffer() {
	if (currentGFXContext) {	
		if (currentGFXContext->submit() != sce::Gnm::kSubmissionSuccess) {
			bool a = true;
		}
		Gnm::submitDone();
	}

	currentGPUBuffer = (currentGPUBuffer + 1) % _MaxCMDBufferCount;

	currentFrame		= &frames[currentGPUBuffer];
	currentGFXContext	= &currentFrame->GetCommandBuffer();
}

void	PS4RendererBase::SetRenderBuffer(PS4ScreenBuffer*buffer, bool clearColour, bool clearDepth, bool clearStencil) {
	currentPS4Buffer = buffer;

	ClearBuffer(clearColour, clearDepth, clearStencil);

	currentGFXContext->setRenderTargetMask(0xF);
	currentGFXContext->setRenderTarget(0, &currentPS4Buffer->colourTarget);
	currentGFXContext->setDepthRenderTarget(&currentPS4Buffer->depthTarget);
}

void	PS4RendererBase::ClearBuffer(bool colour, bool depth, bool stencil) {
	if (colour) {
		//Vector4 defaultClearColour(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f);
		Vector4 defaultClearColour(0.1f, 0.1f, 0.1f, 1.0f);

		SurfaceUtil::clearRenderTarget(*currentGFXContext, &currentPS4Buffer->colourTarget, defaultClearColour);
	}

	if (depth) {
		float defaultDepth = 1.0f;
		SurfaceUtil::clearDepthTarget(*currentGFXContext, &currentPS4Buffer->depthTarget, defaultDepth);
	}

	if (stencil && currentPS4Buffer->depthTarget.getStencilReadAddress()) {
		int defaultStencil = 0;
		SurfaceUtil::clearStencilTarget(*currentGFXContext, &currentPS4Buffer->depthTarget, defaultStencil);
	}
}