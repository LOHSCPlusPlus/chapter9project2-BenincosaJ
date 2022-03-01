#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
//cereal struct
struct Cereal{
    enum {MAX_CHAR_ARRAY_SIZE = 100};
    char cerealName[MAX_CHAR_ARRAY_SIZE];
    double cals;
    double gramsProtein;
    double gramsFat;
    double gramsSodium;
    double gramsFiber;
    double gramsCarbs;
    double gramsSugar;
    double servingSize;
    Cereal();
};

//cereal default constructor
Cereal::Cereal() {
    for (int index = 0; index < MAX_CHAR_ARRAY_SIZE; index++) {
        cerealName[index] = '\0';
    }
    cals = 0;
    gramsProtein = 0;
    gramsFat = 0;
    gramsSodium = 0;
    gramsFiber = 0;
    gramsCarbs = 0;
    gramsSugar = 0;
    servingSize = 0;
}


const int MAX_CEREAL=500;
//reads cereal file
Cereal readCereal(ifstream &inFile){
    Cereal myCereal; 
    inFile.get(myCereal.cerealName, Cereal::MAX_CHAR_ARRAY_SIZE, ';');
    inFile.ignore(100,';');
    inFile >> myCereal.cals;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsProtein;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsFat;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsSodium;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsFiber;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsCarbs;
    inFile.ignore(100,';');
    inFile >> myCereal.gramsSugar;
    inFile.ignore(100, ';');
    inFile >> myCereal.servingSize;
    inFile.ignore(100,'\n');
    return myCereal;
}

//reads user input to make sure it's a valid integer
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;    
    }
    return temp;
}

//reads user input to make sure it's a valid double
double readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;  
    }
    return temp;
}

//puts the cereal from the file into an array
int readCerealData(Cereal cerealArray[]) {
    ifstream cerealFile("cereal.txt");
    int numCereal = 0;
    while(cerealFile.peek() != EOF && numCereal < MAX_CEREAL) {
        cerealArray[numCereal] = readCereal(cerealFile);
        numCereal++;
    }
    return numCereal;  
}

//Prints the Cereal Array
void printCereals(ostream &outFile, Cereal cerealArray[]){
  for (int index = 0; index < MAX_CEREAL; index++){
      outFile << "Index " << index << ": ";
      outFile << cerealArray[index].cerealName << "; " << cerealArray[index].cals << "; " << cerealArray[index].gramsProtein << "; " << cerealArray[index].gramsFat << "; " << cerealArray[index].gramsSodium << "; " << cerealArray[index].gramsFiber << "; " << cerealArray[index].gramsCarbs << "; " << cerealArray[index].gramsSugar << "; " << cerealArray[index].servingSize << endl;
  }
}

//Allows user to add a cereal to the array, checks each inputed user val to make sure it's valid
void addCereal(Cereal cerealArray[]){
  int index = 0;
  while(index < MAX_CEREAL && cerealArray[index].cerealName[0] != '\0'){
    index++;
  }
  if(index == MAX_CEREAL - 1){
    cout << "Database is full" << endl;
  }else{
    cout << "enter the cereal name: " << endl;
    cin.ignore(100, '\n');
    cin.getline(cerealArray[index].cerealName, MAX_CEREAL); 
    cerealArray[index].cals = readDouble("enter the number of calories per serving: ");
    cerealArray[index].gramsProtein = readInt("enter the grams of protein per serving: ");
    cerealArray[index].gramsFat = readDouble("enter the grams of fat per serving: ");
    cerealArray[index].gramsSodium = readDouble("enter the grams of sodium per serving: ");
    cerealArray[index].gramsFiber = readDouble("enter the grams of fiber per serving: ");
    cerealArray[index].gramsCarbs = readDouble("enter the grams of carbs per serving: ");
    cerealArray[index].gramsSugar = readDouble("enter the grams of sugar per serving: ");
    cerealArray[index].servingSize = readDouble("enter the serving size: ");
  }
}

//removes a cereal from the array and shifts all other values down to fill
void removeCereal(Cereal cerealArray[]){
  int indexToRemove = readInt("enter an index to remove: ");
  for (int i = indexToRemove; i < MAX_CEREAL - 1; i++){
    cerealArray[i] = cerealArray[i+1];
  }
}

//saves user changes to the file
void printArrayToFile(const char fileName[], Cereal cerealArray[], int numCereals) {
    ofstream outFile(fileName);
    printCereals(outFile, cerealArray);
    
}


//user menu, user can select what to do, continues looping until user quits
void displayMenu(Cereal cerealArray[], Cereal backupArray[]){
  int userInput = 0;
  while (userInput != 6){
    userInput = readInt("enter the number of the option you wish to choose:\n(1) Reload database from the file\n(2) Print database\n(3) Add new entry\n(4) Remove entry\n(5) Save database to the file\n(6) Quit");
   
    if (userInput == 1){
      printArrayToFile("cereal.txt", backupArray, MAX_CEREAL);;
    }

    if (userInput == 2){
      printCereals(cout, cerealArray);
    }
    if (userInput == 3){
      addCereal(cerealArray);
    }
    if (userInput == 4){
      removeCereal(cerealArray);
    }
    if (userInput == 5){
      printArrayToFile("cereal.txt", cerealArray, MAX_CEREAL);
    }
    if(userInput == 6){
      cout << "goodbye";
    }
  }
}




int main() {
    Cereal cerealArray[500];
    Cereal backupArray[500];
    readCerealData(cerealArray);
    readCerealData(backupArray);
    displayMenu(cerealArray, backupArray);
}
