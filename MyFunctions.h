#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct user {
	string username, hashed_password;
	double balance;
};

string find_username(const string& temp);

string find_password(const string& temp);

double find_balance(const string& temp);

bool validation_for_username(const string& temp, const vector <user>& temp_users);

bool validation_for_password(const string& temp);

void print_main_menu();

void print_second_menu(const double X);

double my_round(const double temp);

int main_menu(vector<user>& users, char letter);

char second_menu(vector<user>& users, char letter, const int user_number);

char second_function(vector<user>& users, int user_number, char second_letter);

char main_function(vector<user>& users, char main_letter);