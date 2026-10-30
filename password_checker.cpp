#include<iostream>
#include<string>
#include<cctype>
#include<vector>

using namespace std;

//Function to validate password against security policies
bool checkPasswordStrength(const string& password){
    if(password.length() < 8) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for(char ch : password){
        if(isupper(ch)) hasUpper = true;
        else if(islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;

}
int main() {
    vector<string> testCases = {
        "weak",         //Fails: too short, missing complexity
        "StillWeak1",   //Fails: no special characters
        "NoNumbersHere!",//Fails: no digits
        "StrongP@ssw0rd!"//Passes all policy checks

    };
    cout<<" Password Policy Compliance Checker"<<endl;

    //Iterate through test cases and print results
    for (const string& pwd : testCases){
        cout<<"Testing: "<<pwd<<"\n Result: ";
        if(checkPasswordStrength(pwd)){
            cout<<"[PASS] Policy met. \n"<<endl;
        }else{
            cout<<"[FAIL] Does not meet policy.\n"<<endl;
        }
    }
    return 0;
}