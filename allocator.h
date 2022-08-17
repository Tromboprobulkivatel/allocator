#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

template <typename T, int Span = 10>
class allocator {
	class chunk {
		size_t capacity;
		size_t used;
		T* from;
		T* to;
	public:
		chunk () : capacity ( 0 ), used ( 0 ), from ( nullptr ), to ( nullptr ) {};

		T* allocate ( size_t need ) {
			if ( capacity == 0 ) {
				reserve ( Span * ( need / Span ) + Span );
			} else if ( need > capacity ) {
				return nullptr;
			}
			return take ( need );
		}

		bool deallocate ( T* address, size_t victims ) {
			if ( address < from || address > to ) {
				return false;
			} else if ( victims == used ) {
				std::free ( from );
				capacity = 0;
				used = 0;
				from = nullptr;
				to = nullptr;
			} else {
				used -= victims;
			}
			return true;
		}
	private:
		void reserve ( size_t items ) {
			capacity = items;
			from = reinterpret_cast<T*> ( std::malloc ( capacity * sizeof ( T ) ) );
			if ( !from ) {
				throw std::bad_alloc ();
			}
			to = from;
		}

		T* take ( size_t need ) {
			capacity -= need;
			used += need;
			auto started = to;
			to += need;
			return started;
		}
	};
	std::vector<chunk> storage;
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind {
		using other = allocator<U>;
	};

	allocator () {
		storage.reserve ( Span );
	}

	template <typename U>
	allocator ( const allocator<U>& ) {
	}

	T* allocate ( std::size_t need ) {
		T* memory;
		for ( auto& chunk: storage ) {
			memory = chunk.allocate ( need );
			if ( memory ) {
				return memory;
			}
		}
		chunk next;
		memory = next.allocate ( need );
		storage.emplace_back ( next );
		return memory;
	}

	void deallocate ( T* from, std::size_t victims ) {
		for ( auto& chunk: storage ) {
			if ( chunk.deallocate ( from, victims ) ) {
				return;
			}
		}
		throw std::runtime_error ( "Bad deallocation address" );
	}

	template <typename U, typename ...Args>
	void construct ( U* p, Args&& ...args ) {
		new ( p ) U ( std::forward<Args> ( args )... );
	};

	void destroy ( T* p ) {
		p->~T ();
	}
};

#endif
