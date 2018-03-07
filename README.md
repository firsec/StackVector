# Stack Vector

A faster C++ dynamic vector allocator that allocates on the stack instead of the heap (better speed for small sizes).

Sample benchmark:
```
Stack vector
sum: 8256
Elapsed ms: 0.000284445 ms
Stack vector no dtor
sum: 8256
Elapsed ms: 0.000853334 ms
Stack vector aligned
sum: 8256
Elapsed ms: 0.00142222 ms
Stack vector aligned no dtor
sum: 8256
Elapsed ms: 0.000853334 ms
Heap vector
sum: 8256
Elapsed ms: 0.00199111 ms
```
`Heap vector` is the default vector allocator that ships with the C++ Standard Library. As you can see, all stack allocators were faster for a small allocation on the stack, which in this case is a vector of size `129 * sizeof(Custom)`, and `Custom` is a class containing a `char` and a `size_t`.

This benchmark gives similar output in Visual Studio, GCC and Clang, even with optimizations on or off, which demonstrates a desirable merging of the flexibility of vectors with the speed of stack arrays.

Allocating the vector is very simple: new_stack_vector(Type, name, size)
where `Type` is the type of element in the vector, `name` is the variable name of the vector, and `size` is the maximum number of elements to allow in the vector.

Example:
```
new_stack_vector(int, vec, 100); //like vector<int> vec; vec.reserve(100); but on the stack :)
vec.push_back(10); //added "10" as the first item in the vector
```
...and that's all!
