#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"

#include <iostream>
#include <queue>
#include <stack>
#include "BinTree.h"

using namespace std;

class TreeNode
{
    public:
    explicit TreeNode(int val, TreeNode *left = nullptr, TreeNode *right = nullptr): value(val), left(left), right(right) {}

    int value;
    TreeNode *right = nullptr;
    TreeNode *left = nullptr;
};

TreeNode *createTree()
{
    printf("INPUT: \n");
    printf("     100                \n");
    printf("    /   \\              \n");
    printf("   50   200             \n");
    printf("  /  \\    \\           \n");
    printf(" 25   75   350          \n");
    printf("   \\        \\         \n");
    printf("    40       400        \n\n");

    TreeNode *h = new TreeNode(40);
    TreeNode *g = new TreeNode(400);

    TreeNode *d = new TreeNode(25, nullptr, h);
    TreeNode *e = new TreeNode(75);
    TreeNode *f = new TreeNode(350, nullptr, g);

    TreeNode *b = new TreeNode(50, d, e);
    TreeNode *c = new TreeNode(200, nullptr, f);

    return new TreeNode(100, b, c);
}

void depthView(TreeNode *tree)
{
    if(tree == nullptr ) return;
    stack<TreeNode *> stack;
    stack.push(tree);

    while( !stack.empty() )
    {
        TreeNode *curr = stack.top();
        stack.pop();

        cout << curr->value << " ";

        if( curr->right != nullptr )
            stack.push(curr->right);

        if( curr->left != nullptr)
            stack.push(curr->left);
    }

}

void depthViewRecursive(TreeNode *tree)
{
    if( tree == nullptr )
        return;

    cout << tree->value << " ";

    depthViewRecursive(tree->left);
    depthViewRecursive(tree->right);
}

void breadthFirst(TreeNode *tree)
{
    std::queue<TreeNode *> queues[2];

    queue<TreeNode*> *current_queue = &queues[0]; current_queue->push(tree);
    queue<TreeNode*> *next_queue = &queues[1];

    int depthLevel = 0;
    while( !current_queue->empty() )
    {
        TreeNode *curr = current_queue->front();
        current_queue->pop();

        if( curr->left != nullptr)
            next_queue->push(curr->left);

        if( curr->right != nullptr )
            next_queue->push(curr->right);

        cout << curr->value << " ";

        if( current_queue->empty() )
        {
            depthLevel++;
            current_queue = &queues[depthLevel % 2];
            next_queue = &queues[(depthLevel + 1) % 2];

            if( !current_queue->empty() )
            {
                cout << endl;
            }
        }
    }

}

std::vector<int> breadthFirstElements(TreeNode *tree)
{
    std::vector<int> output;
    std::queue<TreeNode *> queue;
    queue.push(tree);

    while( !queue.empty() )
    {
        TreeNode *curr = queue.front();
        queue.pop();

        if( curr->left != nullptr)
            queue.push(curr->left);

        if( curr->right != nullptr )
            queue.push(curr->right);

        output.push_back(curr->value);
    }
    return output;
}

bool findVal(TreeNode *tree, int val)
{
    if( tree == nullptr )
        return false;

    if(tree->value == val )
        return true;

    return findVal( tree->left, val ) || findVal( tree->right, val );
}

int treeSum(TreeNode *tree)
{
    if( tree == nullptr )
        return 0;

    return tree->value + treeSum(tree->left) + treeSum(tree->right);
}

int treeMinVal(TreeNode *tree)
{
    if( tree == nullptr )
        return INT32_MAX;

    int leftMin = treeMinVal(tree->left);
    int rightMin = treeMinVal(tree->right);

    return min(min(leftMin, rightMin), tree->value);
}

int maxPathSum(TreeNode *tree)
{
    if( tree == nullptr )
        return 0;

    int maxLeft = maxPathSum( tree->left );
    int maxRight = maxPathSum( tree->right );

    return tree->value + max(maxLeft, maxRight);
}

void inOrderTraversal(TreeNode *tree)
{
    if( tree->left != nullptr )
    {
        inOrderTraversal(tree->left);
    }

    cout << tree->value << " ";

    if( tree->right != nullptr )
    {
        inOrderTraversal(tree->right);
    }
}

void insertNode(TreeNode *tree, int nodeVal)
{
    if( tree == nullptr )
    {
        tree = new TreeNode(nodeVal, nullptr, nullptr);
        return;
    }

    if( nodeVal < tree->value )
    {
        if( tree->left != nullptr )
        {
            insertNode(tree->left, nodeVal);
        }
        else
        {
            tree->left = new TreeNode(nodeVal);
        }
    }
    else if(nodeVal > tree->value)
    {
        if( tree->right != nullptr )
        {
            insertNode(tree->right, nodeVal);
        }
        else
        {
            tree->right = new TreeNode(nodeVal);
        }
    }
}

void leftFace(TreeNode *tree, int level = 0)
{
    static int prevLevel = -1;
    if( tree == nullptr )
    {
        return;
    }

    if(level > prevLevel )
    {
        prevLevel = level;
        cout << tree->value << " ";
    }

    leftFace(tree->left, level + 1);
    leftFace(tree->right, level + 1);
}

void treeFrame(TreeNode *tree, int level = 0)
{
//    static int prevLevel = -1;
//    static
//    if( tree == nullptr )
//    {
//        return;
//    }
//
//    if(level > prevLevel )
//    {
//        prevLevel = level;
//        cout << tree->value << " ";
//    }
//
//    leftFace(tree->left, level + 1);
//    leftFace(tree->right, level + 1);
}


void printTree(TreeNode *tree)
{
    BinTree<int> t;
    for( int i: breadthFirstElements(tree) )
    {
        t.insert(i);
    }
    t.Dump();
    cout << "\n\n";
}

int main()
{
    TreeNode *tree = createTree();

    cout << "Depth first iterative: \n"; depthView(tree); cout << endl << endl;
    cout << "Depth first recursive: \n"; depthViewRecursive(tree); cout << endl << endl;
    cout << "Breadth first:\n"; breadthFirst(tree); cout << endl << endl;
    cout << "Find 75 inside tree: " << (findVal(tree, 75)?"true":"false") << endl << endl;
    cout << "Find 15 inside tree: " << (findVal(tree, 15)?"true":"false") << endl << endl;
    cout << "Tree sum: " << treeSum(tree) << endl << endl;
    cout << "Tree min val: " << treeMinVal(tree) << endl << endl;
    cout << "Max path sum: " << maxPathSum(tree) << endl << endl;
    cout << "In order traversal: "; inOrderTraversal(tree); cout << endl << endl;
    cout << "Add node 150 to the tree"; insertNode(tree, 150); cout << endl << endl;
    cout << "Add node 500 to the tree"; insertNode(tree, 500); cout << endl << endl;
    cout << "Add node 80 to the tree"; insertNode(tree, 80); cout << endl << endl;
    cout << "New tree: \n"; printTree(tree); cout << "\n";
    cout << "Binary tree left face: "; leftFace(tree); cout << endl << endl;
}

#pragma clang diagnostic pop