#pragma once

#include "Iheap.h"
#include <queue>
#include <vector>

class StlHeap : public IHeap {
public:
	void Insert (int key) override;
	const int& GetMin () const override;
	void ExtractMin () override;
	void Merge (IHeap& lh) override;
	bool Empty () const override;
private:
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
};
