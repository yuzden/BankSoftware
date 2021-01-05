#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "MyFunctions.h"

using namespace std;

string find_username(const string& temp) {
	string new_string;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			return new_string;
		}
		new_string.push_back(temp[i]);
	}
}

string find_password(const string& temp) {
	string new_string;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			for (int j = i + 1; j < temp.size(); j++) {
				if (temp[j] == ':') {
					return new_string;
				}
				new_string.push_back(temp[j]);
			}
		}
	}
}

double find_balance(const string& temp) {
	string new_string;
	
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			for (int j = i + 1; j < temp.size(); j++) {
				if (temp[j] == ':') {
					for (int k = j + 1; k < temp.size(); k++) {
						if (isdigit(temp[k] == false)) {
							return -20000;
						}
						new_string.push_back(temp[k]);
					}
				}
			}
		}
	}
	return stod(new_string);
}

bool validation_for_username(const string& temp, const vector <user>& temp_users) {
	for (int i = 0; i < temp_users.size(); i++) {
		if (temp == temp_users[i].username) {
			return 0;
		}
	}

	int count = 0;
	
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == '!' || temp[i] == '@' || temp[i] == '#' || temp[i] == '$' || temp[i] == '%' || temp[i] == '^' || temp[i] == '&' || temp[i] == '*') {
			count++;
		}
	}

	const int min_lower_letter = 97;
	const int max_lower_letter = 122;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= min_lower_letter && temp[i] <= max_lower_letter) {
			count++;
		}
	}

	const int min_upper_letter = 65;
	const int max_upper_letter = 90;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= min_upper_letter && temp[i] <= max_upper_letter) {
			count++;
		}
	}

	if (count == temp.size()) {
		return 1;
	}
	return 0;
}

bool validation_for_password(const string& temp) {
	bool special_char = false;
	bool lower_letter = false;
	bool upper_letter = false;
	const int min_size = 5;
	if (temp.size() < min_size) {
		return 0;
	}

	int count = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == '!' || temp[i] == '@' || temp[i] == '#' || temp[i] == '$' || temp[i] == '%' || temp[i] == '^' || temp[i] == '&' || temp[i] == '*') {
			special_char = true;
			count++;
		}
	}

	const int min_lower_letter = 97;
	const int max_lower_letter = 122;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= min_lower_letter && temp[i] <= max_lower_letter) {
			lower_letter = true;
			count++;
		}
	}

	const int min_upper_letter = 65;
	const int max_upper_letter = 90;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= min_upper_letter && temp[i] <= max_upper_letter) {
			upper_letter = true;
			count++;
		}
	}

	for (int i = 0; i < temp.size(); i++) {
		if (isdigit(temp[i])) {
			count++;
		}
	}

	if (special_char == true && lower_letter == true && upper_letter == true && count == temp.size()) {
		return 1;
	}
	return 0;
}

void print_main_menu() {
	cout << "Choose one of the following options:" << endl;
	cout << "L - Login" << endl;
	cout << "R - Register" << endl;
	cout << "Q - Quit" << endl;
	cout << "Your choice is: ";
	return;
}

void print_second_menu(const double X) {
	cout << "You have " << X << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw" << endl;
	cout << "Your choice is: ";
	return;
}

double my_round(const double temp) {
	double result = (int)(temp * 100 + 0.5);
	return (double)result / 100;
}

string hash_string(string& password) {
	const int hashing_num = 4;
	for (int i = 0; i < password.size(); i++) {
		if (password[i] % 2 == 0) {
			password[i] += hashing_num; 
		}
		else {
			password[i] -= hashing_num;
		}
	}
	return password;
}