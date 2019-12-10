#include "heap headers//stlheap.h"
#include <exception>
#include <stdexcept>
#include <set>

void StlHeap::Insert (int key) {
	pq.push(key);
}

const int& StlHeap::GetMin () const {
	if (pq.size() == 0) {
		throw std::runtime_error ("no min to extract from StlHeap");
	}
	return pq.top();
}

void StlHeap::ExtractMin() {
	if (pq.size() == 0) {
		throw std::runtime_error ("no min to extract from StlHeap");
	}
	pq.pop();
}

void StlHeap::Merge (IHeap& h) {
	StlHeap& sh = dynamic_cast<StlHeap&>(h);
	while (!sh.pq.empty()) {
		pq.push(sh.pq.top());
		sh.pq.pop();
	}
}

bool StlHeap::Empty () const {
	return pq.empty();
}
