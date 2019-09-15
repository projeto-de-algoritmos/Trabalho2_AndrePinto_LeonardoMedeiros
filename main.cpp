#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH=722, HEIGHT=578;

const int N = 60, M = 48;

int blocks[N][M];



int main(){

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "A-MAZE-ING GAME");
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("background.jpg");
	Sprite sBackground(texture);
	
	Sprite sprite;
	RenderTexture t;
	t.create(WIDTH, HEIGHT);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(sBackground);
	
	Vector2f rv2f(10.0, 10.0);
	RectangleShape r(rv2f);
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			r.setPosition(2+i*12, 2+j*12);
			r.setFillColor(Color(150,150,150));
			t.draw(r);
		}
	}
	
	
	
	
	
	
	
	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}
		}
		
		//tick();
		
		
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}
