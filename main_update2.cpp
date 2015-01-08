// save_data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "rapidjson/reader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "mysql_connection.h" 
#include "mysql_driver.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace rapidjson;

int flag = 1;//following are the flag meanings
/*flag = 1 :not initialized
flag = 2 :initialized*/
string command = "INSERT INTO `test`.`stock` VALUES(";
//string stock[41] = { "MCDOWELL-N", "PETRONET", "PFC", "PNB", "POWERGRID", "PTC", "RANBAXY", "RCOM", "RECLTD", "RELCAPITAL", "RELIANCE", "RELINFRA", "RPOWER", "SAIL", "SBIN", "SIEMENS", "SRTRANSFIN", "SSLT", "SUNPHARMA", "SUNTV", "SYNDIBANK", "TATACHEM", "TATACOMM", "TATAGLOBAL", "TATAMOTORS", "TATAMTRDVR", "TATAPOWER", "TATASTEEL", "TCS", "TECHM", "TITAN", "UBL", "UCOBANK", "ULTRACEMCO", "UNIONBANK", "UNITECH", "UPL", "VOLTAS", "WIPRO", "YESBANK", "ZEEL" };
//string stock[49] = { "HAVELLS", "HCLTECH", "HDFC", "HDFCBANK", "HDIL", "HEROMOTOCO", "HEXAWARE", "HINDALCO", "HINDUNILVR", "HINDZINC", "IBREALEST", "ICICIBANK", "IDBI", "IDEA", "IDFC", "IFCI", "IGL", "INDIACEM", "INDUSINDBK", "INFY", "IOB", "IOC", "IRB", "ITC", "JINDALSTEL", "JISLJALEQS", "JPASSOCIAT", "JPPOWER", "JSWENERGY", "JSWSTEEL", "JUBLFOOD", "JUSTDIAL", "KOTAKBANK", "KTKBANK", "L&TFH", "LICHSGFIN", "LT", "LUPIN", "M&M", "M&MFIN", "MARUTI", "MCLEODRUSS", "MRF", "NHPC", "NMDC", "NTPC", "OFSS", "ONGC", "ORIENTBANK" };
string stock[47] = { "ABIRLANUVO", "ACC", "ADANIENT", "ADANIPORTS", "ADANIPOWER", "ALBK", "AMBUJACEM", "ANDHRABANK", "APOLLOHOSP", "APOLLOTYRE", "ARVIND", "ASHOKLEY", "ASIANPAINT", "AUROPHARMA", "AXISBANK", "BAJAJ-AUTO", "BANKBARODA", "BANKINDIA", "BATAINDIA", "BHARATFORG", "BHARTIARTL", "BHEL", "BIOCON", "BPCL", "CAIRN", "CANBK", "CENTURYTEX", "CESC", "CIPLA", "COALINDIA", "COLPAL", "CROMPGREAV", "DABUR", "DISHTV", "DIVISLAB", "DLF", "DRREDDY", "EXIDEIND", "FEDERALBNK", "GAIL", "GLENMARK", "GMRINFRA", "GODREJIND", "GRASIM", "GSKCONS", "HEROMOTOCO", "HINDPETRO" };
int counter = 0;

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
		if (flag == 3){
			command = command + ",\"" + str + "\"";
		}
		if (flag == 2){
			command = command + "\"" + str + "\"";
			flag++;
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
		if (flag == 4){ command = command + ",("; flag = 2;}

		return true;
	}
	bool EndArray(SizeType elementCount) { //cout << "EndArray(" << elementCount << ")" << endl;
		if (flag == 4){ command = command + ";"; }
		if (flag == 3){ command = command + ",\"" + stock[counter] + "\"" + ")"; flag = 4; counter++; }

		return true;
	}
};

void save_data()
{   
	sql::Connection *con;
	sql::Statement *stmt;
	sql::Driver *driver;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "");
	con->setSchema("test");
	stmt = con->createStatement();

	command = "INSERT INTO `test`.`stock` VALUES(";
	flag = 1;
	counter = 0;
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


	try{
		stmt->execute(command);
	}
	catch (sql::SQLException &e){}

}

int main()
//int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{	
	save_data();
	while (1)
	Sleep(100);

	return 0;
}
