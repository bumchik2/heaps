#include "testrunner.h"
#include "profile.h"
#include "heap headers//leftistheap.h"
#include "heap headers//stlheap.h"
#include "heap headers//slantingheap.h"
#include "heap headers//binomialheap.h"
#include "heap headers//AVLtree.h"
#include "test.h"
#include <iostream>
#include <stdexcept>
#include <string>

void doSpeedTestInsertExtrMin (TestRunner& tr) {
	LeftistHeap lh;
	SlantingHeap sh;
	BinomialHeap bh;
	Tree tree;
	std::cout << "enter total number of insert and "
			"extractmin operations:" << std::endl;
	int numberOfOperations;
	std::cin >> numberOfOperations;
	std::cout << "enter probability of insert operation" << std::endl <<
			"it has to be > 0.1 and <= 1 (and probably > 0.5?):" << std::endl;
	double d;
	std::cin >> d;
	generateSpeedTest (numberOfOperations, d);

	bool success[4] = {false, false, false, false};
	success[0] = tr.RunTest (checkTestInsertExtrMin, lh,
			"checking if insert & extrmin speed test works correctly for leftist heap");
	success[1] = tr.RunTest (checkTestInsertExtrMin, sh,
			"checking if insert & extrminspeed test works correctly for slanting heap");
	success[2] = tr.RunTest (checkTestInsertExtrMin, bh,
			"checking if insert & extrmin speed test works correctly for binomial heap");
	success[3] = tr.RunTest (checkTestInsertExtrMin, tree,
			"checking if insert & extrmin speed test works correctly for AVL tree");
	if (success[0]) {
		speedTestInsertExtrMin (lh, "leftist heap");
	}
	if (success[1]) {
		speedTestInsertExtrMin (sh, "slanting heap");
	}
	if (success[2]) {
		speedTestInsertExtrMin (bh, "binomial heap");
	}
	if (success[3]) {
		speedTestInsertExtrMin (bh, "AVL tree");
	}
}

void doSpeedTestMerge (TestRunner& tr) {
	LeftistHeap lh1, lh2;
	SlantingHeap sh1, sh2;
	BinomialHeap bh1, bh2;
	Tree tr1, tr2;
	std::cout << "enter number of elements in the first heap:" << std::endl;
	int number1;
	std::cin >> number1;
	std::cout << "enter number of elements in the second heap:" << std::endl;
	int number2;
	std::cin >> number2;
	generateMergeTest (number1, number2);
	bool success[4] = {false, false, false, false};
	success[0] = tr.RunTest (checkTestMerge, lh1, lh2,
			"checking if merge speed test works correctly for leftist heap");
	success[1] = tr.RunTest (checkTestMerge, sh1, sh2,
			"checking if merge speed test works correctly for slanting heap");
	success[2] = tr.RunTest (checkTestMerge, bh1, bh2,
			"checking if merge speed test works correctly for binomial heap");
	success[3] = tr.RunTest (checkTestMerge, bh1, bh2,
			"checking if merge speed test works correctly for AVL heap");
	if (success[0]) {
		mergeSpeedTest (lh1, lh2, "leftist heap");
	}
	if (success[1]) {
		mergeSpeedTest (sh1, sh2, "slanting heap");
	}
	if (success[2]) {
		mergeSpeedTest (bh1, bh2, "binomial heap");
	}
	if (success[3]) {
		mergeSpeedTest (tr1, tr2, "AVL tree");
	}
}

void TestAll() {
	LeftistHeap lh;
	SlantingHeap sh;
	BinomialHeap bh;
	Tree tree;

	TestRunner tr;
	tr.RunTest(easyTest, lh, "leftist heap easy extract test");
	tr.RunTest(easyTest, sh, "slanting heap easy extract test");
	tr.RunTest(easyTest, bh, "binomial heap easy extract test");
	tr.RunTest(easyTest, tree, "AVL tree easy extract test");

	LeftistHeap lh1, lh2;
	SlantingHeap sh1, sh2;
	BinomialHeap bh1, bh2;
	Tree tr1, tr2;

	tr.RunTest(mergeTest, lh1, lh2, "leftist heap easy merge test");
	tr.RunTest(mergeTest, sh1, sh2, "slanting heap easy merge test");
	tr.RunTest(mergeTest, bh1, bh2, "binomial heap easy merge test");
	tr.RunTest(mergeTest, tr1, tr2, "AVL tree easy merge test");

	doSpeedTestInsertExtrMin (tr);
	doSpeedTestMerge (tr);
}

int main () {
	srand(time(0));
	TestAll();
	return 0;
}

