#include<iostream>
#include<string>
#include<exception>
#include<sstream>
#include<map>
#include<set>
#include <iomanip>

using namespace std;

class Date {
public:
	Date()
	{
		Year = 0;
		Month = 0;
		Day = 0;
	}
	Date(int new_Year, int new_Month, int new_Day) {
		Year = new_Year;
		Month = new_Month;
		Day = new_Day;
	}
	int GetYear() const {
		return Year;
	}

	int GetMonth() const {
		return Month;
	}

	int GetDay() const {
		return Day;
	}

private:
	int Year;
	int Month;
	int Day;
};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
};

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		Base[date].insert(event);
	}


	bool DeleteEvent(const Date& date, const string& event) {
		if (Base.at(date).count(event) > 0) {
			Base[date].erase(event);
			return true;
		}
		else return false;
		
		/*
		if (Base.count(date) > 0) {
			Base.at[date].erase(event);
			return true;
		}
		else return false;
		*/
	}

	int  DeleteDate(const Date& date) {
		int deleted = 0;
		if (Base.count(date) > 0) {
			deleted = Base.at(date).size();
			Base.erase(date);
		}
		return deleted;
	}

	void Find(const Date& date) const {
		if (Base.count(date) > 0) {
			for (const auto& event : Base.at(date)) {
				cout << event << endl;
			}
		}
	}

	void Print() const {
		cout << setfill('0');
		for (const auto& item : Base) {
			for (const auto& event : item.second) {
				cout << setw(4) << item.first.GetYear() << "-"
					<< setw(2) << item.first.GetMonth() << "-"
					<< setw(2) << item.first.GetDay() << " "
					<< event << endl;
			}
		}
	}

private:
	map<Date, set<string>>Base;
};

Date is_correct(string& date_string) {
	int year = 0, month = 0, day = 0;
	char symbol = ' ';
	string wrong_format = "Wrong date format: " + date_string;
	stringstream input(date_string);
	if (!isdigit(input.peek())) {
		throw invalid_argument(wrong_format);
	}
	while (isdigit(input.peek())) {
		symbol = input.peek();
		year = year * 10 + symbol - 48;
		input.ignore(1);
	}
	if (input.peek() != '-') {
		throw invalid_argument(wrong_format);
	}
	input.ignore(1);
	if (!isdigit(input.peek())) {
		throw invalid_argument(wrong_format);
	}
	while (isdigit(input.peek())) {
		symbol = input.peek();
		month = month * 10 + symbol - 48;
		input.ignore(1);
	}
	if (input.peek() != '-') {
		throw invalid_argument(wrong_format);
	}
	input.ignore(1);
	if (!isdigit(input.peek())) {
		throw invalid_argument(wrong_format);
	}
	while (isdigit(input.peek())) {
		symbol = input.peek();
		day = day * 10 + symbol - 48;
		input.ignore(1);
	}
	if (!input.eof()) {
		throw invalid_argument(wrong_format);
	}
	string error;
	if (month < 1 || month > 12) {
		error = "Month value is invalid: " + to_string(month);
		throw invalid_argument(error);
	}
	if (day < 1 || day > 31) {
		error = "Day value is invalid: " + to_string(day);
		throw invalid_argument(error);
	}
	return { year,month,day };
}

int main() {
	Database db;
	string command, cmd, date_string, event;
	Date date;

	while (getline(cin, command)) {
		date_string = "";
		event = "";
		cmd = "";
		stringstream input(command);
		input >> cmd;
		try {
			if (cmd == "Add") {
				input >> date_string;
				date = is_correct(date_string);
				if (!input.eof()) {
					input >> event;
					if (event != ""&&event != " ") {
						db.AddEvent(date, event);
					}
				}
				/*
				else {
					throw invalid_argument("Wrong date format: " + date_string);
				}
				*/
			}
			else if (cmd == "Del") {
				input >> date_string;
				date = is_correct(date_string);
				if (!input.eof()) {
					input >> event;
					if (event != ""&&event != " ") {
						if (db.DeleteEvent(date, event)) {
							cout << "Deleted successfully" << endl;
						}
						else {
							cout << "Event not found" << endl;
						}
					}
				}
				else {
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
				}
			}
			else if (cmd == "Find") {
				input >> date_string;
				date = is_correct(date_string);
				db.Find(date);
			}
			else if (cmd == "Print") {
				db.Print();
			}
			else if (cmd != "") {
				throw invalid_argument("Unknown command: " + cmd);
			}
		}
		catch (exception& error) {
			cout << error.what() << endl;
			return 0;
		}
	}
	//system("pause");
	return 0;
}


