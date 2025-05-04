#include "ofApp.h"
#include "HighScoreManager.cpp"
#include <GLFW/glfw3.h>
#include "materiais.h"




//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	ofDisableArbTex();//para utilizar coordenadas de textura normalizadas

	ofSetFullscreen(true);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	


	//mostra o estado inicial das matrizes
	coutModelviewMatrix();
	coutProjectionMatrix();
	

	glPointSize(200);
	glLineWidth(3);

	lastUpdateTime = 0.0;
	updateInterval; // 0.5 seconds
	touching = false;
	size = 1;
	
	positions.clear();
	positions.push_back(snakeHeadPosition);

	snakeSpeedX = 0;
	snakeSpeedY = 0;
	snakeSpeedZ = 0;

	setupSnake();


	// Initialize scores
	currentScore = 0;
	highScore = 0;

	// Load a font for the scoreboard
	scoreFont.load("fonte.ttf", 30);  // Adjust font and size as needed

	createFood();

	isDeathAnimationActive = false;
	deathAnimationStartTime = 0;
	deathAnimationDuration = 4.0f; // 4 seconds for the entire animation
	screenShakeOffset = ofVec2f(0, 0);
	fadeAlpha = 0;
	overlay = false;

	
	sphere.setRadius(1);
	sphere.setResolution(20);

	multiview = false;
	oneview = true;

	view1 = 0;
	view2 = 0;

	// Inicializa os estados das luzes
	ambientOn = true; // Luz ambiente global
	dirOn = true;     // Luz Direcional
	pointOn = true;   // Luz Pontual
	spotOn = true;    // Luz Spotlight

	// Inicializa os estados das componentes das luzes
	for (int i = 0; i < 3; i++) {
		ambientCompOn[i] = true;
		diffuseCompOn[i] = true;
		specularCompOn[i] = true;
	}

	// Propriedades da Luz Direcional
	dirDirection.set(-1.0f, -1.0f, -1.0f);
	dirAmbient[0] = 0.7f; dirAmbient[1] = 0.7f; dirAmbient[2] = 0.7f; dirAmbient[3] = 1.0f;
	dirDiffuse[0] = 0.8f; dirDiffuse[1] = 0.8f; dirDiffuse[2] = 0.8f; dirDiffuse[3] = 1.0f;
	dirSpecular[0] = 1.0f; dirSpecular[1] = 1.0f; dirSpecular[2] = 1.0f; dirSpecular[3] = 1.0f;


	// Propriedades da Luz Pontual
	//pointPosition.set(0.0f, 0.0f, 100.0f); // Posicionada acima
	pointAmbient[0] = 1.0f; pointAmbient[1] = 1.0f; pointAmbient[2] = 1.0f; pointAmbient[3] = 1.0f;
	pointDiffuse[0] = 0.8f; pointDiffuse[1] = 0.8f; pointDiffuse[2] = 0.8f; pointDiffuse[3] = 1.0f;
	pointSpecular[0] = 1.0f; pointSpecular[1] = 1.0f; pointSpecular[2] = 1.0f; pointSpecular[3] = 1.0f;
	pointAttenuation[0] = 0.0f; // Constante
	pointAttenuation[1] = 0.0005f; // Linear
	pointAttenuation[2] = 0.0f; // Quadrática

	// Propriedades da Luz Spotlight
	//spotPosition.set(0.0f, 0.0f, 100.0f); // Posicionada acima
	//spotDirection.set(0.0f, 0.0f, -1.0f); // Direcionada para baixo
	spotAmbient[0] = 0.0f; spotAmbient[1] = 1.0f; spotAmbient[2] = 0.0f; spotAmbient[3] = 1.0f;
	spotDiffuse[0] = 0.0f; spotDiffuse[1] = 1.0f; spotDiffuse[2] = 0.0f; spotDiffuse[3] = 1.0f;
	spotSpecular[0] = 1.0f; spotSpecular[1] = 1.0f; spotSpecular[2] = 1.0f; spotSpecular[3] = 1.0f;
	spotExponent = 30.0f;
	spotCutoff = 45.0f;
	// Spotlight attenuation factors
	spotAttenuation[0] = 0.01f; // Constante
	spotAttenuation[1] = 0.00001f; // Linear
	spotAttenuation[2] = 0.0f; // Quadrática


	snakeSkinImage.load("SnakeSkin.jpg");
	OrangeSkin.load("OrangeSkin.jpg");
	Death.load("Death.jpg");
	
	
}

//--------------------------------------------------------------
void ofApp::update() {
	double currentTime = glfwGetTime();
	
	if (updateInterval == 0.5 && currentScore >= 150) {
		updateInterval = 0.4;
	}

	if (updateInterval == 0.4 && currentScore >= 300) {
		updateInterval = 0.3;
	}

	if (!isDeathAnimationActive) {
		if (currentTime - lastUpdateTime >= updateInterval) {

			snakeHeadPositionX = snakeHeadPositionX + snakeSpeedX;
			snakeHeadPositionY = snakeHeadPositionY + snakeSpeedY;
			if (resZ != 1) snakeHeadPositionZ = snakeHeadPositionZ + snakeSpeedZ;

			if (touching == true) {
				cout << "Snake size: " << size << endl;  // Add this line
				printSnakePositions(positions);
				size++;
			}

			collide();
			
			
			snakeHeadPosition.x = snakeHeadPositionX * squareWidth + floorInitialX;
			snakeHeadPosition.y = snakeHeadPositionY * squareHeight + floorInitialY;
			snakeHeadPosition.z = snakeHeadPositionZ * squareDepth + floorInitialZ;

	
			positions = updateBody(size, positions);

			// Set the spotlight's position to the snake's head position
			spotPosition.set(snakeHeadPosition.x, snakeHeadPosition.y, snakeHeadPosition.z);

			// Compute the snake's movement direction vector
			ofVec3f movementDirection(snakeSpeedX, snakeSpeedY, snakeSpeedZ);

			// snake is not moving
			if (movementDirection.length() == 0) {
				movementDirection.set(1.0f, 0.0f, 0.0f);
			}

			// Normalize the movement direction
			movementDirection.normalize();

			// Set the spotlight's direction
			spotDirection.set(movementDirection);

			if (checkCollision(positions) || checkGrid()) {
				// Handle game over
				touching = false;
				startDeathAnimation();
				//resetGame();
			}

			lastUpdateTime = currentTime;
		}
	}
	else {
		updateDeathAnimation();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	

	glPushMatrix();

	// Apply screen shake
	if (isDeathAnimationActive) {
		glTranslatef(screenShakeOffset.x, screenShakeOffset.y, 0);
	}
	// Draw fade overlay
	if (overlay) {
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			int materialIndex = 0; // Set the material properties for this segment
			loadMaterial(materialIndex);// Use the desired material index

			Death.bind();

			// Configure the texture to repeat
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glColor3f(1, 1, 1);

			// Calculate the number of tiles
			float tileX = 4.0f; // Number of times along the X axis
			float tileY = 3.0f; // Number of times along the Y axis

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
			glTexCoord2f(tileX, 0); glVertex3f(gw(), 0, 0);
			glTexCoord2f(tileX, tileY); glVertex3f(gw(), gh(), 0);
			glTexCoord2f(0, tileY); glVertex3f(0, gh(), 0);
			glEnd();
			
			Death.unbind();
		glPopMatrix();
	}
	else {

		//desenhar a interface
		glDisable(GL_LIGHTING);

		// Draw scoreboard
		glColor3f(1, 1, 1); // Set text color to white
		string scoreText = "Current Score: " + ofToString(currentScore) +
			"  High Score: " + ofToString(highScoreManager.getHighScore());
		scoreFont.drawString(scoreText, 30, 60); // Position the text in the top-left corner
		
		// Reabilite a iluminação para objetos 3D
		glEnable(GL_LIGHTING);

		// Set the material properties for this segment
		int materialIndex = 4; // Use the desired material index
		loadMaterial(materialIndex);

		if (multiview) {
			// Left viewport
			glViewport(0, (gh() - (gw() * 0.5)) * 0.5, gw() * 0.5, gw() * 0.5);
			switch (view1) {
			case 0:
				cameraView0();
				break;
			case 1:
				cameraView1();
				break;
			case 2:
				cameraView2();
				break;
			}

			
			// Right viewport (First-person snake view)
			glViewport(gw() * 0.5, (gh() - (gw() * 0.5)) * 0.5, gw() * 0.5, gw() * 0.5);
			switch (view2) {
			case 0:
				cameraView0();
				break;
			case 1:
				cameraView1();
				break;
			case 2:
				cameraView2();
				break;
			}
		}
		if (oneview) {
			glViewport((gw() - gh()) / 2, 0, gh(), gh());
			switch (view1) {
			case 0:
				cameraView0();
				break;
			case 1:
				cameraView1();
				break;
			case 2:
				cameraView2();
				break;
			}
		}

		glPopMatrix();
	}
	
}


void ofApp::lights() {
	// Configuração da Iluminação
	glEnable(GL_LIGHTING); // Habilita a iluminação

	// Luz Ambiente Global
	if (ambientOn) {
		GLfloat globalAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	}
	else {
		GLfloat globalAmbientOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientOff);
	}

	// Luz Direcional (GL_LIGHT0)
	if (dirOn) {
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, &dirDirection[0]);
		if (ambientCompOn[0]) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmbient);
		}
		else {
			GLfloat ambientOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientOff);
		}

		if (diffuseCompOn[0]) {
			glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDiffuse);
		}
		else {
			GLfloat diffuseOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseOff);
		}

		if (specularCompOn[0]) {
			glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpecular);
		}
		else {
			GLfloat specularOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT0, GL_SPECULAR, specularOff);
		}
	}
	else {
		glDisable(GL_LIGHT0);
	}

	// Luz Pontual (GL_LIGHT1)
	if (pointOn) {
		glEnable(GL_LIGHT1);

		// Create an array with four components: x, y, z, w
		GLfloat position[] = { pointPosition.x, pointPosition.y, pointPosition.z, 1.0f }; // w = 1.0f para luz pontual

		glLightfv(GL_LIGHT1, GL_POSITION, position);
		if (ambientCompOn[1]) {
			glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmbient);
		}
		else {
			GLfloat ambientOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambientOff);
		}

		if (diffuseCompOn[1]) {
			glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDiffuse);
		}
		else {
			GLfloat diffuseOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseOff);
		}

		if (specularCompOn[1]) {
			glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpecular);
		}
		else {
			GLfloat specularOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT1, GL_SPECULAR, specularOff);
		}

		// Atenuação
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, pointAttenuation[0]);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, pointAttenuation[1]);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, pointAttenuation[2]);
	}
	else {
		glDisable(GL_LIGHT1);
	}

	if (spotOn) {
		glEnable(GL_LIGHT2);

		// Set the position with w = 1.0f (for positional light)
		GLfloat spotPos[] = { spotPosition.x, spotPosition.y, spotPosition.z, 1.0f };
		glLightfv(GL_LIGHT2, GL_POSITION, spotPos);

		// Set the direction (normalized in update())
		GLfloat spotDir[] = { spotDirection.x, spotDirection.y, spotDirection.z };
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

		// Ambient, diffuse, and specular components
		if (ambientCompOn[2]) {
			glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmbient);
		}
		else {
			GLfloat ambientOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT2, GL_AMBIENT, ambientOff);
		}

		if (diffuseCompOn[2]) {
			glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDiffuse);
		}
		else {
			GLfloat diffuseOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseOff);
		}

		if (specularCompOn[2]) {
			glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);
		}
		else {
			GLfloat specularOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glLightfv(GL_LIGHT2, GL_SPECULAR, specularOff);
		}

		// Set attenuation factors
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAttenuation[0]);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAttenuation[1]);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAttenuation[2]);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	// Representação Visual das Luzes (Opcional)
	glDisable(GL_LIGHTING); // Desabilita iluminação para desenhar representações das luzes

	// Luz Direcional
	if (dirOn) {
		glColor3f(255, 255, 0); // Amarelo para direção
		glPushMatrix();
			glTranslatef(dirDirection.x * 50, dirDirection.y * 50, dirDirection.z * 50);
			ofDrawSphere(2);
		glPopMatrix();
	}

	// Luz Pontual
	if (pointOn) {
		glColor3f(255, 0, 0); // Vermelho para ponto
		glPushMatrix();
			glTranslatef(pointPosition.x, pointPosition.y, pointPosition.z);
			ofDrawSphere(2);
		glPopMatrix();
	}

	// Luz Spotlight
	if (spotOn) {
		glColor3f(0, 0, 255); // Azul para spotlight
		glPushMatrix();
			glTranslatef(spotPosition.x, spotPosition.y, spotPosition.z);
			ofDrawSphere(2);
		glPopMatrix();

		// Desenha a direção do Spotlight
		ofSetColor(0, 255, 0);
		glBegin(GL_LINES);
		glVertex3f(spotPosition.x, spotPosition.y, spotPosition.z);
		glVertex3f(spotPosition.x + spotDirection.x * 20, spotPosition.y + spotDirection.y * 20, spotPosition.z + spotDirection.z * 20);
		glEnd();
	}

	glEnable(GL_LIGHTING); // Reabilita a iluminação para desenhar os objetos

}

//3D view
void ofApp::cameraView0() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(30, 100, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (resZ == 1) lookat(floorCenterX, floorCenterY, floorDepth * 1.5, floorCenterX, floorCenterY, floorCenterZ, 0, 1, 0);
	else lookat(floorCenterX, floorCenterY, floorDepth * 2.5, floorCenterX, floorCenterY, floorCenterZ, 0, 1, 0);
	// Apply screen shake
	if (isDeathAnimationActive) {
		glTranslatef(screenShakeOffset.x, screenShakeOffset.y, 0);
	}
	// Draw scene for left viewport
	drawScene();
}

//First - person snake view
void ofApp::cameraView1() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(90, 1, max(floorWidth, max(floorHeight, floorDepth)) * 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Calculate look-at point and up vector based on snake's direction
	float lookAtX = snakeHeadPosition.x, lookAtY = snakeHeadPosition.y, lookAtZ = snakeHeadPosition.z;
	float upX = 0, upY = 1, upZ = 0;  // Default up vector

	if (snakeSpeedX != 0) {
		lookAtX = snakeSpeedX > 0 ? floorCenterX + floorWidth / 2 : floorCenterX - floorWidth / 2;
		// Up vector remains (0, 1, 0) when moving along X
	}
	else if (snakeSpeedY != 0) {
		lookAtY = snakeSpeedY > 0 ? floorCenterY + floorHeight / 2 : floorCenterY - floorHeight / 2;
		// When moving along Y, use Z as up vector
		upY = 0;
		upZ = -snakeSpeedY;  // Negative to keep "up" consistent
	}
	else if (snakeSpeedZ != 0) {
		lookAtZ = snakeSpeedZ > 0 ? floorCenterZ + floorDepth / 2 : floorCenterZ - floorDepth / 2;
		// When moving along Z, use Y as up vector (already default)
	}

	// Set up the camera
	lookat(positions[0].x - snakeSpeedX * squareWidth * 2, positions[0].y - snakeSpeedY * squareWidth * 2, positions[0].z - snakeSpeedZ * squareWidth * 2,  // Camera position (snake's head)
		lookAtX, lookAtY, lookAtZ,  // Look-at point (wall in movement direction)
		upX, upY, upZ);  // Up vector
	// Apply screen shake
	if (isDeathAnimationActive) {
		glTranslatef(screenShakeOffset.x, screenShakeOffset.y, 0);
	}
	// Draw scene for right viewport
	drawScene();
}

//Ortographic view
void ofApp::cameraView2() {
	// Orthographic view from left side
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-floorWidth / 2, floorWidth / 2, -floorHeight / 2, floorHeight / 2, -floorDepth, floorDepth);
	//glOrtho(floorCenterX - floorWidth / 2, floorCenterX + floorWidth / 2, floorCenterY - floorHeight / 2, floorCenterY + floorHeight / 2, floorCenterZ - floorDepth / 2, floorCenterZ + floorDepth / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	lookat(
		floorCenterX, floorCenterY, floorCenterZ,  // Camera position (outside left face)
		floorWidth , floorCenterY, floorCenterZ,       // Look at center of cube
		0, 1, 0                                         // Up vector
	);

	// Draw scene for orthographic view
	drawScene();
}

void ofApp::drawScene() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw Map
	glPushMatrix();
	glTranslatef(floorCenterX, floorCenterY, floorCenterZ);
	glScalef(floorWidth, floorHeight, floorDepth);
	if (resZ == 1) {
		glPushMatrix();
			glTranslatef(0, 0, -floorDepth*0.0005);
			malha_unit(resX, resY);
		glPopMatrix();
	}
	else {
		cube_malha_unit(resX, resY);
	}
	
	glPopMatrix();

	lights();

	// Draw Food
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1, 1, 1);

	OrangeSkin.bind();

	// Set the material properties for this segment
	int materialIndex = 2; // Use the desired material index (e.g., 2 for obsidian)
	loadMaterial(materialIndex);

	glPushMatrix();
		glTranslatef(foodPosition.x, foodPosition.y, foodPosition.z);
		glScalef(squareWidth * 0.5, squareHeight * 0.5, squareDepth * 0.5);
		drawTexturedSphere(1, 20, 20); // Desenhar esfera com textura
	glPopMatrix();

	OrangeSkin.unbind();

	// Draw Snake
	glColor3f(0, 1, 0);
	drawBody(size, positions);

	glColor3f(1, 1, 1);
}

void ofApp::setupSnake() {
	//floor
	resX = 10;
	resY = 10;
	resZ = 10;

	//Position Center
	floorCenterX = gw() * 0.5;
	floorCenterY = gw() * 0.5;
	floorCenterZ = 0;

	//Floor Size
	floorWidth = gw() * 0.9;
	floorHeight = gh() * 0.9;
	floorDepth = gh() * 0.9;

	//Square Size
	squareWidth = floorWidth / resX;
	squareHeight = floorHeight / resY;
	squareDepth = floorDepth / resZ;

	//Position Right Up corner
	floorInitialX = floorCenterX - (floorWidth / 2) + squareWidth * 0.5;
	floorInitialY = floorCenterY - (floorHeight / 2) + squareHeight * 0.5;
	floorInitialZ = floorCenterZ - (floorDepth / 2) + squareDepth * 0.5;


	//Head Initial Position
	snakeHeadPositionX = floor(resX / 2);
	snakeHeadPositionY = floor(resY / 2);
	snakeHeadPositionZ = floor(resZ / 2);

}


bool ofApp::checkGrid(){
	if (snakeHeadPositionX < 0) {
		snakeHeadPositionX = 0;
		return true;
	}
	if (snakeHeadPositionX >= resX) {
		snakeHeadPositionX = resX - 1;
		return true;
	}
	if (snakeHeadPositionY < 0) {
		snakeHeadPositionY = 0;
		return true;
	}
	if (snakeHeadPositionY >= resY) {
		snakeHeadPositionY = resY - 1;
		return true;
	}
	if (snakeHeadPositionZ < 0) {
		snakeHeadPositionZ = 0;
		return true;
	}
	if (snakeHeadPositionZ >= resZ) {
		snakeHeadPositionZ = resZ - 1;
		return true;
	}
	return false;
}

void ofApp::collide()
{
	touching = false;

	if ((snakeHeadPosition.x + squareWidth * 0.25 >= foodPosition.x - squareWidth * 0.25 &&
		snakeHeadPosition.x - squareWidth * 0.25 <= foodPosition.x + squareWidth * 0.25) &&
		(snakeHeadPosition.y + squareHeight * 0.25 >= foodPosition.y - squareHeight * 0.25 &&
		snakeHeadPosition.y - squareHeight * 0.25 <= foodPosition.y + squareHeight * 0.25) &&
		(snakeHeadPosition.z + squareDepth * 0.25 >= foodPosition.z - squareDepth * 0.25 &&
		snakeHeadPosition.z - squareDepth * 0.25 <= foodPosition.z + squareDepth * 0.25))
	{
		touching = true;
		createFood();
		if (resZ == 1) {
			currentScore += 10;  // Increment score when food is eaten
		}else {
			currentScore += 20;  // Increment score when food is eaten
			size++;
		}

		// Save high score using HighScoreManager
		highScoreManager.saveHighScore(currentScore);
	}
		
}
vector <ofVec3f> ofApp::updateBody(GLint size, vector <ofVec3f> positions) {
	// Resize the positions vector if necessary
	while (positions.size() < size) {
		positions.push_back(positions.back()); // Add a new segment at the end
	}

	if (positions.size() >= 2) {

		firstBodyPosition = positions[1];
		// Update positions
		for (int i = positions.size() - 1; i > 0; i--) {
			positions[i] = positions[i - 1];
		}
	}

	positions[0] = snakeHeadPosition;
	return positions;
}

void ofApp::drawBody(GLint size, vector <ofVec3f> positions) {
	// Bind the texture
	snakeSkinImage.bind();
	glColor3f(1, 1, 1);

	// Draw the snake
	for (int i = 0; i < size; i++) {
		glPushMatrix();
		glTranslatef(positions[i].x, positions[i].y, positions[i].z);

		// Set the material properties for this segment
		int materialIndex = 10; // Use the desired material index
		loadMaterial(materialIndex);

		// Draw the textured cube
		glPushMatrix();
		glScalef(squareWidth * 0.99, squareHeight * 0.99, squareDepth * 0.99);
		drawTexturedCube(); // Desenhar cubo com textura
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glScalef(squareWidth, squareHeight, squareDepth);
		cube_unit();
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Unbind the texture
	snakeSkinImage.unbind();
}

void ofApp::drawTexturedCube() {
	float halfSize = 0.5f; // Since we scale the cube, unit size is 1
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	// Front Face
	glNormal3f(0, 0, 1); // Normal pointing forward
	glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, halfSize);

	// Back Face
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, -halfSize);

	// Left Face
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, -halfSize);

	// Right Face
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, -halfSize);

	// Top Face
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, halfSize);

	// Bottom Face
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void ofApp::drawTexturedSphere(float radius, int slices, int stacks) {
	float x, y, z, s, t;
	for (int i = 0; i <= stacks; ++i) {
		//Calcula a fração da divisão e o ângulo theta correspondente à divisão vertical atual
		float V = i / (float)stacks;
		float phi = V * PI;

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= slices; ++j) {
			//Calcula a fração da divisão e o ângulo theta correspondente à divisão horizontal atual
			float U = j / (float)slices;
			float theta = U * (PI * 2);
			
			// Calcula as coordenadas dos vértices para a faixa atual
			x = cos(theta) * sin(phi);
			y = cos(phi);
			z = sin(theta) * sin(phi);

			// Define a coordenada de textura e o vértice da esfera
			s = U;
			t = V;

			glTexCoord2f(s, t);
			glVertex3f(x * radius, y * radius, z * radius);

			// Calcula as coordenadas dos vértices para a próxima faixa
			x = cos(theta) * sin(phi + PI / stacks);
			y = cos(phi + PI / stacks);
			z = sin(theta) * sin(phi + PI / stacks);
			
			// Define a coordenada de textura e o vértice da esfera para a próxima faixa
			s = U;
			t = V + 1.0 / stacks;

			glTexCoord2f(s, t);
			glVertex3f(x * radius, y * radius, z * radius);
		}
		glEnd();
	}
}

void ofApp::printSnakePositions(vector <ofVec3f> positions) {
	cout << "Snake positions:" << endl;
	for (int i = 0; i < positions.size(); i++) {
		cout << "Segment " << i << ": ("
			<< positions[i].x << ", "
			<< positions[i].y << ", "
			<< positions[i].z << ")" << endl;
	}
	cout << "Total segments: " << positions.size() << endl;
}

bool ofApp::checkCollision(vector <ofVec3f> positions) {
	// Check self collision
	
	if (positions.size() == 2) {
		if (snakeHeadPosition.x == firstBodyPosition.x &&
			snakeHeadPosition.y == firstBodyPosition.y &&
			snakeHeadPosition.z == firstBodyPosition.z
			){
			return true;
		}
	}
	else {
		for (int i = 1; i < size; i++) {
			if (positions[0] == positions[i]) {
				return true;
			}
		}
	}

	return false;
}


void ofApp::resetGame() {

	// Reset snake position, size, etc.
	size = 1;
	snakeHeadPositionX = floor(resX / 2);
	snakeHeadPositionY = floor(resY / 2);
	snakeHeadPositionZ = floor(resZ / 2);
	
	snakeSpeedX = 0;
	snakeSpeedY = 0;
	snakeSpeedZ = 0;

	currentScore = 0;
	updateInterval = 0.5;

	isDeathAnimationActive = false;
	screenShakeOffset = ofVec2f(0, 0);
	fadeAlpha = 0;
	overlay = false;

	// Reset positions vector
	positions.clear();
	positions.push_back(ofVec3f(snakeHeadPositionX, snakeHeadPositionY, snakeHeadPositionZ));

}

void ofApp::startDeathAnimation() {
	isDeathAnimationActive = true;
	deathAnimationStartTime = ofGetElapsedTimef();
}

//CHAT GPT
void ofApp::updateDeathAnimation() {
	float currentTime = ofGetElapsedTimef();
	float elapsedTime = currentTime - deathAnimationStartTime;

	if (elapsedTime >= deathAnimationDuration) {
		// Animation complete, reset the game
		isDeathAnimationActive = false;
		screenShakeOffset = ofVec2f(0, 0);
		fadeAlpha = 0;
		resetGame();
	}
	else {
		// Screen shake effect (first half of the animation)
		if (elapsedTime < 2 * deathAnimationDuration / 3) {
			float shakeIntensity = 20 * (1 - elapsedTime / (deathAnimationDuration / 2));
			screenShakeOffset = ofVec2f(ofRandom(-shakeIntensity, shakeIntensity),
				ofRandom(-shakeIntensity, shakeIntensity));
		}
		// Fade to black effect (second half of the animation)
		else {
			screenShakeOffset = ofVec2f(0, 0);
			overlay = true;
			fadeAlpha = ofMap(elapsedTime, deathAnimationDuration / 2, deathAnimationDuration, 0, 255);
		}
	}
}

void ofApp::createFood() {
	GLint X = ofRandom(0, resX - 1);
	GLint Y = ofRandom(0, resY - 1);
	GLint Z = ofRandom(0, resZ - 1);

	foodPosition.x = X * squareWidth + floorInitialX;
	foodPosition.y = Y * squareHeight + floorInitialY;
	foodPosition.z = Z * squareDepth + floorInitialZ;

	// Check food positions
	for (int i = positions.size() - 1; i > 0; i--) {
		if (positions[i].x == foodPosition.x &&
			positions[i].y == foodPosition.y &&
			positions[i].z == foodPosition.z
			) {
			createFood();
		}
	}
	pointPosition.set(foodPosition.x, foodPosition.y, foodPosition.z);
}

void ofApp::changeZ() {
	// Update positions when going 2D
	for (int i = positions.size() - 1; i >= 0; i--) {
		positions[i].z = floorInitialZ;
	}
	snakeHeadPositionZ = 0;
	snakeHeadPosition.z = positions[0].z;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;
	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
		//tank
	case OF_KEY_LEFT:
		snakeSpeedX = - 1;
		snakeSpeedY = 0;
		snakeSpeedZ = 0;

		break;
	case OF_KEY_RIGHT:
		snakeSpeedX = 1;
		snakeSpeedY = 0;
		snakeSpeedZ = 0;

		break;
	case OF_KEY_UP:
		snakeSpeedX = 0;
		snakeSpeedY = 1;
		snakeSpeedZ = 0;

		break;
	case OF_KEY_DOWN:
		snakeSpeedX = 0;
		snakeSpeedY = -1;
		snakeSpeedZ = 0;

		break;
	case 'q':
		if (resZ == 1) {
			resZ = resX;
		}
		else { 
			if (snakeSpeedZ != 0) snakeSpeedX = 1;
			changeZ();
			resZ = 1; 
			
		}
		createFood();
		break;
	case 'j':
		view1 = (view1 + 1) % 3;
		break;
	case 'k':
		view2 = (view2 + 1) % 3;
		break;
	case 'm':
		multiview = true;
		oneview = false;
		break;
	case 'n':
		multiview = false;
		oneview = true;
		break;
	case 'w':
		if (resZ != 1) {
			snakeSpeedX = 0;
			snakeSpeedY = 0;
			snakeSpeedZ = -1;
		}
		break;
	case 's':
		if (resZ != 1) {
			snakeSpeedX = 0;
			snakeSpeedY = 0;
			snakeSpeedZ = 1;
		}
		break;
	case ' ':
		
		break;
	// Controle da Luz Direcional
	case 'd':
		dirOn = !dirOn;
		break;
	case 't':
		ambientCompOn[0] = !ambientCompOn[0];
		break;
	case 'r':
		diffuseCompOn[0] = !diffuseCompOn[0];
		break;
	case 'e':
		specularCompOn[0] = !specularCompOn[0];
		break;

	// Controle da Luz Pontual
	case 'p':
		pointOn = !pointOn;
		break;
	case 'y':
		ambientCompOn[1] = !ambientCompOn[1];
		break;
	case 'u':
		diffuseCompOn[1] = !diffuseCompOn[1];
		break;
	case 'i':
		specularCompOn[1] = !specularCompOn[1];
		break;

	// Controle da Luz Spotlight
	case 'a':
		spotOn = !spotOn;
		break;
	case 'z':
		ambientCompOn[2] = !ambientCompOn[2];
		break;
	case 'x':
		diffuseCompOn[2] = !diffuseCompOn[2];
		break;
	case 'c':
		specularCompOn[2] = !specularCompOn[2];
		break;
	}

	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	cout << endl << x << " " << y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
