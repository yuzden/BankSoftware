#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
string find_username(string temp) {
	string new_string;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			return new_string;
		}
		new_string.push_back(temp[i]);
	}
}

string find_password(string temp) {
	string new_string;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			for (int j = i+1; j < temp.size(); j++) {
				if (temp[j] == ':') {
					return new_string;
				}
				new_string.push_back(temp[j]);
			}
		}
	}
}

double find_balance(string temp) {
	string new_string;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ':') {
			for (int j = i + 1; j < temp.size(); j++) {
				if (temp[j] == ':') {
					for (int k = j + 1; k < temp.size(); k++) {
						new_string.push_back(temp[k]);
					}
				}
			}
		}
	}
	return stod(new_string);
}

struct user {
	string username, hashed_password;
	double balance;
};
void main_menu() {
	cout << "Choose one of the following options: " << endl;
	cout << "L - login" << endl;
	cout << "R - Register" << endl;
	cout << "Q - Quit" << endl;
	return;
}
void second_menu(double X){
	cout << "You have " << X << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw";
	return;
}
void printRegister() {
	cout << "Username must be ";
}

int main() {
	
	vector<string> inputs;
	string buffer, fn, student;

	fstream myFile;

	myFile.open("users.txt", std::fstream::in);

	if (myFile.is_open() == false) {
		cout << "File not open";
		return 1;
	}

	while (getline(myFile, buffer)) {
		inputs.push_back(buffer);
	}
	vector<user> users(inputs.size());
	for (int i = 0; i < inputs.size(); i++) {
		users[i].username = find_username(inputs[i]);
		users[i].hashed_password = find_password(inputs[i]);
		users[i].balance = find_balance(inputs[i]);
	}

	char letter;
	bool isLogin = true;
	main_menu();
	cin >> letter;

	if (letter == 'L') {
		string username;
		string password;
		cout << "Please, insert username: "<< endl;
		cin >> username;
		cout << "Please, insert password:" << endl;
		cin >> password;
		for (int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password != users[i].hashed_password) {
				cout << "Incorrect password. Try again.";
				cin >> password;
				if (password == users[i].hashed_password) {
					second_menu(users[i].balance);
					break;
				}
			}
			if (username != users[i].username && password == users[i].hashed_password) {
				cout << "Incorrect username. Try again.";
				cin >> username;
				if (username == users[i].username) {
					second_menu(users[i].balance);
					break;
				}
			}
			if (username == users[i].username && password == users[i].hashed_password) {
				second_menu(users[i].balance);
				break;
			}
			isLogin = false;
		}
	}

	if (isLogin == false || letter == 'R') {

	}
	

	
	

	

	return 0;
}