#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int mid, int r) {
    int leftIndex, rightIndex, middleIndex;
    int leftSize = mid-l+1;
    int rightSize = r-mid;

    int leftArr[leftSize];
    int rightArr[rightSize];

    for(int i = 0; i < leftSize; i++) {
        leftArr[i] = pData[l+i];
    }
    for(int j = 0; j < rightSize; j++) {
        rightArr[j] = pData[mid + 1 + j];
    }

    leftIndex = 0;
    rightIndex = 0;
    middleIndex = l;

    while(leftIndex < leftSize && rightIndex < rightSize) {
        if(leftArr[leftIndex] <= rightArr[rightIndex]) {
            pData[middleIndex] = leftArr[leftIndex];
            ++leftIndex;
        }
        else {
            pData[middleIndex] = rightArr[rightIndex];
            ++rightIndex;
        }
        ++middleIndex;
    }

    while(leftIndex < leftSize) {
        pData[middleIndex] = leftArr[leftIndex];
        ++leftIndex;
        ++middleIndex;
    }

    while(rightIndex < rightSize) {
        pData[middleIndex] = rightArr[rightIndex];
        ++rightIndex;
        ++middleIndex;
    }

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l<r) {
        int mid=(l+(r-1))/2;
        mergeSort(pData, l, mid);
        mergeSort(pData, mid+1, r);
        merge(pData, l, mid, r);
    }
}


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int key = 0;
    int j = 0;
	for(int i = 1; i < n; ++i) {
        key = pData[i];
        j = i-1;
        while(j>=0 && pData[j] > key) {
            pData[j+1] = pData[j];
            j = j-1;
        }
        pData[j+1] = key;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(pData[j] > pData[j+1]) {
                int temp = pData[j];
                pData[j] = pData[j+1];
                pData[j+1] = temp;
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int minimumIndex;
	for(int i = 0; i < n-1; ++i) {
        minimumIndex = i;
        for(int j = i+1; j < n; ++j) {
            if(pData[j] < pData[minimumIndex]) {
                minimumIndex = j;
            }
        }
        if(minimumIndex != i) {
            int temp = pData[minimumIndex];
            pData[minimumIndex] = pData[i];
            pData[i] = temp;
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
        int val = 0;
        int counter = 0;
        int * arr = *ppData;
		while(fscanf(inFile, "%d\n", &val) > 0) {
            arr[counter] = val;
            ++counter;
        }
	}
    fclose(inFile);
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}