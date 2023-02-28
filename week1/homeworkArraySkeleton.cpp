#include <cassert>
#include <iostream>

struct vector
{
    int *array{nullptr};
    size_t capacity{0};
    size_t size{0};
};

// allocate the memory
void allocateMemory(vector &v, size_t capacity)
{
    assert(v.array == nullptr);

    v.array = new int[capacity];
    v.capacity = capacity;
}

// delete the allocated memory
void freeMemory(vector &v)
{
    assert(v.array != nullptr);

    delete[] v.array;
    v.array = nullptr;
    v.capacity = 0;
    v.size = 0;
}

// reallocate memory with different capacity
bool reallocateMemory(vector &v, size_t newCapacity)
{
    assert(v.array != nullptr);

    int *newArray = new int[newCapacity];
    if (newArray == nullptr)
    {
        return false;
    }

    for (size_t i = 0; i < v.size; i++)
    {
        newArray[i] = v.array[i];
    }

    delete[] v.array;
    v.array = newArray;
    v.capacity = newCapacity;

    return true;
}

// resize the vector, if necessary
// double the capacity
bool resize(vector &v)
{
    assert(v.array != nullptr);

    size_t newCapacity = v.capacity * 2;
    return reallocateMemory(v, newCapacity);
}

// add element at the end of the vector
// if the size is less than the capacity, the vector should be resized
bool addElement(vector &v, int newElem)
{
    assert(v.array != nullptr);

    if (v.size >= v.capacity)
    {
        if (!resize(v))
        {
            return false;
        }
    }

    v.array[v.size] = newElem;
    v.size++;

    return true;
}

// add element at a specified position of the vector
// resize if necessary
bool addElement(vector &v, int newElem, size_t position)
{
    assert(v.array != nullptr);
    assert(position <= v.size);

    if (v.size >= v.capacity)
    {
        if (!resize(v))
        {
            return false;
        }
    }

    for (size_t i = v.size; i > position; i--)
    {
        v.array[i] = v.array[i - 1];
    }

    v.array[position] = newElem;
    v.size++;

    return true;
}

// print the elements of the vector
void print(const vector &v)
{
    assert(v.array != nullptr);

    for (size_t i = 0; i < v.size; i++)
    {
        std::cout << v.array[i] << " ";
    }
    std::cout << std::endl;
}

// remove the element at the specified position
// if the number of elements are less than 1/4 of the capacity,
// resize the vector, use half of its capacity
bool removeElement(vector &v, size_t position)
{
    assert(v.array != nullptr);
    assert(position < v.size);

    for (size_t i = position + 1; i < v.size; i++)
    {
        v.array[i - 1] = v.array[i];
    }

    v.size--;

    if (v.size * 4 < v.capacity)
    {
        size_t newCapacity = v.capacity / 2;
        if (newCapacity < 3)
        {
            newCapacity = 3;
        }
        return reallocateMemory(v, newCapacity);
    }

    return true;
}

int main()
{
    vector v;
    allocateMemory(v, 3);

    // add some elements to the vector
    for (int i = 1; i <= 10; i++)
    {
        addElement(v, i);
    }

    std::cout << "Elements in the vector: ";
    print(v);

    // remove some elements from the vector
    for (int i = 0; i < 5; i++)
    {
        removeElement(v, v.size - 1);
    }

    std::cout << "Elements in the vector after removal: ";
    print(v);

    // add an element at a specific position
    addElement(v, 42, 2);

    std::cout << "Elements in the vector after insert: ";
    print(v);

    // remove an element at a specific position
    removeElement(v, 4);

    std::cout << "Elements in the vector after erase: ";
    print(v);

    freeMemory(v);
}
