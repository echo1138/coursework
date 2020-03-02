
#include <iostream>   
#include <iomanip>   
#include <string>   
#include <fstream>   
using namespace std; 
/************************************* 
LAB 3 
CSC 326 
PURPOSE: MODIFYING LAB 2 --- Here we replace the struct with a class, the move all the members and member functions inside the class.  The program itself will have the same functionalities from the previous lab. 
*************************************/ 
class SG { 
public: 
    float arraySG[10]; 
    string name; 
    char LG; 
    //prototypes 
    char checkGrade(float); 
    float average(float); 
    void HIGHlow(SG); 
    void output(SG, float); 
private: 
    int high, low, // these variables will store the grade numbers  
        h, l,   // these variables will be used for the 'for loop'  
        hi, lo, // these variables will be used to determine which test the student got the high/low grade on 
        zeroCount; // this variable will count zeros, if the zeroes are counted up to 9 then the program will say "student did not complete any tests" 
}; 
int main() 
{ 
    // declaring arrays   
    float sum = 0, averageNum; 
    SG student[3]; 
    ifstream inFile; 
    inFile.open("Data.txt"); 
    if (inFile.fail()) { 
        cout << "This file cannot be opened." << endl; 
        exit(1); 
    } 
    //initializing variables for each student object   
    for (int i = 0; i < 3; i++) { 
        inFile >> student[i].name; // put students name from file into object   
        for (int j = 0; j < 10; j++) { 
            inFile >> student[i].arraySG[j]; // put students grade in obj array   
            sum = sum + student[i].arraySG[j]; // get sum to calculate average   
        } 
        averageNum = student[i].average(sum); 
        student[i].LG = student[i].checkGrade(student[i].average(sum)); 
        student[i].output(student[i], averageNum); 
        //resetting variables for the next student to be inputted   
        averageNum = 0; 
        sum = 0; 
    } 
    inFile.close(); 
    return 0; //end of main   
} 
  
float SG::average(float num) { // function will calculate the average from the grades   
    num = num / 10; 
    return num;  // brings back the average number to main   
} 
  
char SG::checkGrade(float grade) { // function will check the grade of the student and determine letter grade and return a letter based on the average given   
    if (grade == 0) { 
        return 'W'; 
    } 
    if (grade <= 50) { 
        return 'F'; 
    } 
    if (grade > 50 && grade <= 60) { 
        return 'D'; 
    } 
    if (grade > 60 && grade <= 70) { 
        return 'C'; 
    } 
    if (grade > 70 && grade <= 88) { 
        return 'B'; 
    } 
    if (grade > 88 && grade <= 100) { 
        return 'A'; 
    } 
}

void SG::HIGHlow(SG student) { // this function will calculate and output the highest grade and the lowest grade of the student  
    //set variables  
    hi = 1, lo = 1;  
    zeroCount = 0;  
    high = student.arraySG[0]; 
    low = student.arraySG[0]; 
    for (h = 1; h < 10; h++) { // determining highest grade  
        if (high < student.arraySG[h]) { 
            high = student.arraySG[h]; 
            hi = h + 1; 
            if (student.arraySG[h] == 0) { 
                zeroCount++; 
            } 
            if (zeroCount == 9) { 
                cout << "Student did not complete any tests." << endl; 
            } 
        } 
    } 
    zeroCount = 0; // clear count  
    for (l = 1; l < 10; l++) { // determing lowest grade  
        if (low > student.arraySG[l]) { 
            low = student.arraySG[l]; 
            lo = l + 1; 
        } 
        if (student.arraySG[l] == 0) { 
            zeroCount++; 
        } 
        if (zeroCount == 9) { 
            cout << "Student did not complete any tests." << endl; 
        } 
    } 
    //output  
    if (zeroCount != 9) { 
        cout << "Highest Grade: " << student.name << " received a high grade of " << high << " on test " << hi << endl; 
        cout << "Lowest Grade: " << student.name << " received a low grade of " << low << " on test " << lo << endl; 
    } 
} 
  
void SG::output(SG student, float avr) { // function will output a singular student   
    cout << "Name: " << student.name << endl; 
    cout << "Grades: "; 
    for (int k = 0; k < 10; k++) { 
        cout << student.arraySG[k] << " "; 
    } 
    cout << endl; 
    HIGHlow(student); 
    cout << "Average: " << avr << endl; 
    cout << "Grade: " << student.LG << endl; 
    cout << "\n" << endl; // end of individual student output   
} 
  
/* 

OUTPUT:
  
Name: Giselle 
Grades: 95 96 58 0 34.5 69.5 43 54 76.2 98 
Highest Grade: Giselle received a high grade of 98 on test 10 
Lowest Grade: Giselle received a low grade of 0 on test 4 
Average: 62.42 
Grade: C 
  
  
Name: Johnny 
Grades: 86 45 56.4 86 98 60 97 85 85 86 
Highest Grade: Johnny received a high grade of 98 on test 5 
Lowest Grade: Johnny received a low grade of 45 on test 2 
Average: 78.44 
Grade: B 
  
  
Name: Ren 
Grades: 0 0 0 0 0 0 0 0 0 0 
Student did not complete any tests. 
Average: 0 
Grade: W 
*/