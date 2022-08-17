#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "allocator.h"

TEST_CASE( "Testing the allocator class" ) {
	std::map<int, int, std::less<int>,
			allocator<std::pair<const int, int>, 3>> m1;
	m1[0] = 1;
	m1[1] = 2;
	m1[2] = 3;
	m1[3] = 4;
	CHECK( m1[2] == 3 );
	CHECK( m1[3] == 4 );

//	std::vector<chunk, allocator<chunk<chunk>>> storage;

}
