#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "allocator.h"
#include "container.h"

TEST_CASE( "Testing the allocator class for std::map" ) {
	std::map<int, int, std::less<int>,
			allocator<std::pair<const int, int>, 3>> map;
	map[ 0 ] = 1;
	map[ 1 ] = 2;
	map[ 2 ] = 3;
	map[ 3 ] = 4;
	CHECK( map[ 2 ] == 3 );
	CHECK( map[ 3 ] == 4 );
}

TEST_CASE( "Testing the allocator class for std::vector" ) {
	std::vector<int, allocator<int>> list;
	list.reserve ( 15 );
	list.emplace_back ( 1 );
	list.emplace_back ( 2 );
	list.erase ( list.begin () );
	CHECK( list[ 0 ] == 2 );
}

TEST_CASE( "Testing custom container with std::allocator" ) {
	container<int> array;
	array.add ( 1 );
	array.add ( 2 );
	array.remove ( 0 );
	CHECK( array[ 0 ] == 2 );
}

TEST_CASE( "Testing custom container with custom allocator" ) {
	container<int, allocator<int>> array;
	array.add ( 1 );
	array.add ( 2 );
	array.remove ( 0 );
	CHECK( array[ 0 ] == 2 );
}
