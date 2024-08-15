#include <iostream>

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    // check if cin failure occurs and throw error message
    if (std::cin.fail()) {
        std::cerr << "Input failure. Please enter the right type of data (int)" << std::endl;
        return -1;
    }
    
    int *arr = new int[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
        
        // check if cin failure occurs and throw error message
        if (std::cin.fail()) {
            std::cerr << "Input failure. Please enter the right type of data (int)" << std::endl;
            return -1;
        }
    }

    bubbleSort(arr, n);
    std::cout << "Sorted array: ";
    // change <= by < to avoid getting the index out of bounds and accessing out of memory positions    
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
     
    delete[] arr;
    return 0;
}