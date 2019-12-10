#include <algorithm>
#include <exception>
#include <stdexcept>
#include "heap headers//slantingheap.h"

SlantingHeap::SlantingHeap() :
		value_(0), left_(0), right_(0) {}
SlantingHeap::SlantingHeap(int key): value_(key),
			left_(new SlantingHeap()), right_(new SlantingHeap()) {}

void SlantingHeap::fix_() {
	std::swap(left_, right_);
}

bool bottom (const SlantingHeap* sh) {
	return (sh->left_ == 0 && sh->right_ == 0);
}

SlantingHeap Merge (SlantingHeap& lh1, SlantingHeap& lh2) {
	if (bottom(&lh1) || bottom(&lh2)) {
		return bottom(&lh1) ? lh2 : lh1;
	}
	if (lh1.value_ > lh2.value_) {
		std::swap(lh1, lh2);
	}
	*lh1.right_ = Merge (*lh1.right_, lh2);
	lh1.fix_();
	return lh1;
}

void SlantingHeap::Merge (IHeap& h) {
	SlantingHeap& lh1 = *this;
	SlantingHeap& lh2 = dynamic_cast<SlantingHeap&>(h);
	*this = ::Merge (lh1, lh2);
	lh2 = SlantingHeap();
}

void SlantingHeap::Insert (int key) {
	SlantingHeap* lh = new SlantingHeap (key);
	Merge (*lh);
}

const int& SlantingHeap::GetMin() const {
	if (bottom(this)) {
		throw std::runtime_error ("no min to get in SlantingHeap");
	}
	return value_;
}

void SlantingHeap::ExtractMin() {
	if (bottom(this)) {
		throw std::runtime_error ("no min to extract from SlantingHeap");
	}
	*this = ::Merge (*left_, *right_);
}

bool SlantingHeap::Empty() const {
	return left_ == 0 && right_ == 0;
}


