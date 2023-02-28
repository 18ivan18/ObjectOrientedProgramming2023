#include <cassert>
#include <iostream>

// dynamic array with a specified capacity and with certain number of elements (size)

// reason why the input argument for the array is of type int*&?
// create a header file with the declarations of the functions,
// move the definitions to a .cpp file
// show how they are used in main.cpp

// allocate the memory
void allocateMemory(int *&array, size_t capacity)
{
    array = new int[capacity];
}

// delete the allocated memory
void freeMemory(int *&array, size_t &size, size_t &capacity)
{
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}

// reallocate memory with different capacity
bool reallocateMemory(int *&array, size_t size, size_t newCapacity)
{
    int *tempArray = new int[newCapacity];
    if (tempArray == nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < size; i++)
    {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;
    return true;
}

// resize the array, if necessary
// double the size
bool resize(int *&array, size_t size, size_t &capacity)
{
    if (size < capacity)
    {
        return true;
    }
    capacity = capacity * 2;
    return reallocateMemory(array, size, capacity);
}

// add element at the end of the array
// if the size is less than the capacity, the array should be resized
// resize the array, if necessary
bool addElement(int *&array, size_t &size, size_t &capacity, int newElem)
{
    if (size == capacity)
    {
        if (!resize(array, size, capacity))
        {
            return false;
        }
    }
    array[size++] = newElem;
    return true;
}

// add element at a specified position of the array
// resize if necessary
bool addElement(int *&array, size_t &size, size_t &capacity, int newElem, size_t position)
{

    if (position > size)
    {
        return false;
    }
    if (position == size)
    {
        return addElement(array, size, capacity, newElem);
    }

    if (size == capacity)
    {
        if (!resize(array, size, capacity))
        {
            return false;
        }
    }

    for (size_t i = size; i > position; i--)
    {
        array[i] = array[i - 1];
    }

    array[position] = newElem;
    size++;
    return true;
}

// print the elements of the array
void print(const int *array, size_t size, size_t capacity)
{
    std::cout << "Array contents: ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// remove the element at the specified position
// if the number of elements are less than 1/4 of the capacity,
// resize the array, use half of its capacity
bool removeElement(int *&array, size_t &size, size_t &capacity, size_t position)
{
    if (position >= size)
    {
        return false;
    }
    for (size_t i = position; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }

    size--;

    if (size < capacity / 4)
    {
        size_t newCapacity = capacity / 2;
        if (!reallocateMemory(array, size, newCapacity))
        {
            return false;
        }
        capacity = newCapacity;
    }

    return true;
}

int main()
{
    // dynamically allocated array which can be resized
    int *array{nullptr};

    // capacity of the array
    size_t capacity = 3;

    // exact number of elements in the array
    size_t size = 0;

    allocateMemory(array, capacity);

    addElement(array, size, capacity, 1);
    addElement(array, size, capacity, 2);
    addElement(array, size, capacity, 3);

    std::cout << "The capacity of the array is " << capacity << std::endl;
    std::cout << "The real count of the elements in the array is " << size << std::endl;
    print(array, size, capacity);

    addElement(array, size, capacity, 4, 2);

    std::cout << "\nThe capacity of the array is " << capacity << std::endl;
    std::cout << "The real count of the elements in the array is " << size << std::endl;
    print(array, size, capacity);

    removeElement(array, size, capacity, 0);
    removeElement(array, size, capacity, 0);
    removeElement(array, size, capacity, 0);

    std::cout << "\nThe capacity of the array is " << capacity << std::endl;
    std::cout << "The real count of the elements in the array is " << size << std::endl;

    print(array, size, capacity);

    freeMemory(array, size, capacity);
}