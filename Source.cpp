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

void print_main_menu() {
	cout << "Choose one of the following options: " << endl;
	cout << "L - login" << endl;
	cout << "R - Register" << endl;
	cout << "Q - Quit" << endl;
	return;
}
void print_second_menu(double X){
	cout << "You have " << X << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw";
	return;
}
bool validation_for_username(string temp, vector <user>& temp_users) {
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= 48 && temp[i] <= 57) {
			return 0;
		}
	}
	for (int i = 0; i < temp_users.size(); i++) {
		if (temp == temp_users[i].username) {
			return 0;
		}
	}
	return 1;
}
bool validation_for_password(string temp) {
	bool special_char = false;
	bool lower_latter = false;
	bool upper_latter = false;
	if (temp.size() < 5) {
		return 0;
	}
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == '!' || temp[i] == '@' || temp[i] == '#' || temp[i] == '$' || temp[i] == '%' || temp[i] == '^' || temp[i] == '&' || temp[i] == '*') {
			special_char = true;
			break;
		}
	}
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= 97 && temp[i] <= 122) {
			lower_latter = true;
		}
	}
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= 65 && temp[i] <= 90) {
			upper_latter = true;
		}
	}
	if (special_char == true && lower_latter == true && upper_latter == true) {
		return 1;
	}
	return 0;
}

int main_menu(vector<user>& users, char letter) {
	bool isLogin = false;
	int user_number = -1;
	string username;
	string password;

	if (letter == 'L') {
		cout << "Please, insert username: " << endl;
		cin >> username;
		cout << "Please, insert password:" << endl;
		cin >> password;
		for (int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password != users[i].hashed_password) {
				while (password != users[i].hashed_password) {
					cout << "Incorrect password. Try again." << endl;
					cin >> password;
				}
				if (password == users[i].hashed_password) {
					//second_menu(users[i].balance);
					isLogin = true;
					user_number = i;
					break;
				}
			}
			if (username != users[i].username && password == users[i].hashed_password) {
				while (username != users[i].username) {
					cout << "Incorrect username. Try again." << endl;
					cin >> username;
				}
				if (username == users[i].username) {
					//second_menu(users[i].balance);
					isLogin = true;
					user_number = i;
					break;
				}
			}
			if (username == users[i].username && password == users[i].hashed_password) {
				//second_menu(users[i].balance);
				isLogin = true;
				user_number = i;
				break;
			}
		}
	}

	if (isLogin == false && letter == 'L' ) {
		cout << "You don't have registration. Press 'R' to create." << endl;
		cin >> letter;
	}

	if (letter == 'R') {
		cout << "Please, insert username which contains only latin letters or symbols." << endl;
		cin >> username;
		while (validation_for_username(username, users) == false) {
			cout << "The username already exists or is incorrect. Please, try another." << endl;
			cin >> username;
			validation_for_username(username, users);
		}
		cout << "Please, insert password. The password must be at least 5 characters in length and must contain:" << endl;
		cout << "a minimum of 1 lower case letter [a-z]" << endl;
		cout << "a minimum of 1 upper case letter [A-Z]" << endl;
		cout << "a minimum of 1 special character: !@#$%^&*" << endl;
		cin >> password;
		while (validation_for_password(password) == false) {
			cout << "The password is not valid. Please retype the password." << endl;
			cin >> password;
			validation_for_password(password);
		}
		string password1;
		cout << "Please, confirm your password." << endl;
		cin >> password1;
		while (password1 != password) {
			cout << "Your password and confirmation password don't match. Try again." << endl;
			cin >> password1;
		}
		user new_user = {username, password, 0 };
		users.push_back(new_user);
		isLogin = true;
		user_number = users.size()-1;
	}

	if (letter == 'Q') {
		remove("users.txt");
		fstream myFile2;
		myFile2.open("users.txt", fstream::out | fstream::app);
		for (int i = 0; i < users.size(); i++) {
			myFile2 << users[i].username << ":" << users[i].hashed_password << ":" << users[i].balance << endl;
		}
		myFile2.close();
		return -1;
	}

	return user_number;
}

int main() {
	vector<string> inputs;
	string buffer;

	fstream myFile1;
	myFile1.open("users.txt", std::fstream::in);

	if (myFile1.is_open() == false) {
		cout << "File is not open.";
		return 1;
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
	
	char letter;
	print_main_menu();
	cin >> letter;

	int user_number = main_menu(users, letter);

	if (user_number >= 0) {
		print_second_menu(users[user_number].balance);
	}
	else {
		return 0;
	}
	cin >> letter;
	string password;

	if (letter == 'C' && users[user_number].balance == 0) {
		cout << "Please enter your password to confirm." << endl;
		cin >> password;
		while (password != users[user_number].hashed_password) {
			cout << "The password is incorrect. Try again." << endl;
			cin >> password;
		}
		remove("users.txt");
		fstream myFile2;
		myFile2.open("users.txt", fstream::out | fstream::app);
		for (int i = 0; i < users.size(); i++) {
			if (i != user_number) {
				myFile2 << users[i].username << ":" << users[i].hashed_password << ":" << users[i].balance << endl;
			}
		}
		myFile2.close();
	}
	
	cout << endl;
	for (int i = 0; i < users.size(); i++) {
		cout << users[i].username << ":" << users[i].hashed_password << ":" << users[i].balance << endl;
	}
	
	return 0;
}