#pragma once
#include <utility.h>

class Interval {

public :
	double min; 
	double max; 

	Interval() : min(+infinity), max(-infinity) {} // Default to empty interval
		
	Interval(double min, double max) : min(min), max(max) {}

	double size() const {
		return max - min;
	}

	bool contains(double value) const {
		return value >= min && value <= max;
	}

	bool surrounds(double x)
	{
		return x >= min && x <= max;
	}

	static const Interval empty, universe; 




};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);