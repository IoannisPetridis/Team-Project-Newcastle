#include "PS4RendererBase.h"
#include "PS4Input.h"

#include <iostream>

int main(void) {
	PS4RendererBase renderer;

	while (true) {
		renderer.UpdateScene(1.0f);
		renderer.RenderScene();
		renderer.SwapBuffers();
	}

	return 1;
}