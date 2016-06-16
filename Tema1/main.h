/*CALINA CRISTIAN FLORIN 333CA*/
#include <SFML/Graphics.hpp>
#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 600
#define SCENE_WIDTH 1290
#define SCENE_HEIGHT 590
#define SCENE_OUTLINE 5
#define SCENE_RGB 150
#define SCENE_POSITION 5
#define LIGHT_SOURCE_SIZE 50
#define LIGHT_SOURCE_X 250 
#define LIGHT_SOURCE_Y 150
#define LIGHT_SOURCE_CENTER_X 300
#define LIGHT_SOURCE_CENTER_Y 200
#define CAMERA_SIDE_1_X 1205
#define CAMERA_SIDE_1_Y 5
#define CAMERA_SIDE_2_X 1295
#define CAMERA_SIDE_2_Y 5
#define CAMERA_SIDE_3_X 1295
#define CAMERA_SIDE_3_Y 95
#define PI 3.141592653589
#define EPSILON 1

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tema 1");
sf::RectangleShape scene;
sf::CircleShape lightSource(LIGHT_SOURCE_SIZE);
sf::VertexArray camera(sf::Triangles, 3);
sf::RectangleShape obiectRectangle[9];
sf::CircleShape obiectCircle[1];
sf::RectangleShape light[20];
int reflectionCounter = 0;
bool hitCamera = false;