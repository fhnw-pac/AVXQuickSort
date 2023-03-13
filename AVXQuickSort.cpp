#include <iostream>
#include "QuickSort.h"

int main() {

	QuickSort q;
	const uint64_t size = 50 * 1024 * 1024; // 50M * 4Byte = 200MByte

	auto seqData = q.createRandomData(size);			
	auto avxData(seqData);

	double seqTime = q.quickSortNaive(seqData);
	if (!q.prove(seqData)) {
		std::cout << "seq sort did not sort..." << std::endl;
		exit(-42);
	}

	std::cout << "sorted seq in " << seqTime << "ms" << std::endl;

	double parTime = q.quickSortAVX(avxData);
	if (!q.prove(avxData)) {
		std::cout << "avx sort did not sort..." << std::endl;
		exit(-42);
	}

	// compare if both sorts did the same thing
	if (memcmp(avxData.data(), seqData.data(), sizeof(int) * seqData.size())) {
		std::cout << "sorts do not have the same result..." << std::endl;
		exit(-42);
	}

	std::cout << "sorting worked!" << std::endl;

	std::cout << "sorted AVX in " << parTime << "ms" << std::endl;
	std::cout << "speedup is " << seqTime / parTime << std::endl;
}
