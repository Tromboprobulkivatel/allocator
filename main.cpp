#include <iostream>
#include <map>
#include <vector>
#include "allocator.h"

template<typename T>
void fillAndShow ( T&& container ) {
	int key = 0;
	int factorial = 1;
	do {
		container[ key ] = factorial;
		factorial *= ++key;
	} while ( key < 10 );
	for ( const auto& item : container ) {
		std::cout << item.first << ' ' << item.second << std::endl;
	}
}

int main ( int, char* [] ) {
	fillAndShow ( std::map<int, int> {} );
	fillAndShow ( std::map<int, int, std::less<int>,
	        allocator<std::pair<const int, int>, 10>>{} );
//	std::map<int, int, std::less<int>, allocator<std::pair<const int, int>, 10>> x {};
//	x[1] = 1;
//	x[2] = 2;

	/*
	std::map<int, int> container;
	int key = 0;
	int factorial = 1;
	do {
		container[ key ] = factorial;
		factorial *= ++key;
	} while ( key < 10 );
*/
//	auto c2 = std::map<int, int, std::less<int>, allocator<std::pair<const int, int>, 10>>{};
//	for ( int i = 0; i < 10; i++ ) {
		//c2[i] = Factorial<5>::value;
//	}
//	c2[5] = 1;

	//std::map<int, int> c2;
	// 11, Mo
	/*
	auto v = std::vector<int, allocator<int>>{};
	// v.reserve(5);
	for (int i = 0; i < 6; ++i) {
		std::cout << "vector size = " << v.size() << std::endl;
		v.emplace_back(i);
		std::cout << std::endl;
	}
*/
	// std::cout << "\n\n\n\nAfter creation\n\n\n\n" << std::endl;
	// auto v2 = v;
/*
	auto m = std::map<
			int,
			float,
			std::less<int>,
			allocator<
			std::pair<
					const int, float
			>
	>
			 >{};

	for (int i = 0; i < 1; ++i) {
		m[i] = static_cast<float>(i);
	}
*/
	return 0;
}
