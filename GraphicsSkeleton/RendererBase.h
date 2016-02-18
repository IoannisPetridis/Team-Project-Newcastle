#pragma once

class RendererBase
{
public:
	RendererBase();
	virtual ~RendererBase();

	virtual void UpdateScene(float dt)	= 0;
	virtual void RenderScene()			= 0;
	virtual void SwapBuffers()			= 0;
};

