#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MyFunctions.h"

using namespace std;

int main_menu(vector<user>& users, char letter) {
	while (letter != 'L' && letter != 'R' && letter != 'Q') {
		cout << "There is no such option. Try again." << endl;
		cin >> letter;
	}

	bool isLogin = false;
	int user_number = -1;
	string username;
	string password;

	if (letter == 'L') {
		cout << "Please, insert username: ";
		cin >> username;
		cout << "Please, insert password: ";
		cin >> password;
		password = hash_string(password);
		for (int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password != users[i].hashed_password) {
				while (password != users[i].hashed_password) {
					cout << "Incorrect password. Try again." << endl;
					cin >> password;
					password = hash_string(password);
				}
				if (password == users[i].hashed_password) {
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
					isLogin = true;
					user_number = i;
					break;
				}
			}
			if (username == users[i].username && password == users[i].hashed_password) {
				isLogin = true;
				user_number = i;
				break;
			}
		}
	}

	if (isLogin == false && letter == 'L') {
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
		password = hash_string(password);

		user new_user = { username, password, 0 };
		users.push_back(new_user);
		isLogin = true;
		user_number = users.size() - 1;
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

char second_menu(vector<user>& users, char letter, const int user_number) {
	while (letter != 'C' && letter != 'D' && letter != 'L' && letter != 'T' && letter != 'W') { 
		cout << "Тhere is no such option. Try again." << endl;
		cin >> letter;
	}

	if (letter == 'C' && users[user_number].balance == 0) {
		string password;
		cout << "Please enter your password to confirm: ";
		cin >> password;
		password = hash_string(password);

		while (password != users[user_number].hashed_password) {
			cout << "The password is incorrect. Try again." << endl;
			cin >> password;
			password = hash_string(password);
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

		users.clear();

		fstream myFile1;
		myFile1.open("users.txt", fstream::in);
		string buffer;
		vector<string> inputs;

		while (getline(myFile1, buffer)) {
			inputs.push_back(buffer);
		}
		myFile1.close();

		users.resize(inputs.size());
		for (int i = 0; i < inputs.size(); i++) {
			users[i].username = find_username(inputs[i]);
			users[i].hashed_password = find_password(inputs[i]);
			users[i].balance = find_balance(inputs[i]);
		}
		return 'C';
	}

	if (letter == 'C') {
		cout << "Your balance must be 0 to cancel account." << endl;
		return 'c';
	}

	if (letter == 'L') {
		return 'L';
	}

	if (letter == 'D') {
		double deposit;
		cout << "Please, insert deposit: ";
		cin >> deposit;
		users[user_number].balance += my_round(deposit);
		cout << "You successfully deposit your money." << endl;
		return 'D';
	}

	if (letter == 'T') {
		string user_to_transfer;
		cout << "Please, insert username of the person you choose to transfer money: ";
		cin >> user_to_transfer;
		cout << endl;
		for (int i = 0; i < users.size(); i++) {
			if (users[i].username == user_to_transfer) {
				double transfer_money;
				const double overdraft = 10000;
				cout << "Your overdraft limit is " << overdraft << " BGN." << endl;
				cout << "Please, insert how much money you want to transfer: ";
				cin >> transfer_money;
				transfer_money = my_round(transfer_money);
				if (users[user_number].balance - transfer_money >= -overdraft) {
					users[user_number].balance -= transfer_money;
					users[i].balance += transfer_money;
					cout << "You successfully transfer " << transfer_money << " BGN to " << user_to_transfer << endl;
					return 'T';
				}
				cout << "You reach your overdraft limit. Try again." << endl;
				return 'T';
			}
		}
		cout << "There is no user with that username. You can't transfer money." << endl;
		return 'T';
	}

	if (letter == 'W') {
		double with_money;
		const double overdraft = 10000;
		cout << "Please, insert how much money you want to withdraw: ";
		cin >> with_money;
		with_money = my_round(with_money);
		if (users[user_number].balance - with_money >= -overdraft) {
			users[user_number].balance -= with_money;
			return 'W';
		}
		cout << "You reach your overdraft limit. Try again." << endl;
		return 'W';
	}
}

char second_function(vector<user>& users, const int user_number, char second_letter) {
	if (second_letter == 'L') {
		return 'L';
	}

	if (second_letter == 'C') {
		return 'C';
	}

	cout << endl;
	print_second_menu(users[user_number].balance);
	cin >> second_letter;

	second_menu(users, second_letter, user_number);

	return second_function(users, user_number, second_letter);
}

char main_function(vector<user>& users, char main_letter) {
	int user_number = main_menu(users, main_letter);

	if (user_number < 0) {
		return 'Q';
	}
	char second_letter;
	cout << endl;
	print_second_menu(users[user_number].balance);
	cin >> second_letter;

	second_menu(users, second_letter, user_number);
	second_letter = second_function(users, user_number, second_letter);

	if (second_letter == 'L' || second_letter == 'C') {
		cout << endl;
		print_main_menu();
		cin >> main_letter;
		return main_function(users, main_letter);
	}
}