#include "stdexcept"
#include <iostream>
#include <vector>
#include "heap headers//binomialheap.h"

using std::vector;

BinomialHeap::BinomialHeap (): first_vertix_(0), best_vertix_(0) {}

BinomialHeap::Node::Node (int key):
		rightBrother_(0), firstSon_(0), lastSon_(0),
		key_(key), degree_(0) {}

BinomialHeap::BinomialHeap (int key):
		first_vertix_(new Node (key)), best_vertix_(first_vertix_) {}

bool BinomialHeap::Empty () const {
	return first_vertix_ == 0;
}

const int& BinomialHeap::GetMin () const {
	if (Empty()) {
		throw std::runtime_error ("no min to get in BinomialHeap");
	}
	return best_vertix_->key_;
}

BinomialHeap::Node* merge_ (BinomialHeap::Node* node1,
		BinomialHeap::Node* node2) {
	BinomialHeap::Node* result = 0;
	if (node1->key_ > node2->key_) {
		std::swap (node1, node2);
	}
	if (node1->key_ <= node2->key_) {
		result = node1;
		if (result->lastSon_ != 0) {
			result->lastSon_->rightBrother_ = node2;
			result->lastSon_ = result->lastSon_->rightBrother_;
		} else {
			result->firstSon_ = result->lastSon_ = node2;
		}
	}
	result->degree_ = node1->degree_ + 1;
	return result;
}

void add_ (BinomialHeap::Node*& node1, BinomialHeap::Node* node2, bool& moved) {
	if (node1 == 0) {
		node1 = node2;
	} else if (node1->degree_ < node2->degree_) {
		node1->rightBrother_ = node2;
		moved = true;
	} else if (node1->degree_ == node2->degree_) {
		node1 = merge_ (node1, node2);
	} else {
		throw std::invalid_argument ("impossible!");
	}
}

void BinomialHeap::Merge (IHeap& ih) {
	BinomialHeap& bh = dynamic_cast<BinomialHeap&> (ih);
	if (bh.Empty()) {
		return;
	}
	if (Empty()) {
		*this = bh;
		bh = BinomialHeap();
		return;
	}
	BinomialHeap result;
	Node* node1 = this->first_vertix_;
	Node* node2 = bh.first_vertix_;
	Node* node = 0;
	vector<Node*> v;
	bool moved = false;
	while (node1 != 0 || node2 != 0) {
		moved = false;
		if (node1 != 0 && (node2 == 0 || node1->degree_ < node2->degree_)) {
			Node* temp1 = node1->rightBrother_;
			node1->rightBrother_ = 0;
			add_ (node, node1, moved);
			node1 = temp1;
		} else if (node2 != 0 && (node1 == 0 || node2->degree_ < node1->degree_)) {
			Node* temp2 = node2->rightBrother_;
			node2->rightBrother_ = 0;
			add_ (node, node2, moved);
			node2 = temp2;
		} else {
			Node* temp1 = node1->rightBrother_;
			Node* temp2 = node2->rightBrother_;
			node1->rightBrother_ = 0;
			node2->rightBrother_ = 0;
			Node* merged = merge_(node1, node2);
			add_ (node, merged, moved);
			node1 = temp1;
			node2 = temp2;
		}
		if (moved) {
			v.push_back(node);
			node = node->rightBrother_;
		}
	}
	v.push_back(node);
	v.push_back(0);
	for (int i = v.size() - 2; i >= 0; --i) {
		v[i]->rightBrother_ = v[i+1];
	}
	result.first_vertix_ = v[0];
	result.best_vertix_ = minNode_ (result.first_vertix_);
	*this = result;
	bh = BinomialHeap();
}

void BinomialHeap::Insert (int key) {
	BinomialHeap bh (key);
	Merge (bh);
}

BinomialHeap::Node* minNode_ (BinomialHeap::Node* node) {
	BinomialHeap::Node* result = 0;
	while (node != 0) {
		if (result == 0 || node->key_ < result->key_) {
			result = node;
		}
		node = node->rightBrother_;
	}
	return result;
}

BinomialHeap::BinomialHeap (Node* node): BinomialHeap() {
	if (node != 0) {
		first_vertix_ = node->firstSon_;
		best_vertix_ = minNode_ (node->firstSon_);
	}
}

void BinomialHeap::ExtractMin () {
	if (Empty()) {
		throw std::runtime_error ("no min to extract from BinomialHeap");
	}
	BinomialHeap bh (best_vertix_);
	if (first_vertix_ == best_vertix_) {
		first_vertix_ = first_vertix_->rightBrother_;
		delete best_vertix_;
		best_vertix_ = minNode_ (first_vertix_);
	} else {
		Node* node = first_vertix_;
		while (node->rightBrother_ != best_vertix_) {
			node = node->rightBrother_;
		}
		node->rightBrother_ = best_vertix_->rightBrother_;
		delete best_vertix_;
		best_vertix_ = minNode_ (first_vertix_);
	}
	Merge (bh);
}


