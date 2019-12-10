#pragma once

#include "Iheap.h"

class BinomialHeap : public IHeap {
public:
	BinomialHeap ();
	BinomialHeap (int key);
	void Insert (int key) override;
	const int& GetMin () const override;
	void ExtractMin () override;
	void Merge (IHeap& lh) override;
	bool Empty () const override;
private:
	class Node {
	public:
		Node (int key);
		Node* rightBrother_;
		Node* firstSon_;
		Node* lastSon_;
		int key_;
		int degree_;
	};
	friend void add_ (Node*& node1, Node* node2, bool& moved);
	friend Node* merge_ (Node* node1, Node* node2);
	friend Node* minNode_ (Node* node);
	BinomialHeap (Node* node);
	Node* first_vertix_;
	Node* best_vertix_;
};
