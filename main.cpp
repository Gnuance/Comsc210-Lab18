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
        string comment;
        review *next;
    };
    review *head;
    review *tail;
    int reviewCount;

public:
    Movie();
    Movie(string, int);
    void setName(string n);
    string getName();
    void setYearReleased(int yr);
    int getYearReleased();
    void addReview(review, string);
    string getReview(int);   // Returns a review at given index
    void deleteReview(int);  // Deletes Movie review at given index
    void deleteAllReviews(); // Loops through all Movie reviews and deletes
    int getNumReviews();
    bool isReview(int);          // Checks if review at given index is valid
    string reviewsToString(int); // Returns string containing given number of reviews, 0 for all
    ~Movie();                    // Deletes object, as well as all associated Movie reviews
};

// Function declarations
// void createRandomList(Node *&, const int);
// void deleteNodeByIndex(Node *&, const int);
// void insertNodeAfterIndex(Node *&, const int);
// void deleteList(Node *&);
// void output(Node *);              // Outputs entire list to console
// bool validNodeIndex(Node *, int); // Tests whether a user given index is valid or out of bounds. In this case, [1,size of list)
// int getLinkedListSize(Node *);    // Returns the size of a linked list

int main()
{
    // Node *head = nullptr;
    // const int SIZE = 7; // Changed from global variable to a local variable in main
    // int entry;          // To collect user input

    // // Create a rand() generated linked list of size SIZE with random numbers 0-99
    // createRandomList(head, SIZE);
    // cout << "Initial linked list:" << endl;
    // output(head);

    // // Get user input asking which node to delete, validate, delete
    // cout << "Which node to delete? " << endl;
    // output(head);
    // cout << "Choice --> ";
    // cin >> entry;
    // while (!validNodeIndex(head, entry)) // Validate user entry
    // {
    //     cout << "Please enter a valid index. Choice --> ";
    //     cin >> entry;
    // }
    // // Delete selected node and output modified list
    // deleteNodeByIndex(head, entry);
    // cout << "Resulting list after node deletion:" << endl;
    // output(head);

    // // Insert a node after validating entry
    // cout << "After which node to insert 10000? " << endl;
    // output(head);
    // cout << "Choice --> ";
    // cin >> entry;
    // while (!validNodeIndex(head, entry)) // Validate user entry
    // {
    //     cout << "Please enter a valid index. Choice --> ";
    //     cin >> entry;
    // }
    // // Insert node based on user given index, and output modified list
    // insertNodeAfterIndex(head, entry);
    // cout << "Resulting list after insert:" << endl;
    // output(head);

    // // Delete the entire linked list and output
    // deleteList(head);
    // cout << "Resulting list after deletion:" << endl;
    // output(head);

    return 0;
}

// Movie CLASS DEFINITIONS
Movie::Movie()
    : reviewCount(0), head(nullptr), tail(nullptr)
{
}

Movie::Movie(string n, int yrReleased)
    : reviewCount(0), head(nullptr), tail(nullptr)
{
    setName(n);
    setYearReleased(yrReleased);
}
void Movie::setName(string n)
{
    name = n;
}
string Movie::getName()
{
    return name;
}
void Movie::setYearReleased(int yr)
{
    if (yr < 1887)
        throw invalid_argument("Must be a valid year >= 1888 (the first movie).");
    yearReleased = yr;
}
int Movie::getYearReleased()
{
    return yearReleased;
}
void Movie::addReview(review r, string headOrTail)
{
    // If head and tail are null, initialize list
    if (!head && !tail)
    {
        head = tail = &r;
        tail->next = nullptr;
    }
    else if (headOrTail == "head") // Place new node at head
    {
        r.next = head->next;
        head = &r;
    }
    else if (headOrTail == "tail") // Place new node at tail
    {
        tail->next = &r;
        tail = &r;
        tail->next = nullptr;
    }
    else
    {
        return; // Return without performing any operation if no condition matches
    }
    reviewCount++;
}
// Returns a review at given index
string Movie::getReview(int index)
{
    // Check to make sure index in in range
    if (!isReview(index))
        throw invalid_argument("Review not found at index: " + index);

    // Set current pointer equal to review object
    review *current = head;
    for (size_t i = 0; i <= index && current; i++)
    {
        current->next;
    }

    // Check to make sure current object is valid
    if (current)
        return string(to_string(current->rating) + ": " + current->comment);
}
// Deletes Movie review at given index
void Movie::deleteReview(int index)
{
    // Make sure index is valid
    if (!isReview)
        throw invalid_argument("No reviews exist for this movie.");

    // Now that index is valid find review, reroute next pointer, and delete
    // Set current pointer = to review to be deleted
    review *current = head;
    review *prev = head;
    for (size_t i = 0; i < index; i++)
    {
        if (i == 0)
        {
            current = current->next;
        }
        else
        {
            current = current->next;
            prev = prev->next;
        }
    }
    // If current is head, point head to next element and delete current
    // If current is tail, point tail to prev element and delete current
    // Else, point prev = current->next, and delete current
    if (current == head)
    {
        head = head->next;
        delete current;
    }
    else if (current == tail)
    {
        tail = prev;
        delete current;
        tail->next = nullptr;
    }
    else
    {
        prev->next = current->next;
        delete current;
    }
}

// Loops through all Movie reviews and deletes
void Movie::deleteAllReviews()
{
    // Set current = head and continue looping and deleting until current == nullptr
    review *current = head;
    while (current)
    {
        
    }    
}
int Movie::getNumReviews()
{
    return reviewCount;
}
// Checks if review at given index is valid
bool Movie::isReview(int index)
{
    if (index >= 0 && reviewCount > 0 && index <= reviewCount)
        return true;
    return false;
}

string Movie::reviewsToString(int); // Returns string containing given number of reviews, 0 for all
Movie::~Movie()
{
}

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