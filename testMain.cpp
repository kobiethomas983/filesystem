#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "disk.h"
#include "FileSys.h"
using namespace std;

//might use a enum 
string convertToUpper(string convertString);

void Choice(string parsedInput[], FileSys *fs) {
    //we want to create a fs object in this function
    //everything call we use will go through the fs object we have 
    if(parsedInput[0] == "CREATE"){
        if (fs->GetDiscID() > 0)
        {
            cout << "Create file" << endl;
            fs->CreateFile(parsedInput[1]); 
        }
        else {
            cout << "DiscId is less than one";
        }
    }
    else if(parsedInput[0] == "EDIT"){
        cout << "edit file" << endl;
         if (fs->GetDiscID() > 0)
        {
            fs->UpdateFile(parsedInput[1]);
        }
        else {
            cout << "DiscId is less than one";
        }
    }
    else if(parsedInput[0] == "DELETE"){
        cout << "delete file" << endl;
         if (fs->GetDiscID() > 0)
        {
            fs->DeleteFile(parsedInput[1]); 
        }
        else {
            cout << "DiscId is less than one";
        }
    }
    else if(parsedInput[0] == "TYPE"){
        cout << "type file" << endl;
    }
    else if(parsedInput[0] == "DIR"){
        cout << "directory" << endl;
    }
    
    
}

int main()
{
    string userInput;
    string parsedInput[2] = {""};
    string compareString;
    string testString;
    FileSys *fs = new FileSys();
    while(compareString != "EXIT"){
        cout << "$";
        getline(cin,userInput);
        compareString = convertToUpper(userInput.substr(0,userInput.find(" "))); //gives me all the string before the space, the function always makes sure input it capitalized
        
        if (compareString == "EXIT") {
            break;
        }
        if((compareString == "DIR") || (compareString == "EXIT")){
            parsedInput[0] = compareString;
            Choice(parsedInput, fs);
        }
        else if((compareString == "CREATE") || (compareString == "EDIT") || (compareString == "DELETE") || (compareString == "TYPE")){
            parsedInput[0] = compareString;
            compareString = userInput.substr(userInput.find(" ")+1, userInput.length()-1);
            parsedInput[1] = compareString;
            Choice(parsedInput, fs);
        }
    }
  
    
    
    return 0;
    
}

string convertToUpper(string convertString){
    for (int i = 0; i < convertString.length(); i++) {
        convertString[i] = toupper(convertString[i]);
    }
    return convertString;
}

