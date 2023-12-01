#include <bits/stdc++.h>
#include <string.h>
#include <iomanip>
using namespace std;


// Global IO Variables
const char separator = ' ';
const int nameWidth = 7;
const int numWidth = 4;


// Course Class 
class Course
{
public:
    string name;
    vector<string> prof;
    double remaining;
    bool assignedstatus;
    bool partialAssignedstatus;
    Course(string name)
    {
        this->name = name;
        this->prof.clear();
        this->remaining = 1;
        this->assignedstatus = false;
        this->partialAssignedstatus = false;
    }
    void addProf(string prof)
    {
        this->prof.push_back(prof);
    }
};


// Professor Class
class Prof
{
public:
    int id;
    string name;
    double category;
    vector<string> courses;
    vector<string> pref;
    double remaining;
    bool assignedstatus;
    bool partialAssignedstatus;
    Prof(string name, double category, vector<string> pref)
    {
        this->name = name;
        this->category = category;
        this->courses.clear();
        this->pref = pref;
        this->remaining = category;
        this->assignedstatus = false;
        this->partialAssignedstatus = false;
    }
    void addCourse(string course)
    {
        this->courses.push_back(course);
    }
    void getCompleteProf()
    {
        cout << left << setw(nameWidth - 3) << setfill(separator) << this->name;
        cout << " | ";
        cout << "Category: ";
        cout << left << setw(numWidth) << setfill(separator) << this->category;
        cout << " | ";
        cout << "Courses: ";
        for (int i = 0; i < this->courses.size(); i++)
        {
            cout << left << setw(nameWidth) << setfill(separator) << this->courses[i] << " ";
        }
        cout << endl;
    }
};


// Global Variables
int numCourses;
int numProfs;
vector<Course> courses;
vector<Prof> profs;
int assignNo = 1;
int prefListSize;
vector<vector<Prof>> Solutions;


// Print Function
void printAssignment(vector<Prof> profs)
{
    cout << "Assignment: " << assignNo << endl;
    for (int i = 0; i < profs.size(); i++)
    {
        profs[i].getCompleteProf();
    }
    assignNo++;
    cout << "-----------------------------------------------\n"
         << endl;
}


// Helper Function
int getProfPos(string name)
{
    for (int i = 0; i < profs.size(); i++)
    {
        if (profs[i].name == name)
        {
            return i;
        }
    }
    cout << "No Prof Found" << endl;
}


// Helper Function
int getCoursePos(string name)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i].name == name)
        {
            return i;
        }
    }
    cout << "No Course Found" << endl;
}


// Helper Function
bool checkAllProfAssigned(vector<Prof> profs){
    for(int i=0; i<profs.size(); i++){
        if(profs[i].remaining > 0){
            return false;
        }
    }
    return true;
}


// Helper Function
void printAllAssignments(){
    for(int i=0; i<Solutions.size(); i++){
        printAssignment(Solutions[i]);
    }
}


// Main Function implementing the heuristic approach
void solve(vector<Prof> profs, vector<Course> courses)
{
    int check = 0;
    for (int i = 0; i < profs.size(); i++)
    {
        if (profs[i].remaining == 0)
        {
            check++;
        }
        else
        {
            for (int j = 0; j < profs[i].pref.size(); j++)
            {
                int coursePos = getCoursePos(profs[i].pref[j]);
                if (courses[coursePos].remaining > 0)
                {
                    double minm = min(profs[i].remaining, courses[coursePos].remaining);
                    profs[i].remaining -= minm;
                    courses[coursePos].remaining -= minm;
                    profs[i].addCourse(courses[coursePos].name);
                    courses[coursePos].addProf(profs[i].name);
                    break;
                }
            }
        }
        if (check == profs.size())
        {
            break;
        }
        if (i == numProfs - 1)
        {
            i = -1;
        }
    }
    sort(profs.begin(), profs.end(), [](Prof a, Prof b)
         { return a.name < b.name; });

    if(checkAllProfAssigned(profs)){
        if (Solutions.size() == 0)
        {
            Solutions.push_back(profs);
        }
        else
        {
            bool unique = true;
            for (int i = 0; i < Solutions.size(); i++)
            {
                int check = 0;
                for (int j = 0; j < profs.size(); j++)
                {
                    if (Solutions[i][j].courses == profs[j].courses)
                    {
                        check++;
                    }
                }
                if (check == profs.size())
                {
                    unique = false;
                }
            }
            if (unique)
            Solutions.push_back(profs);
        }
    }
}




// C++ Main Function
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("heuristic_output.txt", "w", stdout);
    cin >> prefListSize >> numCourses >> numProfs;
    for (int i = 0; i < numCourses; i++)
    {
        string name;
        cin >> name;
        Course course(name);
        courses.push_back(course);
    }
    for (int i = 0; i < numProfs; i++)
    {
        string name;
        double category;
        cin >> name >> category;
        vector<string> pref;
        for (int j = 0; j < prefListSize; j++)
        {
            string course;
            cin >> course;
            pref.push_back(course);
        }
        Prof prof(name, category, pref);
        profs.push_back(prof);
    }
    int numOfVariations = 100; // Number of times the algorithm is run
    cout << "Heuristic Approach: \n" << endl;
    for (int i = 0; i < numOfVariations; i++)
    {
        random_shuffle(profs.begin(), profs.end());
        vector<Prof> profsCopy;
        copy(profs.begin(), profs.end(), back_inserter(profsCopy));
        vector<Course> coursesCopy;
        copy(courses.begin(), courses.end(), back_inserter(coursesCopy));

        solve(profsCopy, coursesCopy);
    }
    printAllAssignments();
    return 0;
}