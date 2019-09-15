#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <time.h>

using namespace sf;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

const int WIDTH=722, HEIGHT=578;

const int N = 60, M = 48;
int speed=2;

int blocks[N][M];

class Tree{
public:
	Tree *parent;
	
	Tree(){
		parent = NULL;
	}
	
	Tree * root(){
		return parent ? parent->root() : this;
	}
	
	bool connected(Tree* t){
		return root() == t->root();
	}
	
	void connect(Tree* t){
		t->root()->parent = this;
	}
	
};

class Edge{
public:
	int x, y;
	int direction;  
	
	Edge(int x, int y, int direction) : x(x), y(y), direction(direction) {}
};

Tree *trees[N][M];

int randomGenerate(int i){ return std::rand()%i; }

int inverse(int dir){
	if(dir==UP) return DOWN;
	if(dir==DOWN) return UP;
	if(dir==LEFT) return RIGHT;
	if(dir==RIGHT) return LEFT;
	
	return -1;
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	if(argc >= 2){
		try{
			int s = atoi(argv[1]);
			if(s>=1 && s<=20){
				speed = s;
			}
			else{
				std::cout << "Speed must be between 1 and 20. Using default speed as 2." << std::endl;
			}
		}
		catch(...){
			std::cout << "Invalid argument was passed, speed must be an integer. Using default speed as 2." << std::endl;
		}
	}
	
	
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "A-MAZE-ING GAME");
	
	Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	
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
			trees[i][j] = new Tree();
			r.setPosition(2+i*12, 2+j*12);
			r.setFillColor(Color(150,150,150));
			t.draw(r);
		}
	}
	
	bool canPlay=false;
	
	Vector2f vhor(22.0, 10.0);
	Vector2f vver(10.0, 22.0);
	
	RectangleShape rhor(vhor);
	RectangleShape rver(vver);
	
	RectangleShape rplayer(rv2f);
	rplayer.setPosition(2, HEIGHT-12);
	rplayer.setFillColor(Color(231, 84, 128));
	int playerx=2, playery=HEIGHT-12;
	
	r.setFillColor(Color(255,255,255));
	
	std::vector<Edge> edges;
	
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(i) edges.emplace_back(i, j, LEFT);
			if(j) edges.emplace_back(i, j, DOWN);
		}
	}
	
	random_shuffle(edges.begin(), edges.end(), randomGenerate);
	
	std::set<int> sets[N][M];
	
	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}else if(e.type == Event::KeyPressed and canPlay){
				switch (e.key.code){
					case Keyboard::Up :{
						if(sets[playerx/12][playery/12].find(UP) != sets[playerx/12][playery/12].end()){
							r.setPosition(playerx, playery);
							t.draw(r);
				
							playery+=12;
							rplayer.setPosition(playerx, playery);
							t.draw(rplayer);
							//canMove=false;
						}
						break;
					}
					case Keyboard::Down :{
						if(sets[playerx/12][playery/12].find(DOWN) != sets[playerx/12][playery/12].end()){
							r.setPosition(playerx, playery);
							t.draw(r);
			
							playery-=12;
							rplayer.setPosition(playerx, playery);
							t.draw(rplayer);
						}
						break;
					}
					case Keyboard::Left :{
						if(sets[playerx/12][playery/12].find(LEFT) != sets[playerx/12][playery/12].end()){
							r.setPosition(playerx, playery);
							t.draw(r);
			
							playerx-=12;
							rplayer.setPosition(playerx, playery);
							t.draw(rplayer);
						}
						break;
					}
					case Keyboard::Right :{
						if(sets[playerx/12][playery/12].find(RIGHT) != sets[playerx/12][playery/12].end()){
							r.setPosition(playerx, playery);
							t.draw(r);
			
							playerx+=12;
							rplayer.setPosition(playerx, playery);
							t.draw(rplayer);
						}
						break;
					}
					
					default:{}
				}
			}
			
			
		}
		/*

		if(Keyboard::isKeyPressed(Keyboard::Up)){
			if(canMove and sets[playerx/12][playery/12].find(UP) != sets[playerx/12][playery/12].end()){
				r.setPosition(playerx, playery);
				t.draw(r);
				
				playery+=12;
				rplayer.setPosition(playerx, playery);
				t.draw(rplayer);
				canMove=false;
			}
		}
		*/
		
		for(int i=0; i<speed; i++){
			if(canPlay) break;
			if(edges.size()){
				auto edge = edges.back(); edges.pop_back();
				auto tree1 = trees[edge.x][edge.y];
				auto tree2 = trees[edge.x+dx[edge.direction]][edge.y+dy[edge.direction]];
				if(!tree1->connected(tree2)){
					tree1->connect(tree2);
					
					sets[edge.x][edge.y].insert(edge.direction);
					sets[edge.x+dx[edge.direction]][edge.y+dy[edge.direction]].insert(inverse(edge.direction));
					
					if(edge.direction==LEFT){
						rhor.setPosition((2+(edge.x+dx[edge.direction])*12), (2+(edge.y+dy[edge.direction])*12));
						t.draw(rhor);
					}
					else if(edge.direction==DOWN){
						rver.setPosition((2+(edge.x+dx[edge.direction])*12), (2+(edge.y+dy[edge.direction])*12));
						t.draw(rver);
					}
				}
			}else{
				canPlay=true;
				RectangleShape rpoint(rv2f);
				rpoint.setPosition(WIDTH-12, 2);
				rpoint.setFillColor(Color(1, 1, 200));
				t.draw(rpoint);
				t.draw(rplayer);
				break;
			}
		}

		
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}
