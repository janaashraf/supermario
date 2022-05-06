#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
using namespace sf;
using namespace std;
//jump
bool grounded = false;
int vy = 0;
RectangleShape rec1(Vector2f(3300, 100));
RectangleShape rec2(Vector2f(675, 100));
RectangleShape rec3(Vector2f(3050, 100));
RectangleShape rec4(Vector2f(3050, 100));

void checkPos(Vector2i mousepos);
void checkXPos(Vector2i Mousepos);
void checkmusic(Vector2i musicpos);
bool checkground();
//player struct
struct player
{
	Sprite playersprite;
	Texture playertex;
	int playerIndicator = 0, playerDirection = 0;
} mario;
//enemy struct
struct enemies
{
	Sprite enemySprite;
	Texture enemytex;
} enemy[12];
//enemy top struct
struct top
{
	RectangleShape enemytop;
} enemycollision[24];
//menu struct
struct gameMenu
{
	Sprite menuSprite, infoSprite;
	Texture menutex, infotex;
	int startBut = 0, exitBut = 0, infoBut = 0, XBut = 0, muteBut = 0;
}menu;


// coins struct
struct marioCoin {
	Sprite coinSprite;
	Texture coinTex;
	int coinIndicator = 0;
} coins[100];
//main function
int main() {

	RenderWindow window(VideoMode(1200, 700), "Super Mario");
	window.setFramerateLimit(15);
	//score text
	int score = 0;
	Font font;
	font.loadFromFile("PressStart2P-Regular.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setString("score : " + to_string(score));
	text.setPosition(30, 15);
	text.setCharacterSize(20);
	//gameover text
	Text gameOver;
	Font gameOverFont;
	gameOverFont.loadFromFile("PressStart2P-Regular.ttf");
	gameOver.setFont(gameOverFont);
	gameOver.setCharacterSize(100);
	bool dead = false;
	gameOver.setString("GAME OVER!");
	gameOver.setFillColor(Color::Black);

	//mario character
	mario.playertex.loadFromFile("mario sheet.png");
	mario.playersprite.setTexture(mario.playertex);
	mario.playersprite.setTextureRect(IntRect(1 * 45, 2 * 64, 45, 64));
	mario.playersprite.setScale(1.5, 1.5);
	mario.playersprite.setPosition(300, 535);
	//enemy character
	int checkbarrier1 = 1;
	int checkbarrier2 = 1;
	int checkbarrier3 = 1;
	bool enemystate[12] = { };
	RectangleShape barrier1(Vector2f(100, 100));
	RectangleShape barrier2(Vector2f(250, 100));
	RectangleShape barrier3(Vector2f(150, 100));
	RectangleShape barrier4(Vector2f(150, 100));
	barrier1.setPosition(3320, 585);
	barrier2.setPosition(4100, 585);
	barrier3.setPosition(7300, 585);
	barrier4.setPosition(8300, 585);
	for (int i = 0; i < 12; i++) {
		enemy[i].enemytex.loadFromFile("enemy.png");
		enemy[i].enemySprite.setTexture(enemy[i].enemytex);
		enemy[i].enemySprite.setTextureRect(IntRect(0 * 193.666, 0, 193.666, 161));
		enemy[i].enemySprite.setScale(0.25, 0.25);
		enemycollision[i].enemytop.setSize(Vector2f(2, 8));
		enemycollision[2 * i].enemytop.setSize(Vector2f(2, 8));

		if (i == 0) {
			enemy[i].enemySprite.setPosition(1300, 585);
			enemycollision[2 * i].enemytop.setPosition(1305, 610);
			enemycollision[2 * i + 1].enemytop.setPosition(1345, 610);
		}
		else if (i == 1) {
			enemy[i].enemySprite.setPosition(2100, 585);
			enemycollision[2 * i].enemytop.setPosition(2105, 610);
			enemycollision[2 * i + 1].enemytop.setPosition(2145, 610);
		}
		else if (i == 2) {
			enemy[i].enemySprite.setPosition(2500, 585);
			enemycollision[2 * i].enemytop.setPosition(2505, 610);
			enemycollision[2 * i + 1].enemytop.setPosition(2545, 610);
		}
		else if (i == 3) {
			enemy[i].enemySprite.setPosition(3200, 585);
			enemycollision[2 * i].enemytop.setPosition(3205, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(3245, 605);
		}
		else if (i == 4) {
			enemy[i].enemySprite.setPosition(3900, 585);
			enemycollision[2 * i].enemytop.setPosition(3905, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(3945, 605);
		}
		else if (i == 5) {
			enemy[i].enemySprite.setPosition(4600, 585);
			enemycollision[2 * i].enemytop.setPosition(4605, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(4645, 605);
		}
		else if (i == 6) {
			enemy[i].enemySprite.setPosition(5600, 585);
			enemycollision[2 * i].enemytop.setPosition(5605, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(5645, 605);
		}
		else if (i == 7) {
			enemy[i].enemySprite.setPosition(6200, 585);
			enemycollision[2 * i].enemytop.setPosition(6205, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(6245, 605);
		}
		else if (i == 8) {
			enemy[i].enemySprite.setPosition(6300, 585);
			enemycollision[2 * i].enemytop.setPosition(6305, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(6345, 605);
		}
		else if (i == 9) {
			enemy[i].enemySprite.setPosition(6900, 585);
			enemycollision[2 * i].enemytop.setPosition(6905, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(6945, 605);
		}
		else if (i == 10) {
			enemy[i].enemySprite.setPosition(7500, 585);
			enemycollision[2 * i].enemytop.setPosition(7505, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(7545, 605);
		}
		else if (i == 11) {
			enemy[i].enemySprite.setPosition(7600, 585);
			enemycollision[2 * i].enemytop.setPosition(7605, 605);
			enemycollision[2 * i + 1].enemytop.setPosition(7645, 605);
		}
	}
	//jump
	rec1.setPosition(0, 630);
	rec2.setPosition(3430, 630);
	rec3.setPosition(4285, 630);
	rec4.setPosition(7450, 630);
	//coin collision sound
	SoundBuffer buffer;
	buffer.loadFromFile("mariocoin.ogg");
	Sound sound;
	sound.setBuffer(buffer);
	// coins 

	coins->coinTex.loadFromFile("coinss.png");
	for (int i = 0; i < 100; i++) {
		coins[i].coinSprite.setTexture(coins->coinTex);
		coins[i].coinSprite.setTextureRect(IntRect(0, 0, 192, 171));


		if (i >= 0 && i <= 3)
			coins[i].coinSprite.setPosition(350 + (i * 100), 580);

		else if (i >= 4 && i <= 6)
			coins[i].coinSprite.setPosition(950 + ((i - 4) * 100), 390);
		else if (i >= 7 && i <= 11)
			coins[i].coinSprite.setPosition(1500 + ((i - 7) * 100), 580);
		else if (i >= 12 && i <= 17)
			coins[i].coinSprite.setPosition(2400 + ((i - 12) * 100), 580);
		else if (i >= 18 && i <= 20)
			coins[i].coinSprite.setPosition(3000 + ((i - 18) * 100), 580);
		else if (i >= 21 && i <= 22)
			coins[i].coinSprite.setPosition(3700 + ((i - 21) * 100), 390);
		else if (i >= 23 && i <= 28)
			coins[i].coinSprite.setPosition(3830 + ((i - 23) * 70), 200);
		else if (i >= 29 && i <= 31)
			coins[i].coinSprite.setPosition(4370 + ((i - 29) * 70), 200);
		else if (i == 32)
			coins[i].coinSprite.setPosition(4520, 390);
		else if (i >= 33 && i <= 34)
			coins[i].coinSprite.setPosition(4800 + ((i - 33) * 60), 390);
		else if (i >= 35 && i <= 37)
			coins[i].coinSprite.setPosition(5000 + ((i - 35) * 100), 580);
		else if (i == 38)
			coins[i].coinSprite.setPosition(5670, 390);
		else if (i >= 39 && i <= 41)
			coins[i].coinSprite.setPosition(5800 + ((i - 39) * 60), 200);
		else if (i >= 42 && i <= 43)
			coins[i].coinSprite.setPosition(6150 + ((i - 42) * 120), 200);
		else if (i >= 44 && i <= 45)
			coins[i].coinSprite.setPosition(6200 + ((i - 44) * 60), 390);
		else if (i >= 46 && i <= 48)
			coins[i].coinSprite.setPosition(6900 + ((i - 46) * 60), 580);
		else if (i >= 49 && i <= 50)
			coins[i].coinSprite.setPosition(8050 + ((i - 49) * 60), 390);
		else if (i == 51)
			coins[i].coinSprite.setPosition(8200, 390);
		coins[i].coinSprite.setScale(0.2, 0.2);
	}


	//menu
	menu.menutex.loadFromFile("menu mario 6.png");
	menu.menuSprite.setTexture(menu.menutex);
	menu.menuSprite.setPosition(-20, -10);
	menu.menuSprite.setScale(1.6, 1.5);
	menu.infotex.loadFromFile("infomenu.png");
	menu.infoSprite.setTexture(menu.infotex);
	menu.infoSprite.setScale(1.25, 1.25);
	menu.infoSprite.setPosition(190, 30);
	//other sprites
	Texture mapTex;
	Sprite map;
	mapTex.loadFromFile("NES - Super Mario Bros - World 1-1.png");
	map.setTexture(mapTex);
	map.setScale(3, 3);

	//mario music
	Music music;
	music.openFromFile("supermusic.ogg");
	music.play();

	//Camera
	View camera(FloatRect(0, 0, 1200, 700));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i pos = Mouse::getPosition(window);
			checkPos(pos);
			checkmusic(pos);
		}
		if (menu.infoBut == 1 && Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i xpos = Mouse::getPosition(window);
			checkXPos(xpos);

		}
	

		//Moving Right
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (mario.playersprite.getPosition().y < 580 && !dead) {
				mario.playerDirection = 1;
				if (mario.playersprite.getPosition().x < 540 || mario.playersprite.getPosition().x >= 9420 && mario.playersprite.getPosition().x < 9780)
				{
					mario.playersprite.move(15, 0);
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 2 * 64, 45, 64));
					mario.playerIndicator++;
				}
				else if (mario.playersprite.getPosition().x == 9780)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 3 * 64, 45, 64));
				else
				{
					mario.playersprite.move(15, 0);
					camera.move(15, 0);
					text.move(15, 0);
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 2 * 64, 45, 64));
				}
			}
		}
		//Moving Left 
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (mario.playersprite.getPosition().y < 580 && !dead) {
				mario.playerDirection = -1;
				if ((mario.playersprite.getPosition().x > 100 && mario.playersprite.getPosition().x <= 540) || (mario.playersprite.getPosition().x <= 9780 && mario.playersprite.getPosition().x > 9420))
				{
					mario.playersprite.move(-15, 0);
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 1 * 64, 45, 64));
				}
				else if (mario.playersprite.getPosition().x <= 100)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 1 * 64, 45, 64));
				else
				{
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 1 * 64, 45, 64));
					camera.move(-15, 0);
					text.move(-15, 0);
					mario.playersprite.move(-15, 0);


				}
			}
		}
		else
		{
			if (mario.playersprite.getPosition().x == 9780)
				mario.playersprite.setTextureRect(IntRect(1 * 45, 3 * 64, 45, 64));
			else
			{
				if (mario.playerDirection == 1)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 2 * 64, 45, 64));
				else if (mario.playerDirection == -1)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 1 * 64, 45, 64));
			}
		}
		//enemy moving
		for (int i = 0; i < 12; i++) {
			if (i == 4 && !enemystate[i]) {
				if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier1.getGlobalBounds())) {
					checkbarrier1 = 0;
				}
				else if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier2.getGlobalBounds())) {
					checkbarrier1 = 1;
				}
				if (checkbarrier1 == 1) {
					enemy[i].enemySprite.move(-3, 0);
					enemycollision[2 * i].enemytop.move(-3, 0);
					enemycollision[2 * i + 1].enemytop.move(-3, 0);
				}
				else {
					enemy[i].enemySprite.move(3, 0);
					enemycollision[2 * i].enemytop.move(3, 0);
					enemycollision[2 * i + 1].enemytop.move(3, 0);
				}
			}
			else if (i > 4 && i < 10 && !enemystate[i]) {
				if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier2.getGlobalBounds()))
					checkbarrier2 = 0;
				else if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier3.getGlobalBounds()))
					checkbarrier2 = 1;
				if (checkbarrier2 == 1) {
					enemy[i].enemySprite.move(-3, 0);
					enemycollision[2 * i].enemytop.move(-3, 0);
					enemycollision[2 * i + 1].enemytop.move(-3, 0);
				}
				else {
					enemy[i].enemySprite.move(3, 0);
					enemycollision[2 * i].enemytop.move(3, 0);
					enemycollision[2 * i + 1].enemytop.move(3, 0);
				}
			}
			else if (i > 9 && i < 12 && !enemystate[i])
			{
				if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier3.getGlobalBounds()))
					checkbarrier3 = 0;
				else if (enemy[i].enemySprite.getGlobalBounds().intersects(barrier4.getGlobalBounds()))
					checkbarrier3 = 1;
				if (checkbarrier3 == 1) {
					enemy[i].enemySprite.move(-3, 0);
					enemycollision[2 * i].enemytop.move(-3, 0);
					enemycollision[2 * i + 1].enemytop.move(-3, 0);
				}
				else {
					enemy[i].enemySprite.move(3, 0);
					enemycollision[2 * i].enemytop.move(3, 0);
					enemycollision[2 * i + 1].enemytop.move(3, 0);
				}
			}
			else {
				enemy[i].enemySprite.move(-3, 0);
				enemycollision[2 * i].enemytop.move(-3, 0);
				enemycollision[2 * i + 1].enemytop.move(-3, 0);
			}
		}
		//collision with enemies
		for (int i = 0; i < 12; i++) {
			if (enemy[i].enemySprite.getGlobalBounds().intersects(mario.playersprite.getGlobalBounds()) && vy < 0) {
				enemy[i].enemySprite.setTextureRect(IntRect(1 * 193.666, 0, 193.666, 161));
				enemystate[i] = true;
				text.setString("score : " + to_string(score));
				score++;
				sound.play();
				vy = 0;
			}

			else if ((mario.playersprite.getGlobalBounds().intersects(enemycollision[2 * i].enemytop.getGlobalBounds()) || mario.playersprite.getGlobalBounds().intersects(enemycollision[2 * i + 1].enemytop.getGlobalBounds())) && !enemystate[i]) {
				dead = true;
				mario.playersprite.move(0, 0);
				gameOver.setPosition(mario.playersprite.getPosition().x - 450, mario.playersprite.getPosition().y - 100);
				mario.playersprite.setScale(0, 0);
			}
		}


		//jump
		if (checkground()) {
			grounded = true;
			vy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				vy = 35;
			}
		}
		else {
			grounded = false;
			vy -= 5;
		}
		//gameover check
		if (mario.playersprite.getPosition().y > 580) {
			dead = true;
			gameOver.setPosition(text.getPosition().x + 100, text.getPosition().y + 200);
		}

		//coin animation
		for (int i = 0; i < 100; i++) {
			coins[i].coinSprite.setTextureRect(IntRect(coins->coinIndicator * 192, 0, 192, 171));
		}
		// collision with coins
		for (int i = 0; i < 100; i++) {
			if (mario.playersprite.getGlobalBounds().intersects(coins[i].coinSprite.getGlobalBounds())) {
				coins[i].coinSprite.setScale(0, 0);
				text.setString("score : " + to_string(score));
				score++;
				if (menu.startBut == 1) {
					sound.play();
				}

			}
		}
		coins->coinIndicator++;
		coins->coinIndicator %= 6;

		window.setView(camera);
		window.clear();
		window.draw(menu.menuSprite);


		if (menu.startBut == 1) {
			window.draw(map);
			window.draw(mario.playersprite);
			window.draw(text);
			for (int i = 0; i < 12; i++) {
				window.draw(enemy[i].enemySprite);
			}
			for (int i = 0; i < 100; i++) {
				if (coins[i].coinSprite.getPosition().x != 0 && coins[i].coinSprite.getPosition().y != 0) {
					window.draw(coins[i].coinSprite);
				}
			}
			mario.playersprite.move(0, -vy);
			if (dead)
				window.draw(gameOver);

		}

		else if (menu.exitBut == 1) {
			window.close();
		}
		else if (menu.infoBut == 1) {
			window.draw(menu.infoSprite);
			if (menu.XBut == 1) {
				window.draw(menu.menuSprite);
				menu.infoBut = 0;
				menu.XBut = 0;
			}
		}
		if (menu.muteBut == 1)
			music.pause();
		else if (menu.muteBut == 0) {
			music.pause();
			music.play();
		}



		window.display();
	}
	return 0;
}
//to check mouse position in menu
void checkPos(Vector2i mousepos) {
	// to press start
	if (mousepos.x >= 470 && mousepos.x <= 730 && mousepos.y >= 330 && mousepos.y <= 430) {
		menu.startBut = 1;
	}

	// to exit
	else if (mousepos.x >= 465 && mousepos.x <= 735 && mousepos.y >= 431 && mousepos.y <= 536) {
		menu.exitBut = 1;
	}
	//to open info
	else if (mousepos.x >= 465 && mousepos.x <= 742 && mousepos.y >= 537 && mousepos.y <= 623) {
		menu.infoBut = 1;
	}

}
// to check closing the info window
void checkXPos(Vector2i Mousepos) {
	if (Mousepos.x >= 893 && Mousepos.x <= 978 && Mousepos.y >= 27 && Mousepos.y <= 108)
		menu.XBut = 1;
}
// to mute and unmute the music
void checkmusic(Vector2i musicpos) {
	if (musicpos.x >= 183 && musicpos.x <= 230 && musicpos.y >= 82 && musicpos.y <= 132 && menu.infoBut == 0)
		menu.muteBut = 1;
	else if (musicpos.x >= 269 && musicpos.x <= 322 && musicpos.y >= 82 && musicpos.y <= 136 && menu.infoBut == 0)
		menu.muteBut = 0;
}

bool checkground() {
	if (mario.playersprite.getGlobalBounds().intersects(rec1.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec2.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec3.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec4.getGlobalBounds()))
		return 1;
	else
		return 0;
}
