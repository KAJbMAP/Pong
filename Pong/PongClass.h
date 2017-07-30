#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

const unsigned int PADDLE_WIDTH = 10, PADDLE_HEIGHT = 100;
const unsigned int WIDTH = 800, HEIGHT = 600;
class Player
{
public:
	RectangleShape paddle;
	struct key
	{
		Keyboard::Key up = Keyboard::Up;
		Keyboard::Key down = Keyboard::Down;	
	}key;
	unsigned int score;
	Player(int startPosX, int startPosY, Keyboard::Key up, Keyboard::Key down)
	{
		key.up = up; key.down = down; 
		paddle.setSize(Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
		paddle.setOrigin(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
		paddle.setPosition(startPosX, startPosY);
		score = 0;
	}

	void update()
	{
		getInput();
		if (paddle.getPosition().y < PADDLE_HEIGHT / 2)
			paddle.setPosition(paddle.getPosition().x, PADDLE_HEIGHT / 2);
		if (paddle.getPosition().y > HEIGHT-PADDLE_HEIGHT/2)
			paddle.setPosition(paddle.getPosition().x, HEIGHT - PADDLE_HEIGHT / 2);
	}

	void getInput()
	{
		if (Keyboard::isKeyPressed(key.up))
			paddle.move(0, -5);
		if (Keyboard::isKeyPressed(key.down))
			paddle.move(0, 5);
	}
};

class Ball
{
public:
	CircleShape ball;
	Vector2f speed;
	Ball()
	{
		ball.setRadius(5.f);
		ball.setOrigin(5.0f / 2, 5.0f / 2);
		ball.setPosition(WIDTH / 2, HEIGHT / 2);
		if (rand() % 2 == 0)
			speed.x = -10;
		else
			speed.x = 10;
		if (rand() % 2 == 0)
			speed.y = -2;
		else
			speed.y = 2;
	}
	
	void update()
	{
		ball.move(speed);
	}
};