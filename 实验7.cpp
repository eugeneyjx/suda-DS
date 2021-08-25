#include <iostream>

using namespace std;

template <class Entry>
struct Binary_node
{
public:
	// data members:
	Entry data;
	Binary_node<Entry> *left;
	Binary_node<Entry> *right;
	// constructors:
	Binary_node();
	Binary_node(const Entry &x)
	{
		data = x;
		left = NULL;
		right = NULL;
	}
};

enum Error_code
{
	success, fail, not_present, duplicate_error
};

template<class Entry>
void print(Entry data)
{
	cout << data << endl;
}

template <class Entry>
class Binary_tree
{
protected:
	// Add auxiliary function prototypes here.
	Binary_node<Entry> *root;
public:
	Binary_tree();
	Error_code insert(const Entry &new_data);
	Error_code search_and_insert(Binary_node<Entry> * &sub_root, const Entry &new_data);
	bool empty() const;
	void preorder(void(*visit)(Entry &));
	void recursive_preorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &));
	void inorder(void(*visit)(Entry &));
	void recursive_inorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &));
	void postorder(void(*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &));
	int size() const;
	int recursive_size(Binary_node<Entry> *sub_root) const;
	void clear();
	void recursive_clear(Binary_node<Entry> * &sub_root);
	void deleteleaf();
	void recursive_deleteleaf(Binary_node<Entry>* &sub_root);
	int height() const;
	int recursive_height(Binary_node<Entry> *sub_root) const;
	Binary_node<Entry> *recursive_copy(Binary_node<Entry> *sub_root);
	Binary_tree(const Binary_tree<Entry> &original);
	Binary_tree & operator = (const Binary_tree<Entry> &original);
	void set_root(Entry x)
	{
		root = new Binary_node<Entry>(x);
	}
};

template <class Entry>
Error_code Binary_tree<Entry> ::insert(const Entry &new_data)
{
	return search_and_insert(root, new_data);
}

template <class Entry>
Error_code Binary_tree<Entry> ::search_and_insert(Binary_node<Entry> * &sub_root, const Entry &new_data)
{
	if (sub_root == NULL)
	{
		sub_root = new Binary_node<Entry>(new_data);
		return success;
	}
	else if (new_data < sub_root->data)
		return search_and_insert(sub_root->left, new_data);
	else if (new_data > sub_root->data)
		return search_and_insert(sub_root->right, new_data);
	else return duplicate_error;
}

template <class Entry>
int Binary_tree<Entry>::size() const
{
	return recursive_size(root);
}

template <class Entry>
int Binary_tree<Entry> ::recursive_size(Binary_node<Entry> *sub_root) const
/* Post: The number of entries in the subtree rooted at sub_root is returned. */
{
	if (sub_root == NULL) return 0;
	return  1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template <class Entry>
int Binary_tree<Entry>::height() const
{
	return recursive_height(root);
}

template <class Entry>
int Binary_tree<Entry> ::recursive_height(Binary_node<Entry> *sub_root) const
/* Post: The height of the subtree rooted at sub_root is returned. */
{
	if (sub_root == NULL) return 0;
	int l = recursive_height(sub_root->left);
	int r = recursive_height(sub_root->right);
	if (l > r) return 1 + l;
	else return 1 + r;
}

template <class Entry>
Binary_tree<Entry> ::Binary_tree()
/* Post: An empty binary tree has been created. */
{
	root = nullptr;
}

template <class Entry>
bool Binary_tree<Entry> ::empty() const
/* Post: A result of true is returned if the binary tree is empty. Otherwise, false is returned. */
{
	return root == NULL;
}

template <class Entry>
void Binary_tree<Entry> ::clear()
{
	recursive_clear(root);
}

template <class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry> * &sub_root)
{
	if (sub_root != NULL)
	{
		recursive_clear(sub_root->left);
		recursive_clear(sub_root->right);
		delete sub_root;
		sub_root = NULL;
	}
}

template <class Entry>
void Binary_tree<Entry> ::preorder(void(*visit)(Entry &))
/* Post: The tree has been been traversed in inorder sequence.
Uses: The function recursive_inorder */
{
	recursive_preorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry> ::recursive_preorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &))
{
	if (sub_root != NULL)
	{
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->left, visit);
		recursive_inorder(sub_root->right, visit);
	}
}

template <class Entry>
void Binary_tree<Entry> ::inorder(void(*visit)(Entry &))
/* Post: The tree has been been traversed in inorder sequence.
Uses: The function recursive_inorder */
{
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry> ::recursive_inorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &))
{
	if (sub_root != NULL)
	{
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}

template <class Entry>
void Binary_tree<Entry> ::postorder(void(*visit)(Entry &))
/* Post: The tree has been been traversed in inorder sequence.
Uses: The function recursive_inorder */
{
	recursive_postorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry> ::recursive_postorder(Binary_node<Entry> *sub_root, void(*visit)(Entry &))
{
	if (sub_root != NULL)
	{
		recursive_inorder(sub_root->left, visit);
		recursive_inorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}

template <class Entry>
Binary_tree<Entry>::Binary_tree(const Binary_tree<Entry> &original)
{
	root = recursive_copy(original.root);
}

template <class Entry>
Binary_node<Entry> *Binary_tree<Entry> ::recursive_copy(Binary_node<Entry> *sub_root)
/* Post: The subtree rooted at sub_root is copied, and a pointer to the root of the new copy is returned. */
{
	if (sub_root == NULL) return NULL;
	Binary_node<Entry> *temp = new Binary_node<Entry>(sub_root->data);
	temp->left = recursive_copy(sub_root->left);
	temp->right = recursive_copy(sub_root->right);
	return temp;
}

template <class Entry>
void Binary_tree<Entry>::recursive_deleteleaf(Binary_node<Entry>* &sub_root)
{

	if (sub_root == NULL)
		return;
	if (sub_root->left == NULL && sub_root->right == NULL)
	{
		delete sub_root; sub_root = NULL; return;
	}

	recursive_deleteleaf(sub_root->left);
	recursive_deleteleaf(sub_root->right);

}

template <class Entry>
void Binary_tree<Entry>::deleteleaf()
{
	recursive_deleteleaf(root);
}


template <class Record>
class Search_tree : public Binary_tree<Record> {
public:
	int size() const;
	int recursive_size(Binary_node<Record> *sub_root) const;
	Error_code insert(const Record &new_data);
	Error_code remove(const Record &old_data);
	Error_code tree_search(Record &target) const;
	Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, const Record &target) const;
	Error_code search_and_insert(Binary_node<Record> * &sub_root, const Record &new_data);
	Error_code search_and_destroy(Binary_node<Record>* &sub_root, const Record &target);
	Error_code remove_root(Binary_node<Record> * &sub_root);
private:
	// Add auxiliary function prototypes here.
	Binary_node<Record> *root;
};

template <class Record>
int Search_tree<Record>::size() const
{
	return recursive_size(root);
}

template <class Record>
int Search_tree<Record> ::recursive_size(Binary_node<Record> *sub_root) const
/* Post: The number of entries in the subtree rooted at sub_root is returned. */
{
	if (sub_root == NULL) return 0;
	return  1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template <class Record>
Binary_node<Record> *Search_tree<Record> ::search_for_node(Binary_node<Record>* sub_root, const Record &target) const
{
	if (sub_root == NULL || sub_root->data == target)
		return sub_root;
	else if (sub_root->data < target)
		return search_for_node(sub_root->right, target);
	else return search_for_node(sub_root->left, target);
}

template <class Record>
Error_code Search_tree<Record> ::tree_search(Record &target) const
{
	Error_code result = success;
	Binary_node<Record> *found = search_for_node(root, target);
	if (found == NULL)
		result = not_present;
	else
		target = found->data;
	return result;
}

template <class Record>
Error_code Search_tree<Record> ::insert(const Record &new_data)
{
	return search_and_insert(root, new_data);
}

template <class Record>
Error_code Search_tree<Record> ::search_and_insert(Binary_node<Record> * &sub_root, const Record &new_data)
{
	if (sub_root == NULL)
	{
		sub_root = new Binary_node<Record>(new_data);
		return success;
	}
	else if (new_data < sub_root->data)
		return search_and_insert(sub_root->left, new_data);
	else if (new_data > sub_root->data)
		return search_and_insert(sub_root->right, new_data);
	else return duplicate_error;
}

template <class Record>
Error_code Search_tree<Record> ::remove(const Record &target)
/* Post: If a Record with a key matching(符合） that of target belongs to the Search_tree a code of success is returned and the co. rresponding node is removed from the tree. Otherwise, a code of not_present is returned.
Uses: Function search_and_destroy */
{
	return search_and_destroy(root, target);
}

template <class Record>
Error_code Search_tree<Record> ::search_and_destroy(Binary_node<Record>* &sub_root, const Record &target)
{
	if (sub_root == NULL || sub_root->data == target)
		return remove_root(sub_root);
	else if (target < sub_root->data)
		return search_and_destroy(sub_root->left, target);
	else
		return search_and_destroy(sub_root->right, target);
}

template <class Record>
Error_code Search_tree<Record> ::remove_root(Binary_node<Record> * &sub_root)
{
	if (sub_root == NULL) return not_present;
	Binary_node<Record> *to_delete = sub_root;
	// Remember node to delete at end.
	if (sub_root->right == NULL) sub_root = sub_root->left;
	else if (sub_root->left == NULL) sub_root = sub_root->right;
	else { // Neither subtree is empty.
		to_delete = sub_root->left;
		// Move left to find predecessor(前驱）.
		Binary_node<Record> *parent = sub_root; // parent of to_delete
		while (to_delete->right != NULL)
		{ // to delete is not the predecessor.
			parent = to_delete;
			to_delete = to_delete->right;
		}
		sub_root->data = to_delete->data; // Move from to_delete to root.
		if (parent == sub_root) sub_root->left = to_delete->left;
		else parent->right = to_delete->left;
	}
	delete to_delete; //Remove to_delete from tree.
	return success;
}

int main()
{
	Binary_tree<int> bt;
	int root_value,n,node_value;
	cout << "现有一颗二叉树，请输入他的根节点的值(整数)："<<endl;
	cin >> root_value;
	bt.set_root(root_value);
	cout << "请输入节点数量:"<<endl;
	cin >> n;
	cout << "请输入更多节点值，节点将会以构建二叉查找树的顺序添加："<<endl;
	for (int i = 0; i < n; i++)
	{
		cin >> node_value;
		int result;
		result=bt.insert(node_value);
		if (result == 0) cout << "节点添加成功！" << endl;
	}

	cout << "二叉树构建完成。" << endl;
	cout << "先序遍历这棵树，得到序列：" << endl;
	bt.preorder(print);
	cout << "中序遍历这棵树，得到序列：" << endl;
	bt.inorder(print);
	cout << "后序遍历这棵树，得到序列：" << endl;
	bt.postorder(print);
	cout << "二叉树高度为" << bt.height() << endl;
	cout << "二叉树大小为" << bt.size() << endl;

	Search_tree<int> st;
	int root_value2, n2, node_value2;
	cout << "现有一颗二叉查找树，请输入他的根节点的值(整数)：" << endl;
	cin >> root_value2;
	st.set_root(root_value2);
	cout << "请输入需要添加的节点数量:" << endl;
	cin >> n;
	cout << "请输入更多节点值，构建二叉查找树：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> node_value2;
		int result;
		result = st.insert(node_value2);
		if (result == 0) cout << "节点添加成功！" << endl;
		else cout << "节点删除失败！";
	}

	cout << "请输入需要删除的节点数量:" << endl;
	cin >> n;
	cout << "请输入需要删除的节点值：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> node_value2;
		int result;
		result = st.remove(node_value2);
		if (result == 0) cout << "节点删除成功！" << endl;
		else cout << "节点删除失败！" << endl;
	}
	system("pause");

}


