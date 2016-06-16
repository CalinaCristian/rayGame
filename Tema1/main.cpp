/*CALINA CRISTIAN FLORIN 333CA*/
#include "main.h"
#include "functions.h"

int main()
{
	init(camera, lightSource, scene, light, obiectCircle, obiectRectangle, reflectionCounter, hitCamera);
	while (window.isOpen())
	{
		treatEvents();
		window.clear();
		drawScene(scene);
		drawCamera(camera);
		drawLightSource(lightSource);
		drawObjects(obiectCircle, obiectRectangle);
		drawLight(light, reflectionCounter);
		window.display();
	}
	return 0;
}