#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class LinkedList
{
public:
    struct Node
    {
        int val;
        Node *next = nullptr;
        Node *arbitrary_ptr = nullptr;
        explicit Node(int val, Node *next = nullptr): val(val), next(next) {}
    };

    static void printList( Node *head, bool printArbitraryPointer = false)
    {
        if( head == nullptr )
            return;

        cout << head->val;
        if(printArbitraryPointer && (head->arbitrary_ptr != nullptr))
            cout << "(" << head->arbitrary_ptr->val << ")";
        cout << " ";

        if( head->next != nullptr )
        {
            printList(head->next, printArbitraryPointer);
        }
    }

    static int SUM(Node *head, int s = 0)
    {
        s += head->val;
        if( head->next != nullptr )
        {
            return SUM(head->next, s);
        }
        return s;
    }

    static int NodeExists(Node *head, Node *target)
    {
        if( head == nullptr )
            return false;

        if( head->val == target->val )
            return true;

        return NodeExists(head->next, target);
    }

    static int GetVal(Node *head, int index)
    {
        if( head == nullptr )
            return -1;

        if( index == 0 )
            return head->val;

        return GetVal(head->next, index - 1);
    }

    static vector<int> VALS(Node *head)
    {
        if( head == nullptr)
            return {};

        vector<int> output;
        output.push_back(head->val);

        Node *curr = head;
        while( curr->next != nullptr )
        {
            curr = curr->next;
            output.push_back(curr->val);
        }
        return output;
    }

    static Node *Reverse(Node *head)
    {
        Node *prev = nullptr;
        Node *curr = head;

        while(curr != nullptr)
        {
            Node *next = curr->next;
            curr->next = prev;

            prev = curr;
            curr = next;
        }

        return prev;
    }

    static Node *ReverseRecursive(Node *head, Node *prev = nullptr)
    {
        if( head == nullptr)
            return prev;

        Node *next = head->next;
        head->next = prev;
        return ReverseRecursive(next, head);
    }

    static Node *Zip(Node *a, Node *b)
    {
        int counter = 0;
        Node *currA = a->next, *currB = b;
        Node *prev = a;

        while( currA != nullptr && currB != nullptr )
        {
            if(counter%2!=0)
            {
                prev->next = currA;
                prev = currA;
                currA = currA->next;
            }
            else
            {
                prev->next = currB;
                prev = currB;
                currB = currB->next;
            }

            counter++;
        }

        if( currA != nullptr)
            prev->next = currA;

        if( currB != nullptr )
            prev->next = currB;

        return a;
    }

    static Node *SumNodes(Node *a, Node *b)
    {
        int carry = 0;
        Node *currA = a, *currB = b;
        Node *tail = nullptr;
        Node *head = nullptr;

        while( currA != nullptr || currB != nullptr )
        {
            int val_A = currA != nullptr?currA->val:0;
            int val_B = currB != nullptr?currB->val:0;

            int s = (val_A + val_B + carry) % 10;
            carry = (val_A + val_B + carry) / 10;

            if( head == nullptr )
            {
                head = new Node(s);
                tail = head;
            }
            else
            {
                tail->next = new Node(s);
                tail = tail->next;
            }

            currA = currA!=nullptr?currA->next:nullptr;
            currB = currB!=nullptr?currB->next:nullptr;
        }

        if( carry > 0 )
            tail->next = new Node(carry);

        return head;
    }

    static Node *DeepCopy(Node *a)
    {
        if( a == nullptr )
            return nullptr;

        unordered_map<Node *, Node*> map;
        Node *head = nullptr, *tail = nullptr;
        Node *curr = a;

        while( curr != nullptr )
        {
            Node *newNode = new Node( curr->val );
            newNode->arbitrary_ptr = curr->arbitrary_ptr;

            if( head == nullptr )
            {
                head = newNode;
                tail = head;
            }
            else
            {
                tail->next = newNode;
                tail = tail->next;
            }

            map[curr] = newNode;
            curr = curr->next;
        }

        curr = head;
        while( curr != nullptr )
        {
            if( curr->arbitrary_ptr != nullptr )
            {
                curr->arbitrary_ptr = map[curr->arbitrary_ptr];
            }
            curr = curr->next;
        }

        return head;
    }

};

int main()
{
    LinkedList::Node z(9);
    LinkedList::Node y(8, &z);
    LinkedList::Node x(7, &y);
    LinkedList::Node v(6, &x);
    v.arbitrary_ptr = &y;
    x.arbitrary_ptr = &z;
    z.arbitrary_ptr = &x;

    LinkedList::Node f(5);
    LinkedList::Node e(4);
    LinkedList::Node d(3, &e);
    LinkedList::Node c(2, &d);
    LinkedList::Node b(1, &c);
    LinkedList::Node a(0, &b);

    std::cout << "Initial list: "; LinkedList::printList(&a); cout << endl;
    std::cout << "List sum: " << LinkedList::SUM(&a) << endl;
    std::cout << "Values converted to vector: ";
    vector<int> vect = LinkedList::VALS(&a);
    for( int tmp: vect )
        cout << tmp << " ";
    cout <<endl;
    std::cout << "Node with value d exists: " << (LinkedList::NodeExists(&a, &d)?"true":"false") << endl;
    std::cout << "Node with value f exists: " << (LinkedList::NodeExists(&a, &f)?"true":"false") << endl;
    std::cout << "Get val from index 2: " << LinkedList::GetVal(&a, 2) << endl;
    std::cout << "Get val from index 3: " << LinkedList::GetVal(&a, 3) << endl;
    std::cout << "Get val from index 0: " << LinkedList::GetVal(&a, 0) << endl;

//    LinkedList::Node *reversed = LinkedList::Reverse(&a);
//    cout << "Reversed list: "; LinkedList::printList(reversed); cout << endl;
//
//    LinkedList::Node *reversed2 = LinkedList::ReverseRecursive(reversed);
//    cout << "Reversed list recursively: "; LinkedList::printList(reversed2); cout << endl;
//
//    LinkedList::Node *zipped = LinkedList::Zip(reversed2, &x);
//    cout << "Zipped list a and list b: "; LinkedList::printList(zipped); cout << endl;

    cout << "a =  "; LinkedList::printList(&a); cout << endl;
    cout << "x =  "; LinkedList::printList(&x); cout << endl;
    LinkedList::Node *sum = LinkedList::SumNodes(&a, &x);
    cout << "a + x = "; LinkedList::printList(sum); cout << endl;

    cout << "Deep copy list: "; LinkedList::printList(&v, true); cout <<endl;
    LinkedList::Node *v_copy = LinkedList::DeepCopy(&v);
    cout << "sum deep copy : "; LinkedList::printList(v_copy, true); cout << endl;

    return 0;
}
