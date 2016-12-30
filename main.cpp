// NOTICE!!! You should not change anything in this file.  
// You can look at it to understand what is going on, but you 
//   must not change anything.
#include <iostream>
#include <fstream>
#include <sstream>
#include "Arena.h"

const int NUM_FILES = 5;//the total number of files to be read from

const string fileArray[NUM_FILES] = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt" };//the string aray containing the file names 

//This will take a string temp and an arena object and will execute an instruction from the string
//no return, but writes the results of the instruction into the ofs filestream
void parse_instruction(string temp, ofstream &ofs, Arena* aptr);

//to determine whether or not to use abilities during a battle
//will begin as false, but can be set true by a certain instruction at the begining of the file
bool useAbilities;

int main() {

	for (int i = 0; i < NUM_FILES; i++) {
		ifstream ifs;//create the stream to read in from the files
		ofstream ofs;//create the output stream to write to an output file
		string temp;//used to store the current instruction
		Arena* aptr = new Arena();
		ifs.open(fileArray[i]);//open the file to read from
		ofs.open("out_" + fileArray[i]);//open the file to write to
		if (!ifs.is_open()) {//if the file did not open, there was no such file
			cout << "File " << i << " could not open, please check your lab setup\n";
		}
		useAbilities = false;
		getline(ifs, temp);//get the first instruction
		if (temp == "USE ABILITY") {//first line of file determines whether or not to use abilities during fights
			useAbilities = true;
		}
		while (getline(ifs, temp)) {//while there are more instructions to get,
			parse_instruction(temp, ofs, aptr);//parse the instructions
		}
	}
	cout << "end\n";//indicate that the program has successfuly executed all instructions
	return 0;
}

void parse_instruction(string temp, ofstream &ofs, Arena* aptr) {
	cout << "Beginning file write\n";
	string command, arg1, arg2;
	stringstream ss(temp);
	ss >> command;
	if (command == "addFighter") {//comand to add a new fighter to the arena
		if (aptr->addFighter(ss.str().substr(10, string::npos))) {//use the rest of the stringstream as addFighter input
			ofs << temp << " True\n";
		}
		else {
			ofs << temp << " Invalid\n";
		}
	}
	else if (command == "removeFighter") {//command to remove a fighter from the arena (given the fighters name)
		ss >> arg1;//get the name of the fighter to remove
		if (aptr->removeFighter(arg1)) {
			ofs << temp << " True\n";
		}
		else {
			ofs << temp << " False\n";
		}
	}
	else if (command == "getFighter") {//command to return a pointer to a fighter (given the name of the fighter)
		ss >> arg1;//get the name of the fighter to print
		FighterInterface* fptr = aptr->getFighter(arg1);
		if (fptr != NULL) {
			ofs << temp << "\n  " << fptr->getName() << " " << fptr->getCurrentHP() << " " << fptr->getMaximumHP() << " " << fptr->getStrength() << " " << fptr->getSpeed() << " " << fptr->getMagic() << "\n";
		}
		else {
			ofs << temp << " NULL\n";
		}
	}
	else if (command == "getSize") {//command to get the number of fighters in the arena
		ofs << temp << " " << aptr->getSize() << "\n";
	}
	else if (command == "battle") {//command to print the results of a battle between two fighters
		ss >> arg1 >> arg2;
		FighterInterface *fptr1 = aptr->getFighter(arg1), *fptr2 = aptr->getFighter(arg2);//get the pointers to the two fighters who will be fighting
		if (fptr1 == NULL || fptr2 == NULL) {//if one of the fighters was not found, stop here
			ofs << temp << " Fighter not found\n";
			return;
		}
		//print the info about the fighters
		ofs << temp << "\n";
		ofs << "\n  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
		ofs << "\n  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << "\n";
		
		//while the fight has not ended (both fighters have positive HP)
		//fighters take turns attacking the opposing fighter
		//abilities and regenerate are used only if the useAbilities bool has been set 
		//after each fighter deals damage, fighter info is printed out again
		while (fptr1->getCurrentHP() > 0 && fptr2->getCurrentHP() > 0) {
			int dmg;

			if (useAbilities) {
				fptr1->regenerate();
				fptr1->useAbility();
			}
			dmg = fptr1->getDamage();
			fptr2->takeDamage(dmg);

			if (fptr2->getCurrentHP() < 1) {
				ofs << "\n  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
				ofs << "\n  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << "\n";
				return;
			}

			if (useAbilities) {
				fptr2->regenerate();
				fptr2->useAbility();
			}
			dmg = fptr2->getDamage();
			fptr1->takeDamage(dmg);

			ofs << "\n  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
			ofs << "\n  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << "\n";

			if (fptr1->getCurrentHP() < 1) {
				return;
			}
		}
	} 
	else {//invalid command, wrong input file format
		cout << "Invalid command.  Do you have the correct input file?\n";
	}

	cout << "File write complete\n";
}