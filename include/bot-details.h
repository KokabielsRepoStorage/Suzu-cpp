#pragma once
#include <string>
#include <iostream>

using std::string;

const string TOKEN = "TOKEN_HERE";

void log(string text) {
	std::cout << text << std::endl;
}