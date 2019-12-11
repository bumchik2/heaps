#pragma once

#include "heap headers//Iheap.h"
#include "heap headers//StlHeap.h"
#include "heap headers//AVLtree.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

void processRequest (const std::string& request, IHeap& heap,
		int number, const std::string& finish) {
	if (request == "extractmin") {
		heap.ExtractMin();
	} else if (request == "insert") {
		heap.Insert(number);
	} else if (request != finish) {
		throw std::invalid_argument ("unknown request");
	}
}

void doRequests (IHeap& heap, StlHeap& sh, std::ifstream& fin,
		const std::string& finish, bool check) {
	std::string request;
	while (request != finish) {
		fin >> request;
		int number = 0;
		if (request == "insert")  {
			fin >> number;
		}
		processRequest (request, heap, number, finish);
		if (check) {
			processRequest (request, sh, number, finish);
			if (!sh.Empty() || !heap.Empty()) {
				ASSERT_EQUAL (heap.GetMin(), sh.GetMin());
			}
		}
	}
}

void checkEqual (IHeap& heap1, IHeap& heap2, const std::string& errorMessage) {
	while (!heap1.Empty()) {
		//std::cout << heap1.GetMin() << " " << heap2.GetMin() << std::endl;
		ASSERT_EQUAL (heap1.GetMin(), heap2.GetMin());
		heap1.ExtractMin();
		heap2.ExtractMin();
	}
	if (!heap2.Empty()) {
		throw std::runtime_error (errorMessage);
	}
}

void easyTest (IHeap& heap) {
	StlHeap sh;
	std::ifstream fin ("tests//easy_extract_test.txt");
	doRequests (heap, sh, fin, "end", 1);
	checkEqual (heap, sh, "results of easyTest are not equal");
}

void mergeTest (IHeap& heap1, IHeap& heap2) {
	StlHeap sh1, sh2;
	std::ifstream fin ("tests//easy_merge_test.txt");
	std::string request;
	doRequests (heap1, sh1, fin, "second_heap", 1);
	doRequests (heap2, sh2, fin, "end", 1);
	heap1.Merge(heap2);
	sh1.Merge(sh2);
	if (!heap2.Empty() || !sh2.Empty()) {
		throw std::runtime_error ("merge works incorrectly");
	}
	checkEqual (heap1, sh1, "results of merge are not equal");
}

int randomInt (int module = 1000000) {
	return ((rand() % 1000) + (rand() % 1000) * 1000 +
			(rand() % 1000) * 1000 * 1000) % module;
}

void checkNumberOfOperations (int numberOfOperations) {
	if (numberOfOperations < 0 || numberOfOperations > 1000000) {
		throw std::invalid_argument ("bad number of operations value");
	}
}

void checkProbability (double d) {
	if (d < 0.1 || d > 1) {
		throw std::invalid_argument ("bad insert probability value");
	}
}

void addOperation (std::ofstream& fout, double d, int& cnt) {
	int r = rand() % 1000;
	if (cnt < 0) {
		throw std::runtime_error ("impossible");
	}
	if (r < 1000 * d || cnt == 0) {
		++cnt;
		fout << "insert " << randomInt() << std::endl;
	} else {
		--cnt;
		fout << "extractmin" << std::endl;
	}
}

void addOperations (std::ofstream& fout, double d, int numberOfOperations, const std::string& finish) {
	int cnt = 0; // to check, if insert is met more often than extractmin
	while (numberOfOperations--) {
		addOperation (fout, d, cnt);
	}
	fout << finish << '\n';
}

void generateSpeedTest (int numberOfOperations, double d) {
	checkNumberOfOperations (numberOfOperations);
	checkProbability(d);
	std::ofstream fout ("tests//speed_test.txt");
	addOperations (fout, d, numberOfOperations, "end");
}

void generateMergeTest (int number1, int number2) {
	checkNumberOfOperations (number1);
	checkNumberOfOperations (number1);
	std::ofstream fout ("tests//speed_merge_test.txt");
	addOperations (fout, 1, number1, "second_heap");
	addOperations (fout, 1, number2, "end");
}

void checkTestInsertExtrMin (IHeap& heap) {
	std::ifstream fin ("tests//speed_test.txt");
	StlHeap sh;
	doRequests (heap, sh, fin, "end", 1);
	checkEqual (heap, sh, "heaps are not equal");
}

void speedTestInsertExtrMin (IHeap& heap, const std::string& heapName) {
	LOG_DURATION (heapName + " insert & extractmin:")
	std::ifstream fin ("tests//speed_test.txt");
	StlHeap garbage;
	doRequests (heap, garbage, fin, "end", 0);
}

void checkTestMerge (IHeap& heap1, IHeap& heap2) {
	std::ifstream fin ("tests//speed_merge_test.txt");
	StlHeap sh1, sh2;
	doRequests (heap1, sh1, fin, "second_heap", 1);
	doRequests (heap2, sh2, fin, "end", 1);
	heap1.Merge(heap2);
	sh1.Merge(sh2);
	checkEqual (heap1, sh1, "heaps are not equal");
}

void mergeSpeedTest (IHeap& heap1, IHeap& heap2, const std::string& heapName) {
	std::ifstream fin ("tests//speed_merge_test.txt");
	StlHeap garbage;
	doRequests (heap1, garbage, fin, "second_heap", 0);
	doRequests (heap2, garbage, fin, "end", 0);
	LOG_DURATION (heapName + " merge:");
	heap1.Merge(heap2);
}
