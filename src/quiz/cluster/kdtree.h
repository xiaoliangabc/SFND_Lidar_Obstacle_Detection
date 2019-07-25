/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
        // the function should create a new node and place correctly with in the root
		insertHelper(root, 0, point, id);

	}

	void insertHelper(Node *&node, uint depth, std::vector<float> point, int id)
    {
        if(node == NULL)
		{
			node = new Node(point, id);
		}
		else if (depth % 2 == 0) 
		{
			if(point[0] < node->point[0])
			{
				insertHelper(node->left, depth + 1, point, id);
			}
			else
			{
				insertHelper(node->right, depth + 1, point, id);
			}
		}
		else
		{
			if(point[1] < node->point[1])
			{
				insertHelper(node->left, depth + 1, point, id);
			}
			else
			{
				insertHelper(node->right, depth + 1,point, id);
			}
		}
    }

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
        searchHelper(root, 0, ids, target, distanceTol);
		return ids;
	}
	
    void searchHelper(Node *&node, uint depth, std::vector<int>& ids, std::vector<float> target, float distanceTol)
    {
		if(node != NULL)
		{
            uint cd = depth % 2;
            if (fabs(node->point[cd] - target[cd]) < distanceTol) {
                float distance = sqrt(pow(node->point[0] - target[0], 2) + pow(node->point[1] - target[1], 2));
                if (distance <= distanceTol)
                    ids.push_back(node->id);
                searchHelper(node->left, depth + 1, ids, target, distanceTol);
                searchHelper(node->right, depth + 1, ids, target, distanceTol);
            }
            else
            {
                if (node->point[cd] < target[cd])
                    searchHelper(node->right, depth + 1, ids, target, distanceTol);
                else 
                    searchHelper(node->left, depth + 1, ids, target, distanceTol);
            }
		}
    }
};




