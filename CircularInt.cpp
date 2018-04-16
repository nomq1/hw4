#include "CircularInt.hpp"
#include <string>
using namespace std;

ostream& operator<<(ostream& out, const CircularInt& c) {
	return (out << c._now);
}

CircularInt::CircularInt(int min, int max, int now): 
	_min(min), _max(max), _now(now), _count(max-min+1) {
	if (min>max)
		throw string("min>max: min=")+to_string(min)+", max="+to_string(max);
}

int CircularInt::normalized(int num) const {
	num -= _min;
	num %= _count;
	if (num<0) num += _count;
	num += _min;
	return num;
}

const CircularInt operator-(int n, const CircularInt& c) {
	return CircularInt(c._min, c._max, c.normalized(n-c._now));
}

const CircularInt operator/(const CircularInt& c, int n) {
	for (int x=c._min; x<=c._max; ++x) {
		if (c.normalized(x*n)==c._now) {
			return CircularInt(c._min, c._max, x);
		}
	}
	throw string(
		"There is no number x in {"+to_string(c._min)+","+to_string(c._max)+"}"+
		" such that x*"+to_string(n)+"="+to_string(c._now)
	);
}
