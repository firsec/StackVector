#include "stdio.h"
#include "stopwatch.h"
#include "stack_vector.h"

using namespace std;

static constexpr size_t num = 129;

class Custom {
public:
	char paddingLol;
	size_t val;

	Custom() : val(0) {
	}

	Custom(size_t value) : val(value) {
	}

	~Custom() {
		val = 0;
	}
};

int main() {
	Stopwatch watch;
	size_t sum, i;
	for (int iter = 0; iter < 2; iter++) {
		printf("Iteration %d\n", iter);
		{
			printf("Stack vector\n");
			watch.restart();
			new_stack_vector(Custom, v, num);
			sum = 0;
			for (i = 0; i < num; i++) {
				v.emplace_back(i);
				sum += v[v.size() - 1].val;
			}
			watch.stop();
		}
		printf("sum: %zu\n", sum);
		printf("Elapsed ms: %g ms\n", watch.getElapsedMilliseconds());
		{
			printf("Stack vector no dtor\n");
			watch.restart();
			new_stack_vector(Custom, v, num);
			sum = 0;
			for (i = 0; i < num; i++) {
				v.emplace_back(i);
				sum += v[v.size() - 1].val;
			}
			watch.stop();
		}
		printf("sum: %zu\n", sum);
		printf("Elapsed ms: %g ms\n", watch.getElapsedMilliseconds());
		{
			printf("Stack vector aligned\n");
			watch.restart();
			new_stack_vector_align(Custom, v, num);
			sum = 0;
			for (i = 0; i < num; i++) {
				v.emplace_back(i);
				sum += v[v.size() - 1].val;
			}
			watch.stop();
		}
		printf("sum: %zu\n", sum);
		printf("Elapsed ms: %g ms\n", watch.getElapsedMilliseconds());
		{
			printf("Stack vector aligned no dtor\n");
			watch.restart();
			new_stack_vector_align_no_dtor(Custom, v, num);
			sum = 0;
			for (i = 0; i < num; i++) {
				v.emplace_back(i);
				sum += v[v.size() - 1].val;
			}
			watch.stop();
		}
		printf("sum: %zu\n", sum);
		printf("Elapsed ms: %g ms\n", watch.getElapsedMilliseconds());
		{
			printf("Heap vector\n");
			watch.restart();
			vector<Custom> v;
			v.reserve(num);
			sum = 0;
			for (i = 0; i < num; i++) {
				v.emplace_back(i);
				sum += v[v.size() - 1].val;
			}
			watch.stop();
		}
		printf("sum: %zu\n", sum);
		printf("Elapsed ms: %g ms\n\n", watch.getElapsedMilliseconds());
	}

	printf("Benchmark completed, press enter to exit...");
	char shitlol[8];
	return fgets(shitlol, 8, stdin) == nullptr;
}