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
	cout << "L - Login" << endl;
	cout << "R - Register" << endl;
	cout << "Q - Quit" << endl;
	cout << "Your choice is: ";
	return;
}

void print_second_menu(double X){
	cout << endl;
	cout << "You have " << X << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw" << endl;
	cout << "Your choice is: ";
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

double my_round(double temp) {
	double result = (int)(temp * 100 + 0.5);
	return (double)result/ 100;
}

int main_menu(vector<user>& users, char letter) {
	hash<string> my_hash;
	bool isLogin = false;
	int user_number = -1;
	string username;
	string password;

	if (letter == 'L') {
		cout << "Please, insert username: " << endl;
		cin >> username;
		cout << "Please, insert password:" << endl;
		cin >> password;
		password = my_hash(password);
		for (int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password != users[i].hashed_password) {
				while (password != users[i].hashed_password) {
					cout << "Incorrect password. Try again." << endl;
					cin >> password;
					password = my_hash(password);
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
		password = my_hash(password);
		user new_user = { username, password, 0 };
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

char second_menu(vector<user>& users, char letter, int user_number) {
	hash<string> my_hash;
	if (letter == 'C') {
		cout << "Your balance must be 0 to cancel account." << endl;
		return 'c';
	}
	if (letter == 'C' && users[user_number].balance == 0) {
		string password;
		cout << "Please enter your password to confirm." << endl;
		cin >> password;
		password = my_hash(password); 
		while (password != users[user_number].hashed_password) {
			cout << "The password is incorrect. Try again." << endl;
			cin >> password;
			password = my_hash(password);
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
		myFile1.open("users.txt", std::fstream::in);
		string buffer;
		vector<string> inputs;
		while (getline(myFile1, buffer)) {
			inputs.push_back(buffer);
		}

		for (int i = 0; i < inputs.size(); i++) {
			users[i].username = find_username(inputs[i]);
			users[i].hashed_password = find_password(inputs[i]);
			users[i].balance = find_balance(inputs[i]);
		}
		return 'C';
	}

	if (letter == 'L') {
		return 'L';
	}

	if (letter == 'D') {
		double deposit;
		cout << "Please, insert deposit: ";
		cin >> deposit;
		users[user_number].balance += my_round(deposit);
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
				if (users[user_number].balance - transfer_money > -overdraft) {
					users[user_number].balance -= transfer_money;
					users[i].balance += transfer_money;
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
		if (users[user_number].balance - with_money > -overdraft) {
			users[user_number].balance -= with_money;
			return 'W';
		}
		cout << "You reach your overdraft limit. Try again." << endl;
		return 'W';
	}
}

char second_function(vector<user>& users, int user_number, char second_letter) {
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
	
	char main_letter;
	print_main_menu();
	cin >> main_letter;
	if (main_function(users, main_letter) == 'Q') {
		return 0;
	}
}