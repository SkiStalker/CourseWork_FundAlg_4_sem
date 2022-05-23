#pragma once
#include <stack>
#include <exception>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <deque>

#include "Exceptions.h"
#include "Comparator.h"

using namespace std;


template<typename Key, typename Value>
class Tree
{
public:
	using callbackFunction = function<void(const Key& k, const Value& v, int d)>;

	class Node
	{
		friend class Tree;
	public:
		Node(const Key& key, const Value& value);
		Key key;
		Value value;
	protected:
		Node() {}
	};

	Tree(Comparator<Key>* comp)
	{
		this->comparator = std::shared_ptr<Comparator<Key>>(comp);
	}

	virtual ~Tree();
	Tree& operator += (const Node& node);
	Tree& operator *= (const Node& node);
	Tree& operator -= (const Key& key);
	Value& operator [] (const Key& index);
	virtual void prefixTraversal(callbackFunction func) const = 0;
	virtual void postfixTraversal(callbackFunction func) const = 0;
	virtual void infixTraversal(callbackFunction func) const = 0;
	void copy(Tree* tree);
	virtual void clearTree() = 0;

protected:
	Tree() {}
	std::shared_ptr<Comparator<Key>> comparator;
	virtual void addToTree(const Node& node) = 0;
	virtual void removeFromTree(const Key& key) = 0;
	virtual void replaceInTree(const Node& node) = 0;
	virtual Value& findInTree(const Key& key) = 0;
};


template <typename Key, typename Value>
class BinaryTree : public Tree<Key, Value>
{
public:
	using Tree = Tree<Key, Value>;
	using callbackFunction = Tree::callbackFunction;
	using Node = Tree::Node;

	BinaryTree(Comparator<Key>* comparator);

	BinaryTree(const BinaryTree<Key, Value>& tree);

	BinaryTree& operator = (const BinaryTree& right);

	~BinaryTree() override;

	class BinaryNode : public Node
	{
		friend class BinaryTree;
	public:
		BinaryNode(const Key& key, const Value& value);
	protected:
		BinaryNode* left = nullptr;
		BinaryNode* right = nullptr;
	};

	void prefixTraversal(callbackFunction func) const;
	void postfixTraversal(callbackFunction func) const;
	void infixTraversal(callbackFunction func) const;

	void infixTraversalIterative(callbackFunction func) const;

	void clearTree() override;

private:
	void deleteTree(BinaryNode*& cur);
	void prefixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const;
	void postfixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const;
	void infixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const;
	void addToTree(const Node& node) override;
	void removeFromTree(const Key& key) override;
	void replaceInTree(const Node& node) override;
	Value& findInTree(const Key& key) override;

protected:
	virtual void swapValues(BinaryNode** left, BinaryNode** right);
	virtual void deleteFindNode(BinaryNode** node);
	virtual void deleteNode(BinaryNode** node);
	virtual typename BinaryNode* newNode(const Node& node);
	BinaryNode* root = nullptr;

	typename BinaryNode** findSwapForRemove(BinaryTree<Key, Value>::BinaryNode* start,
		stack<BinaryNode**>* last_parents);

	stack<BinaryNode**>* findConcrete(BinaryNode*& root, const Key& key);
	virtual void pastFind(stack<BinaryNode**>* last_parents);

	stack<BinaryNode**>* addToTree—oncrete(BinaryNode*& root, const Node& node);
	virtual void pastAddToTree(stack<BinaryNode**>* last_parents);

	void replaceInTree—oncrete(BinaryNode*& root, const Node& node);
	virtual void pastReplaceInTree();

	stack<BinaryNode**>* removeFromTree—oncrete(BinaryNode*& root, const Key& key);
	virtual void pastRemoveFromTree(stack<BinaryNode**>* last_parents);

};


template<typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(Comparator<Key>* comparator) : Tree(comparator)
{
}

template<typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree<Key, Value>& tree)
{
	this->deleteTree(this->root);
	this->comparator = tree.comparator;
	vector<Node> nodes;
	tree.prefixTraversal([&nodes](const Key& k, const Value& v, int d) { nodes.push_back({ k, v }); });
	for (int i = 0; i < nodes.size(); i++)
	{
		(*this) += nodes[i];
	}
}

template<typename Key, typename Value>
BinaryTree<Key, Value>& BinaryTree<Key, Value>::operator=(const BinaryTree& right)
{
	this->deleteTree(this->root);
	this->comparator = right.comparator;
	vector<Node> nodes;
	right.prefixTraversal([&nodes](const Key& k, const Value& v, int d) { nodes.push_back({ k, v }); });
	for (int i = 0; i < nodes.size(); i++)
	{
		(*this) += nodes[i];
	}
	return *this;
}

template<typename Key, typename Value>
BinaryTree<Key, Value>::~BinaryTree()
{
	deleteTree(root);
}

template<typename Key, typename Value>
Tree<Key, Value>& Tree<Key, Value>::operator+=(const Node& node)
{
	addToTree(node);
	return *this;
}

template<typename Key, typename Value>
Tree<Key, Value>& Tree<Key, Value>::operator*=(const Node& node)
{
	replaceInTree(node);
	return *this;
}

template<typename Key, typename Value>
Tree<Key, Value>& Tree<Key, Value>::operator-=(const Key& key)
{
	removeFromTree(key);
	return *this;
}

template<typename Key, typename Value>
Value& Tree<Key, Value>::operator[](const Key& index)
{
	return findInTree(index);
}

template<typename Key, typename Value>
inline void Tree<Key, Value>::copy(Tree* tree)
{
	tree->clearTree();
	vector<Node> nodes;
	this->prefixTraversal([&nodes](Key k, Value v, int d) {nodes.push_back({ k, v }); });
	for (auto node : nodes)
		tree->addToTree(node);

}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::deleteTree(BinaryNode*& cur)
{
	if (cur == nullptr)
		return;

	deleteTree(cur->right);
	deleteTree(cur->left);
	delete cur;
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::prefixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const
{

	func(current->key, current->value, depth);

	if (current->left)
		prefixTraversal—oncrete(current->left, func, depth + 1);

	if (current->right)
		prefixTraversal—oncrete(current->right, func, depth + 1);
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::postfixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const
{
	if (current->left)
		postfixTraversal—oncrete(current->left, func, depth + 1);

	if (current->right)
		postfixTraversal—oncrete(current->right, func, depth + 1);

	func(current->key, current->value, depth);
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::infixTraversal—oncrete(const BinaryNode* const& current, callbackFunction func, int depth) const
{
	if (current->left)
		infixTraversal—oncrete(current->left, func, depth + 1);

	func(current->key, current->value, depth);

	if (current->right)
		infixTraversal—oncrete(current->right, func, depth + 1);
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::prefixTraversal(callbackFunction func) const
{
	prefixTraversal—oncrete(root, func, 0);
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::postfixTraversal(callbackFunction func) const
{
	postfixTraversal—oncrete(root, func, 0);
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::infixTraversal(callbackFunction func) const
{
	infixTraversal—oncrete(root, func, 0);
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::infixTraversalIterative(callbackFunction func) const
{
	struct FindNode
	{
		BinaryNode* node;
		bool leftComplete;
		bool rightComplete;
	};

	vector<FindNode*> nodes;

	nodes.push_back(new FindNode{ root, false, false });

	FindNode* cur = nodes.back();

	int d = 0;

	while (!nodes.empty())
	{
		cur = nodes.back();
		if (cur->node->left && !cur->leftComplete)
		{
			cur->leftComplete = true;
			nodes.push_back( new FindNode{cur->node->left, false, false});
			d++;
		}
		else if (cur->node->right && !cur->rightComplete)
		{
			cur->rightComplete = true;
			nodes.push_back(new FindNode{ cur->node->right, false, false });
			d++;
		}
		else
		{
			func(cur->node->key, cur->node->value, d);
			d--;
			delete nodes.back();
			nodes.pop_back();
		}
	}
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::addToTree(const Node& node)
{
	auto last_parents = addToTree—oncrete(root, node);
	pastAddToTree(last_parents);
	delete last_parents;
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::removeFromTree(const Key& key)
{
	auto last_parents = removeFromTree—oncrete(root, key);
	pastRemoveFromTree(last_parents);
	delete last_parents;
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::replaceInTree(const Node& node)
{
	replaceInTree—oncrete(root, node);
	pastReplaceInTree();
}

template<typename Key, typename Value>
inline Value& BinaryTree<Key, Value>::findInTree(const Key& key)
{
	auto last_parents = findConcrete(root, key);
	Value& val = (*last_parents->top())->value;
	pastFind(last_parents);
	delete last_parents;
	return val;
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::clearTree()
{
	deleteTree(root);
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::swapValues(BinaryNode** left, BinaryNode** right)
{
	swap((*left)->key, (*right)->key);
	swap((*left)->value, (*right)->value);
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::deleteFindNode(BinaryNode** node)
{
	BinaryNode* tmp = *node;
	(*node) = (*node)->left;
	delete tmp;
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::deleteNode(BinaryNode** node)
{
	BinaryNode* tmp = *node;
	(*node) = (*node)->right;
	delete tmp;
}

template<typename Key, typename Value>
inline typename BinaryTree<Key, Value>::BinaryNode* BinaryTree<Key, Value>::newNode(const Node& node)
{
	return new BinaryNode(node.key, node.value);
}


template<typename Key, typename Value>
inline typename BinaryTree<Key, Value>::BinaryNode** BinaryTree<Key, Value>::findSwapForRemove(BinaryTree<Key, Value>::BinaryNode* start, 
	stack<BinaryNode**>* last_parents)
{
	BinaryNode** cur = &start->left;
	last_parents->push(cur);
	if (!(*cur))
		return nullptr;
	while (true)
	{
		if ((*cur)->right)
		{
			cur = &(*cur)->right;
			last_parents->push(cur);
		}
		else
			break;
	}
	return cur;
}


template<typename Key, typename Value>
stack<typename BinaryTree<Key, Value>::BinaryNode**>* BinaryTree<Key, Value>::findConcrete(BinaryNode*& root, const Key& index)
{
	stack<BinaryNode**>* last_parents = new stack<BinaryNode**>();
	BinaryNode** cur = &root;
	while (*cur)
	{
		last_parents->push(cur);
		switch (this->comparator->compare(index, (*cur)->key))
		{
		case -1:
			cur = &(*cur)->left;
			break;
		case 1:
			cur = &(*cur)->right;
			break;
		case 0:
			return last_parents;
			break;
		}
	}
	throw NETreeException();
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::pastFind(stack<BinaryNode**>* last_parents)
{
}


template<typename Key, typename Value>
stack<typename BinaryTree<Key, Value>::BinaryNode**>* BinaryTree<Key, Value>::addToTree—oncrete(BinaryNode*& root, const Node& node)
{
	stack<BinaryNode**>* last_parents = new stack<BinaryNode**>();
	BinaryNode** cur = &root;

	while (*cur)
	{
		last_parents->push(cur);
		switch (this->comparator->compare(node.key, (*cur)->key))
		{
		case -1:
			cur = &(*cur)->left;
			break;
		case 1:
			cur = &(*cur)->right;
			break;
		case 0:
			throw AETreeException();
			break;
		default:
			throw ICTreeException();
			break;
		}
	}
	last_parents->push(cur);
	(*cur) = newNode(node);
	return last_parents;
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::pastAddToTree(stack<BinaryNode**>* last_parents)
{
}


template<typename Key, typename Value>
void BinaryTree<Key, Value>::replaceInTree—oncrete(BinaryNode*& root, const Node& node)
{
	BinaryNode* cur = root;
	while (cur)
	{
		switch (this->comparator->compare(node.key, cur->key))
		{
		case -1:
			cur = cur->left;
			break;
		case 1:
			cur = cur->right;
			break;
		case 0:
			cur->value = node.value;
			return;
		}
	}
	throw NETreeException();
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::pastReplaceInTree()
{
}

template<typename Key, typename Value>
stack<typename BinaryTree<Key, Value>::BinaryNode**>* BinaryTree<Key, Value>::removeFromTree—oncrete(BinaryNode*& root, const Key& key)
{
	stack<BinaryNode**>* last_parents = new stack<BinaryNode**>();
	// “ÂÍÛ˘ËÈ ÛÁÂÎ
	BinaryNode** cur = &root;
	while (*cur)
	{
		last_parents->push(cur);
		switch (this->comparator->compare(key, (*cur)->key))
		{
		case -1:
		{
			cur = &(*cur)->left;
			break;
		}
		case 1:
		{
			cur = &(*cur)->right;
			break;
		}
		case 0:


			// ›ÎÂÏÂÌÚ ‰Îˇ swap
			BinaryNode * *res = findSwapForRemove(*cur, last_parents);
			if (res)
			{
				// ÃÂÌˇÂÏ ÏÂÒÚ‡ÏË ÁÌ‡˜ÂÌËˇ Ë ÍÎ˛˜Ë
				swapValues(res, cur);
				deleteFindNode(res);
			}
			else
			{
				deleteNode(cur);
			}
			return last_parents;
		}
	}
	throw NETreeException();
}

template<typename Key, typename Value>
inline void BinaryTree<Key, Value>::pastRemoveFromTree(stack<BinaryNode**>* last_parents)
{
}


template<typename Key, typename Value>
BinaryTree<Key, Value>::BinaryNode::BinaryNode(const Key& key, const Value& value) : Node(key, value)
{
}

template<typename Key, typename Value>
inline Tree<Key, Value>::Node::Node(const Key& key, const Value& value) : key(key), value(value)
{
}

template<typename Key, typename Value>
inline Tree<Key, Value>::~Tree()
{
}