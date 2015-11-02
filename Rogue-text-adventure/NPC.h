#pragma once
#include <string>
#include "GameObject.h"


using std::string;

class NPC : public GameObject
{
	private:
		string size;
		string desc;
		string attackDesc;

		bool death = false;

		int level = 1;
		int health = 8;
		int maxHealth = 8;
		int maxDamage = 2;
		int exp = 8;

	public:
		NPC(std::string type, std::string size, std::string desc, std::string attackDesc);
		~NPC();

		void setLevel(int l);

		string getNpcName();
		string getNpcCleanName();
		string getNpcInputName();
		string getLvlAndHp();
		int getHealth() { return this->health; }
		int getMaxDamage() { return this->maxDamage; }
		string getSize() { return this->size; }
		void setSize(string s) { this->size = s; }
		string getDesc() { return this->desc; }
		void setDesc(string s) { this->desc = s; }
		string getAttackDesc(bool hit, int dmg);
		void setAttackDesc(string s) { this->attackDesc = s; }

		void loseHealth(int h);
		bool isDeath() { return this->death; }
		int getExp() { return this->exp; }
};

