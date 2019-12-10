#pragma once

#include "IHeap.h"

class LeftistHeap : public IHeap {
public:
	LeftistHeap ();
	LeftistHeap (int key);
	void Insert (int key) override;
	const int& GetMin () const override;
	void ExtractMin () override;
	void Merge (IHeap& lh) override;
	bool Empty () const override;
private:
	int height_;
	int value_;
	LeftistHeap* left_;
	LeftistHeap* right_;
	friend int h_ (LeftistHeap* ptr);
	void countHeight_();
	void fix_();
	friend LeftistHeap Merge (LeftistHeap& lh1, LeftistHeap& lh2);
};
