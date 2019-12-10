#include <algorithm>
#include <exception>
#include <stdexcept>
#include "heap headers//leftistheap.h"

LeftistHeap::LeftistHeap() :
		height_ (0), value_(0), left_(0), right_(0) {}
LeftistHeap::LeftistHeap(int key): height_(1), value_(key),
			left_(new LeftistHeap()), right_(new LeftistHeap()) {}

int h_ (LeftistHeap* ptr) {
	return ptr == 0 ? 0 : ptr->height_;
}

void LeftistHeap::countHeight_() {
	height_ = std::max(h_(left_), h_(right_));
}

void LeftistHeap::fix_() {
	countHeight_();
	if (h_(right_) > h_(left_)) {
		std::swap(left_, right_);
	}
}

LeftistHeap Merge (LeftistHeap& lh1, LeftistHeap& lh2) {
	if (h_(&lh1) == 0 || h_(&lh2) == 0) {
		return h_(&lh1) == 0 ? lh2 : lh1;
	}
	if (lh1.value_ > lh2.value_) {
		std::swap(lh1, lh2);
	}
	*lh1.right_ = Merge (*lh1.right_, lh2);
	lh1.fix_();
	return lh1;
}

void LeftistHeap::Merge (IHeap& h) {
	LeftistHeap& lh1 = *this;
	LeftistHeap& lh2 = dynamic_cast<LeftistHeap&>(h);
	*this = ::Merge (lh1, lh2);
	lh2 = LeftistHeap();
}

void LeftistHeap::Insert (int key) {
	LeftistHeap* lh = new LeftistHeap (key);
	Merge (*lh);
}

const int& LeftistHeap::GetMin() const {
	if (height_ == 0) {
		throw std::runtime_error ("no min to get in LeftistHeap");
	}
	return value_;
}

void LeftistHeap::ExtractMin() {
	if (height_ == 0) {
		throw std::runtime_error ("no min to extract from LeftistHeap");
	}
	*this = ::Merge (*left_, *right_);
}

bool LeftistHeap::Empty() const {
	return height_ == 0;
}


