#include "Scene.h"

int main() {
	Scene scene("Tutorial", 640, 480, 4, 3, true);

	while (!scene.GetWindowShouldClose()) {
		//Update input
		scene.Update();
		scene.Render();
	}
	
}