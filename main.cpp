// Support Code written by Michael D. Shah
//
// You can modify this could however you like in order to implement your 'pong'
//
// Last Updated: 01/17/23
// Please do not redistribute without asking permission.


// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
	#include <windows.h>     
#endif
#include <iostream>
#include "GameObject.hpp"
//#include "Texture.hpp"
#include "SDLApp.hpp"
#include "Text.hpp"
// Our entry point into our program.
// Remember, C++ programs have exactly one entry point
// where the program starts.

SDLApp* app;
GameObject* left;
GameObject* right;
GameObject* ball;
GameObject* middleLine;
Collider2D* ballCollider;
Collider2D* leftCollider;
Collider2D* rightCollider;
Text* leftText;
Text* rightText;
Text* winnerText;

struct GameState {
	float playerSpeed;
	float ballSpeed;
	int ballXDirection;
	int ballYDirection;
	int leftScore;
	int rightScore;
};
GameState* gameState;

void HandleLeftControl() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	int leftX = left->GetTexture()->GetPositionX();
	int leftY = left->GetTexture()->GetPositionY();
	
	//std::cout << "Hello from main::HandleLeftControl "<<std::endl;
	if (state[SDL_SCANCODE_W]) {
		//std::cout << "Hello from main:：HandleLeftControl -> W is pressed" << std::endl;
		leftY -= gameState->playerSpeed;
		left->SetPosition(leftX, leftY);
	}
	else if (state[SDL_SCANCODE_S]) {
		//std::cout << "Hello from main:：HandleLeftControl -> S is pressed" << std::endl;
		leftY += gameState->playerSpeed;
		left->SetPosition(leftX, leftY);
	}
	
	if (leftY <= 0) {
		leftY = 0;
		left->SetPosition(leftX, leftY);
	}
	else if (leftY >= app->GetHeight() - left->GetTexture()->GetSizeHeight()) {
		leftY = app->GetHeight() - left->GetTexture()->GetSizeHeight();
		left->SetPosition(leftX, leftY);
	}
}

void HandleRightControl() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	int rightX = right->GetTexture()->GetPositionX();
	int rightY = right->GetTexture()->GetPositionY();

	//std::cout << "Hello from main::HandleLeftControl "<<std::endl;
	if (state[SDL_SCANCODE_UP]) {
		//std::cout << "Hello from main:：HandleLeftControl -> W is pressed" << std::endl;
		rightY -= gameState->playerSpeed;
		right->SetPosition(rightX, rightY);
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		//std::cout << "Hello from main:：HandleLeftControl -> S is pressed" << std::endl;
		rightY += gameState->playerSpeed;
		right->SetPosition(rightX, rightY);
	}

	if (rightY <= 0) {
		rightY = 0;
		right->SetPosition(rightX, rightY);
	}
	else if (rightY >= app->GetHeight() - right->GetTexture()->GetSizeHeight()) {
		rightY = app->GetHeight() - right->GetTexture()->GetSizeHeight();
		right->SetPosition(rightX, rightY);
	}
}

void HandleBallMovement() {
	int ballX = ball->GetTexture()->GetPositionX();
	int ballY = ball->GetTexture()->GetPositionY();
	if (gameState->ballXDirection == 1) {
		ballX += gameState->ballSpeed;
	}
	else {
		ballX -= gameState->ballSpeed;
	}
	if (gameState->ballYDirection == 1) {
		ballY += gameState->ballSpeed;
	}
	else {
		ballY -= gameState->ballSpeed;
	}
	ball->SetPosition(ballX, ballY);
}


void CheckWinner() {
	if (gameState->leftScore == 3) {
		app->StopAppLoop();
		std::cout << "player: left wins!" << std::endl;
		winnerText->Render("player: left wins!");
	}
	else if (gameState->rightScore == 3) {
		app->StopAppLoop();
		std::cout << "player: right wins!" << std::endl;
		winnerText->Render("player: right wins!");
	}
	else {
		winnerText->Render("");
	}
}



void HandleRender() {
	left->Render();
	right->Render();
	ball->Render();
	middleLine->Render();
	leftText->Render(std::to_string(gameState->leftScore));
	rightText->Render(std::to_string(gameState->rightScore));
	CheckWinner();
}

void HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			app->StopAppLoop();
		}
	}
	HandleLeftControl();
	HandleRightControl();
}

void ResetBall() {
	int centerX = app->GetWidth() / 2 - (ball->GetTexture()->GetSizeWidth() / 2);
	int centerY = app->GetHeight() / 2 - (ball->GetTexture()->GetSizeHeight() / 2);
	ball->SetPosition(centerX, centerY);
}

void CheckBoundary() {
	int ballX = ball->GetTexture()->GetPositionX();
	int ballY = ball->GetTexture()->GetPositionY();
	if (ballY > app->GetHeight()) {
		gameState->ballYDirection = -1;
	}
	else if (ballY < 0) {
		gameState->ballYDirection = 1;
	}	

	if (ballX > app->GetWidth()+50) {
		gameState->leftScore += 1;
		gameState->ballXDirection = -1;
		std::cout << "left player: "<< gameState->leftScore << " | right player: " << gameState->rightScore << std::endl;
		ResetBall();
	}
	else if (ballX < -50) {
		gameState->rightScore += 1;
		gameState->ballXDirection = 1;
		std::cout << "left player: " << gameState->leftScore << " | right player: " << gameState->rightScore << std::endl;
		ResetBall();
	}

}

void HandleCollision() {
	int ballX = ball->GetTexture()->GetPositionX();
	int ballY = ball->GetTexture()->GetPositionY();
	int ballMidPoint = ballY + ball->GetTexture()->GetSizeHeight() / 2;
	leftCollider->SetPosition(left->GetTexture());
	rightCollider->SetPosition(right->GetTexture());
	ballCollider->SetPosition(ball->GetTexture());
	if (ballX < app->GetWidth() / 2
		&& gameState->ballXDirection == -1
		&& left->GetCollider2D()->IsColliding(*ballCollider)) {
		//std::cout << "Hello from HandleCollision" << std::endl;
		gameState->ballXDirection = 1;
		int paddleMidPoint = left->GetTexture()->GetPositionY() + left->GetTexture()->GetSizeHeight() / 2;
		if (ballMidPoint >= paddleMidPoint) {
			gameState->ballYDirection = -1;
		}
		else {
			gameState->ballYDirection = 1;
		}
	}

	if (ballX >= app->GetWidth() / 2
		&& gameState->ballXDirection == 1
		&& right->GetCollider2D()->IsColliding(*ballCollider)) {
		gameState->ballXDirection = -1;
		int paddleMidPoint = right->GetTexture()->GetPositionY() + right->GetTexture()->GetSizeHeight() / 2;
		if (ballMidPoint >= paddleMidPoint) {
			gameState->ballYDirection = 1;
		}
		else {
			gameState->ballYDirection = -1;
		}
	}

}

void HandleUpdate() {
	HandleBallMovement();
	CheckBoundary();
	HandleCollision();
}

int main(int argc, char* args[])
{	//Initialize screen and game state
	const char* title = "SDL2 Series - Pong";
	app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, 50, 50, 640, 480);
	gameState = new GameState;
	gameState->playerSpeed = 5.0f;
	gameState->ballSpeed = 4.0f;
	gameState->ballXDirection = 1;
	gameState->ballYDirection = 1;
	gameState->leftScore = 0;
	gameState->rightScore = 0;
	//create left paddle
	left = new GameObject(app->GetRenderer());
	left->AddTexture("./media/image.bmp");
	left->SetPosition(10, 200);
	left->AddCollider2D();
	leftCollider = left->GetCollider2D();


	//create right paddle
	right = new GameObject(app->GetRenderer());
	right->AddTexture("./media/image.bmp");
	right->SetPosition(610, 200);
	right->AddCollider2D();
	rightCollider = right->GetCollider2D();
	

	//create ball
	ball = new GameObject(app->GetRenderer());
	ball->AddTexture("./media/image.bmp");
	ResetBall();
	ball->SetSize(10,10);
	ball->AddCollider2D();	
	ballCollider = ball->GetCollider2D();

	//create middle line
	middleLine = new GameObject(app->GetRenderer());
	middleLine->AddTexture("./media/image.bmp");
	middleLine->SetSize(2, 480);
	middleLine->SetPosition(315, 0);

	//create text 
	leftText = new Text();
	leftText->Init(app->GetRenderer());
	rightText = new Text();
	rightText->Init(app->GetRenderer());
	rightText->SetPosition(430, 50);
	winnerText = new Text();
	winnerText->Init(app->GetRenderer());
	winnerText->SetPosition(0, 300);
	winnerText->SetDimension(200, 100);
	//create app
	app->SetEventCallback(HandleEvents);
	app->SetRenderCallback(HandleRender);
	app->SetUpdateCallback(HandleUpdate);
	app->RunLoop();
	

	SDL_Delay(2000);
	delete app;
	delete left;
	delete right;
	delete ball;
	delete middleLine;
	delete leftText;
	return 0;
}
