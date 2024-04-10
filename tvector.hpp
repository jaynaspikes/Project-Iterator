//defualt constructor
template<typename T>
TVector<T>::TVector()
{
    size = 0;
    capacity = SPARECAPACITY;
    array = new T [capacity];
}
//
template<typename T>
TVector<T>::TVector(T val, int num)
{
    capacity = num + SPARECAPACITY;
    array = new T[capacity];
    size = num;
    for(int i = 0; i< num; i++)
    {
        array[i] = val;
    }
}
//destuctor
template<typename T>
TVector<T>::~TVector()
{
    delete [] array;
}
//copy constructor
template<typename T>
TVector<T>::TVector(const TVector<T>& v)
{
    capacity = v.capacity;
    size = v.size;
    array = new T [capacity];
    for(int k = 0; k<size; ++k)
        array[k] = v.array[k];
}
//copy assignment operator
template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{
    TVector<T> temp = v;
    std::swap(*this,temp);
    return *this;
}
//move constructor
template<typename T>
TVector<T>::TVector(TVector<T> && v)
{
    std::swap(capacity,v.capacity);
    std::swap(size,v.size);
    std::swap(array,v.array);
}

//move assignment operator
template<typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v)
{
    std::swap(size,v.size);
    std::swap(capacity,v.capacity);
    std::swap(array,v.array);
    return *this;
}
//empty
template<typename T>
bool TVector<T>::IsEmpty() const
{
    if(size == 0)
        return true;
    else
        return false;
}
//clear
template<typename T>
void TVector<T>::Clear()
{
    size == 0;
}
//size
template<typename T>
int TVector<T>::GetSize() const
{
    return size;
}

template<typename T>
void TVector<T>::InsertBack(const T& d)
{
    if(size==capacity)
    {
        SetCapacity(2*capacity+1);
    }
    array[size++]= d;
}

//remove last element in the vector if the container empty remain empty
template<typename T>
void TVector<T>::RemoveBack()
{
    --size;
}

template<typename T>
T& TVector<T>::GetFirst() const
{
    if(size == 0)
    {
        return dummy;
    }
    else{
        return array[0];
    }
}

template<typename T>
T& TVector<T>::GetLast() const
{
    if(size == 0)
    {
        return dummy;
    }
    else{
        return array[ GetSize()-1 ];
    }
}

template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
    TVectorIterator<T> it;
    if(size>=0)
    {
        it.ptr = array;
        it.index = 0;
        it.vsize = size;
    }
    return it;
}

template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    TVectorIterator<T> it;
    if(size > 0)
    {
        it.ptr = array + size -1;
        it.index = size -1;
        it.vsize = size;
    }
    return it;
}

template<typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    capacity = c;
    T* array1 = new T[c];
    if(size > c)
    {
        size = c;
    }
    for(int i = 0; i<size; i++)
    {
        array1[i] = array[i];
    }
    delete [] array;
    array = array1;
    array1 = nullptr;
}

//insert
template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d)
{
    int temp = pos.index;
    TVectorIterator<T> insertuno = pos;
    if(size==capacity)
    {
        SetCapacity(2*capacity+1);
        insertuno.ptr = array + pos.index;
    }
    if(size==0)
    {
        array[0] = d;
        insertuno.index=0;
        insertuno.ptr=array;
    }
    else if(temp>=0 && temp<=size-1)
    {
        for(int i = size-1; i>=temp; i--)
        {
            array[i+1] = array[i];
        }
        array[temp] = d;
    }
    else
    {
        array[size] = d;
        insertuno.index = size;
        insertuno.ptr = array+size;
    }
    size++;
    insertuno.vsize = size;
    return insertuno;
}

//Remove
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    if(size >= capacity)
    {
        TVectorIterator<T> returnpos;
        return returnpos;
    }
    for(int i = pos.index; i < size-1; i++)
    {
        array[i] = array[i+1];
    }
    size--;
    TVectorIterator<T> returnpos = pos;
    return returnpos;   
}

//Remove
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
   if(size == 0 || pos2.index>= size)
    {
        TVectorIterator<T>tempos;
        return tempos;
    }
    if(pos1.index > pos2.index)
    {
        return pos1;
    }
    int subtraction = pos2.index - pos1.index + 1;
    int check = pos1.index;

    for(int i = pos2.index + 1; i < size; i++)
    {
       array[check++] = array[i];
    }
    size -= subtraction;

    if(size < capacity / 2)
    {
        SetCapacity(size);
    }
    TVectorIterator<T> tempos;
    tempos.index = pos1.index;
    tempos.vsize = size;
    return tempos;

    //  calulate whatever at end move everything over return at the end
}

//print function
template<typename T>
void TVector<T>::Print(std::ostream& os, char delim) const 
{
    for(int i = 0; i<size; i++)
    {
        os << array[i] << delim;
    }
}

//Operator+ concatenation two vector objects together
template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
    // TVector<T>store;
    TVectorIterator<T>itr1=t1.GetIterator(); 
    TVectorIterator<T>itr2=t2.GetIterator();
    TVector<T> stored(itr1.GetData(), 1);
    //create iterator that points to t1 and t2 use those to to call the itr iterators 
    while(itr1.HasNext())
    {
        itr1.Next();
        stored.InsertBack(itr1.GetData());
    }
    stored.InsertBack(itr1.GetData());
    while(itr2.HasNext())
    {
        itr2.Next();
        stored.InsertBack(itr2.GetData());
    }
    stored.InsertBack(itr2.GetData());
    return stored;
}


//default constructor
template<typename T>
TVectorIterator<T>::TVectorIterator()
{
    ptr = nullptr;
    // ptr = &TVector<T>::dummy;
    index = 0;
    vsize = 0;
}

template<typename T>
bool TVectorIterator<T>::HasNext() const
{
    if(index<vsize-1)
    {
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
bool TVectorIterator<T>::HasPrevious() const
{
    if(index<0)
    {
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
    if(HasNext())
    {
        index++;
        ptr++;
    }
    return *this;
}

template<typename T>
TVectorIterator <T> TVectorIterator<T>::Previous()
{
    if(HasPrevious())
    {
        index--;
        ptr--;
    }
    return *this;
}

template<typename T>
T& TVectorIterator<T>::GetData() const
{
    if(ptr==nullptr)
    {
        return TVector<T>::dummy;
    }
    else{
        return *ptr;
    }
}
//working here getting the wrong output on linprog






