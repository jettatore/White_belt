#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using namespace std;

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}
	Rational(int numerator_, int denominator_) {
		int a = abs(numerator_), b = abs(denominator_);
		int c = 1;
		if (numerator_) {
			while (c) {
				c = a % b;
				a = b;
				b = c;
			}
			if (numerator_ < 0 && denominator_ < 0) {
				numerator_ = abs(numerator_);
				denominator_ = abs(denominator_);
			}
			else if (numerator_ < 0 || denominator_ < 0) {
				numerator_ = -1 * abs(numerator_);
				denominator_ = abs(denominator_);
			}
			numerator = numerator_ / a;
			denominator = denominator_ / a;
		}
		else { numerator = 0; denominator = 1; }
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

private:
	int numerator;
	int denominator;
};

bool operator==(Rational lhs, Rational rhs) {
	return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(Rational lhs, Rational rhs) {
	int num = 0, den = 0;
	num = lhs.Numerator()*rhs.Denominator() + rhs.Numerator()*lhs.Denominator();
	den = lhs.Denominator()*rhs.Denominator();
	return Rational(num, den);
}

Rational operator-(Rational lhs, Rational rhs) {
	int num = 0, den = 0;
	num = lhs.Numerator()*rhs.Denominator() - rhs.Numerator()*lhs.Denominator();
	den = lhs.Denominator()*rhs.Denominator();
	return Rational(num, den);
}

Rational operator*(Rational lhs, Rational rhs) {
	return Rational(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator/(Rational lhs, Rational rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& rat) {
	stream << rat.Numerator() << "/" << rat.Denominator();
	return stream;
}

istream& operator>>(istream& in, Rational& rat) {
	int num;
	in >> num;
	in.ignore(1);
	int den;
	in >> den;
	rat = Rational(num, den);
	return in;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	//int ok = lhs.Denominator()*rhs.Denominator();
	int com_lhs = lhs.Numerator()*rhs.Denominator();
	int com_rhs = rhs.Numerator()*lhs.Denominator();
	return com_lhs < com_rhs;
}

int main() {
	{
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10) {
			cout << "Rational(3, 10) != 3/10" << endl;
			return 1;
		}
	}

	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			cout << "Rational(8, 12) != 2/3" << endl;
			return 2;
		}
	}

	{
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(-4, 6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(4, -6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			cout << "Rational(0, 15) != 0/1" << endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
			cout << "Rational() != 0/1" << endl;
			return 5;
		}
	}
	cout << "OK" << endl;
	

	//operators ==, +, -
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}
	cout << "OK" << endl;


	//operators *, /
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}
	cout << "OK" << endl;

	
	//operators <<, >>
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			//return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			//return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			//return 3;
		}
	}
	cout << "OK" << endl;


	//containers
	{
		const set<Rational> rs = { { 1, 2 },{ 1, 25 },{ 3, 4 },{ 3, 4 },{ 1, 2 } };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}
	cout << "OK" << endl;

	return 0;
}