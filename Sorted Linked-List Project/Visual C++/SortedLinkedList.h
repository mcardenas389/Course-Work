#ifndef SortedLinkedList_h
#define  SortedLinkedList_h

template<class itemtype>
struct node
{
     itemtype info;
     node<itemtype> *next;
};

template<class itemtype>
class SortedLinkedList
{
     private:
          int length;
          node<itemtype> *data;
          node<itemtype> *position;
          
     public:
          SortedLinkedList();
          ~SortedLinkedList();
          SortedLinkedList(const SortedLinkedList<itemtype>&);
          void operator=(SortedLinkedList<itemtype>);
          void InsertItem(itemtype);
          void DeleteItem(itemtype);
          void ReplaceAll(itemtype, itemtype);
          void DeleteAll(itemtype);
          int  CountAll(itemtype);
          void MakeEmpty();
          void GetLength();
          void GetList();
          bool SearchItem(itemtype);
		  bool IsSorted(itemtype, itemtype);
          bool IsEmpty() const;
          bool IsFull() const;
};

#endif
