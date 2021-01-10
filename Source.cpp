/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Yuzden Karadalieva
* @idnumber 62566
* @compiler VC
*
* <file with main function>
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MyFunctions.h"

using namespace std;

int main() {
	vector<string> inputs;
	string buffer;

	fstream myFile1;
	myFile1.open("users.txt", fstream::in);

	if (myFile1.is_open() == false) {
		ofstream myFile("users.txt");
		myFile.close();
	}

	while (getline(myFile1, buffer)) {
		inputs.push_back(buffer);
	}

	vector<user> users(inputs.size());
	for (int i = 0; i < inputs.size(); i++) {
		users[i].username = find_username(inputs[i]);
		users[i].hashed_password = find_password(inputs[i]);
		users[i].balance = find_balance(inputs[i]);
	}
	myFile1.close();

	char main_letter;
	print_main_menu();
	cin >> main_letter;

	if (main_function(users, main_letter) == 'Q') {
		return 0;
	}
}