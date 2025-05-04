#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"
#include "HighScoreManager.h"




class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);



	//camera variables
	int view1, view2 = 0;


	ofVec3f camPos;
	ofVec3f lookatPos;
	ofVec3f camUp;
	GLfloat orbitAngle;

	//game variables
	void cameraView0();
	void cameraView1();
	void cameraView2();
	void setupSnake();
	bool checkGrid();
	void collide();
	void drawBody(GLint size, vector <ofVec3f> positions);
	vector <ofVec3f> updateBody(GLint size, vector <ofVec3f> positions);
	void printSnakePositions(vector <ofVec3f> positions);
	void resetGame();
	bool checkCollision(vector <ofVec3f> positions);
	void drawScene();
	void createFood();
	void changeZ();
	void updateDeathAnimation();
	void startDeathAnimation();

	void lights();

	void drawTexturedCube();
	void drawTexturedSphere(float radius, int slices, int stacks);

	//floor
	GLint resX, resY, resZ;
	GLfloat floorWidth, floorHeight, floorDepth;
	GLfloat squareWidth, squareHeight, squareDepth;
	GLfloat floorInitialX, floorInitialY, floorInitialZ;
	GLfloat floorCenterX, floorCenterY, floorCenterZ;

	//Snake Head Position
	ofVec3f snakeHeadPosition;
	GLfloat snakeCubeWidth, snakeCubeHeight, snakeCubeDepth;
	GLfloat snakeHeadPositionX, snakeHeadPositionY, snakeHeadPositionZ;

	//Snake body
	GLint snakeSpeedX, snakeSpeedY, snakeSpeedZ;
	GLint size;
	vector <ofVec3f> positions;
	ofVec3f firstBodyPosition;

	//Food Variables
	GLfloat foodCubeWidth, foodCubeHeight, foodCubeDepth;
	ofVec3f foodPosition;

	double lastUpdateTime;
	double updateInterval = 0.5;

	bool touching;


	ofVec3f firstPersonCameraPosition;
	ofVec3f firstPersonCameraLookAt;



	int currentScore;
	int highScore;
	ofTrueTypeFont scoreFont;

	bool isDeathAnimationActive;
	float deathAnimationStartTime;
	float deathAnimationDuration;
	ofVec2f screenShakeOffset;
	float fadeAlpha;
	bool overlay;

	ofSpherePrimitive sphere;

	bool multiview;
	bool oneview;


	// Variáveis para Iluminação

	// Estados das luzes
	bool ambientOn;
	bool dirOn;
	bool pointOn;
	bool spotOn;

	// Componentes de cada luz
	bool ambientCompOn[3]; // 0: Direcional, 1: Pontual, 2: Spotlight
	bool diffuseCompOn[3];
	bool specularCompOn[3];

	// Propriedades das luzes
	// Luz Direcional (GL_LIGHT0)
	ofVec3f dirDirection;
	GLfloat dirAmbient[4];
	GLfloat dirDiffuse[4];
	GLfloat dirSpecular[4];

	// Luz Pontual (GL_LIGHT1)
	ofVec3f pointPosition;
	GLfloat pointAmbient[4];
	GLfloat pointDiffuse[4];
	GLfloat pointSpecular[4];
	GLfloat pointAttenuation[3];

	// Luz Spotlight (GL_LIGHT2)
	ofVec3f spotPosition;
	ofVec3f spotDirection;
	GLfloat spotAmbient[4];
	GLfloat spotDiffuse[4];
	GLfloat spotSpecular[4];
	GLfloat spotExponent;
	GLfloat spotCutoff;
	GLfloat spotAttenuation[3];


	ofImage snakeSkinImage;
	ofImage OrangeSkin;
	ofImage Death;

private:
	HighScoreManager highScoreManager; // Instance of HighScoreManager
};