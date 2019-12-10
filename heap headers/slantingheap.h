#pragma once

#include "IHeap.h"

class SlantingHeap : public IHeap {
public:
	SlantingHeap ();
	SlantingHeap (int key);
	void Insert (int key) override;
	const int& GetMin () const override;
	void ExtractMin () override;
	void Merge (IHeap& lh) override;
	bool Empty () const override;
private:
	int value_;
	SlantingHeap* left_;
	SlantingHeap* right_;
	friend bool bottom (const SlantingHeap* sh);
	void fix_();
	friend SlantingHeap Merge (SlantingHeap& lh1, SlantingHeap& lh2);
};
