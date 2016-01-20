#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

enum class State { Init, Sign, Coeff, Power };

map<int, int> make_deriviate(map<int, int> p) {
	map<int, int> dp;
	for(auto it=p.begin(); it != p.end(); ++it) {
		if (it->first == 0)
			continue;
		dp.insert(make_pair(it->first-1, it->second*it->first));
	}
	return dp;
}

string polly_to_str(map<int, int> p) {
	if(p.empty())
		return "0";
	bool first = true;
	stringstream s;
	for(auto it = p.rbegin(); it != p.rend(); ++it) {
		if(it->second == 0)
			continue;
		if(!first && it->second > 0) {
			first = false;
			s << "+";
		}
		if(it->first != 0) {
			if (it->second == 1) {
				//nothing
			} else if (it->second == -1) {
				s << "-";
			} else {
				s << it->second << "*";
			}
			if (it->first > 1) {
				s << "x^" << it->first;
			} else if (it->first == 1) {
				s << "x";
			}
		} else {
			s << it->second;
		}
		first = false;
	}
	
	return s.str();
}

void add_member(map<int, int> &p, int coeff, int power, bool sign) {
	if (sign) coeff *= -1;
	auto it = p.find(power);
	if (it == p.end()) {
		p.insert(make_pair(power, coeff));
	} else {
		it->second += coeff;
	}
}

map<int, int> parse(string s) {
	map<int, int> p;
	
	State st = State::Init;
	int coeff = 1;
	bool coeff_present = false;
	int power = 0;
	bool power_present = false;
	bool sign = false;
	auto it = s.begin();
	while(it != s.end()) {
		switch (st) {
			case State::Init:
				if (coeff_present || power)
					add_member(p, coeff, power, sign);
				coeff = 1;
				coeff_present = false;
				power = 0;
				power_present = false;
				sign = false;
			case State::Sign:
				if(*it == '-' || *it == '+') {
					if(*it == '-') {
						sign = true;
					}
					++it;
				}
				st = State::Coeff;
				break;
			case State::Coeff:
				if (*it == '*') {
					power = 1;
					st = State::Power;
					it+=2;
					break;
				}
				else if (*it == 'x') {
					power = 1;
					st = State::Power;
					++it;
					break;
				}
				else if (*it == '+' || *it == '-') {
					st = State::Init;
					break;
				}
				if (coeff_present)
					coeff = coeff*10 + (*it - '0');
				else
					coeff = (*it - '0');
				coeff_present = true;
				++it;
				break;
			case State::Power:
				if( *it == '^') {
					++it;
				}
				if (*it == '+' || *it == '-') {
					st = State::Init;
					break;
				}
				if(power_present)
					power = power*10 + (*it - '0');
				else
					power = (*it - '0');
				power_present = true;
				++it;
				break;
			default:
				cout << "Error parsing" << endl;
		}
	}
	
	if (coeff || power)
		add_member(p, coeff, power, sign);
		
	return p;
}

int main() {
	string s;
	cin >> s;
	//cout << polly_to_str(make_deriviate(parse(s))) << endl;
	cout << polly_to_str(parse(s)) << endl;
	return 0;
}