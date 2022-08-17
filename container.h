#ifndef ALLOCATOR_CONTAINER_H
#define ALLOCATOR_CONTAINER_H
#include <memory>

template <typename T, typename A = std::allocator<T>>
class container {
public:
	container ( std::size_t reserve = 10 ) {
		references.reserve ( reserve );
	}

	void add ( const T value ) {
		auto address = storage.allocate ( 1 );
		storage.construct ( address, value );
		references.emplace_back ( address );
	}

	void remove ( std::size_t index ) {
		auto pointer = references[ index ];
		storage.destroy ( pointer );
		storage.deallocate ( pointer, 1 );
		references.erase ( references.begin () + index );
	}

	T& operator[] ( std::size_t index ) {
		return *references[ index ];
	}

	~container () {
		for ( const auto& pointer: references ) {
			storage.destroy ( pointer );
			storage.deallocate ( pointer, 1 );
		}
	}
private:
	A storage;
	std::vector<T*, A> references;
};
#endif
