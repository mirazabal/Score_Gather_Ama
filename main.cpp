#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class score_gathering
{
	struct Node
	{
		Node(int key, Node* parent): key_(key), parent_(parent), count_(1){};

		int key_;
		int count_;

		Node* parent_;
		unique_ptr<Node> left_;
		unique_ptr<Node> right_;
	};

	struct Tree
	{
		Tree() {};
		
		~Tree()
		{				
		}

		void insert_node( Node* parent, Node* node ,  int key)
		{
			if( node == nullptr){
				if(root_ == nullptr){
					root_ = unique_ptr<Node>(new Node(key, nullptr) );
					return;
				}
					if(key < parent->key_)
						parent->left_ = std::unique_ptr<Node>( new Node( key, parent ));
					else
						parent->right_ = std::unique_ptr<Node>( new Node (key, parent)); 
					return;
			}

			if(key == node->key_){
				node->count_++;
				return;
			}
			if( key < node->key_)
				insert_node(node, node->left_.get() , key );
			else
				insert_node(node, node->right_.get() , key);
		}

		string print_level(Node* root)
		{
			string retString;
			queue<Node*> q;
		
			if(root == nullptr){
				retString += ",";
			}else {
				retString += to_string(root->key_) + ":" + to_string(root->count_);
				if( root->left_ != nullptr || root->right_ != nullptr){
					q.emplace(root->left_.get());
					q.emplace(root->right_.get());
				}
			}
			
			while(q.size() != 0){
				Node* temp = q.front();
				q.pop();

				if(temp == nullptr )
					retString += ",";
				else {
				retString += "," + to_string(temp->key_) + ":" + to_string(temp->count_) ;
					if(temp->left_ != nullptr || temp->right_ != nullptr){
						q.emplace(temp->left_.get() );
						q.emplace(temp->right_.get());
					}
				}
			}
			return retString;
		}
		unique_ptr<Node> root_;
	};

	public:
		score_gathering(){};
		~score_gathering()
		{
		};
	void create_tree(vector<int>& vec )
	{
		for(auto value : vec){
			tree_.insert_node(tree_.root_.get(), tree_.root_.get(), value);
		}
	}

	std::string serialize()
	{
		return tree_.print_level(tree_.root_.get());
	}

	private:
		Tree tree_;
};

int main()
{
	score_gathering sg;
	vector<int> vec{ 4,2,5,5,6,1,4};
	sg.create_tree(vec);
	cout << sg.serialize() << endl;

	return 0;
}

