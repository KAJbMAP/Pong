#include <sfml/Graphics.hpp>
#include <ctime>
#include "PongClass.h"
using namespace sf;

void main()
{
	srand(time(NULL));

	Player* player[2];	
	player[0] = new Player(10, HEIGHT / 2, Keyboard::W, Keyboard::S);
	player[1] = new Player(WIDTH - 10, HEIGHT / 2, Keyboard::Up, Keyboard::Down);
	Ball ball;

	Font font;
	font.loadFromFile("PixelFont.ttf");
	Text text;
	text.setFont(font);
	text.setScale(1.5f, 1.5f);
	
	RectangleShape lineOnOrigin(Vector2f(4, 20));
	lineOnOrigin.setOrigin(2, 0);

	RenderWindow win(VideoMode(WIDTH, HEIGHT), "Pong");
	win.setVerticalSyncEnabled(true);

	Image img;
	img.loadFromFile("icon.png");

	win.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
		}

			for (int i = 0; i != 2; i++)
				//player[0]->update();
				player[i]->paddle.setPosition(player[i]->paddle.getPosition().x, ball.ball.getPosition().y);
			ball.update();
			for (int i = 0; i != 2; i++)
				if (ball.ball.getGlobalBounds().intersects(player[i]->paddle.getGlobalBounds()))
					ball.speed.x /= -1;
			if (ball.ball.getPosition().y > HEIGHT - 2.5f || ball.ball.getPosition().y < 2.5f)
				ball.speed.y /= -1;

			if (ball.ball.getPosition().x > WIDTH || ball.ball.getPosition().x < 0)
			{
				if (ball.ball.getPosition().x > WIDTH)
					player[0]->score++;
				else
					player[1]->score++;
				ball.ball.setPosition(WIDTH / 2, HEIGHT / 2);
				if (rand() % 2 == 0)
					ball.speed.x = -10;
				else
					ball.speed.x = 10;
				if (rand() % 2 == 0)
					ball.speed.y = -2;
				else
					ball.speed.y = 2;
			}
						

		win.clear();

			for (int i = 0; i!= HEIGHT; i+=40)
			{
				lineOnOrigin.setPosition(WIDTH/2,i);
				win.draw(lineOnOrigin);
			}

			for (int i = 0; i != 2; i++)
			{
				win.draw(player[i]->paddle);
			}
			win.draw(ball.ball);
		
			text.setString(std::to_string(player[0]->score));
			text.setPosition(((WIDTH/2) - 33) - text.getCharacterSize(), 10);
			win.draw(text);

			text.setString(std::to_string(player[1]->score));
			text.setPosition(WIDTH/2 + 27,10);
			win.draw(text);		
		
		win.display();

	}
}