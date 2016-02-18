#include "ExampleRenderer.h"
#include "PS4Input.h"

#include <iostream>

int main(void) {
	ExampleRenderer renderer;


	while (true) {
		//for the controller
		


		renderer.UpdateScene(1.0f);
		renderer.RenderScene();
		renderer.SwapBuffers();


		
		//if (input.GetButton(6)) { //L1
		//	return 1;
		//}
	}

	return 1;
}