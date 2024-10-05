/*  Lab 18: Movie reviews with linked list to hold review items
    IDE: Vscode

    Design Decisions:
    1. I'm starting with code from Lab 17 and modifying to fit this lab.
    2. Going to create a class for movie to hold the movie object to make the code more maintainable overall.
    3. For adding to head or tail, it could be implemented as separate functions or one function with an if statement.
        Not sure which is better overall.
    4. Seems straightforward overall.
*/

#include <iostream>
using namespace std;

// Movie object file declaration to hold info on movie and list of reviews
class Movie
{
private:
    string name;
    int yearReleased;
    // Linked list struct to hold Movie reviews
    struct review
    {
        double rating;
        string comments;
        review *next;
    };
    review* head;
    review* tail;
    int reviewCount = 0;

public:
    Movie();
    Movie(int, int);
    void setName(string n);
    string getName();
    void setYearReleased(string yr);
    int getYearReleased();
    void addReview(string headOrTail);
    void deleteReviewByIndex(int); // Deletes Movie review at given index
    void deleteAllReviews(); // Loops through all Movie reviews and deletes
    int getNumReviews();
    string reviewsToString(int); // Returns string containing given number of reviews, 0 for all
    ~Movie(); // Deletes object, as well as all associated Movie reviews
};

// Function declarations
void createRandomList(Node *&, const int);
void deleteNodeByIndex(Node *&, const int);
void insertNodeAfterIndex(Node *&, const int);
void deleteList(Node *&);
void output(Node *);              // Outputs entire list to console
bool validNodeIndex(Node *, int); // Tests whether a user given index is valid or out of bounds. In this case, [1,size of list)
int getLinkedListSize(Node *);    // Returns the size of a linked list

int main()
{
    Node *head = nullptr;
    const int SIZE = 7; // Changed from global variable to a local variable in main
    int entry;          // To collect user input

    // Create a rand() generated linked list of size SIZE with random numbers 0-99
    createRandomList(head, SIZE);
    cout << "Initial linked list:" << endl;
    output(head);

    // Get user input asking which node to delete, validate, delete
    cout << "Which node to delete? " << endl;
    output(head);
    cout << "Choice --> ";
    cin >> entry;
    while (!validNodeIndex(head, entry)) // Validate user entry
    {
        cout << "Please enter a valid index. Choice --> ";
        cin >> entry;
    }
    // Delete selected node and output modified list
    deleteNodeByIndex(head, entry);
    cout << "Resulting list after node deletion:" << endl;
    output(head);

    // Insert a node after validating entry
    cout << "After which node to insert 10000? " << endl;
    output(head);
    cout << "Choice --> ";
    cin >> entry;
    while (!validNodeIndex(head, entry)) // Validate user entry
    {
        cout << "Please enter a valid index. Choice --> ";
        cin >> entry;
    }
    // Insert node based on user given index, and output modified list
    insertNodeAfterIndex(head, entry);
    cout << "Resulting list after insert:" << endl;
    output(head);

    // Delete the entire linked list and output
    deleteList(head);
    cout << "Resulting list after deletion:" << endl;
    output(head);

    return 0;
}

// Movie object definitions
Movie::Movie()
{
}

Movie::~Movie()
{
}

Movie::Movie(int, int);
    void setName(string n);
    string getName();
    void setYearReleased(string yr);
    int getYearReleased();
    void addReview(string headOrTail);
    void deleteReviewByIndex(int); // Deletes Movie review at given index
    void deleteAllReviews(); // Loops through all Movie reviews and deletes
    int getNumReviews();
    string reviewsToString(int); // Returns string containing given number of reviews, 0 for all

// Creates a linked list of size SIZE with random integers
void createRandomList(Node *&head, const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        int tmp_val = rand() % 100;
        Node *newVal = new Node;

        // adds node at head
        if (!head)
        { // if this is the first node, it's the new head
            head = newVal;
            newVal->next = nullptr;
            newVal->value = tmp_val;
        }
        else
        { // its a second or subsequent node; place at the head
            newVal->next = head;
            newVal->value = tmp_val;
            head = newVal;
        }
    }
}

// Deletes a node based on it's index in the linked list
void deleteNodeByIndex(Node *&head, const int index)
{
    Node *current = head;
    Node *prev = head;
    for (int i = 0; i < (index - 1); i++)
        if (i == 0)
            current = current->next;
        else
        {
            current = current->next;
            prev = prev->next;
        }
    // Added logic: if the first element was selected for deletion, we need to replace head with the next element in the list
    if (current && current == head)
    {
        head = head->next;
    }
    // at this point, delete current and reroute pointers
    if (current)
    { // checks for current to be valid before deleting the node
        prev->next = current->next;
        delete current;
        current = nullptr;
    }
}

void insertNodeAfterIndex(Node *&head, const int index)
{
    Node *current = head;
    Node *prev = head;
    for (int i = 0; i < (index); i++)
    {
        if (i == 0)
            current = current->next;
        else
        {
            current = current->next;
            prev = prev->next;
        }
    }
    // at this point, insert a node between prev and current
    if (current != head)
    {
        Node *newnode = new Node;
        newnode->value = 10000;
        newnode->next = current;
        prev->next = newnode;
    }
}

// Deletes an entire linked list node by node starting at head
void deleteList(Node *&head)
{
    Node *current = head;
    while (current)
    {
        head = current->next;
        delete current;
        current = head;
    }
    head = nullptr;
}

// Outputs linked list starting at head element
void output(Node *hd)
{
    if (!hd)
    {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    Node *current = hd;
    while (current)
    {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

// Returns whether a given node index is valid
bool validNodeIndex(Node *head, int userInput)
{
    return userInput > 0 && userInput <= getLinkedListSize(head);
}

// Returns size of a given linked list
int getLinkedListSize(Node *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}