//============================================================================
// Name        : SortAndPrintCourses.cpp
// Author      : Kevin Fleming
// Version     : 1.0
// Description : Project Two
//============================================================================

// InOrderTraversal and SortAndPrintCourses handle sorting and printing a list
// of courses in alphanumeric order

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // For std::transform
#include <cctype>    // For std::toupper

using namespace std;
using std::cout;

// Structure to hold course data
struct Course {
    string number;
    string title;
    vector<string> prerequisites;

    Course(string courseNumber, string courseTitle, vector<string> coursePrerequisites)
        : number(courseNumber), title(courseTitle), prerequisites(coursePrerequisites) {}
};

// Node structure for the binary search tree
struct Node {
    Course course;
    Node *left;
    Node *right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Function to insert a course into the binary search tree
void InsertCourse(Node*& tree, const Course& course) {
    if (tree == nullptr) {
        tree = new Node(course); // Allocate a new node if the tree is empty
    } else if (course.number < tree->course.number) {
        InsertCourse(tree->left, course); // Recursively insert into the left subtree
    } else if (course.number > tree->course.number) {
        InsertCourse(tree->right, course); // Recursively insert into the right subtree
    } else {
        // Course already exists in the tree, so do nothing
        return;
    }
}

// Function to sanitize a string by removing carriage returns and other control characters
void SanitizeString(string& str) {
    str.erase(remove_if(str.begin(), str.end(), [](char c) {
        return c == '\r' || c == '\n' || c == '\t';
    }), str.end());
}

// Function to search for a course by course number in the binary search tree
void SearchCourse(Node*& tree, const string& courseNumber) {
    // Alert the user if a course entered isn't found
    if (!tree) {
        cout << "Course not found." << endl;
        return;
    }

    // Handle case-insensitivity
    string upperCourseNumber = courseNumber;
    std::transform(upperCourseNumber.begin(), upperCourseNumber.end(), upperCourseNumber.begin(), ::toupper);

    // If a course is found, output its information
    if (upperCourseNumber == tree->course.number) {
        cout << tree->course.number << ", " << tree->course.title << endl;

        string prerequisitesLabel = "Prerequisites: ";
        cout << prerequisitesLabel;

        for (auto& prereq : tree->course.prerequisites) {
            SanitizeString(prereq);  // Sanitize each prerequisite to remove any '\r'
            cout << prereq << " ";
        }

        cout << endl;  // Ensure the cursor moves to a new line after the prerequisites
    } else if (upperCourseNumber < tree->course.number) { // Otherwise...
        SearchCourse(tree->left, courseNumber); // Recursively search the left subtree
    } else {
        SearchCourse(tree->right, courseNumber); // Recursively search the right subtree
    }
}

// Function to perform in-order traversal and print course information
void InOrderTraversal(Node*& tree) {
    if (tree) {
        InOrderTraversal(tree->left); // Recursively traverse the left subtree

        // Ouput course information
        cout << tree->course.number << ", " << tree->course.title << endl;
        
        InOrderTraversal(tree->right); // Recursively traverse the right subtree
    }
}

// Function to sort and print courses in alphanumeric order
void SortAndPrintCourses(Node*& tree) {
    cout << "Here is a sample schedule:\n" << endl;

    InOrderTraversal(tree);
}

// Function to handle Windows-style line endings
void TrimString(string& str) {
    // Remove trailing whitespace (including carriage return)
    str.erase(str.find_last_not_of(" \r\n\t") + 1);
}

// Function to load course data from a file
bool LoadCourseDataFromFile(const string& fileName, Node*& courseBinaryTree) {
    ifstream file(fileName);
    
    // Handle when there is an issue opening the specified file
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return false; // Indicate failure to load course data
    }

    vector<string> courseNumbers;
    string line;

    // First, collect all course numbers and validate line format
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        
        // Consume the remaining line data, representing prerequisites
        vector<string> prerequisites;
        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        // Handle incomplete course information
        if (courseNumber.empty() || courseTitle.empty()) {
            cout << "Error: Line doesn't contain enough information." << endl;
            continue;
        }

        courseNumbers.push_back(courseNumber);

        Course course(courseNumber, courseTitle, prerequisites);
        InsertCourse(courseBinaryTree, course);
    }

    // Rewind the file to the beginning for the second pass
    file.clear();  // Clear any errors
    file.seekg(0, ios::beg);

    // Next, populate binary tree with courses
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        
        // Consume the remaining line data, representing prerequisites
        vector<string> prerequisites;
        while (getline(ss, prereq, ',')) {
            TrimString(prereq);

            // Check if each prerequisite exists in the courseNumbers list
            if (!prereq.empty() && find(courseNumbers.begin(), courseNumbers.end(), prereq) != courseNumbers.end()) {
                prerequisites.push_back(prereq);
            } else if (!prereq.empty()) {
                cout << "Warning: Prerequisite '" << prereq 
                     << "' for course '" << courseNumber 
                     << "' does not exist and will be ignored." << endl;
            }
        }

        Course course(courseNumber, courseTitle, prerequisites);
        InsertCourse(courseBinaryTree, course);
    }

    if (courseNumbers.empty()) {
        cout << "No courses were found in the file." << endl;
        return false; // Return false if no courses were found
    } else {
        cout << "File loaded successfully." << endl;
        return true; // Return true indicating success
    }

    file.close();
}

// Function to display the main menu
int DisplayMenu() {
    cout << "\n    1: Load Data Structure.\n"
         << "    2: Print Course List.\n"
         << "    3: Print Course.\n"
         << "    9: Exit\n\n"
         << "What would you like to do? ";
    
    int choice;
    cin >> choice;
    
    return choice;
}

// Main function
int main() {
    int choice;
    bool isCourseDataLoaded = false;
    Node* courseBinaryTree = nullptr;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        choice = DisplayMenu();

        if (choice == 1) {
            string fileName;

            // Get the file that the user would like to load
            cout << "Enter the filename to load: ";
            cin >> fileName;

            isCourseDataLoaded = LoadCourseDataFromFile(fileName, courseBinaryTree);
        } else if (choice == 2) {
            // Handle unloaded courses
            if (!isCourseDataLoaded) {
                cout << "Error: Course data isn't loaded." << endl;
            } else {
                SortAndPrintCourses(courseBinaryTree);
            }
        } else if (choice == 3) {
            // Handle unloaded courses
            if (!isCourseDataLoaded) {
                cout << "Error: Course data isn't loaded." << endl;
            } else {
                string courseNumber;

                // Get the course number that the user would like to search for
                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                SearchCourse(courseBinaryTree, courseNumber);
            }
        } else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        } else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
