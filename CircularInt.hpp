#include <iostream>
using std::ostream;
using std::istream;
class CircularInt {
	int _min, _max;   // smallest and largest possible values
	int _count;       // how many different values are there (auxiliary field)
	int _now;         // current value;

	int normalized(int num) const;

	// inits _min to min, _max to max, and _now to now.
	// Does NOT normalize now (this is why it is private).
	CircularInt(int min, int max, int now);

public: 
	// inits _min to min, _max to max, and _now to _min.
	CircularInt(int min, int max): 
		CircularInt(min, max, min) { }

	CircularInt& operator+= (int i) {
		_now = normalized(_now + i);
		return *this;
	}

	CircularInt& operator*= (int i) {
		_now = normalized(_now * i);
		return *this;
	}

	const CircularInt operator+(const CircularInt& other) {
		return CircularInt(_min,_max, normalized(_now+other._now));
	}

	const CircularInt operator++(int) {
		int _previous = _now;
		_now = normalized(_now + 1);
		return CircularInt(_min,_max,_previous);
	}

	CircularInt operator-() const {
		return CircularInt{_min, _max, normalized(-_now)};
	}
	

	friend ostream& operator<<(ostream&, const CircularInt&);
	friend const CircularInt operator-(int, const CircularInt&);
	friend const CircularInt operator/(const CircularInt& c, int n);
};

