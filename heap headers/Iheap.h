#pragma once

class IHeap {
public:
	virtual void Insert (int key) = 0;
	virtual const int& GetMin () const = 0;
	virtual void ExtractMin () = 0;
	virtual void Merge (IHeap& h) = 0;
	virtual bool Empty () const = 0;
};
