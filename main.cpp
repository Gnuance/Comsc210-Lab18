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
#include <string>
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
    void setName(string);
    string getName();
    void setYearReleased(int);
    int getYearReleased();
    void addReview(double, string, int);
    string getReview(int);   // Returns a review at given index
    void deleteReview(int);  // Deletes Movie review at given index
    void deleteAllReviews(); // Loops through all Movie reviews and deletes
    int getNumReviews();
    bool isReview(int);       // Checks if review at given index is valid
    string reviewsToString(); // Returns string containing given number of reviews, 0 for all
    ~Movie();                 // Deletes object, as well as all associated Movie reviews
};

int main()
{
    string userInput = "";
    string reviewRating = "";
    string reviewComment = "";
    Movie movie0 = Movie("Chinatown", 1974);
    int headOrTail = 0;

    // Phew, now that the object structure is in place, let's start working on the console ui
    // Get user input for program, either 0 or 1 for how to add new reviews to linked list
    cout << "Which linked list method should we use?" << endl;
    cout << "\t[0] Nodes added to the head." << endl;
    cout << "\t[1] Nodes added to the tail." << endl;
    cout << "\tChoice: ";
    getline(cin, userInput);
    while (stoi(userInput) != 0 || stoi(userInput) != 1)
    {
        cout << "Invalid option. Please enter 0 or 1: ";
        getline(cin, userInput);
    }
    headOrTail = stoi(userInput); // Set value of head or tail insertion

    // Now that we have a valid option, prompt for review ratings
    do
    {
        // Get review rating from user
        cout << "Enter review rating 0-5: ";
        getline(cin, reviewRating);
        while (stod(reviewRating) < 0 || stod(reviewRating) > 5)
        {
            cout << "Invalid option. Please enter a rating betwee 0 and 5: ";
            getline(cin, reviewRating);
        }
        // Get review comment
        cout << "Enter review comments: ";
        getline(cin, reviewComment);

        // We have rating and comment, now add to Movie object review
        movie0.addReview(stod(reviewRating), reviewComment, headOrTail);

        // Ask if user wanna do it again
        cout << "Add another review (y/n): ";
        getline(cin, userInput);
    } while (userInput == "y" || userInput == "yes" || userInput == "Y");

    // Ouput all reviews to console
    cout << "All movie reviews for movie: " << movie0.getName() << " (" << movie0.getYearReleased() << "):" << endl;
    cout << movie0.reviewsToString() << endl;

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
void Movie::addReview(double movRating, string movComment, int headOrTail)
{
    // Create new object to add to reviews
    review *r = new review;
    r->rating = movRating;
    r->comment = movComment;
    // If head and tail are null, initialize list
    if (!head && !tail)
    {
        head = tail = r;
        tail->next = nullptr;
    }
    else if (headOrTail == 0) // Place new node at head
    {
        r->next = head->next;
        head = r;
    }
    else if (headOrTail == 1) // Place new node at tail
    {
        tail->next = r;
        tail = r;
        tail->next = nullptr;
    }
    else
    {
        // Return without performing any operation if no condition matches
        delete r;
        return;
    }
    reviewCount++;
}
// Returns a review at given index
string Movie::getReview(int index)
{
    string output = "";

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
        string(to_string(current->rating) + ": " + current->comment);

    return output;
}
// Deletes Movie review at given index
void Movie::deleteReview(int index)
{
    // Make sure index is valid
    if (!isReview(index))
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
        head = head->next;
        delete current;
        current = head;
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

// Returns string containing given number of reviews, 0 for all
string Movie::reviewsToString()
{
    // Loop through all reviews and return string
    string output = "";
    for (size_t i = 0; i < reviewCount; i++)
    {
        output += getReview(i) + "\n";
    }
    return output;
}

// Make sure to clean up all movie reviews from heap before object destruction
Movie::~Movie()
{
    deleteAllReviews();
}