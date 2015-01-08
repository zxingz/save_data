// save_data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
//#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "mysql_connection.h" 
#include "mysql_driver.h"
#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
//DLL int GetString(std::string& text);

void seperate(string stock[], sql::Statement *stmt){
	string STRING;
	int code = 0;
	string command;
	const char* data = command.c_str();
	//stringstream buffer;
	ifstream t;// ("file.txt");
	int max_size = 0;
	//while (1){
	stringstream buffer;
	t.open("D:/part1.txt");
	buffer << t.rdbuf();
	t.close();
	STRING = buffer.str();
	STRING.erase(remove(STRING.begin(), STRING.end(), '\n'), STRING.end());

	//infile.open("D:/part3.txt");
	//getline(infile, STRING);
	//infile.close();
	//int a = STRING.find("]]");
	//if (STRING.length()>0 && STRING.find("]]") == STRING.length()-2)
	if (STRING[0] == '[' && STRING[1] == '['){//&& STRING[STRING.length() - 1] == ']' && STRING[STRING.length() - 2] == ']'){
		code = 0;
		command = "";
		//cout << STRING[STRING.length()-1];
		//while(1){}	
		//const char* data = command.c_str();


		command = "INSERT INTO `test`.`stock` VALUES (";
		//try{
		max_size = STRING.find("]]") + 1;
		for (int i = 0; i < max_size + 1; i++)
		{
			if (i + 1 <= max_size)//abort saver
			if (STRING[i] == '[' && STRING[i + 1] == '['){
				if (i + 3 <= max_size)//abort saver
					i = i + 3;
				while (STRING[i] != '\"'){
					command = command + STRING[i];
					if (i + 1 <= max_size){//abort saver
						i++;
					}
					else{ break; }
				}
			}
			else if (STRING[i - 1] == '"' && STRING[i] != ']' && STRING[i + 1] != ']'){
				command = command + ',';
				if (i + 2 <= max_size)//abort saver
					i = i + 2;
				if (STRING[i + 2] == ':' && STRING[i + 5] == ':'){ command = command + '\"'; }
				while (STRING[i] != '"'){
					command = command + STRING[i];
					if (i + 1 <= max_size){//abort saver
						i++;
					}
					else{ break; }
				}
			}
			else if (STRING[i - 1] == '"' && STRING[i] == ']' && STRING[i + 1] != ']'){
				command = command + "\",\"" + stock[code] + "\");";
				data = command.c_str();
				try{
					stmt->execute(data);
				}
				catch (sql::SQLException &e){}
				command = "INSERT INTO `test`.`stock` VALUES (";
				code++;
				if (i + 4 <= max_size)//abort saver
					i = i + 4;
				while (STRING[i] != '"'){
					command = command + STRING[i];
					if (i + 1 <= max_size){//abort saver
						i++;
					}
					else{ break; }
				}
			}
			else if (STRING[i - 1] == '"' && STRING[i] == ']' && STRING[i + 1] == ']'){
				command = command + "\",\"" + stock[code] + "\");";
				data = command.c_str();
				try{
					stmt->execute(data);
				}
				catch (sql::SQLException &e){}
				if (i + 1 <= max_size)//abort saver
					i++;
			}
		}//for
		//}catch (std::exception& e){}

		//	cout << command;
		//			while (1){}
		//const char* data = command.c_str();
		//stmt->execute(data);
		//	delete data;

	} //if
}

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	

	//string stock[41] = { "MCDOWELL-N", "PETRONET", "PFC", "PNB", "POWERGRID", "PTC", "RANBAXY", "RCOM", "RECLTD", "RELCAPITAL", "RELIANCE", "RELINFRA", "RPOWER", "SAIL", "SBIN", "SIEMENS", "SRTRANSFIN", "SSLT", "SUNPHARMA", "SUNTV", "SYNDIBANK", "TATACHEM", "TATACOMM", "TATAGLOBAL", "TATAMOTORS", "TATAMTRDVR", "TATAPOWER", "TATASTEEL", "TCS", "TECHM", "TITAN", "UBL", "UCOBANK", "ULTRACEMCO", "UNIONBANK", "UNITECH", "UPL", "VOLTAS", "WIPRO", "YESBANK", "ZEEL" };
	//string stock[49] = { "HAVELLS", "HCLTECH", "HDFC", "HDFCBANK", "HDIL", "HEROMOTOCO", "HEXAWARE", "HINDALCO", "HINDUNILVR", "HINDZINC", "IBREALEST", "ICICIBANK", "IDBI", "IDEA", "IDFC", "IFCI", "IGL", "INDIACEM", "INDUSINDBK", "INFY", "IOB", "IOC", "IRB", "ITC", "JINDALSTEL", "JISLJALEQS", "JPASSOCIAT", "JPPOWER", "JSWENERGY", "JSWSTEEL", "JUBLFOOD", "JUSTDIAL", "KOTAKBANK", "KTKBANK", "L&TFH", "LICHSGFIN", "LT", "LUPIN", "M&M", "M&MFIN", "MARUTI", "MCLEODRUSS", "MRF", "NHPC", "NMDC", "NTPC", "OFSS", "ONGC", "ORIENTBANK" };
	string stock[47] = { "ABIRLANUVO", "ACC", "ADANIENT", "ADANIPORTS", "ADANIPOWER", "ALBK", "AMBUJACEM", "ANDHRABANK", "APOLLOHOSP", "APOLLOTYRE", "ARVIND", "ASHOKLEY", "ASIANPAINT", "AUROPHARMA", "AXISBANK", "BAJAJ-AUTO", "BANKBARODA", "BANKINDIA", "BATAINDIA", "BHARATFORG", "BHARTIARTL", "BHEL", "BIOCON", "BPCL", "CAIRN", "CANBK", "CENTURYTEX", "CESC", "CIPLA", "COALINDIA", "COLPAL", "CROMPGREAV", "DABUR", "DISHTV", "DIVISLAB", "DLF", "DRREDDY", "EXIDEIND", "FEDERALBNK", "GAIL", "GLENMARK", "GMRINFRA", "GODREJIND", "GRASIM", "GSKCONS", "HEROMOTOCO", "HINDPETRO" };
	sql::Connection *con;
	sql::Statement *stmt;
	sql::Driver *driver;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
	con->setSchema("test");
	stmt = con->createStatement();
	
	//while (1)
	for (int i = 0; i < 10000;i++)
	{
		seperate(stock, stmt);
		Sleep(100);
	}

//	}//while
	//delete stmt;
//	delete con;
	return 0;
	//system("pause");
}
