#include "ActorFactory.h"

#include "Player.h"
#include <iostream>
#include "math\Geometry.h"
#include <vector>
#include "SceneManager.h"
#include "HealthPackActor.h"
#include "FearActor.h"
#include "CoinActor.h"

ActorFactory* ActorFactory::instance;

using namespace std;
vector<string> split(const string & str, const char * c);



shared_ptr<Actor> ActorFactory::createActor(ActorType type) {
	switch (type) {
	case ENEMY:
		return make_shared<Enemy>(30, LRGB(255,0,0), LRGB(240,0,0), POINT2(rand() % 1000, rand() % 1000));
	case SCORE:
		return make_shared<CoinActor>(POINT2(rand() % 1000, rand() % 1000));
	}

	

}

shared_ptr<Actor> ActorFactory::createEffectActor(EffectType effect) {
	switch (effect) {
	case SLOWHEAL:
		return make_shared<HealthPackActor>();
	case FEAR:
		return make_shared<FearActor>();

	}



}


double ActorFactory::getPlayerSpeed() {
	return playerSpeed;
}




/*
	Reads all the lines in the file, if it matches one of the configurable variables
	It splits it with the ':' delimeter, and converts the 2nd element to a double and saves it.
*/
void ActorFactory::loadProperties() {

	// When handling files, a lot of errors can happen, so catch them.
	// Additionally, if the files aren't loaded, each property has a default value.
	try {
		std::ifstream conf("config.txt");
		string bullet = "Bullet Speed:";
		string player = "Player Speed:";
		string enemy = "Enemy Speed:";

		std::string line;
		if (conf.good()) {
			if (conf.is_open()) {
				const  char* c;
				while (std::getline(conf, line)) {
					cout << line << endl;
					if (line.find(bullet) != string::npos) {
						c = bullet.c_str();
						bulletSpeed = atof(split(line, ":")[1].c_str());

					} else if (line.find(player) != string::npos) {
						 c = player.c_str();
						playerSpeed = atof(split(line, ":")[1].c_str());

					} else if (line.find(enemy) != string::npos) {
						 c = enemy.c_str();
						enemySpeed = atof(split(line, ":")[1].c_str());


					}
				}
			}
		}
	}
	catch (std::exception & ex) {
		
		cout << ex.what() << endl;
	}

}

/*
	I couldn't find an effective way to split a string into an array,
	so I made this algorithm that loops through each character in a string
	until it finds the delimeter, then adds each element to a string vector.
*/
vector<string> split(const string & str, const char * ch) {
	string temp;
	vector<string> vec;

	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (*it == *ch) { // If character matches delimeter
			if (!temp.empty()) { 
				vec.push_back(temp); // Add everything up to the delimeter into the vector
				temp.clear(); // clear the temp string
			}
		} else {
			// Append the character to the temp string if character isnt delimeter.
			temp += *it;
		}
	}
	if (!temp.empty())
		vec.push_back(temp); // Add the remainer of the text as a vector element
	return vec;
}