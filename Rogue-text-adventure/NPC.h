#pragma once
#include <string>
#include "GameObject.h";


using std::string;

class NPC : public GameObject
{
	private:
		string desc;
		string attackDesc;

		int level = 1;
		int health = 8;
		int maxHealth = 8;
		int maxDamage = 2;
		int exp = 10;

	public:
		NPC(std::string type, std::string desc, std::string attackDesc);
		~NPC();

		void setLevel(int l);

		string getNpcName();
		string getLvlAndHp();
		string getDesc() { return this->desc; }
		void setDesc(string s) { this->desc = s; }
		string getAttackDesc() { return this->attackDesc; }
		void setAttackDesc(string s) { this->attackDesc = s; }
};

