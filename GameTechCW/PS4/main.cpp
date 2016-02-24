#include "PS4RendererBase.h"
#include "PS4Input.h"

#include <iostream>

using std::cout;
using std::endl;

unsigned int sceLibcHeapExtendedAlloc = 1;
size_t sceLibcHeapSize = 512 * 1024 * 1024;

int main(void) {
	PS4RendererBase renderer;

	while (true) {
		renderer.UpdateScene(1.0f);
		renderer.RenderScene();
		renderer.SwapBuffers();	
	}

	return 1;
}