# Quick start

``` Python

from PriorityQueue.Heap import MaxHeap 

#Create a heap structure
myHeap = MaxHeap()

#this is the vector for example
A=[4, 1, 3, 2, 16, 9, 10, 14, 8, 7]

print('Inserting elements in the queue:\n')
for i in A:
    print('Inserting element %g'%i)
    myHeap.Insert(i)
    print(myHeap.GetHeap())

print('\nUpdating the element in the position %g with key %g for a new key %g:\n'%(myHeap.GetHeapSize()-1,myHeap.GetItem(myHeap.GetHeapSize()-1),myHeap.GetItem(myHeap.GetHeapSize()-1)+9))

myHeap.IncreaseKey(myHeap.GetHeapSize()-1, myHeap.GetItem(myHeap.GetHeapSize()-1)+9)
print(myHeap.GetHeap())

print('\nRemoving the elements in the queue with highest priority:\n')
Max = myHeap.ExtractMax()
while (Max != -10):
    print(Max)
    print(myHeap.GetHeap()) 
    Max = myHeap.ExtractMax()

```
