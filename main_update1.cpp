// json.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rapidjson/reader.h"
#include <iostream>
#include <sstream>
#include<fstream>

using namespace rapidjson;
using namespace std;

int flag = 1;//following are the flag meanings
/*flag = 1 :not initialized
flag = 2 :initialized*/
string command = "INSERT INTO `test`.`stock` VALUES(";

struct MyHandler {
	bool Null() { cout << "Null()" << endl; return true; }
	bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
	bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
	bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
	bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
	bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
	bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
	bool String(const char* str, SizeType length, bool copy) {
		//cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		if (flag == 2){
			command = command + "\""  + str + "\"";
			flag++;
		}
		if (flag == 3){
			command = command + ",\"" + str + "\"";
		}
		return true;
	}
	bool StartObject() { cout << "StartObject()" << endl; return true; }
	bool Key(const char* str, SizeType length, bool copy) {
		cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		return true;
	}
	bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
	bool StartArray() { //cout << "StartArray()" << endl;
		                if (flag < 2){ flag++; }
						if (flag == 4){ command = command + ",("; flag = 2; }

	                    return true; }
	bool EndArray(SizeType elementCount) { //cout << "EndArray(" << elementCount << ")" << endl;
		               if (flag == 4){ command = command + ";"; }
		               if (flag == 3){ command = command + ")"; flag = 4; }
						
	                                       return true; }
};

void save_data()
{
	command = "INSERT INTO `test`.`stock` VALUES(";
	flag = 1;
	ifstream t;
	stringstream buffer;
	t.open("D:/part1.txt");
	buffer << t.rdbuf();
	t.close();

	const std::string tmp = buffer.str();
	const char* cstr = tmp.c_str();

	MyHandler handler;
	Reader reader;
	StringStream ss(cstr);
	reader.Parse(ss, handler);
	cout << command;
}

int main() {	
	save_data();
	while (1){}
	return 0;
}
