#include <cmath>
#include <iostream>
void __swap(int * a, int * b) {
	int tmp = * a;
	* a = * b;
	* b = tmp;
}

void __makeHeap(int *arr, int left, int right) {
	for(int i=left; i <= right; i++) {
		int now = i;
		while(now > 0) {
			int par = (now - 1) >> 1;
			if(arr[par] < arr[now]) __swap(arr+par, arr+now);
			now = par;
		}
	}
}

void __heapSort(int *arr, int left, int right) {
	__makeHeap(arr, left, right);
	for(int i=right; i>left; i--) {
		__swap(arr, arr+i);
		int left = 1, right = 2;
		int sel = 0, par = 0;
		while(1) {
			if(left >= i) break;
			if(right >= i) sel = left;
			else {
				if(arr[left] < arr[right]) sel = right;
				else sel = left;
			}
			if(arr[sel] > arr[par]) {
				__swap(arr+sel, arr+par);
				par = sel;
			} else break;
			left = (par<<1) + 1;
			right = left+1;
		}
	}
}

void __insertionSort(int arr[], int left, int right) {
	for(int i=left; i<right; i++) {
		int key = arr[i+1];
		int j;
		for(j=i; j>=left; j--) {
			if(arr[j] > key) arr[j+1] = arr[j];
			else break;
		}
		arr[j+1] = key;
	}
}


void __quickSort(int arr[], int left, int right, int depth) {
	if(depth == 0) {
		int size = right-left+1;
		if(size > 16) {
			__heapSort(arr, left, right);
		}
		return;
	}

	int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    int temp;
    do {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i<= j) {
            __swap(arr+i, arr+j);
            i++;
            j--;
        }
    } while (i<= j);

    if (left < j)
        __quickSort(arr, left, j, depth-1);

    if (i < right)
        __quickSort(arr, i, right, depth-1);

}

void introSort(int arr[], int n) {
	int limit = 2*ceil(log2(n));
	if(n <= 16){
		__insertionSort(arr, 0, n-1);
		return;
	}
	__quickSort(arr, 0, n-1, limit);
	__insertionSort(arr, 0, n-1);
}

int main(void)
{
	int arr[] = {3,5,6,12,1,4,7,123,29,99,5,8,1222321, 231,2,3,1,2};

	for (int i = 0; i < 18; ++i)
		std::cout << arr[i] << std::endl;
	introSort(arr, 12);
	std::cout << std::endl;
	for (int i = 0; i < 12; ++i)
		std::cout << arr[i] << std::endl;
}