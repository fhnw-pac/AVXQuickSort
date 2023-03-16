#include "QuickSort.h"
#include <assert.h>
#include <immintrin.h>

constexpr int elemsIn256 = (sizeof(__m256i) / sizeof(int));

// naive quicksort without tail recursion elimination
void QuickSort::qSortNaive(std::vector<int>& a, size_t beg, size_t end)
{
	if (beg < end) {
		int x = a[(beg + end) / 2];
		size_t i = beg, j = end;
		while (i <= j) {
			while (a[i] < x)
				i++;
			while (a[j] > x)
				j--;
			if (i <= j) {
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				i++;
				j--;
			}
		}
		qSortNaive(a, beg, j);
		qSortNaive(a, i, end);
	}
}

void QuickSort::qSortAVX(std::vector<int>& a, size_t beg, size_t end)
{
	size_t range = end - beg;
	assert((range > 0) && "invalid sorting range");

	// 1. TODO do left, then do right
	
	// 2. TODO do the rest in between

	// 3. TODO finish the rest sequentially

	// 4. TODO recursive calls on left and right side
}

double QuickSort::meassuredSort(void(QuickSort::* sortFunc)(std::vector<int>&), std::vector<int>& a)
{
	auto start = std::chrono::high_resolution_clock::now();

	(this->*sortFunc)(a);

	auto stop = std::chrono::high_resolution_clock::now();

	return (double)std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}

bool QuickSort::prove(std::vector<int>& a)
{
	for (uint64_t i = 0; i < a.size() - 1; ++i) {
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

std::vector<int> QuickSort::createRandomData(uint64_t size)
{
	std::vector<int> data;

	// random gen
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, INT_MAX);
	generator.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < size; ++i) {
		data.push_back(distribution(generator));
	}

	return data;
}
