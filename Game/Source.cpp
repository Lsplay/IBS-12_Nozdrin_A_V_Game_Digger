#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;


const int H = 17;
const int W = 33;
String Map[H]{
	"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
	"NBBBBBBBBBBB    BBBBBBBB0BBBBBBN",
	"NBBBBB       BBBBBBBBBBBBBBBBBBN",
	"NBBBBBBBBB00BBB0BBBBBBBBB000BBBN",
	"NBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBN",
	"NBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBN",
	"NBBBBBBBBBBBBBBBBBBBBBBBB000000N",
	"NBBBBBB  B     BBBBBBB     BBBBN",
	"NBBBBBBBBBBBBB    B   BBBBBBBBBN",
	"NBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBN",
	"NBBBB0BBBBBBBBBBBBBBBBBBB000BBBN",
	"NBBBBBBBB0BBBBBBBBBBBBBBBBBBBBBN",
	"NBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBN",
	"NBBBBBBBBBBBBB BBB     B  BBBBBN",
	"NBBB  BBBBBBBBBBBBBBBBB0BBBBBBBN",
	"NBBBBBBBBBBB0BBBBBBBBBB0BBBBBBBN",
	"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN"
};
class Player
{
public:
	int x, y, speed, score;// o-начальная координата по x p- начальная координата по y
	Texture Miner;
	Sprite miner;
	bool timer = true, life = true;
	Clock TIME;
	Player(int x, int y, int speed)
	{
		score = 0; this->x = x; this->y = y;
		this->speed = 1000 - speed;
		Miner.loadFromFile("1.png");
		miner.setTexture(Miner);
		miner.setTextureRect(IntRect(0, 0, 45, 60));
		miner.setPosition(x * 60, y * 60);
	}

	int GetScore()
	{
		return score;
	}

	void control()
	{
		float time = TIME.getElapsedTime().asMilliseconds();
		if (time > speed)
		{
			timer = true;
			TIME.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && timer && Map[y][x + 1] != 'N')
		{
			x++;
			timer = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && timer && Map[y + -1][x] != 'N')
		{
			y--;
			timer = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && timer && Map[y][x - 1] != 'N')
		{
			x--;
			timer = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && timer && Map[y + 1][x] != 'N')
		{
			y++;
			timer = false;
		}

	}
	void draw()
	{
		control();
		miner.setPosition(x * 60, y * 60);
		if (Map[y][x] == 'B')
		{
			Map[y][x] = ' ';
		}
		if (Map[y][x] == '0')
		{
			Map[y][x] = ' ';
			score++;
		}
	}
};

Player Hero(7, 7, 500);


class Mob
{
public:
	int x, y, speed;
	bool timer=true ;
	Texture MOB;
	Sprite mob;
	Clock TIME;

	Mob(int x, int y,  int speed)
	{
		this->x = x; this->y = y; this->speed = -speed;
		MOB.loadFromFile("Mob.png");
		mob.setTexture(MOB);
		mob.setTextureRect(IntRect(0, 0, 60, 60));
		mob.setPosition(x * 60, y * 60);
	}
	
	

	void move()
	{
		float time = TIME.getElapsedTime().asSeconds();

		if (time >1)
		{
			timer = true;
			TIME.restart();
			
		}
		if (Hero.x<x&&Map[y][x-1]==' '&&timer)
		{
			x--;
			timer = false;
		}
		if (Hero.y<y&&Map[y-1][x] == ' '&&timer)
		{
			y--;
			timer = false;
		}
		if (Hero.x>x&&Map[y][x+1] == ' '&&timer)
		{
			x++;
			timer = false;
		}
		
		if (Hero.y>y&&Map[y+1][x] == ' '&&timer)
		{
			y++;
			timer = false;
		}
		
	}

	void draw()
	{
		move();
		mob.setPosition(x * 60, y * 60);
	}


};




int main()
{
	Texture Block;
	Block.loadFromFile("Kamen.png");

	Texture FON;
	FON.loadFromFile("FON.jpg");
	Sprite fon;
	fon.setTexture(FON);

	Texture KRAI;
	KRAI.loadFromFile("KRAI.jpg");

	Texture GOLD;
	GOLD.loadFromFile("Gold.png");

	Font font;
	font.loadFromFile("Q.ttf");
	Text text;

	RenderWindow window(VideoMode(1920, 1080), "Lesson 1. kychka-pc.ru");

	
	Mob Vrag(25, 7, 1);
	Mob Vrag2(6, 2, 1);
	Mob Vrag3(5, 15, 1);
	bool onGame = true;
	bool Life = true;
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		while (Life)
		{

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			while (onGame)
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
				window.draw(fon);

				for (int i = 0; i < H; i++)
					for (int j = 0; j < W; j++)
					{

						if (Map[i][j] == 'B') {
							Sprite block;
							block.setTexture(Block);
							block.setTextureRect(IntRect(0, 0, 60, 60));
							block.setPosition(j * 60, i * 60);
							window.draw(block);
						}
						if (Map[i][j] == '0') {
							Sprite gold;
							gold.setTexture(GOLD);
							gold.setTextureRect(IntRect(0, 0, 60, 60));
							gold.setPosition(j * 60, i * 60);
							window.draw(gold);
						}
						if (Map[i][j] == 'N') {
							Sprite krai;
							krai.setTexture(KRAI);
							krai.setTextureRect(IntRect(0, 0, 60, 60));
							krai.setPosition(j * 60, i * 60);
							window.draw(krai);
						}
						Hero.draw();
						Vrag.draw(); Vrag2.draw(); Vrag3.draw();
						if (Hero.x == Vrag3.x && Hero.y == Vrag3.y) {
							onGame = false;
							Life = false;
						}
						if (Hero.x == Vrag2.x && Hero.y == Vrag2.y) {
							onGame = false;
							Life = false;
						}
						if (Hero.x == Vrag.x && Hero.y == Vrag.y) {
							onGame = false;
							Life = false;
						}
					}
				if (Hero.score == 21)
				{
					onGame = false;
				}

				window.draw(Vrag.mob); window.draw(Vrag2.mob); window.draw(Vrag3.mob);window.draw(Hero.miner);


				std::ostringstream playerScoreString;
				playerScoreString << Hero.score;
				text.setFont(font);
				text.setString("Score:" + playerScoreString.str());
				text.setCharacterSize(25);
				text.setFillColor(Color::Red);
				text.setStyle(Text::Bold | Text::Underlined);
				text.setPosition(20, 20);
				window.draw(text);
				window.display();
			}
			window.clear(Color::White);
			text.setFont(font);
			text.setString("You win");
			text.setCharacterSize(150);
			text.setFillColor(Color::Blue);
			text.setStyle(Text::Bold | Text::Underlined);
			text.setPosition(960, 460);
			window.draw(text);
			window.display();
		}
		window.clear(Color::White);
		text.setFont(font);
		text.setString("You lose");
		text.setCharacterSize(150);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold | Text::Underlined);
		text.setPosition(960, 460);
		window.draw(text);
		window.display();
	}
	return 0;
}

