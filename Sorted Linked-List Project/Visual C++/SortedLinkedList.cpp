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

//insert item
template<class itemtype>
void SortedLinkedList<itemtype>::InsertItem(itemtype item)
{
     node<itemtype> *p, *q;
     
     length++;
     
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
               p = data;
          
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
     }
     else
     {
          cout<< "The list is full.";
     }
}

//delete item
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
          
                    length--;
			   }
               else
			   {
                    while(p->next->info != item && p->next != NULL)
					{
                         p = p->next;
					}
         
                    q = p->next;
                    p->next = q->next;
		            delete q;
		      
		            length--;
				}
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

//replaces all occurrences of item with another item
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
                              p->info = item;
                              p->next->info = item;
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
               cout<< "Action cannot be executed." 
				   << " The order of the list would be compromised." << endl;
          }
	 }
	 else
	 {
		  cout<< "The number " << replace
              << " was not found in the list." << endl;
	 }
}

//deletes all occurrences of an item
template<class itemtype>
void SortedLinkedList<itemtype>::DeleteAll(itemtype item)
{
     node<itemtype> *p = data, *q;
     
     if(!IsEmpty() && SearchItem(item))
     {
          if(item != data->info)
		  {
               while(item = p->info && p->next != NULL)
			   {
                    p = p->next;
              
                    if(p->info == item)
					{
                         q = p->next;
                         p->next = q->next;
                         delete q;
                   
                         length--;
					}
			   }
		  }
          else
		  {
			   while(item == data->info && data->next != NULL)
			   {
				    data = data->next;
                    delete p;
                    p = data;

					length--;
			   }

			   /*if(item == data->info && data->next == NULL)
			   {
				   MakeEmpty();
			   }*/
               
		  }

		  cout<< "All occurences of " << item << " was deleted.";
	 }
	 else
	 {
          cout<< "There are no items to delete." << endl;
	 }
}

//counts all occurrences of an item
template<class itemtype>
int SortedLinkedList<itemtype>::CountAll(itemtype item)
{
     node<itemtype> *p = data;
     
     int counter = 0;
     
     if(!IsEmpty())
     {
          if(item == data->info && data->next == NULL)
		  {
               counter++;
		       return counter;
		  }
	      else
		  {
               while(item >= p->info && p->next != NULL)
			   {
			        if(item == p->next->info && p->next->next == NULL)
					{
                         counter += 2;
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

//make empty
template<class itemtype>
void SortedLinkedList<itemtype>::MakeEmpty()
{
     node<itemtype> *q;
     
     if(!IsEmpty())
     {
          while(data != NULL)
          {
               q = data;
               data = data->next;
               delete q;
          }
     }
     else
     {
          cout<< "The list is already empty.";
     }
}

//get length
template<class itemtype>
void SortedLinkedList<itemtype>::GetLength()
{
     if(!IsEmpty())
     {
          cout<< "The length is: " << length << endl;
     }
     else
     {
         cout<< "The list is empty.";
     }
}

//get list
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

//search item
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

//is sorted(fix so it can compare the last node without crashing)
template<class itemtype>
bool SortedLinkedList<itemtype>::IsSorted(itemtype item, itemtype n)
{
	 node<itemtype> *p = data;

     while(n >= p->info)
	 {
		  p = p->next;
	 }
	 
	 if(item > p->info && p != NULL)
	 {
	      return false;
	 }
	 else
	 {
		 return true;
	 }
}

//is empty
template<class itemtype>
bool SortedLinkedList<itemtype>::IsEmpty() const
{
     return (data == NULL);
}

//is full
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
