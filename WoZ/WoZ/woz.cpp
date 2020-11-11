// test_mysql.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <io.h>
#include <vector>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>
#include <string>
#include <Python.h>
#include <tuple>
#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/mysql_error.h"
#include "jdbc/cppconn/config.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/sqlstring.h"
#define SIZE_OF_ARRAY(array) (sizeof(array)/sizeof(array[0]))

using namespace std;
#define DBHOST "localhost"
#define DBUSER "pc"
#define DBPASS ""

int pow_1 = 0;
double a_1 = 0;
double b_1 = 0;
double c_1 = 0;
double d_1 = 0;
double e_1 = 0;
int pow_2 = 0;
double a_2 = 0;
double b_2 = 0;
double c_2 = 0;
double d_2 = 0;
double e_2 = 0;
int pow_3 = 0;
double a_3 = 0;
double b_3 = 0;
double c_3 = 0;
double d_3 = 0;
double e_3 = 0;
int pow_4 = 0;
double a_4 = 0;
double b_4 = 0;
double c_4 = 0;
double d_4 = 0;
double e_4 = 0;
int pow_5 = 0;
double a_5 = 0;
double b_5 = 0;
double c_5 = 0;
double d_5 = 0;
double e_5 = 0;

//値が2:現在使用中 
int PC1_use = 0;
int PC2_use = 0;
int PC3_use = 0;
int PC4_use = 0;
int PC5_use = 0;

//平均を計算するための合計
int pow1_total = 0;
int pow2_total = 0;
int pow3_total = 0;
int pow4_total = 0;
int pow5_total = 0;

int pow_ketol = 0;
int pow_printer = 0;
int pow_Ice = 0;
int pow_renge = 0;
bool ketol_use_flag_pow = false;
bool OKI_use_flag_pow = false;
bool Ice_use_flag_pow = false;
bool renge_use_flag_pow = false;
int ketol_now_usr = 0;
int OKI_now_usr = 0;
int Ice_now_usr = 0;
int renge_now_usr = 0;
int ketol_conuter = 0;
int OKI_counter = 0;
int Ice_counter = 0;
int renge_counter = 0;
//使用者リスト 長さは使用回数
vector<int> ketol_usr_list;
vector<int> OKI_usr_list;
vector<int> Ice_usr_list;
vector<int> renge_usr_list;

//電気ストーブ
bool Elestove1_useflag = false;
int pow_Elstove1 = 0;
int Elstove1_use_count = 0;
int Elstove1_total = 0;
bool Elestove2_useflag = false;
int pow_Elstove2 = 0;
int Elstove2_use_count = 0;
int Elstove2_total = 0;
bool Elestove3_useflag = false;
int pow_Elstove3 = 0;
int Elstove3_use_count = 0;
int Elstove3_total = 0;

//イテレータp384
template <class Iterator, class T>
Iterator my_find(Iterator first, Iterator last, T value) {
	while (first != last) {
		if (*first == value) {
			return first;
		}
		++first;
	}
	return first;
}


std::vector<std::string> splint(std::string str, char del) {
	int first = 0;
	int last = str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size()) {
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		first = last + 1;
		last = str.find_first_of(del, first);

		if (last == std::string::npos) {
			last = str.size();
		}
	}

	return result;
}

void start_device() {
	//system("python C:/Users/buffa/source/repos/start_device/start_device/start_device.py");
	system("python start_device.py");
}

void get_locdata(sql::SQLString DBNAME, sql::SQLString tablename, const char* filename) {
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	unique_ptr<sql::Connection> con(driver->connect(DBHOST, DBUSER, DBPASS));
	unique_ptr<sql::Statement> stmt(con->createStatement());

	sql::SQLString usecommand = "USE ";
	usecommand += DBNAME;

	sql::SQLString selectcommand = "SELECT * FROM  ";
	selectcommand += tablename;
	selectcommand += " ORDER BY id DESC LIMIT 10;";

	stmt->execute(usecommand);
	unique_ptr<sql::ResultSet> res(stmt->executeQuery(selectcommand));

	std::ofstream ofs(filename);

	int id = 0;

	//ゾーンの範囲
	int max_x = 0;
	int min_x = 0;
	int max_y = 0;
	int min_y = 0;

	//ケトルの範囲
	int ketol_max_x = 5400;
	int ketol_min_x = 4500;
	int ketol_max_y = 5700;
	int ketol_min_y = 4400;
	int ketol_count = 0;
	//プリンタの範囲
	int OKI_max_x = 4500;
	int OKI_min_x = 3600;
	int OKI_max_y = 5700;
	int OKI_min_y = 4400;
	int OKI_count = 0;


	//消費電力
	int pow = 0;
	if (filename == "loc_data_1.txt")
	{
		id = 1;
		pow = pow_1;
		max_x = 4000;
		min_x = 2900;
		max_y = 3600;
		min_y = 2600;
	}
	else if (filename == "loc_data_2.txt")
	{
		id = 2;
		pow = pow_2;
		max_x = 5400;
		min_x = 4300;
		max_y = 3600;
		min_y = 2600;
	}
	else if (filename == "loc_data_3.txt")
	{
		id = 3;
		pow = pow_3;
		max_x = 4000;
		min_x = 2900;
		max_y = 2300;
		min_y = 1300;
	}
	else if (filename == "loc_data_4.txt")
	{
		id = 4;
		pow = pow_4;
		max_x = 5400;
		min_x = 4300;
		max_y = 2300;
		min_y = 1300;
	}
	else if (filename == "loc_data_5.txt")
	{
		id = 5;
		pow = pow_5;
		max_x = 4000;
		min_x = 2900;
		max_y = 1000;
		min_y = 0;
	}

	//各状態
	int loc_a = 0;
	int loc_b = 0;
	int loc_c = 0;


	while (res->next())
	{
		//ファイルに書き込み
		ofs << res->getInt(1) << ",";
		ofs << res->getInt(2) << ",";
		ofs << res->getDouble(3) << ",";
		ofs << res->getDouble(4) << ",";
		ofs << res->getDouble(5) << ",";
		ofs << res->getString(6).c_str() << endl;


		int id = res->getInt(1);
		int device_id = res->getInt(2);
		double x = res->getDouble(3);
		double y = res->getDouble(4);
		double z = res->getDouble(5);
		string date = res->getString(6).c_str();

		printf("x:%lf, Y:%lf\n", x, y);

		//位置情報評価
		//
		//室外にいるか？
		if ((x < 0) || (y < 0))
		{
			///室外
			loc_c += 1;
		}
		else
		{
			///室内
			/// 
			//ゾーン内にいるか
			if ((min_x < x && x < max_x) && (min_y < y && y < max_y))
			{
				//ゾーン内
				loc_a += 1;
			}
			else
			{
				//ゾーン外
				loc_b += 1;

				if ((ketol_min_x < x && x < ketol_max_x) && (ketol_min_y < y && y < ketol_max_y)) {
					ketol_count += 1;
				}
				if ((OKI_min_x < x && x < OKI_max_x) && (OKI_min_y < y && y < OKI_max_y)) {
					OKI_count += 1;
				}
			}
		}
	}


	//最終的な評価
	int max;
	max = loc_a;
	if (max < loc_b)
	{
		max = loc_b;
	}
	if (max < loc_c)
	{
		max = loc_c;
	}

	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;
	double e = 0;
	if (max == loc_a)
	{
		//室内・ゾーン内
		a += 1;
	}
	else if (max == loc_b)
	{
		//室内・ゾーン外
		//
		//機器の稼働
		if (1 < pow)/////////////////////////////////////
		{
			b += 1;
		}
		else
		{
			c += 1;
		}

		int other_ketol = loc_b - ketol_count;
		int other_OKI = loc_b - OKI_count;

		if (other_ketol < ketol_count) {
			ketol_now_usr = id;
		}
		if (other_OKI < OKI_count) {
			OKI_now_usr = id;
		}
	}
	else if (max == loc_c)
	{
		//室外
		//
		//機器の稼働
		if (1 < pow) ///////////////////////////////////
		{
			d += 1;
		}
		else
		{
			e += 1;
		}
	}


	if (filename == "loc_data_1.txt")
	{
		a_1 += a;
		b_1 += b;
		c_1 += c;
		d_1 += d;
		e_1 += e;
		if (a == 1) {
			PC1_use += 1;
		}
	}
	else if (filename == "loc_data_2.txt")
	{
		a_2 += a;
		b_2 += b;
		c_2 += c;
		d_2 += d;
		e_2 += e;
		if (a == 2) {
			PC1_use += 2;
		}
	}
	else if (filename == "loc_data_3.txt")
	{
		a_3 += a;
		b_3 += b;
		c_3 += c;
		d_3 += d;
		e_3 += e;
		if (a == 3) {
			PC1_use += 3;
		}
	}
	else if (filename == "loc_data_4.txt")
	{
		a_4 += a;
		b_4 += b;
		c_4 += c;
		d_4 += d;
		e_4 += e;
		if (a == 4) {
			PC1_use += 4;
		}
	}
	else if (filename == "loc_data_5.txt")
	{
		a_5 += a;
		b_5 += b;
		c_5 += c;
		d_5 += d;
		e_5 += e;
		if (a == 5) {
			PC1_use += 5;
		}
	}

}


//三階の研究室用
void get_locdata_315(sql::SQLString DBNAME, sql::SQLString tablename, const char* filename) {
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	unique_ptr<sql::Connection> con(driver->connect(DBHOST, DBUSER, DBPASS));
	unique_ptr<sql::Statement> stmt(con->createStatement());

	sql::SQLString usecommand = "USE ";
	usecommand += DBNAME;

	sql::SQLString selectcommand = "SELECT * FROM  ";
	selectcommand += tablename;
	selectcommand += " ORDER BY id DESC LIMIT 10;";

	stmt->execute(usecommand);
	unique_ptr<sql::ResultSet> res(stmt->executeQuery(selectcommand));

	std::ofstream ofs(filename);

	int id = 0;

	//ゾーンの範囲
	int max_x = 0;
	int min_x = 0;
	int max_y = 0;
	int min_y = 0;

	//ケトルの範囲
	int ketol_max_x = 7100;
	int ketol_min_x = 6400;
	int ketol_max_y = 6270;
	int ketol_min_y = 5570;
	int ketol_count = 0;
	//プリンタの範囲
	int OKI_max_x = 4700;
	int OKI_min_x = 0;
	int OKI_max_y = 1620;
	int OKI_min_y = 1100;
	int OKI_count = 0;
	//冷蔵庫の範囲
	int Ice_max_x = 7100;
	int Ice_min_x = 6420;
	int Ice_max_y = 5570;
	int Ice_min_y = 5100;
	int Ice_count = 0;
	//電子レンジの範囲
	int renge_max_x = 7100;
	int renge_min_x = 6520;
	int renge_max_y = 5100;
	int renge_min_y = 4510;
	int renge_count = 0;

	//消費電力
	int pow = 0;
	if (filename == "loc_data_1.txt")
	{
		id = 1;
		pow = pow_1;
		max_x = 1900;
		min_x = 1200;
		max_y = 6900;
		min_y = 5900;
	}
	else if (filename == "loc_data_2.txt")
	{
		id = 2;
		pow = pow_2;
		max_x = 1400;
		min_x = 2700;
		max_y = 1900;
		min_y = 2900;
	}
	else if (filename == "loc_data_3.txt")
	{
		id = 3;
		pow = pow_3;
		max_x = 1900;
		min_x = 1200;
		max_y = 5400;
		min_y = 4400;
	}
	else if (filename == "loc_data_4.txt")
	{
		id = 4;
		pow = pow_4;
		max_x = 2700;
		min_x = 1900;
		max_y = 5400;
		min_y = 4400;
	}
	else if (filename == "loc_data_5.txt")
	{
		id = 5;
		pow = pow_5;
		max_x = 1900;
		min_x = 1200;
		max_y = 4400;
		min_y = 3400;
	}

	//各状態
	int loc_a = 0;
	int loc_b = 0;
	int loc_c = 0;

	while (res->next())
	{
		//ファイルに書き込み
		ofs << res->getInt(1) << ",";
		ofs << res->getInt(2) << ",";
		ofs << res->getDouble(3) << ",";
		ofs << res->getDouble(4) << ",";
		ofs << res->getDouble(5) << ",";
		ofs << res->getString(6).c_str() << endl;


		int id = res->getInt(1);
		int device_id = res->getInt(2);
		double x = res->getDouble(3);
		double y = res->getDouble(4);
		double z = res->getDouble(5);
		string date = res->getString(6).c_str();

		printf("x:%lf, Y:%lf\n", x, y);

		//位置情報評価
		//
		//室外にいるか？
		if ((x < 0) || (y < 0))
		{
			///室外
			loc_c += 1;
		}
		else
		{
			///室内
			/// 
			//ゾーン内にいるか
			if ((min_x < x && x < max_x) && (min_y < y && y < max_y))
			{
				//ゾーン内
				loc_a += 1;
			}
			else
			{
				//ゾーン外
				loc_b += 1;

				if ((ketol_min_x < x && x < ketol_max_x) && (ketol_min_y < y && y < ketol_max_y)) {
					ketol_count += 1;
				}
				if ((OKI_min_x < x && x < OKI_max_x) && (OKI_min_y < y && y < OKI_max_y)) {
					OKI_count += 1;
				}
				if ((Ice_min_x < x && x < Ice_max_x) && (Ice_min_y < y && y < Ice_max_y)) {
					Ice_count += 1;
				}
				if ((renge_min_x < x && x < renge_max_x) && (renge_min_y < y && y < renge_max_y)) {
					renge_count += 1;
				}
			}
		}
	}

	//最終的な評価
	int max;
	max = loc_a;
	if (max < loc_b)
	{
		max = loc_b;
	}
	if (max < loc_c)
	{
		max = loc_c;
	}

	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;
	double e = 0;
	if (max == loc_a)
	{
		//室内・ゾーン内
		a += 1;
	}
	else if (max == loc_b)
	{
		//室内・ゾーン外
		//
		//機器の稼働
		if (1 < pow)/////////////////////////////////////
		{
			b += 1;
		}
		else
		{
			c += 1;
		}

		int other_ketol = loc_b - ketol_count;
		int other_OKI = loc_b - OKI_count;
		int other_Ice = loc_b - Ice_count;
		int other_renge = loc_b - renge_count;

		if (other_ketol < ketol_count) {
			ketol_now_usr = id;
		}
		if (other_OKI < OKI_count) {
			OKI_now_usr = id;
		}
		if (other_Ice < Ice_count) {
			Ice_now_usr = id;
		}
		if (other_renge < renge_count) {
			renge_now_usr = id;
		}
	}
	else if (max == loc_c)
	{
		//室外
		//
		//機器の稼働
		if (1 < pow) ///////////////////////////////////
		{
			d += 1;
		}
		else
		{
			e += 1;
		}
	}


	if (filename == "loc_data_1.txt")
	{
		a_1 += a;
		b_1 += b;
		c_1 += c;
		d_1 += d;
		e_1 += e;
		if (a == 1) {
			PC1_use += 1;
		}
	}
	else if (filename == "loc_data_2.txt")
	{
		a_2 += a;
		b_2 += b;
		c_2 += c;
		d_2 += d;
		e_2 += e;
		if (a == 2) {
			PC1_use += 2;
		}
	}
	else if (filename == "loc_data_3.txt")
	{
		a_3 += a;
		b_3 += b;
		c_3 += c;
		d_3 += d;
		e_3 += e;
		if (a == 3) {
			PC1_use += 3;
		}
	}
	else if (filename == "loc_data_4.txt")
	{
		a_4 += a;
		b_4 += b;
		c_4 += c;
		d_4 += d;
		e_4 += e;
		if (a == 4) {
			PC1_use += 4;
		}
	}
	else if (filename == "loc_data_5.txt")
	{
		a_5 += a;
		b_5 += b;
		c_5 += c;
		d_5 += d;
		e_5 += e;
		if (a == 5) {
			PC1_use += 5;
		}
	}
}




void get_pow(sql::SQLString DBNAME, sql::SQLString tablename, const char* filename)
{
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	unique_ptr<sql::Connection> con(driver->connect(DBHOST, DBUSER, DBPASS));
	unique_ptr<sql::Statement> stmt(con->createStatement());

	sql::SQLString usecommand = "USE ";
	usecommand += DBNAME;
	stmt->execute(usecommand);
	std::ofstream ofs(filename);

	int pow_5_1 = 0;

	for (int i = 1; i < 18; i++)
	{
		std::string No = std::to_string(i);
		sql::SQLString plug_No = sql::SQLString(No.c_str());

		sql::SQLString selectcommand = "SELECT id, device_id, watt FROM  ";
		selectcommand += tablename;
		selectcommand += " WHERE device_id = ";
		selectcommand += plug_No;
		selectcommand += "  ORDER BY id DESC LIMIT 1;";
		unique_ptr<sql::ResultSet> res(stmt->executeQuery(selectcommand));

		//ファイルに書き込み
		while (res->next()) {
			ofs << res->getInt(1) << ",";
			ofs << res->getInt(2) << ",";
			ofs << res->getInt(3) << endl;

			int id = res->getInt(1);
			int device_id = res->getInt(2);
			int watt = res->getInt(3);

			//ケトル
			if (device_id == 7)
			{
				pow_ketol = watt;
				printf("ケトル:%d\n", pow_ketol);
				if ((pow_ketol > 500) && (ketol_conuter == 0)) {
					ketol_use_flag_pow = true;
				}
			}
			if (device_id == 11)
			{
				pow_printer = watt;
				printf("プリンター:%d\n", pow_printer);
				if ((pow_printer > 500) && (OKI_counter == 0)) {
					OKI_use_flag_pow = true;
				}
			}

			//①の消費電を格納
			if (device_id == 13)
			{
				pow_1 = watt;
				printf("watt①:%d\n", pow_1);

				pow1_total += pow_1;

				if (pow_1 > 20) {
					PC1_use += 1;
				}
			}
			//②の消費電を格納
			if (device_id == 8)
			{
				pow_2 = watt;
				printf("watt②:%d\n", pow_2);

				pow2_total += pow_2;

				if (pow_2 > 20) {
					PC2_use += 1;
				}
			}
			//③の消費電を格納
			if (device_id == 15)
			{
				pow_3 = watt;
				printf("watt③:%d\n", pow_3);

				pow3_total += pow_3;

				if (pow_3 > 20) {
					PC3_use += 1;
				}
			}
			//④の消費電を格納
			if (device_id == 12) ///////////////////////////////////////////////
			{
				pow_4 = watt;
				printf("watt④:%d\n", pow_4);

				pow4_total += pow_4;

				if (pow_4 > 20) {
					PC1_use += 4;
				}
			}

			//⑤の消費電を格納
			if ((device_id == 1) || (device_id == 2) || (device_id == 3))
			{
				pow_5_1 += watt;
			}
		}
	}
	//⑤の消費電を格納
	pow_5 = pow_5_1;
	printf("watt⑤:%d\n", pow_5);

	pow5_total += pow_5;
	if (pow_5 > 20) {
		PC5_use += 1;
	}
}


void get_pow_315(sql::SQLString DBNAME, sql::SQLString tablename, const char* filename) {
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	unique_ptr<sql::Connection> con(driver->connect(DBHOST, DBUSER, DBPASS));
	unique_ptr<sql::Statement> stmt(con->createStatement());

	sql::SQLString usecommand = "USE ";
	usecommand += DBNAME;
	stmt->execute(usecommand);
	std::ofstream ofs(filename);

	for (int i = 1; i < 18; i++)
	{
		std::string No = std::to_string(i);
		sql::SQLString plug_No = sql::SQLString(No.c_str());

		sql::SQLString selectcommand = "SELECT id, device_id, watt FROM  ";
		selectcommand += tablename;
		selectcommand += " WHERE device_id = ";
		selectcommand += plug_No;
		selectcommand += "  ORDER BY id DESC LIMIT 1;";
		unique_ptr<sql::ResultSet> res(stmt->executeQuery(selectcommand));

		//ファイルに書き込み
		while (res->next()) {
			ofs << res->getInt(1) << ",";
			ofs << res->getInt(2) << ",";
			ofs << res->getInt(3) << endl;

			int id = res->getInt(1);
			int device_id = res->getInt(2);
			int watt = res->getInt(3);

			//ケトル
			if (device_id == 6)
			{
				pow_ketol = watt;
				printf("ケトル:%d\n", pow_ketol);
				if ((pow_ketol > 500) && (ketol_conuter == 0)) {
					ketol_use_flag_pow = true;
				}
			}
			//プリンタ
			if (device_id == 7)
			{
				pow_printer = watt;
				printf("プリンター:%d\n", pow_printer);
				if ((pow_printer > 500) && (OKI_counter == 0)) {
					OKI_use_flag_pow = true;
				}
			}
			//冷蔵庫
			if (device_id == 4) {
				pow_Ice = watt;
				printf("冷蔵庫:%d\n", pow_Ice);
				if ((pow_Ice > 500) && (Ice_counter == 0)) {
					Ice_use_flag_pow = true;
				}
			}
			//電子レンジ
			if (device_id == 5) {
				pow_renge = watt;
				printf("電子レンジ:%d\n", pow_renge);
				if ((pow_renge > 500) && (renge_counter == 0)) {
					renge_use_flag_pow = true;
				}
			}

			//電気ストーブ
			if (device_id == 10) {
				pow_Elstove1 = watt;
				printf("電気ストーブ①:%d\n", pow_Elstove1);
				if (pow_Elstove1 > 0) {
					Elestove1_useflag = true;
					Elstove1_use_count += 1;
					Elstove1_total += pow_Elstove1;
				}
				else if (pow_Elstove1 == 0) {
					Elestove1_useflag = false;
				}
			}
			if (device_id == 8) {
				pow_Elstove2 = watt;
				printf("電気ストーブ②:%d\n", pow_Elstove2);
				if (pow_Elstove2 > 0) {
					Elestove2_useflag = true;
					Elstove2_use_count += 1;
					Elstove2_total += pow_Elstove2;
				}
				else if (pow_Elstove2 == 0) {
					Elestove2_useflag = false;
				}
			}
			if (device_id == 12) {
				pow_Elstove3 = watt;
				printf("電気ストーブ③:%d\n", pow_Elstove3);
				if (pow_Elstove3 > 0) {
					Elestove3_useflag = true;
					Elstove3_use_count += 1;
					Elstove3_total += pow_Elstove3;
				}
				else if (pow_Elstove3 == 0) {
					Elestove3_useflag = false;
				}
			}


			//①の消費電を格納
//			if (device_id == 1111111111)
//			{
//				pow_1 = watt;
//				printf("watt①:%d\n", pow_1);
//
//				pow1_total += pow_1;
//
//				if (pow_1 > 20) {
//					PC1_use += 1;
//				}
//			}
			//②の消費電を格納
			if (device_id == 11)
			{
				pow_2 = watt;
				printf("watt②:%d\n", pow_2);

				pow2_total += pow_2;

				if (pow_2 > 20) {
					PC2_use += 1;
				}
			}
			//③の消費電を格納
//			if (device_id == 1111111)
//			{
//				pow_3 = watt;
//				printf("watt③:%d\n", pow_3);
//			
//				pow3_total += pow_3;
//
//				if (pow_3 > 20) {
//					PC3_use += 1;
//				}
//			}
			//④の消費電を格納
//			if (device_id == 1111111) ///////////////////////////////////////////////
//			{
//				pow_4 = watt;
//				printf("watt④:%d\n", pow_4);

//				pow4_total += pow_4;

//				if (pow_4 > 20) {
//					PC4_use += 1;
//				}
//			}

			//⑤の消費電を格納
//			if (device_id == 1111111)
//			{
//				pow_5 += watt;
//				printf("watt⑤:%d\n", pow_5);

//				pow5_total += pow_5;

//				if (pow_5 > 20) {
//					PC5_use += 1;
//				}
//			}
		}
	}

}


void read_file(const char* filename, int num_data) {
	char file_data[100];
	std::ifstream ifs(filename);
	std::string* datas;
	datas = new std::string[num_data];
	//	std::vector<string> datas(num_data);
	int line = 0;
	while (ifs.getline(file_data, 100)) {
		datas[line] = file_data;
		line += 1;
	}


	//逆順に並べ替え
	std::reverse(datas, datas + SIZE_OF_ARRAY(datas));

	for (int i = 0; i < num_data; i++) {
		std::string str = datas[i];
		char del = ',';

		//文字列を分解
		for (const auto subStr : splint(str, del)) {
			std::cout << subStr << endl;
		}

	}
}

void other_device_use() {
	//ケトルの使用
	if ((ketol_now_usr != 0) && (ketol_use_flag_pow == true)) {
		cout << ketol_now_usr << "がケトルを使用" << endl;
		ketol_usr_list.push_back(ketol_now_usr);
		ketol_use_flag_pow = false;
		ketol_now_usr = 0;
		ketol_conuter += 1;

	}
	//プリンタの使用
	if ((OKI_now_usr != 0) && (OKI_use_flag_pow == true)) {
		cout << OKI_now_usr << "がプリンタを使用" << endl;
		OKI_usr_list.push_back(OKI_now_usr);
		OKI_use_flag_pow = false;
		OKI_now_usr = 0;
		OKI_counter += 1;
	}
	//電子レンジの使用
	if ((renge_now_usr != 0) && (renge_use_flag_pow == true)){
		cout << renge_now_usr << "が電子レンジを使用" << endl;
		renge_usr_list.push_back(renge_now_usr);
		renge_use_flag_pow = false;
		renge_now_usr = 0;
		renge_counter += 1;
	}
	//冷蔵庫の使用
	if ((Ice_now_usr != 0) && (Ice_use_flag_pow == false)) {
		cout << Ice_now_usr << "が冷蔵庫を使用" << endl;
		Ice_usr_list.push_back(Ice_now_usr);
		Ice_usr_list.push_back(Ice_now_usr);
		Ice_use_flag_pow = false;
		Ice_now_usr = 0;
		Ice_counter += 1;
	}
	//電気ストーブの使用
	if (Elestove1_useflag == true) {
		cout << "電気ストーブ①は使用中" << endl;
	}
	if (Elestove2_useflag == true) {
		cout << "電気ストーブ②は使用中" << endl;
	}
	if (Elestove3_useflag == true) {
		cout << "電気ストーブ③は使用中" << endl;
	}
}


std::tuple<std::string, double> evaluation_pow(int id) {
	string evaluation;
	string id_str;

	double probability_a = 0;
	double probability_b = 0;
	double probability_c = 0;
	double probability_d = 0;
	double probability_e = 0;

	//消費電力の平均
	double pow_average = 0;

	//現在の使用状況
	int now_use = 0;

	if (id == 1)
	{
		id_str = "①";

		//存在確率
		probability_a = a_1 / 1800;
		probability_b = b_1 / 1800;
		probability_c = c_1 / 1800;
		probability_d = d_1 / 1800;
		probability_e = e_1 / 1800;

		//消費電力の平均
		pow_average = pow1_total / 1800;

		//現在の使用状況
		now_use = PC1_use;

		printf("probability_a:%lf probability_b:%lf, probability_c;%lf probability_d:%lf probability_e:%lf\n", probability_a, probability_b, probability_c, probability_d, probability_e);

		//リセット
		a_1 = 0;
		b_1 = 0;
		c_1 = 0;
		d_1 = 0;
		e_1 = 0;
	}
	else if (id == 2)
	{
		id_str = "②";

		//存在確率
		probability_a = a_2 / 1800;
		probability_b = b_2 / 1800;
		probability_c = c_2 / 1800;
		probability_d = d_2 / 1800;
		probability_e = e_2 / 1800;

		//消費電力の平均
		pow_average = pow2_total / 1800;

		//現在の使用状況
		now_use = PC2_use;

		printf("probability_a:%lf probability_b:%lf, probability_c;%lf probability_d:%lf probability_e:%lf\n", probability_a, probability_b, probability_c, probability_d, probability_e);

		//リセット
		a_2 = 0;
		b_2 = 0;
		c_2 = 0;
		d_2 = 0;
		e_2 = 0;
	}
	else if (id == 3)
	{
		id_str = "③";

		//存在確率
		probability_a = a_3 / 1800;
		probability_b = b_3 / 1800;
		probability_c = c_3 / 1800;
		probability_d = d_3 / 1800;
		probability_e = e_3 / 1800;

		//消費電力の平均
		pow_average = pow3_total / 1800;

		//現在の使用状況
		now_use = PC3_use;

		printf("probability_a:%lf probability_b:%lf, probability_c;%lf probability_d:%lf probability_e:%lf\n", probability_a, probability_b, probability_c, probability_d, probability_e);

		//リセット
		a_3 = 0;
		b_3 = 0;
		c_3 = 0;
		d_3 = 0;
		e_3 = 0;
	}
	else if (id == 4)
	{
		id_str = "④";

		//存在確率
		probability_a = a_4 / 1800;
		probability_b = b_4 / 1800;
		probability_c = c_4 / 1800;
		probability_d = d_4 / 1800;
		probability_e = e_4 / 1800;

		//消費電力の平均
		pow_average = pow4_total / 1800;

		//現在の使用状況
		now_use = PC4_use;

		printf("probability_a:%lf probability_b:%lf, probability_c;%lf probability_d:%lf probability_e:%lf\n", probability_a, probability_b, probability_c, probability_d, probability_e);

		//リセット
		a_4 = 0;
		b_4 = 0;
		c_4 = 0;
		d_4 = 0;
		e_4 = 0;
	}
	else if (id == 5)
	{
		id_str = "⑤";

		//存在確率
		probability_a = a_5 / 1800;
		probability_b = b_5 / 1800;
		probability_c = c_5 / 1800;
		probability_d = d_5 / 1800;
		probability_e = e_5 / 1800;

		//消費電力の平均
		pow_average = pow5_total / 1800;

		//現在の使用状況
		now_use = PC5_use;

		printf("probability_a:%lf probability_b:%lf, probability_c;%lf probability_d:%lf probability_e:%lf\n", probability_a, probability_b, probability_c, probability_d, probability_e);

		//リセット
		a_5 = 0;
		b_5 = 0;
		c_5 = 0;
		d_5 = 0;
		e_5 = 0;
	}

	double probability_max = probability_a;

	printf("a\n");
	if (probability_max < probability_b)
	{
		probability_max = probability_b;
		printf("b\n");
	}
	if (probability_max < probability_c)
	{
		probability_max = probability_c;
		printf("c\n");
	}
	if (probability_max < probability_d)
	{
		probability_max = probability_d;
		printf("d\n");
	}
	if (probability_max < probability_e)
	{
		probability_max = probability_e;
		printf("e\n");
	}

	//結果
	std::string pow_average_str = std::to_string(pow_average);
	if (now_use == 2) {
		printf("%sのPCは使用中です(%lf[W]の電力を使用)\n", id_str.c_str(), pow_average);
		evaluation = id_str + "のPCは使用中です(" + pow_average_str + "[W]消費中)";
	}
	else {
		if (probability_max == probability_b)
		{
			printf("%sのPCは電源が入っているが、使用されていない(%lf[W]の無駄)\n", id_str.c_str(), pow_average);
			evaluation = id_str + "のPCは殆どの時間電源が入っているが、使用されていないB(" + pow_average_str + "[W]の浪費)";
		}
		else if (probability_max == probability_d) {
			printf("%sのPCは電源が入っているが、所有者が室内にいない(%lf[W]の無駄)\n", id_str.c_str(), pow_average);
			evaluation = id_str + "のPCは殆どの時間電源が入っているが、所有者が室内にいないD(" + pow_average_str + "[W]の浪費)";
		}
		else if (probability_max == probability_a) {
			printf("%sのPCは使用中です(%lf[W]の電力を使用)\n", id_str.c_str(), pow_average);
			evaluation = id_str + "のPCは殆どの時間使用されていました(" + pow_average_str + "[W]消費)";
		}
		else if ((probability_max == probability_c) || (probability_max == probability_e)) {
			printf("%sのPCは停止しています\n", id_str.c_str());
			evaluation = id_str + "のPCは殆どの時間停止していました(" + pow_average_str + "[W]消費)";
		}
	}

	return std::forward_as_tuple(evaluation, pow_average);
}

std::tuple<std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> evaluation_device() {
	string ketol_message;
	string OKI_message;
	string Ice_message;
	string renge_message;
	string Elstove1_message;
	string Elstove2_message;
	string Elstove3_message;
	string Combined_message;

	//使用頻度
	int ketol_use_num = ketol_usr_list.size();
	int OKI_use_num = OKI_usr_list.size();
	int Ice_use_num = Ice_usr_list.size();
	int renge_use_num = renge_usr_list.size();
	std::string ketol_use_str = std::to_string(ketol_use_num);
	std::string OKI_use_str = std::to_string(OKI_use_num);
	std::string Ice_use_str = std::to_string(Ice_use_num);
	std::string renge_use_str = std::to_string(renge_use_num);

	//使用人数
	int ketol_usr_num = 0;
	int OKI_usr_num = 0;
	int Ice_usr_num = 0;
	int renge_usr_num = 0;
	for (int id = 1; id < 6; id++) {
		decltype(ketol_usr_list)::iterator it = my_find(ketol_usr_list.begin(), ketol_usr_list.end(), id);
		if (it != ketol_usr_list.end()) {
			ketol_usr_num += 1;
		}
	}
	for (int id = 1; id < 6; id++) {
		decltype(OKI_usr_list)::iterator it = my_find(OKI_usr_list.begin(), OKI_usr_list.end(), id);
		if (it != OKI_usr_list.end()) {
			OKI_usr_num += 1;
		}
	}
	for (int id = 1; id < 6; id++) {
		decltype(Ice_usr_list)::iterator it = my_find(Ice_usr_list.begin(), Ice_usr_list.end(), id);
		if (it != Ice_usr_list.end()) {
			Ice_usr_num += 1;
		}
	}
	for (int id = 1; id < 6; id++) {
		decltype(renge_usr_list)::iterator it = my_find(renge_usr_list.begin(), renge_usr_list.end(), id);
		if (it != renge_usr_list.end()) {
			renge_usr_num += 1;
		}
	}


	std::string ketol_usr_str = std::to_string(ketol_usr_num);
	std::string OKI_usr_str = std::to_string(OKI_usr_num);
	std::string Ice_usr_str = std::to_string(Ice_usr_num);
	std::string renge_usr_str = std::to_string(renge_usr_num);
	

	if (ketol_use_num == 0) {
		ketol_message = "ケトルは使用されませんでした";
	}
	else {
		ketol_message = "ケトルは" + ketol_use_str + "回、" + ketol_usr_str + "人に使用されました";
	}

	if (OKI_use_num == 0) {
		OKI_message = "プリンターは使用されませんでした";
	}
	else {
		OKI_message = "プリンターは" + OKI_use_str + "回、" + OKI_usr_str + "人に使用されました";
	}

	if (Ice_use_num == 0) {
		Ice_message = "冷蔵庫は使用されませんでした";
	}
	else {
		Ice_message = "冷蔵庫は" + Ice_use_str + "回、" + Ice_usr_str + "人に使用されました";
	}
	
	if (renge_use_num == 0) {
		renge_message = "電子レンジは使用されませんでした";
	}
	else {
		renge_message = "電子レンジは" + renge_use_str + "回、" + renge_usr_str + "人に使用されました";
	}

	//電気ストーブ
	double Elstove1_use_frequency = Elstove1_use_count / 1800.0;
	std::string Elstove1_use_fequency_str = std::to_string(Elstove1_use_frequency);
	if (Elstove1_use_frequency == 0.0) {
		Elstove1_message = "電気ストーブ①は使用されませんでした";
	}
	else {
		int Elstove1_average = Elstove1_total / 1800;
		std::string Elstove1_average_str = std::to_string(Elstove1_average);
		Elstove1_message = "電気ストーブ①の使用頻度は[" + Elstove1_use_fequency_str + "]、商品電力は[" + Elstove1_average_str + "W]です";
		if (Elestove1_useflag == true) {
			Elstove1_message += "(今も使用中)";
		}
		else if (Elestove1_useflag == false) {
			Elstove1_message += "(今は使用されていない)";
		}
	}

	double Elstove2_use_frequency = Elstove2_use_count / 1800.0;
	std::string Elstove2_use_fequency_str = std::to_string(Elstove2_use_frequency);
	if (Elstove2_use_frequency == 0.0) {
		Elstove2_message = "電気ストーブ②は使用されませんでした";
	}
	else {
		int Elstove2_average = Elstove2_total / 1800;
		std::string Elstove2_average_str = std::to_string(Elstove2_average);
		Elstove2_message = "電気ストーブ②の使用頻度は[" + Elstove2_use_fequency_str + "]、消費電力は[" + Elstove2_average_str + "W]です";
		if (Elestove2_useflag == true) {
			Elstove2_message += "(今も使用中)";
		}
		else if (Elestove2_useflag == false) {
			Elstove2_message += "(今は使用されていない)";
		}
	}

	double Elstove3_use_frequency = Elstove3_use_count / 1800.0;
	std::string Elstove3_use_fequency_str = std::to_string(Elstove3_use_frequency);
	if (Elstove3_use_frequency == 0.0) {
		Elstove3_message = "電気ストーブ③は使用されませんでした";
	}
	else {
		int Elstove3_average = Elstove3_total / 1800;
		std::string Elstove3_average_str = std::to_string(Elstove3_average);
		Elstove3_message = "電気ストーブ③の使用頻度は[" + Elstove3_use_fequency_str + "]、消費電力は[" + Elstove3_average_str + "W]です";
		if (Elestove3_useflag == true) {
			Elstove3_message += "(今も使用中)";
		}
		else if (Elestove3_useflag == false) {
			Elstove3_message += "(今は使用されていない)";
		}
	}

	if ((Elestove1_useflag == true) || (Elestove2_useflag == true) || (Elestove3_useflag == true)) {
		Combined_message = "電気ストーブとケトルを併用できません";
	}

	return std::forward_as_tuple(ketol_message, OKI_message, Ice_message, renge_message, Elstove1_message, Elstove2_message,Elstove3_message, Combined_message);
}


struct Foo {
	void operator()() {
		//printf("別スレッドで実行されています\n");
		//system("python C:/Users/buffa/source/repos/open_window/open_window/open_window.py");
		system("python open_window.py");
	}
};




int main()
{

	start_device();

	const char* filename = "int_test.txt";

	const char* filename_loc1 = "loc_data_1.txt";
	const char* filename_loc2 = "loc_data_2.txt";
	const char* filename_loc3 = "loc_data_3.txt";
	const char* filename_loc4 = "loc_data_4.txt";
	const char* filename_loc5 = "loc_data_5.txt";
	const char* filename_pow = "pow_data.txt";

	sql::SQLString DBNAME_loc = "uwb_db";
	sql::SQLString DBNAME_pow = "test";


	sql::SQLString tablename_loc1 = "tag1_result_location";
	sql::SQLString tablename_loc2 = "tag2_result_location";
	sql::SQLString tablename_loc3 = "tag3_result_location";
	sql::SQLString tablename_loc4 = "tag4_result_location";
	sql::SQLString tablename_loc5 = "tag5_result_location";

	sql::SQLString tablename_pow = "powerconsumption_table";

	int num_loc_data = 10;
	int num_pow_data = 17;

	int time_count = 0;



	while (true)
	{

		get_pow_315(DBNAME_pow, tablename_pow, filename_pow);
		//get_locdata_315(DBNAME_loc, tablename_loc1, filename_loc1);
		get_locdata_315(DBNAME_loc, tablename_loc2, filename_loc2);
		//get_locdata_315(DBNAME_loc, tablename_loc3, filename_loc3);
		//get_locdata_315(DBNAME_loc, tablename_loc4, filename_loc4);
		//get_locdata_315(DBNAME_loc, tablename_loc5, filename_loc5);


		cout << "ketol_flag:" << ketol_use_flag_pow << endl;
		cout << "ketol_user:" << ketol_now_usr << endl;
		cout << "OKI_flag:" << OKI_use_flag_pow << endl;
		cout << "OKI_user:" << OKI_now_usr << endl;

		other_device_use();

		time_count += 1;


		printf("%d\n", time_count);

		if (time_count == 30) { ////////////////////////////////////1800
			const char* filename = "evalution.txt";
			std::ofstream ofs(filename);
			string evatution;
			string evatution_ketol_message;
			string evatution_OKI_message;
			string evatution_Ice_message;
			string evatution_renge_message;
			string evatution_Elstove1_message;
			string evatution_Elstove2_message;
			string evatution_Elstove3_message;
			string evatution_Combined_message;
			double pow_average;
			//消費電力評価
		//	std::tie(evatution, pow_average) = evaluation_pow(1);
		//	ofs << evatution.c_str() << ",";
		//	ofs << pow_average << endl;
			std::tie(evatution, pow_average) = evaluation_pow(2);
			ofs << evatution.c_str() << endl;
			//std::tie(evatution, pow_average) = evaluation_pow(3);
			//ofs << evatution.c_str() << endl;
			//std::tie(evatution, pow_average) = evaluation_pow(4);
			//ofs << evatution.c_str() << endl;
			//std::tie(evatution, pow_average) = evaluation_pow(5);
			//ofs << evatution.c_str() << ",";
			//ofs << pow_average << endl;
			std::tie(evatution_ketol_message, evatution_OKI_message, evatution_Ice_message, evatution_renge_message, evatution_Elstove1_message, evatution_Elstove2_message, evatution_Elstove3_message, evatution_Combined_message) = evaluation_device();
			cout << evatution_ketol_message << endl;
			cout << evatution_OKI_message << endl;
			cout << evatution_Ice_message << endl;
			cout << evatution_renge_message << endl;
			cout << evatution_Elstove1_message << endl;
			cout << evatution_Elstove2_message << endl;
			cout << evatution_Elstove3_message << endl;
			ofs << evatution_ketol_message.c_str() << endl;
			ofs << evatution_OKI_message.c_str() << endl;
			ofs << evatution_Ice_message.c_str() << endl;
			ofs << evatution_renge_message.c_str() << endl;
			ofs << evatution_Elstove1_message.c_str() << endl;
			ofs << evatution_Elstove2_message.c_str() << endl;
			ofs << evatution_Elstove3_message.c_str() << endl;
			ofs << evatution_Combined_message.c_str() << endl;
			time_count = 0;
			Foo foo;
			thread th(foo);
			th.detach();
		}

		if (ketol_conuter == 60) {
			ketol_conuter = 0;
		}
		else if (ketol_conuter != 0) {
			ketol_conuter += 1;
		}

		if (OKI_counter == 60) {
			OKI_counter = 0;
		}
		else if (OKI_counter != 0) {
			OKI_counter += 1;
		}

		if (Ice_counter == 30) {
			Ice_counter = 0;
		}
		else if (Ice_counter != 0) {
			Ice_counter += 1;
		}

		if (renge_counter == 60) {
			renge_counter = 0;
		}
		else if (renge_counter != 0) {
			renge_counter += 1;
		}

		PC1_use = 0;
		PC2_use = 0;
		PC3_use = 0;
		PC4_use = 0;
		PC5_use = 0;


		Sleep(2000);
	}
}