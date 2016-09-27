//Michael Cardenas
//Project 1
//CSC330 511

#include "SortedLinkedList.h"
#include <iostream>
using namespace std;

//constructor
template<class itemtype>
SortedLinkedList<itemtype>::SortedLinkedList()
{
     length = 0;
     data = position = NULL;
}

//destructor
template<class itemtype>
SortedLinkedList<itemtype>::~SortedLinkedList()
{
     node<itemtype> *q;
     
     while(data != NULL)
     {
          q = data;
          data = data->next;
          delete q;
     }
}

//copy constructor
template<class itemtype>
SortedLinkedList<itemtype>::SortedLinkedList(const SortedLinkedList<itemtype> &other)
{
     node<itemtype> *p, *q;

	 length = other.length;

	 if (other.data == NULL)
	 {
		 data = NULL;
	 }
	 else
	 {   
	     data = new node<itemtype>;
         data->info = other.data->info;
         p = other.data->next;
         q = data;

		 while (p != NULL)
		 {    
			  q->next = new node<itemtype>;
			  q = q->next;
			  q->info = p->info;
			  p = p->next;
		 }

		 q->next = NULL;
	 }
}

//overload operator=
template<class itemtype>
void SortedLinkedList<itemtype>::operator=(SortedLinkedList<itemtype> other)
{
     node<itemtype> *p, *q;

	 length = other.length;

	 if (other.data == NULL)
	 {
		 data = NULL;
	 }
	 else
	 {   
	     data = new node<itemtype>;
         data->info = other.data->info;
         p = other.data->next;
         q = data;

		 while (p != NULL)
		 {    
			  q->next = new node<itemtype>;
			  q = q->next;
			  q->info = p->info;
			  p = p->next;
		 }

		 q->next = NULL;
	 }
}

//insert item: inserts one item to the list
template<class itemtype>
void SortedLinkedList<itemtype>::InsertItem(itemtype item)
{
     node<itemtype> *p = data, *q;
     
     if(!IsFull())
     {
          q = new node<itemtype>;
          
          if(data == NULL)
          {
               q->info = item;
               q->next = NULL;
               data = q;
          }
          else if(item <= data->info)
          {
               q->info = item;
               q->next = data;
               data = q;
          }
          else
          {
               while(item > p->info && p->next != NULL)
               {
                    position = p;
                    p = p->next;
               }
          
               if(item <= p->info)
               {
                    q->info = item;
                    q->next = p;
                    position->next = q;
               }
               else if(p->next == NULL)
               {
                    q->info = item;
                    q->next = NULL;
                    p->next = q;
               }
          }
          
          length++;
     }
     else
     {
          cout<< "The list is full.";
     }
}

//delete item: deletes one item from the list
template<class itemtype>
void SortedLinkedList<itemtype>::DeleteItem(itemtype item)
{
     node<itemtype> *p = data, *q;
     
     if(!IsEmpty())
     {
		  if(SearchItem(item))
		  {
               if(data->info == item)
			   {
                    data = data->next;
                    delete p;
               }
               else
			   {
                    while(p->next->info != item && p->next != NULL)
					{
                         p = p->next;
					}
         
                    if(p->next->info == item && p->next != NULL)
					{
                         q = p->next;
                         p->next = q->next;
		                 delete q;
		            }
			   }
			   
			   length--;
		  }
		  else
		  {
			   cout<< "The number " << item 
				   << " was not found in the list." << endl;
		  }
	 }
     else
     {
          cout<< "The list is empty." << endl;
     }
}

//replace all: replaces all occurrences of item with another item
template<class itemtype>
void SortedLinkedList<itemtype>::ReplaceAll(itemtype item, itemtype replace)
{
     node<itemtype> *p = data;
     
     if(!IsEmpty() && SearchItem(replace))
     {
          if(IsSorted(item, replace))
          {
               if(replace == data->info && data->next == NULL)
		       {
		            data->info = item;
		       }
               else
		       {    
                    while(replace >= p->info && p->next != NULL)
			        {
                         if(replace == p->next->info && p->next->next == NULL)
                         {
                              if(replace == p->info)
                              {
                                   p->info = item;
                                   p->next->info = item;
                              }
                              else
                              {
                                   p->next->info = item;
                              }
                              
                         }
                         else if(replace == p->info)
					     {
                              p->info = item;
                         }

                         p = p->next;
			        }
		       }
		       
		       cout<< "All occurences of " << replace << " was replaced with " 
                   << item << endl;
          }
          else
          {
               cout<< "Action cannot be executed." << endl
				   << "The order of the list would be compromised." << endl;
          }
	 }
	 else
	 {
		  cout<< "The number " << replace
              << " was not found in the list." << endl;
	 }
}

//delete all: deletes all occurrences of an item
template<class itemtype>
void SortedLinkedList<itemtype>::DeleteAll(itemtype item)
{
     node<itemtype> *p = data, *q;
     
     if(!IsEmpty())
     {
          if(SearchItem(item))
          {
               while(p != NULL && p->info <= item)
               {
                    if(item == data->info)
                    {
                         data = data->next;
                         delete p;
                         p = data;
                         length--;
                    }
                    else if(item == p->next->info)
                    {
                         q = p->next;
                         p->next = q->next;
		                 delete q;
                         length--;                         
                    }
                    else
                    {
                         p = p->next;
                    }
               }
		       
		       cout<< "All occurences of " << item 
                        << " was deleted from the list." << endl;
          }
          else
          {
               cout<< "The number " << item 
                   << " was not found on the list." << endl;
          }
	 }
	 else
	 {
          cout<< "There are no items to delete." << endl;
	 }
}

//count all:  returns an int of all occurrences of an item
template<class itemtype>
int SortedLinkedList<itemtype>::CountAll(itemtype item)
{
     node<itemtype> *p = data;
     
     int counter = 0;
     
     if(!IsEmpty() && SearchItem(item))
     {
          if(item == data->info && data->next == NULL)
		  {
               counter++;
		  }
	      else
		  {
               while(item >= p->info && p->next != NULL)
			   {
			        if(item == p->next->info && p->next->next == NULL)
					{
                         if(item == p->info)
                         {
                              counter += 2;
                         }
                         else
                         {
                              counter++;
                         }
					}
			        else if(item == p->info)
					{
				         counter++;
					}

			        p = p->next;
			   }
          }
	 }

     return counter;
}

//make empty: empties the list and resets data to NULL
template<class itemtype>
void SortedLinkedList<itemtype>::MakeEmpty()
{
     node<itemtype> *q;
     
     length = 0;
     
     while(data != NULL)
     {
          q = data;
          data = data->next;
          delete q;
     }
}

//get length: prints the number of elements in the list
template<class itemtype>
void SortedLinkedList<itemtype>::GetLength()
{
     if(!IsEmpty())
     {
          cout<< "The length is: " << length << endl;
     }
     else
     {
         cout<< "The list is empty." << endl;
     }
}

//get list: prints the list
template<class itemtype>
void SortedLinkedList<itemtype>::GetList()
{
     node<itemtype> *p = data;
     
     if(!IsEmpty())
     {
          cout<< "The items in the list are: ";
          
          while(p != NULL)
          {
               cout<< p->info << " ";
               p = p->next;
          }
          
          cout<< "\n";
     }
     else
     {
          cout<< "The list is empty." << endl;
     }
}

//search item: checks if the item entered is in the list
template<class itemtype>
bool SortedLinkedList<itemtype>::SearchItem(itemtype item)
{
     node<itemtype> *p = data;
     
     while(p != NULL)
     {
          if(p->info == item)
          {
               return true;
          }
                    
          p = p->next;
     }
               
     return false;
}

//is sorted: checks the list to see if the changes made by ReplaceAll would
//           compromise the order of the list
template<class itemtype>
bool SortedLinkedList<itemtype>::IsSorted(itemtype item, itemtype n)
{
	 node<itemtype> *p = data;
	 
	 itemtype element = p->info;

     while(n >= p->info && p->next != NULL)
	 {
          if(p->info < n)
          {
               element = p->info;
          }

		  p = p->next;
	 }
	 
	 if(element == p->info)
	 {
          return true;
     }
     else if(n == data->info)
     {
          if(item <= data->info && item <= p->info)
          {
               return true;
          }
     }
	 else if(element <= item && item <= p->info)
	 {
   	      return true;
     }
     else if(item >= p->info && p->next == NULL)
     {
          return true;
     }
     
     return false;
}

//is empty: checks if there are any items in the list
template<class itemtype>
bool SortedLinkedList<itemtype>::IsEmpty() const
{
     if(data == NULL)
     {
          return true;
     }
     else
     {
          return false;
     }
}

//is full: checks of the list has exceeded memory
template<class itemtype>
bool SortedLinkedList<itemtype>::IsFull() const
{
     node<itemtype> *q;
     
     try
     {
          q = new node<itemtype>;
          delete q;
          return false;
     }
     catch (std::bad_alloc)
     {
           return true;
     }
}
