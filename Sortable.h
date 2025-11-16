#include "utility.h"

const int max_entry = 20000;   

template <class Entry>
class Sortable {
public:
    Sortable( );
    Sortable(Entry* arr, int n);
    int size( ) const;
    bool full( ) const;
    bool empty( ) const;
    void clear( );
    void traverse(void (*visit)(Entry &));
    Error_code retrieve(int position, Entry &x) const;
    Error_code replace(int position, const Entry &x);
    Error_code remove(int position, Entry &x);
    Error_code insert(int position, const Entry &x);
    void quick_sort();
    void quick_sort(int option);
    void merge_sort();
    void recursive_merge_sort(int low, int high);
    void merge(int low, int high);
protected:
    int count;
    Entry entry[max_entry];
    void recursive_quick_sort(int low, int high);
    void recursive_quick_sort(int low, int high, int option);
    int partition(int low, int high);
    void swap(int n, int m);
};

template <class Entry>
Sortable<Entry>::Sortable()
/*  
Post: The Sortable is initialized to be empty. 
*/
{
   count = 0;
}

template <class Entry>
Sortable<Entry>::Sortable(Entry* arr, int n)
/*  
Pre: The array to be copied in this contiguous implementation.
Post: The Sortable is initialized to be empty. 
*/
{
   for (int i = 0; i < n && i < max_entry; i++) {
      entry[i] = arr[i];
   }
   count = n;
}
 
template <class Entry>
void Sortable<Entry>::clear()
//  clear:  clear the Sortable.
/*  
Post: The Sortable is cleared. 
*/
{
   count = 0;
}
 
template <class Entry>
int Sortable<Entry>::size() const
/*  
Post: The function returns the number of entries in the Sortable. 
*/
{
   return count;
}
 
template <class Entry>
bool Sortable<Entry>::empty() const
//  empty: returns non-zero if the Sortable is empty.
/*  
Post: The function returns true or false
according as the Sortable is empty or not. 
*/
{
   return count <= 0;
}
 
template <class Entry>
bool Sortable<Entry>::full() const
//  full: returns non-zero if the Sortable is full.
/*  
Post: The function returns true or false
according as the Sortable is full or not. 
*/
{
   return count >= max_entry;
}
 
template <class Entry>
void Sortable<Entry>::traverse(void (*visit)(Entry &))
/*  
Post: The action specified by function (*visit) has been performed on every
entry of the Sortable, beginning at position 0 and doing each in turn. 
*/
{
   for (int i = 0; i < count; i++)
      (*visit)(entry[i]);
}
 
template <class Entry>
Error_code Sortable<Entry>::insert(int position, const Entry &x)
/*  
Post: If the Sortable is not full and 0 <= position <= n,
where n is the number of entries in the Sortable,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1 and
x is inserted at position of the Sortable.
 
Else:
The function fails with a diagnostic error code. 
*/
{
   if (full())
      return overflow;

   if (position < 0 || position > count)
      return range_err;

   for (int i = count - 1; i >= position; i--)
      entry[i + 1] = entry[i];

   entry[position] = x;
   count++;
   return success;
}
 
template <class Entry>
Error_code Sortable<Entry>::retrieve(int position, Entry &x) const
/*  
Post: If the Sortable is not full and 0 <= position < n,
where n is the number of entries in the Sortable,
the function succeeds:
The entry in position is copied to x.
Otherwise the function fails with an error code of range_err. 
*/
{
   if (position < 0 || position >= count) return range_err;
   x = entry[position];
   return success;
}
 
template <class Entry>
Error_code Sortable<Entry>::replace(int position, const Entry &x)
/*  
Post: If 0 <= position < n,
where n is the number of entries in the Sortable,
the function succeeds:
The entry in position is replaced by x,
all other entries remain unchanged.
Otherwise the function fails with an error code of range_err. 
*/
{
   if (position < 0 || position >= count) return range_err;
   entry[position] = x;
   return success;
}
 

template <class Entry>
Error_code Sortable<Entry>::remove(int position, Entry &x)
/*  
Post: If 0 <= position < n,
where n is the number of entries in the Sortable,
the function succeeds:
The entry in position is removed
from the Sortable, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x Entrys a copy of
the entry formerly in position.
Otherwise the function fails with a diagnostic error code. 
*/
{
   if (count == 0) return underflow;
   if (position < 0 || position >= count) return range_err;

   x = entry[position];
   count--;
   while (position < count) {
      entry[position] = entry[position + 1];
      position++;
   }
   return success;
}

template <class Entry>
void Sortable<Entry>::swap(int m, int n) {
/*
Post: swap two entries at indices m and n.
*/
    Entry temp = entry[m];
    entry[m] = entry[n];
    entry[n] = temp;
}

template <class Entry>
void Sortable<Entry>::quick_sort()
/*
Post: The entries of the Sortable have been rearranged so
      that their keys are sorted into nondecreasing order.
*/
{
   recursive_quick_sort(0, count - 1);
}


template <class Entry>
void Sortable<Entry>::recursive_quick_sort(int low, int high)
/*
Pre:  low and high are valid positions in the Sortable.
Post: The entries of the Sortable have been
      rearranged so that their keys are sorted into nondecreasing order.
*/
{
   int pivot_position;
   if (low < high) {   //   Otherwise, no sorting is needed.
      pivot_position = partition(low, high);
      recursive_quick_sort(low, pivot_position - 1);
      recursive_quick_sort(pivot_position + 1, high);
   }
}


template <class Entry>
int Sortable<Entry>::partition(int low, int high)
/*
Pre:  low and high are valid positions of the Sortable, with low <= high.
Post: The center (or left center) entry in the range between indices
      low and high of the Sortable
      has been chosen as a pivot.  All entries of the Sortable
      between indices low and high, inclusive, have been
      rearranged so that those with keys less than the pivot come
      before the pivot and the remaining entries come
      after the pivot.  The final position of the pivot is returned.
*/
{
   Entry pivot;
   int i,            //  used to scan through the aray
       last_small;   //  position of the last key less than pivot
   swap(low, (low + high) / 2);
   pivot = entry[low];   //  First entry is now pivot.
   last_small = low;
   for (i = low + 1; i <= high; i++)
/*
At the beginning of each iteration of this loop, we have the following
conditions:
        If low < j <= last_small then entry[j].key < pivot.
        If last_small < j < i then entry[j].key >= pivot.
*/
      if (entry[i] < pivot) {
         last_small = last_small + 1;
         swap(last_small, i);  //  Move large entry to right and small to left.
      }
   swap(low, last_small);      //  Put the pivot into its proper position.
   return last_small;
}

template <class Entry>
void Sortable<Entry>::quick_sort(int option)
/*
Post: The entries of the Sortable have been rearranged so
      that their keys are sorted into nondecreasing order by using quicksort.
      The pivot option 1: first element as pivot.
      The pivot option 2: randomly choosing the pivot.
      The pivot option 3: choose the median of 3 randomly selected elements as pivot.
      The pivot option 4: choose the median of first, center, and last elements as pivot.
*/
{
   if (option > 4 || option < 1) {
       std::cout << "Invalid argument." << std::endl;
       return;
   }
   recursive_quick_sort(0, count - 1, option);
}

template <class Entry>
void Sortable<Entry>::recursive_quick_sort(int low, int high, int option)
/*
Pre:  low and high are valid positions in the Sortable.
Post: The entries of the Sortable have been
      rearranged so that their keys are sorted into nondecreasing order.
      The pivot option 1: first element as pivot.
      The pivot option 2: randomly choosing the pivot.
      The pivot option 3: choose the median of 3 randomly selected elements as pivot.
      The pivot option 4: choose the median of first, center, and last elements as pivot.
*/
{
   // TODO 1: implement quicksort with different pivot strategies

}

template <class Entry>
void Sortable<Entry>::merge_sort()
/*
Post: The entries of the Sortable have been rearranged so
      that their keys are sorted into nondecreasing order.
*/
{
   // TODO 2: implement merge_sort
   recursive_merge_sort(0, count-1);
}


template <class Entry>
void Sortable<Entry>::recursive_merge_sort(int low, int high){
   if(low < high){
      int mid = (low + high)/2;
      recursive_merge_sort(low, mid);
      recursive_merge_sort(mid + 1, high);
      merge(low, high);
   }
}


template <class Entry>
void Sortable<Entry>::merge(int low, int high){
   Entry* temp = new Entry[high - low + 1];
   int index = 0;
   int index1 = low;
   int mid = (low + high) / 2;
   int index2 = mid + 1;
   while (index1 <= mid && index2 <= high){
      if (entry[index1] < entry[index2]){
         temp[index] = entry[index1];
         index++;
         index1++;
      } else {
         temp[index] = entry[index2];
         index++;
         index2++;
      }
   }
   while(index1 <= mid){
      temp[index] = entry[index1];
      index++;
      index1++;
   }
   while(index2 <= high){
      temp[index] = entry[index2];
      index++;
      index2++;
   }
   for(index = low; index <= high; index++){
      entry[index] = temp[index - low];
   }
   delete[] temp;
}