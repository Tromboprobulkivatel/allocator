#include <iostream>
#include <map>
#include <vector>
#include "allocator.h"
#include "container.h"

template<typename T>
void testMap ( T&& container ) {
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

template<typename T>
void testContainer ( T&& container ) {
	for ( std::size_t i = 0; i < 10; i++ ) {
		container.add ( i );
	}
	for ( std::size_t i = 0; i < 10; i++ ) {
		std::cout << container [ i ] << std::endl;
	}
}

int main ( int, char* [] ) {
	testMap ( std::map<int, int> {} );
	testMap ( std::map<int, int, std::less<int>,
			allocator<std::pair<const int, int>, 10>> {} );
	testContainer ( container<int> {} );
	testContainer ( container<int, allocator<int>> {} );
	return 0;
}
