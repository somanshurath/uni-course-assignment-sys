#include <bits/stdc++.h>
#include <string.h>
#include <iomanip>
using namespace std;

// Global IO Variables
const char separator = ' ';
const int nameWidth = 5;
const int numWidth = 4;

// Global Classes
class Course
{
public:
    string name;
    vector<string> prof;
    double remaining;
    bool assignedstatus;
    Course(string name)
    {
        this->name = name;
        this->prof.clear();
        this->remaining = 1;
        this->assignedstatus = false;
    }
    void addProf(string prof)
    {
        this->prof.push_back(prof);
    }
};

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
    Prof(string name, double category, vector<string> pref)
    {
        this->name = name;
        this->category = category;
        this->courses.clear();
        this->pref = pref;
        this->remaining = category;
        this->assignedstatus = false;
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
            cout << this->courses[i] << " ";
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
int prefListSize = 7;

// Final Functions
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

void solve(vector<Prof> profs, vector<Course> courses)
{
    for (int i = 0; i < profs.size(); i++)
    {
        int check = 0;
        if (profs[i].assignedstatus == true)
        {
            check++;
            continue;
        }
        for (int j = 0; j < profs[i].pref.size(); j++)
        {
            int coursePos = getCoursePos(profs[i].pref[j]);
            if (courses[coursePos].assignedstatus == false && profs[i].remaining > 0)
            {
                double minm = min(profs[i].remaining, courses[coursePos].remaining);
                profs[i].addCourse(courses[coursePos].name);
                profs[i].remaining -= minm;
                courses[coursePos].addProf(profs[i].name);
                courses[coursePos].remaining -= minm;
                if (courses[coursePos].remaining == 0)
                    courses[coursePos].assignedstatus = true;
                if (profs[i].remaining == 0)
                {
                    check++;
                    profs[i].assignedstatus = true;
                }
                
            }
        }
    }
    printAssignment(profs);
}

// Main Function
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> numCourses >> numProfs;
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
        // get pref list
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
    int numOfVariations = 2;
    for (int i = 0; i < numOfVariations; i++)
    {
        random_shuffle(profs.begin(), profs.end());
        vector<Prof> profsCopy;
        copy(profs.begin(), profs.end(), back_inserter(profsCopy));
        vector<Course> coursesCopy;
        copy(courses.begin(), courses.end(), back_inserter(coursesCopy));
        solve(profsCopy, coursesCopy);
    }
    return 0;
}