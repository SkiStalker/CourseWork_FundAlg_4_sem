#pragma once
#include "BinaryTree.h"

template<class TKey, class TValue>
class AVLTree : public BinaryTree<TKey, TValue>
{
public:

	using BinaryTree = BinaryTree<TKey, TValue>;
	using Tree = BinaryTree::Tree;
	using Node = Tree::Node;
	using BinaryNode = BinaryTree::BinaryNode;

	class AVLNode : public BinaryNode
	{
		friend class AVLTree;
	public:
		AVLNode(const TKey& key, const TValue& value);
		int balance;
	};

	AVLNode*& root;
	AVLTree(Comparator<TKey>* comp) : BinaryTree(comp), root((AVLNode*&)BinaryTree::root)
	{

	}


private:
	void doBalance(AVLNode** axis);
	int recalñBalance(AVLNode* node);
	void bigRightRot(AVLNode** node);
	void bigLeftRot(AVLNode** node);
	void rightRot(AVLNode** node);
	void leftRot(AVLNode** node);


protected:
	typename BinaryNode* newNode(const Node& node) override;

	void pastFind(stack<BinaryNode**>* last_parents) override;

	void pastAddToTree(stack<BinaryNode**>* last_parents) override;

	void pastReplaceInTree() override;

	void pastRemoveFromTree(stack<BinaryNode**>* last_parents) override;
};


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::doBalance(AVLNode** axis)
{
	// Ñïðàâà íà 2 áîëüøå ÷åì ñëåâà
	if ((*axis)->balance > 1)
	{
		if (((AVLNode*)(*axis)->right)->balance > -1)
		{
			leftRot(axis);
		}
		else
		{
			bigLeftRot(axis);
		}
	}
	// Ñëåâà íà 2 áîëüøå ÷åì ñïðàâà
	else if ((*axis)->balance < -1)
	{
		if (((AVLNode*)(*axis)->left)->balance < 1)
		{
			rightRot(axis);
		}
		else
		{
			bigRightRot(axis);
		}
	}
}

template<class TKey, class TValue>
inline int AVLTree<TKey, TValue>::recalñBalance(AVLNode* node)
{
	int r_bal = 0;
	int l_bal = 0;
	if (!node->right && !node->left)
	{
		r_bal = 0;
		l_bal = 0;
	}
	else if (!node->right && node->left)
	{
		r_bal = 0;
		l_bal = recalñBalance((AVLNode*)node->left);
	}
	else if (node->right && !node->left)
	{
		r_bal = recalñBalance((AVLNode*)node->right);
		l_bal = 0;
	}
	else
	{
		r_bal = recalñBalance((AVLNode*)node->right);
		l_bal = recalñBalance((AVLNode*)node->left);
	}
	node->balance = r_bal - l_bal;
	return 1 + (r_bal > l_bal ? r_bal : l_bal);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::rightRot(AVLNode** node)
{
	auto tmp = (AVLNode*)(*node)->left;
	swap((*node)->left, ((AVLNode*)(*node)->left)->right);
	tmp->right = *node;
	*node = tmp;
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::leftRot(AVLNode** node)
{
	auto tmp = (AVLNode*)(*node)->right;
	swap((*node)->right, ((AVLNode*)(*node)->right)->left);
	tmp->left = *node;
	*node = tmp;
}

template<class TKey, class TValue>
typename AVLTree<TKey, TValue>::BinaryNode* AVLTree<TKey, TValue>::newNode(const Node& node)
{
	return new AVLNode(node.key, node.value);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::bigRightRot(AVLNode** node)
{
	leftRot((AVLNode**)(&(*node)->left));
	rightRot(node);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::bigLeftRot(AVLNode** node)
{
	rightRot((AVLNode**)(&(*node)->right));
	leftRot(node);
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::pastFind(stack<BinaryNode**>* last_parents)
{
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::pastAddToTree(stack<BinaryNode**>* last_parents)
{
	last_parents->pop();
	if (last_parents->empty())
		return;

	recalñBalance(*(AVLNode**)last_parents->top());
	while (!last_parents->empty() && ((AVLNode*)*last_parents->top())->balance) // balance == 0
	{
		recalñBalance(*(AVLNode**)last_parents->top());
		doBalance((AVLNode**)last_parents->top());
		recalñBalance(*(AVLNode**)last_parents->top());
		last_parents->pop();
	}
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::pastReplaceInTree()
{
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::pastRemoveFromTree(stack<BinaryNode**>* last_parents)
{
	if (!last_parents)
	{
		return;
	}

	last_parents->pop();
	while (!last_parents->empty() && !(*last_parents->top()))
		last_parents->pop();

	if (last_parents->empty())
		return;

	recalñBalance(*(AVLNode**)last_parents->top());
	while (!last_parents->empty() && ((AVLNode*)*last_parents->top())->balance) // balance == 0
	{
		recalñBalance(*(AVLNode**)last_parents->top());
		doBalance((AVLNode**)last_parents->top());
		recalñBalance(*(AVLNode**)last_parents->top());
		last_parents->pop();
	}
}

template<class TKey, class TValue>
AVLTree<TKey, TValue>::AVLNode::AVLNode(const TKey& key, const TValue& value) : BinaryNode(key, value)
{

}
