#include "SortedLinkedList.cpp"
#include <iostream>
using namespace std;

//prints menu to user
int PrintMenu();

//prints the results of the function SearchItem()
void PrintSearch(SortedLinkedList<int>, int);

//prints the results of the function CountAll()
void PrintCount(SortedLinkedList<int>, int);

int main()
{
     SortedLinkedList<int> sll;
     
     int item, replace, choice;
     
     cout<< "Enter a number that corresponds with the action you wish to take."
         << endl;

	 choice = PrintMenu();

	 while(choice != 0)
	 {
          switch(choice)
		  {
               //insert item
	           case 1: 
                    cout<< "Enter a number to insert: ";
                    cin>> item;
                    sll.InsertItem(item);
		            break;
    
               //delete item
               case 2: 
                    cout<< "Enter a number to delete: ";
                    cin >> item;
                    sll.DeleteItem(item);
		            break;
		          
               //get results of search
               case 3:
                    cout<< "Enter a number to search for: ";
                    cin >> item;
                    PrintSearch(sll, item);
                    break;
                  
               //get results of count
               case 4:
                    cout<< "Enter a number to count: ";
                    cin >> item;
                    PrintCount(sll, item);
                    break;
                  
               //get list
               case 5:
                    sll.GetList();
				    break;
			 
               //get length of list	  
		       case 6:
                    sll.GetLength();
                    break;
                  
               //replace item(s)
               case 7:
                    cout<< "Enter item(s) you want to replace: ";
                    cin >> replace;
                  
                    cout<< "Enter item you want to replace " 
                        << replace << " with: ";
                    cin >> item;
                  
                    sll.ReplaceAll(item, replace);
                    break;
                  
               //delete all occurrences of an item
               case 8:
                    cout<< "Enter a number: ";
                    cin >> item;
                  
                    sll.DeleteAll(item);
                    break;
                  
               //empty list
               case 9:
                    sll.MakeEmpty();
				    cout<< "\nThe list is empty\n";
		            break;

               default:
                    cout<< "\nNumber is not correct."
                        << " Please enter one of the choices.\n" << endl;
				    break;
		  }

		choice = PrintMenu();
	 }

	 cout<< "\nProgram terminated\n\n";
	 return 0;
}

int PrintMenu()
{
	int num;

	cout<< "\n1: Add an item to the list."
	    << "\n2: Delete an item from the list."
	    << "\n3: Search for item."
        << "\n4: Count all occurences of an item."
        << "\n5: Print the list."
        << "\n6: Get length."
	    << "\n7: Replace all occurences of an item."
	    << "\n8: Delete all occurences of an item."
	    << "\n9: Empty the list."
	    << "\n0: Quit.\n"
	    << endl << "Enter your choice: ";
	    
	cin >> num;

	return num;
}

void PrintSearch(SortedLinkedList<int> sll, int item)
{
     if(sll.SearchItem(item))
     {
          cout<< "The item was in the list." << endl;
     }
     else
     {
          cout<< "The item was not in the list." << endl;
     }
}

void PrintCount(SortedLinkedList<int> sll, int item)
{
     int count = sll.CountAll(item);
     
     if(count == 0)
     {
          cout<< "The number " << item 
              << " did not appear on the list." << endl;
     }
     else
     {
         cout<< "The number " << item << " appeared on the list " 
             << count << " time(s)." << endl;
     }
}
