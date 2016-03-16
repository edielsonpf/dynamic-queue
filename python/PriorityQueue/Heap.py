'''
Created on Mar 10, 2016

@author: Edielson
'''

class MaxHeap(object):
    '''
    classdocs
    '''
    __heapSize = 0
    __Heap = []
    
    def __init__(self):
        '''
        Constructor
        '''
    def __DecrementHeapSize(self):
        self.__heapSize=self.__heapSize-1
    
    def __IncrementHeapSize(self):
        self.__heapSize=self.__heapSize+1  
            
    def __MaxHeapify(self,i): 
        
        l=self.__Left(i)
        r=self.__Right(i)

        if((l <= self.GetHeapSize()-1) and (self.GetItem(l) > self.GetItem(i))): 
            maior=l 
        else:  
            maior=i 
        
        if((r<=self.GetHeapSize()-1) and (self.GetItem(r) > self.GetItem(maior))): 
            maior=r 
          
        if (maior!=i): 
            aux = self.GetItem(i) 
            self.SetItem(i, self.GetItem(maior))
            self.SetItem(maior, aux) 
            self.__MaxHeapify(maior) 
    
    def __BuildMaxHeap(self,A):
        
        self.__Heap = A
        self.__heapSize = len(A)
        
        for i in range((len(A)-1)/2, -1, -1):   
#             print i
            self.__MaxHeapify(i) 
    
    def __RemoveItem(self,index):
        item = self.GetItem(index)
        self.__Heap.pop(index)
        self.__DecrementHeapSize()
        return item
    
    def __InsertItem(self,key):
        self.__Heap.append(key)
        self.__IncrementHeapSize()
    
    def __CleanHeap(self):
        self.__heapSize = 0
        self.__Heap=[]
    
    def __Parent(self,i):
        return (i-1)/2
    
    def __Left(self,i):
        return 2*i+1
    
    def __Right(self,i):
        return 2*i+2
    
    def GetItem(self,i):
        return self.__Heap[i]
    
    def GetMax(self):
        return self.__Heap[0]
    
    def SetItem(self,i,value):
        self.__Heap[i] = value
     
    def GetHeapSize(self):
        return self.__heapSize
    
    def GetHeap(self):
        return self.__Heap
    
    def Sort(self): 
        
        for i in range (self.GetHeapSize()-1, 0, -1): 
            aux=self.GetItem(0) 
            self.SetItem(0, self.GetItem(i)) 
            self.SetItem(i, aux) 
            self.__DecrementHeapSize() 
            self.__MaxHeapify(0)
       
    def ExtractMax(self):
        
        if self.GetHeapSize() < 1:  
            Max = -10
            print ('error: heap underflow')
        else:
            Max = self.GetItem(0)
            self.SetItem(0, self.GetItem(self.GetHeapSize()-1))
            self.__RemoveItem(self.GetHeapSize()-1)
            self.__MaxHeapify(0)
        return Max
    
    def IncreaseKey(self,index,key):
        
        if key < self.GetItem(index):
            print ('error: new key smaller then current key')
        else:  
            self.SetItem(index, key)
            while (index > 0) and (self.GetItem(self.__Parent(index)) < self.GetItem(index)):
                aux=self.GetItem(index) 
                self.SetItem(index, self.GetItem(self.__Parent(index))) 
                self.SetItem(self.__Parent(index), aux) 
                index = self.__Parent(index)
                
    def Insert(self,key):
        self.__InsertItem(key)
        self.IncreaseKey(self.GetHeapSize()-1, key)