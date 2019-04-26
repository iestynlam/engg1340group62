// NEEDS TO BE REVAMPED, give error message and error processing at the end, return NULL if user decides
// to abandon process.
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/* checks if all characters are digits to ensure input is an int. Returns true if not all
characters are digits and the main insert command prompts users to reenter a valid input.*/
bool digit_check(string str_input) {
  for (int i = 0; i < str_input.length() ; i++) {
    if (isdigit(str_input[i]) == false) {
      cout << "Only integers can be entered for this field. Please enter a valid input." << endl;
      return false;
    }
  }
  return true;
}

void insert(commodity* &head) {
  commodity* new_item;
  string str_input;

  cout << "A new item will be entered into the system. Please provide the required details.\n"
  "If the manufacturer is unavailable, please enter \"-\"." << endl;

  cout << "NAME: ";
  getline(cin,str_input);
  str_input = lowercase(fill_spaces(str_input)); // function to fill any spaces with '_', probably will be used elsewhere in the program for searches and such
  new_item->name = str_input;

  cout << "here0?\n";

  cout << "MANUFACTURER: ";
  getline(cin,str_input);
  str_input = lowercase(fill_spaces(str_input));
  if (str_input == "-") {
    new_item->manuf = "[n/a]";
  }
  else {
    new_item->manuf = str_input;
  }
// error handling if user inputs words instead of numbers
  cout << "QUANTITY: ";
  cin >> str_input; // no need for getline because no spaces for an int
  while (digit_check(str_input)==false) {
    cout << "QUANTITY: ";
    cin >> str_input;
  }
  cout << "here?\n";
  // converting string back into integer
  int temp=0;
  for (int i = 0; i < str_input.length(); i++) {
    temp+=(int(str_input[i])-48)*pow(10,(str_input.length()-i-1));
  }
  new_item->qty = temp;

  //CHECK IF ITEM ALREADY EXISTS
  cout << "checking exist";
  commodity* current = head;
  while(current!=NULL) {
    if (current->name == new_item->name && current->manuf == new_item->manuf) {
      cout << "An item already exists in the system with the same name and manufacturer:\n";
      print_item(current);
      cout << "What would you like to do?\n1. Merge items\n2.Change name\n3.Change manufactuer\n4.Cancel\n";
      int choice;
      cin >> choice;
      if (choice == 1) {
        current->qty+=new_item->qty;
        append_item(head, new_item->name, new_item->manuf, new_item->qty);
      }
      else if (choice == 2) {
        cout << "NAME: ";
        getline(cin,str_input);
        str_input = lowercase(fill_spaces(str_input)); // function to fill any spaces with '_', probably will be used elsewhere in the program for searches and such
        new_item->name = str_input;
        append_item(head, new_item->name, new_item->manuf, new_item->qty);
      }
      else if (choice == 3) {
        cout << "MANUFACTURER: ";
        getline(cin,str_input);
        str_input = lowercase(fill_spaces(str_input));
        if (str_input == "-") {
          new_item->manuf = "[n/a]";
        }
        else {
          new_item->manuf = str_input;
        }
        append_item(head, new_item->name, new_item->manuf, new_item->qty);
      }
      else if (choice == 4) {
        cout << "Action cancelled.";
      }
    }
    current = current->next;
  }
}
