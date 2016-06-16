/*CALINA CRISTIAN FLORIN 333CA*/
//functie ce initializeaza toate obiectele ce urmeaza sa fie desenate
void init(sf::VertexArray &camera, sf::CircleShape &lightSource, sf::RectangleShape &scene,
	sf::RectangleShape light[20], sf::CircleShape  obiectCircle[1], sf::RectangleShape  obiectRectangle[9], int &reflectionCounter,
	bool &hitCamera) {

	lightSource.setFillColor(sf::Color(255, 255, 0));
	lightSource.setPosition(LIGHT_SOURCE_X, LIGHT_SOURCE_Y);

	camera[0].position = sf::Vector2f(CAMERA_SIDE_1_X, CAMERA_SIDE_1_Y);
	camera[1].position = sf::Vector2f(CAMERA_SIDE_2_X, CAMERA_SIDE_2_Y);
	camera[2].position = sf::Vector2f(CAMERA_SIDE_3_X, CAMERA_SIDE_3_Y);

	camera[0].color = sf::Color::Black;
	camera[1].color = sf::Color::Black;
	camera[2].color = sf::Color::Black;

	scene.setSize(sf::Vector2f(SCENE_WIDTH, SCENE_HEIGHT));
	scene.setOutlineColor(sf::Color::Black);
	scene.setOutlineThickness(SCENE_OUTLINE);
	scene.setFillColor(sf::Color(SCENE_RGB, SCENE_RGB, SCENE_RGB));
	scene.setPosition(SCENE_POSITION, SCENE_POSITION);

	light[0].setFillColor(sf::Color(255, 255, 0));
	light[0].setPosition(sf::Vector2f(LIGHT_SOURCE_CENTER_X, LIGHT_SOURCE_CENTER_Y));
	light[0].setOrigin(sf::Vector2f(5, 0));
	light[0].setSize(sf::Vector2f(10, 1));

	for (int i = 0; i < 10; i++){
		if (i < 1){
			//am folosit si un cerc pentru testarea coliziunii cu acesta.
			obiectCircle[i].setRadius((i * 244) % 75 + 34);
			obiectCircle[i].setFillColor(sf::Color(143,123,240));
			obiectCircle[i].setPosition(940,290);
		}
		else {
			//am incercat sa fac cat mai aleator poizitionarea obiectelor folosind % (pentru a nu le amplasa manual pe toate ci printr-un for)
			obiectRectangle[i - 1].setSize(sf::Vector2f((i * 93) % 250, (i * 699) % 100));
			obiectRectangle[i - 1].setPosition((i * 5030 + 31) % SCENE_WIDTH, (i * 355) % SCENE_HEIGHT + 3);
			obiectRectangle[i - 1].setFillColor(sf::Color((i * 314) % 255, (i * 845) % 255, (i * 623) % 255));
		}
	}
	reflectionCounter = 0;
	hitCamera = false;
}

//functie ce trateaza evenimentele (dreapta stanga escape)
void treatEvents(){
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::Right){
				reflectionCounter = 0;
				hitCamera = false;
				light[reflectionCounter].setFillColor(sf::Color(255, 255, 0));
				light[reflectionCounter].setPosition(sf::Vector2f(LIGHT_SOURCE_CENTER_X, LIGHT_SOURCE_CENTER_Y));
				light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
				light[reflectionCounter].setSize(sf::Vector2f(10, 1));
				light[reflectionCounter].setRotation(light[reflectionCounter].getRotation() - 5);
			}
			else if (event.key.code == sf::Keyboard::Left){
				reflectionCounter = 0;
				hitCamera = false;
				light[reflectionCounter].setFillColor(sf::Color(255, 255, 0));
				light[reflectionCounter].setPosition(sf::Vector2f(LIGHT_SOURCE_CENTER_X, LIGHT_SOURCE_CENTER_Y));
				light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
				light[reflectionCounter].setSize(sf::Vector2f(10, 1));
				light[reflectionCounter].setRotation(light[reflectionCounter].getRotation() + 5);
			}
			else if (event.key.code == sf::Keyboard::Escape){
				window.close();
			}
		}

	}
}

//desenat scena
void drawScene(sf::RectangleShape &scene){
	window.draw(scene);
}
//desenat sursa lumina
void drawLightSource(sf::CircleShape &lightSource){
	window.draw(lightSource);
}
//desenat camera
void drawCamera(sf::VertexArray &camera){
	window.draw(camera);
}
//desenat obiecte (dreptunghiuri si cercuri)
void drawObjects(sf::CircleShape  obiectCircle[3], sf::RectangleShape  obiectRectangle[7]){
	for (int i = 0; i < 10; i++){
		if (i < 1){
			window.draw(obiectCircle[i]);
		}
		else {
			window.draw(obiectRectangle[i - 1]);
		}
	}
}
//desenat raza
void drawLight(sf::RectangleShape light[20], int &reflectionCounter){
	//Cat timp nu s-a atins maximul de reflexii si nu s-a lovit camera , se recalculeaza raza.
	if ((reflectionCounter < 19)&&(!hitCamera)){
		sf::Vector2f size = light[reflectionCounter].getSize();
		sf::Vector2f pos = light[reflectionCounter].getPosition();
		//cresc height-ul razei cu 1 la fiecare redesenare
		light[reflectionCounter].setSize(sf::Vector2f(size.x, size.y + 1));
		//onx si ony sunt x-ul si y-ul folosite tinand cont de pozitia initiala si unghiul de rotatie.
		float onx = pos.x + size.y * (cos((light[reflectionCounter].getRotation() + 90) * PI / 180));
		float ony = pos.y + size.y * (sin((light[reflectionCounter].getRotation() + 90) * PI / 180));

		//ecuatia dreptei pentru intersectarea cu camera:
		float A = CAMERA_SIDE_3_Y - CAMERA_SIDE_1_Y;
		float B = CAMERA_SIDE_1_X - CAMERA_SIDE_3_X;
		float C = -(A * CAMERA_SIDE_1_X) + B * CAMERA_SIDE_1_Y;

		//distanta de la punct la dreapta (raza la latura camerei)
		float cameraCollision = (abs( (A * onx) + (B * ony ) + C)) / (sqrt(pow(A, 2) + pow(B, 2)));

		//coliziunea cu peretele de jos
		if (ony >= SCENE_HEIGHT){
			//trec la raza urmatoare
			reflectionCounter++;
			light[reflectionCounter].setSize(sf::Vector2f(10, 1));
			//calculez media aritmetica a culorilor razei antecedente si obiectului de care s-a lovit
			light[reflectionCounter].setFillColor
				(sf::Color((light[reflectionCounter - 1].getFillColor().r + scene.getOutlineColor().r) / 2,
				(light[reflectionCounter - 1].getFillColor().g + scene.getOutlineColor().g) / 2,
				(light[reflectionCounter - 1].getFillColor().b + scene.getOutlineColor().b) / 2));
			//ii setez originea pentru a fi pe centru rotatia (are width-ul 10 deci ii pun pe 5 originea)
			light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
			//setez pozitia in locul in care a lovit
			light[reflectionCounter].setPosition(onx, SCENE_HEIGHT);
			//setez rotatia ca fiind opusul rotatiei antecendente
			light[reflectionCounter].setRotation(180 - (light[reflectionCounter - 1].getRotation()));
		}
		//coliziunea cu peretele de sus
		else if (ony <= SCENE_OUTLINE){
			reflectionCounter++;
			if (reflectionCounter < 19){
				light[reflectionCounter].setSize(sf::Vector2f(10, 1));
				light[reflectionCounter].setFillColor
					(sf::Color((light[reflectionCounter - 1].getFillColor().r + scene.getOutlineColor().r) / 2,
					(light[reflectionCounter - 1].getFillColor().g + scene.getOutlineColor().g) / 2,
					(light[reflectionCounter - 1].getFillColor().b + scene.getOutlineColor().b) / 2));
				light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
				light[reflectionCounter].setPosition(onx, SCENE_OUTLINE);
				light[reflectionCounter].setRotation(180 - (light[reflectionCounter - 1].getRotation()));
			}
		}
		//coliziunea cu peretele din dreapta
		else if (onx >= SCENE_WIDTH){
			reflectionCounter++;
			if (reflectionCounter < 19){
				light[reflectionCounter].setSize(sf::Vector2f(10, 1));
				light[reflectionCounter].setFillColor
					(sf::Color((light[reflectionCounter - 1].getFillColor().r + scene.getOutlineColor().r) / 2,
					(light[reflectionCounter - 1].getFillColor().g + scene.getOutlineColor().g) / 2,
					(light[reflectionCounter - 1].getFillColor().b + scene.getOutlineColor().b) / 2));
				light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
				light[reflectionCounter].setPosition(sf::Vector2f(SCENE_WIDTH, ony));
				light[reflectionCounter].setRotation(-(light[reflectionCounter - 1].getRotation()));
			}
		}
		//coliziunea cu peretele din stanga
		else if (onx <= SCENE_OUTLINE){
			reflectionCounter++;
			if (reflectionCounter < 19){
				light[reflectionCounter].setSize(sf::Vector2f(10, 1));
				light[reflectionCounter].setFillColor
					(sf::Color((light[reflectionCounter - 1].getFillColor().r + scene.getOutlineColor().r) / 2,
					(light[reflectionCounter - 1].getFillColor().g + scene.getOutlineColor().g) / 2,
					(light[reflectionCounter - 1].getFillColor().b + scene.getOutlineColor().b) / 2));
				light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
				light[reflectionCounter].setPosition(sf::Vector2f(SCENE_OUTLINE, ony));
				light[reflectionCounter].setRotation(-(light[reflectionCounter - 1].getRotation()));
			}
		}
		//coliziunea cu camera cu o marja de eroare
		else if (cameraCollision < 5){
			hitCamera = true;
		}

		//coliziunea cu un obiect(cerc sau dreptunghi)
		for (int i = 0; i < 10; i++){
			if (i < 1){
				//cerc
				float radius = obiectCircle[i].getRadius();
				float circlex = obiectCircle[i].getPosition().x + radius;
				float circley = obiectCircle[i].getPosition().y + radius;
				//calculez distanta de la punctul de pe raza la centru cercului
				float distanceCenter = sqrt(pow((onx - circlex), 2) + pow((ony - circley), 2));
				//daca distanta e mai mica decat raza cercului atunci avem coliziune
				if (distanceCenter <= radius){
					reflectionCounter++;
					if (reflectionCounter < 19){
						light[reflectionCounter].setSize(sf::Vector2f(10, 1));
						light[reflectionCounter].setFillColor
							(sf::Color((light[reflectionCounter - 1].getFillColor().r + obiectCircle[i].getFillColor().r) / 2,
							(light[reflectionCounter - 1].getFillColor().g + obiectCircle[i ].getFillColor().g) / 2,
							(light[reflectionCounter - 1].getFillColor().b + obiectCircle[i].getFillColor().b) / 2));
						light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
						light[reflectionCounter].setPosition(onx, ony);
						
						//panta ecuatiei normalei la intersectie
						float panta = ( circley - ony ) / ( circlex - onx );

						//unghiul de rotatie (cu ajutorul internetului am gasit aceasta formula).
						light[reflectionCounter].setRotation(2 * (atan(panta * 180/PI)) - (270 - light[reflectionCounter-1].getRotation()));
					}
				}
			}
			else {
				//drepthunghi
				sf::Vector2f rectanglePos = obiectRectangle[i-1].getPosition();
				sf::Vector2f rectangleSize = obiectRectangle[i-1].getSize();

				//coliziunea cu unul dintre peretii dreptunghiului(in acest caz se afla in interiorul dreptunghiului)
				if ((ony >= rectanglePos.y) &&
					(ony <= rectanglePos.y + rectangleSize.y) &&
					(onx >= rectanglePos.x) &&
					(onx <= rectanglePos.x + rectangleSize.x)){
				
					//Daca sunt si pe y si pe x (foarte aproape de ambele) cu eroare epsilon , vad care e la distanta mai 
					//mica(mi s-a intamplat pe cazul meu asa ca am tratat si acest caz).
					if ((((int)onx == (int)rectanglePos.x) || ((int)onx + EPSILON == (int)rectanglePos.x) ||
				((int)onx == (int)(rectanglePos.x + rectangleSize.x)) || ((int)onx + EPSILON == (int)(rectanglePos.x + rectangleSize.x))) &&
				(((int)ony == (int)rectanglePos.y) || ((int)ony + EPSILON == (int)rectanglePos.y) ||
				((int)ony == (int)(rectanglePos.y + rectangleSize.y)) || ((int)ony + EPSILON == (int)(rectanglePos.y + rectangleSize.y))))
					{
						float distanceX = rectanglePos.x - onx;
						float distanceY = rectanglePos.y - ony;
						//daca distanta nu e buna (e prea mare) , mai scad si size-ul (inseamna ca sunt pe cealalta latura).
						//sau il cresc daca e negativ mai mic ca -1.
						if (distanceX > EPSILON){
							distanceX -= rectangleSize.x;
						}
						else if (distanceX < -EPSILON){
							distanceX += rectangleSize.x;
						}
						if (distanceY > EPSILON){
							distanceY -= rectangleSize.y;
						}
						else if (distanceY < -EPSILON){
							distanceY += rectangleSize.y;
						}
						if (distanceX < distanceY){
							reflectionCounter++;
							if (reflectionCounter < 19){
								light[reflectionCounter].setSize(sf::Vector2f(10, 1));
								light[reflectionCounter].setFillColor
									(sf::Color((light[reflectionCounter - 1].getFillColor().r + obiectRectangle[i - 1].getFillColor().r) / 2,
									(light[reflectionCounter - 1].getFillColor().g + obiectRectangle[i - 1].getFillColor().g) / 2,
									(light[reflectionCounter - 1].getFillColor().b + obiectRectangle[i - 1].getFillColor().b) / 2));
								light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
								light[reflectionCounter].setPosition(onx, ony);
								light[reflectionCounter].setRotation(-(light[reflectionCounter - 1].getRotation()));
							}
						}
						else {
							reflectionCounter++;
							if (reflectionCounter < 19){
								light[reflectionCounter].setSize(sf::Vector2f(10, 1));
								light[reflectionCounter].setFillColor
									(sf::Color((light[reflectionCounter - 1].getFillColor().r + obiectRectangle[i - 1].getFillColor().r) / 2,
									(light[reflectionCounter - 1].getFillColor().g + obiectRectangle[i - 1].getFillColor().g) / 2,
									(light[reflectionCounter - 1].getFillColor().b + obiectRectangle[i - 1].getFillColor().b) / 2));
								light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
								light[reflectionCounter].setPosition(onx, ony);
								light[reflectionCounter].setRotation(180 - (light[reflectionCounter - 1].getRotation()));
							}
						}
					}
					//altfel verific daca se intra pe x
					else if (((int)onx == (int)rectanglePos.x) || ((int)onx + EPSILON == (int)rectanglePos.x) ||
						((int)onx == (int)(rectanglePos.x + rectangleSize.x)) || ((int)onx + EPSILON == (int)(rectanglePos.x + rectangleSize.x))){
						reflectionCounter++;
						if (reflectionCounter < 19){
							light[reflectionCounter].setSize(sf::Vector2f(10, 1));
							light[reflectionCounter].setFillColor
								(sf::Color((light[reflectionCounter - 1].getFillColor().r + obiectRectangle[i - 1].getFillColor().r) / 2,
								(light[reflectionCounter - 1].getFillColor().g + obiectRectangle[i - 1].getFillColor().g) / 2,
								(light[reflectionCounter - 1].getFillColor().b + obiectRectangle[i - 1].getFillColor().b) / 2));
							light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
							light[reflectionCounter].setPosition(onx, ony);
							light[reflectionCounter].setRotation(-(light[reflectionCounter - 1].getRotation()));
						}
					}
					//sau pe y
					else {
						reflectionCounter++;
						if (reflectionCounter < 19){
							light[reflectionCounter].setSize(sf::Vector2f(10, 1));
							light[reflectionCounter].setFillColor
								(sf::Color((light[reflectionCounter - 1].getFillColor().r + obiectRectangle[i - 1].getFillColor().r) / 2,
								(light[reflectionCounter - 1].getFillColor().g + obiectRectangle[i - 1].getFillColor().g) / 2,
								(light[reflectionCounter - 1].getFillColor().b + obiectRectangle[i - 1].getFillColor().b) / 2));
							light[reflectionCounter].setOrigin(sf::Vector2f(5, 0));
							light[reflectionCounter].setPosition(onx, ony);
							light[reflectionCounter].setRotation(180 - (light[reflectionCounter - 1].getRotation()));
						}
					}
				}
			}
		}
	}
	//desenez doar pana la reflectionCounter , astfel se rescriu razele si se afiseaza doar cele dorite.
	for (int i = 0; i <= reflectionCounter; i++){
		window.draw(light[i]);
	}
}
