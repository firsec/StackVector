#pragma once

#include <functional>
#include <vector>
#include <cstddef>

namespace internal_namespace {
	template <typename Destructible>
	class stack_allocator {
		template <typename T2>
		friend class stack_allocator;
	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Destructible* pointer;
		typedef const Destructible* const_pointer;
		typedef Destructible& reference;
		typedef const Destructible& const_reference;
		typedef Destructible value_type;

		template <typename T2>
		struct rebind {
			typedef stack_allocator<T2> other;
		};

	private:
		Destructible* ptr;
		size_t currentSize, maxSize;

	public:
		inline stack_allocator() noexcept :
			ptr(nullptr),
			currentSize(0),
			maxSize(0) {
		}

		inline stack_allocator(Destructible* buffer, size_t size) noexcept :
			ptr(buffer),
			currentSize(0),
			maxSize(size) {
		}

		template <typename T2>
		inline explicit stack_allocator(const stack_allocator<T2>& other) noexcept :
			ptr(reinterpret_cast<Destructible*>(other.ptr)),
			currentSize(other.currentSize),
			maxSize(other.maxSize) {
		}

		inline Destructible* allocate(size_t n, const void* hint = nullptr) {
			Destructible* pointer = ptr + currentSize;
			currentSize += n;
			return pointer;
		}

		inline void deallocate(Destructible* p, size_t n) {
			currentSize -= n;
		}

		inline size_t capacity() const noexcept {
			return maxSize;
		}

		inline size_t max_size() const noexcept {
			return maxSize;
		}

		inline Destructible* address(Destructible& x) const noexcept {
			return &x;
		}

		inline const Destructible* address(const Destructible& x) const noexcept {
			return &x;
		}

		inline Destructible* buffer() const noexcept {
			return ptr;
		}

		template <typename T2>
		inline stack_allocator<Destructible>& operator=(const stack_allocator<T2>& alloc) {
			return *this;
		}

		template <typename... Args>
		inline void construct(Destructible* p, Args&&... args) {
			new (p) Destructible(std::forward<Args>(args)...);
		}

		inline void destroy(Destructible* p) {
			p->~Destructible();
		}

		template <typename T2>
		inline bool operator==(const stack_allocator<T2>& other) const noexcept {
			return ptr == other.ptr;
		}

		template <typename T2>
		inline bool operator!=(const stack_allocator<T2>& other) const noexcept {
			return ptr != other.ptr;
		}
	};

	template <typename Indestructible>
	class stack_allocator<const Indestructible> {
		template <typename T2>
		friend class stack_allocator;

	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Indestructible* pointer;
		typedef const Indestructible* const_pointer;
		typedef Indestructible& reference;
		typedef const Indestructible& const_reference;
		typedef Indestructible value_type;

		template <typename T2>
		struct rebind {
			typedef stack_allocator<const T2> other;
		};

	private:
		Indestructible* ptr;
		size_t currentSize, maxSize;

	public:
		inline stack_allocator() noexcept :
			ptr(nullptr),
			currentSize(0),
			maxSize(0) {
		}

		inline stack_allocator(Indestructible* buffer, size_t size) noexcept :
			ptr(buffer),
			currentSize(0),
			maxSize(size) {
		}

		template <typename T2>
		inline explicit stack_allocator(const stack_allocator<T2>& other) noexcept :
			ptr(reinterpret_cast<Indestructible*>(other.ptr)),
			currentSize(other.currentSize),
			maxSize(other.maxSize) {
		}

		inline Indestructible* allocate(size_t n, const void* hint = nullptr) {
			Indestructible* pointer = ptr + currentSize;
			currentSize += n;
			return pointer;
		}

		inline void deallocate(Indestructible* p, size_t n) {
			currentSize -= n;
		}

		inline size_t capacity() const noexcept {
			return maxSize;
		}

		inline size_t max_size() const noexcept {
			return maxSize;
		}

		inline Indestructible* address(Indestructible& x) const noexcept {
			return &x;
		}

		inline const Indestructible* address(const Indestructible& x) const noexcept {
			return &x;
		}

		inline Indestructible* buffer() const noexcept {
			return ptr;
		}

		template <typename T2>
		inline stack_allocator<Indestructible>& operator=(const stack_allocator<T2>& alloc) {
			return *this;
		}

		template <typename... Args>
		inline void construct(Indestructible* p, Args&&... args) {
			new (p) Indestructible(std::forward<Args>(args)...);
		}

		inline void destroy(Indestructible* p) {
		}

		template <typename T2>
		inline bool operator==(const stack_allocator<T2>& other) const noexcept {
			return ptr == other.ptr;
		}

		template <typename T2>
		inline bool operator!=(const stack_allocator<T2>& other) const noexcept {
			return ptr != other.ptr;
		}
	};
}

#define aligned_alloca(T, size) reinterpret_cast<T*>((reinterpret_cast<unsigned long long>(alloca((size) * sizeof(T) + alignof(T) - 1)) + (alignof(T) - 1)) & ~(alignof(T) - 1))

#define new_stack_vector(Type, Name, Size) std::vector<Type, internal_namespace::stack_allocator<Type>> Name((internal_namespace::stack_allocator<Type>(reinterpret_cast<Type*>(alloca((Size) * sizeof(Type))), (Size))));\
			Name.reserve(Size)
#define new_stack_vector_no_dtor(Type, Name, Size) std::vector<Type, internal_namespace::stack_allocator<const Type>> Name((internal_namespace::stack_allocator<const Type>(reinterpret_cast<Type*>(alloca((Size) * sizeof(Type))), (Size))));\
			Name.reserve(Size)

#define new_stack_vector_align(Type, Name, Size) std::vector<Type, internal_namespace::stack_allocator<Type>> Name((internal_namespace::stack_allocator<Type>(aligned_alloca(Type, (Size)), (Size))));\
			Name.reserve(Size)
#define new_stack_vector_align_no_dtor(Type, Name, Size) std::vector<Type, internal_namespace::stack_allocator<const Type>> Name((internal_namespace::stack_allocator<const Type>(aligned_alloca(Type, (Size)), (Size))));\
			Name.reserve(Size)
