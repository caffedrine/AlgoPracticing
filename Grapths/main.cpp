#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
class Graph
{
public:
    class Node
    {
    public:
        explicit Node(T key): id(key){}
        T id;
        list<Node *> Neighbours;
    };

    list<Node *> Nodes;

    Graph()= default;;
    ~Graph() = default;;

    void AddNode(Node *node)
    {
        this->Nodes.push_back(node);
    }

    void print()
    {
        for(Node *node: this->Nodes)
        {
            cout << node->id << " --> ";
            for(Node *it: node->Neighbours)
            {
                cout << it->id << " ";
            }
            cout << endl;
        }
    }

    void depthFirstPrint(Node *root, unordered_set<T> VisitedNodes = {})
    {
        cout << root->id << " ";
        VisitedNodes.insert(root->id);

        for( Node *neighbour: root->Neighbours )
        {
            if( VisitedNodes.find(neighbour->id) == VisitedNodes.end() )
            {
                depthFirstPrint(neighbour, VisitedNodes);
            }
        }
    }

    void breadthFirstPrint(Node *root)
    {
        unordered_set<T> VisitedNodes = {};
        queue<Node *> queue;
        queue.push(root);
        VisitedNodes.insert(root->id);

        while( !queue.empty() )
        {
            Node *curr = queue.front();
            queue.pop();

            cout << curr->id << " ";
            VisitedNodes.insert(curr->id);

            for(Node *neighbour: curr->Neighbours)
                if(VisitedNodes.find(neighbour->id) == VisitedNodes.end())
                {
                    queue.push(neighbour);
                }
        }
    }

    bool hasPath(Node *src, Node *dst, unordered_set<T> VisitedNodes = {})
    {
        if( src->id == dst->id )
            return true;

        VisitedNodes.insert(src->id);

        for( Node *neighbour: src->Neighbours )
        {
            if(VisitedNodes.find(neighbour->id) == VisitedNodes.end())
            {
                if(hasPath(neighbour, dst, VisitedNodes))
                    return true;
            }
        }

        return false;

    }

    int countDisconnectedGraphs()
    {
        unordered_set<T> VisitedNodes = {};
        int result = 0;

        for( Node *node: this->Nodes )
        {
            // Skip nodes that were already discovered
            if( VisitedNodes.find(node->id) != VisitedNodes.end() )
                continue;

            result++;

            queue<Node *> queue;
            queue.push(node);

            while( !queue.empty() )
            {
                Node *curr = queue.front();
                queue.pop();

                VisitedNodes.insert(curr->id);

                for(Node *neighbour: curr->Neighbours)
                    if(VisitedNodes.find(neighbour->id) == VisitedNodes.end())
                    {
                        queue.push(neighbour);
                    }
            }
        }

        return result;
    }

    int largestDisconnectedGraphs(unordered_set<T> VisitedNodes = {})
    {
        int max_count = 0;

        for( Node *node: this->Nodes )
        {
            // Skip nodes that were already discovered
            if( VisitedNodes.find(node->id) != VisitedNodes.end() )
                continue;

            queue<Node *> queue;
            queue.push(node);
            int curr_count = 0;
            while( !queue.empty() )
            {
                Node *curr = queue.front();
                queue.pop();

                VisitedNodes.insert(curr->id);
                curr_count++;

                for(Node *neighbour: curr->Neighbours)
                    if(VisitedNodes.find(neighbour->id) == VisitedNodes.end())
                    {
                        queue.push(neighbour);
                    }
            }
            max_count = std::max(max_count, curr_count);
        }

        return max_count;
    }

    int shortestPath(Node *src, Node *dst)
    {
        if( src->id == dst->id )
            return 0;

        unordered_map<T, int> distanceToSrc = {};
        queue<Node *> queue;

        // Init queue with first node and init distance to 0
        queue.push(src);
        distanceToSrc[src->id] = 0;

        while( !queue.empty() )
        {
            Node *curr = queue.front();
            queue.pop();

            for( Node *neighbour: curr->Neighbours )
            {
                // One of the neighbours is the destination?
                if( neighbour->id == dst->id )
                {
                    return distanceToSrc.at(curr->id) + 1;
                }

                // Only add neighbours that were not visited already
                if( distanceToSrc.find(neighbour->id) == distanceToSrc.end() )
                {
                    distanceToSrc[neighbour->id] = distanceToSrc.at(curr->id) + 1;
                    queue.push(neighbour);
                }
            }
        }

        return -1;

    }

    int longestPath(Node *src, Node *dst)
    {
        unordered_set<T> VisitedNodes = {};
        queue<Node *> queue;
        queue.push(src);

        int distance = -1;

        while( !queue.empty() )
        {
            Node *curr = queue.front();
            queue.pop();

            if( VisitedNodes.find(curr->id) != VisitedNodes.end() )
                continue;
            VisitedNodes.insert(curr->id);

            // Is current node the destination?
            if( curr->id == dst->id )
                break;

            distance++;

            for( Node *neighbour: curr->Neighbours )
            {
                queue.push(neighbour);
            }
        }

        return distance;

    }
};

bool IsValidIslandNode(vector<vector<int>> &matrix, int row, int col, int size_rows, int size_cols)
{
    if( row < 0 || row >= size_rows || col < 0 || col >= size_cols || matrix[row][col] != 1 )
        return false;
    return true;
}

int exploreIsland(vector<vector<int>> &matrix, int ROW, int COL, vector<vector<bool>> &visited, int size_rows, int size_cols)
{
    int count = 0;
    queue<pair<int, int>> queue;
    queue.push({ROW, COL});

    while( !queue.empty() )
    {
        pair<int, int> curr = queue.front();
        queue.pop();
        int curr_row = curr.first;
        int curr_col = curr.second;

        if( visited[curr_row][curr_col] )
            continue;

        count++;
        visited[curr_row][curr_col] = true;

        // Explore upper element
        if( IsValidIslandNode(matrix, curr_row - 1, curr_col, size_rows, size_cols))
        {
            queue.push({curr_row - 1, curr_col});
        }

        // explore below element
        if(IsValidIslandNode(matrix, curr_row + 1, curr_col, size_rows, size_cols))
        {
            queue.push({curr_row + 1, curr_col});
        }

        // Explore left element
        if(IsValidIslandNode(matrix, curr_row, curr_col - 1, size_rows, size_cols))
        {
            queue.push({curr_row, curr_col - 1});
        }

        // explore right element
        if(IsValidIslandNode(matrix, curr_row, curr_col + 1, size_rows, size_cols))
        {
            queue.push({curr_row, curr_col + 1});
        }
    }
    return count;
}

pair<int, int> islandsCount(vector<vector<int>> &matrix)
{
    int islands = 0;
    int biggestIsland = 0;

    int ROWS = (int)matrix.size();
    int COLS = (int)matrix[0].size();

    // Make a matrix copy
    vector<vector<bool>> visited_nodes(ROWS, vector<bool>(COLS, false));

    for( int i = 0; i < ROWS; i++ )
    {
        for( int  j = 0; j < COLS; j++ )
        {
            if( !visited_nodes[i][j] && matrix[i][j] == 1)
            {
                islands++;
                biggestIsland = max(biggestIsland, exploreIsland(matrix, i, j, visited_nodes, ROWS, COLS));
            }
        }
    }

    return pair<int, int>(islands, biggestIsland);
}

Graph<unsigned char>::Node *DeepCopyImpl(Graph<unsigned char>::Node *root, unordered_map<Graph<unsigned char>::Node *, Graph<unsigned char>::Node *> &NodesCompleted)
{
    if( root == nullptr )
        return nullptr;

    auto *copy = new Graph<unsigned char>::Node(root->id);
    NodesCompleted[root] = copy;

    for(Graph<unsigned char>::Node *neighbour: root->Neighbours)
    {
        if( NodesCompleted.find(neighbour) == NodesCompleted.end()  )
        {
            DeepCopyImpl(neighbour, NodesCompleted);
        }

        copy->Neighbours.push_back( NodesCompleted.find(neighbour)->second );
    }

    return copy;
}

Graph<unsigned char>::Node *DeepCopy(Graph<unsigned char>::Node *root)
{
    unordered_map<Graph<unsigned char>::Node *, Graph<unsigned char>::Node *> NodesCompleted = {};
    return DeepCopyImpl(root, NodesCompleted);
}

void printGraph(Graph<unsigned char>::Node *root)
{
    if( root == nullptr ) return;

    unordered_set<unsigned char> VisitedNodes = {};
    queue<Graph<unsigned char>::Node *> queue;

    queue.push(root);
    VisitedNodes.insert(root->id);

    while( !queue.empty() )
    {
        Graph<unsigned char>::Node *curr = queue.front();
        queue.pop();

        VisitedNodes.insert(curr->id);

        cout << curr->id << " --> ";
        for(Graph<unsigned char>::Node *neighbour: curr->Neighbours)
        {
            cout << neighbour->id << " ";
            if(VisitedNodes.find(neighbour->id) == VisitedNodes.end())
            {
                queue.push(neighbour);
            }
        }
        cout << "\n";
    }
}

int main()
{
    // Create nodes
    Graph<unsigned char>::Node a('a');
    Graph<unsigned char>::Node b('b');
    Graph<unsigned char>::Node c('c');
    Graph<unsigned char>::Node d('d');
    Graph<unsigned char>::Node e('e');
    Graph<unsigned char>::Node f('f');
    Graph<unsigned char>::Node g('g');
    Graph<unsigned char>::Node h('h');
    Graph<unsigned char>::Node i('i');
    Graph<unsigned char>::Node j('j');

    // Create edges
    a.Neighbours = {&b, &c};
    b.Neighbours = {&d, &g};
    c.Neighbours = {&e};
    d.Neighbours = {&f};
    e.Neighbours = {&b};
    f.Neighbours = {};
    g.Neighbours = {&b, &d};
    h.Neighbours = {&i};
    i.Neighbours = {&h};
    j.Neighbours = {};

    Graph<unsigned char> graph;
    graph.AddNode(&a);
    graph.AddNode(&b);
    graph.AddNode(&c);
    graph.AddNode(&d);
    graph.AddNode(&e);
    graph.AddNode(&f);
    graph.AddNode(&g);
    graph.AddNode(&h);
    graph.AddNode(&i);
    graph.AddNode(&j);

    cout << "Input graph: \n"; graph.print(); cout << endl;

    Graph<unsigned char>::Node *graph2 = DeepCopy(&a);
    cout << "Deep copy: \n"; printGraph(graph2); cout << endl;

    cout << "Depth first print from a: "; graph.depthFirstPrint(&a); cout << endl << endl;

    cout << "Breadth first print from a: "; graph.breadthFirstPrint(&a); cout << endl << endl;

    cout << "Breadth first print from h: "; graph.breadthFirstPrint(&h); cout << endl << endl;

    cout << "Is path from a to g: " << (graph.hasPath(&a, &g)?"true":"false") << endl << endl;

    cout << "Is path from f to a: " << (graph.hasPath(&f, &a)?"true":"false") << endl << endl;

    cout << "Disconnected graphs count: " << graph.countDisconnectedGraphs() << endl << endl;

    cout << "Largest components nodes count: " << graph.largestDisconnectedGraphs() << endl << endl;

    cout << "shortest path from a to b: " << graph.shortestPath(&a, &b) << endl << endl;

    cout << "shortest path from a to d: " << graph.shortestPath(&a, &d) << endl << endl;

    cout << "shortest path from g to f: " << graph.shortestPath(&g, &f) << endl << endl;

    cout << "shortest path from e to f: " << graph.shortestPath(&e, &f) << endl << endl;

    cout << "shortest path from e to e: " << graph.shortestPath(&e, &e) << endl << endl;

    cout << "shortest path from a to h: " << graph.shortestPath(&a, &h) << endl << endl;

    vector<vector<int>> island_matrix = {
            {0, 1, 0, 0, 1, 0},
            {1, 1, 0, 0, 1, 0},
            {0, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0},
            {0, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0}};

    cout << "island count: " << islandsCount(island_matrix).first << ", biggest have " << islandsCount(island_matrix).second << endl << endl;
}
