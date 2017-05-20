//Brendan Burke
//ECE 2620
//Lab 5
/*Note: When using the large input file, program must be run through
 outside terminal; remember to set ulimit -s to 819200*/
#include<fstream> //header file required for opening file streams
#include <iostream>
#include <ctime>
#define MaxSize 2100000
using namespace std;

void menu() {
	cout << "(1) Read Data from input file" << endl;
	cout << "(2) Sort Data using Bubble Sort" << endl;
	cout << "(3) Sort Data using Merge Sort" << endl;
	cout << "(4) Exit" << endl;
} //Menu function outputs text for the four options to the screen

//Bubblesort function; 
/*each adjacent pair of elements is compared all the way 
until the final two elements. If two elements are not in order, 
they are swapped*/

void bubbleSort(long int array[],int n){
	int swap;//temp variable
	for (int i=0 ; i<(n-1); ++i){
		for (int j=0;j<n-i-1; ++j){
			if (array[j] > array[j+1]){
				swap=array[j];
				array[j]   = array[j+1];
				array[j+1] = swap;
			}
		}
	}
	return;
}

//Merge function
/*merges the two sorted partitions into a single array by repeatedly 
 selecting the smallest element from either the left or right partition and 
 adding tht element to a temp merged array. Once fully merged, elements 
 in temp are copied back to the original array.*/ 

void Merge(long int numbers[], int beg, int end) {
	int size=(end-beg+1); //size of merged partition
	long int *temp=new long int[size]; //Temporary array for merged numbers
	int mid = (end+beg)/2; //find midpoint in the partition
	int i=0; //(array) position for inserting merged value
	int j=beg; // Position of elements in left partition
	int k=mid + 1; //Position of elements in right partition

	while(i < size) {
		if(j <= mid && k <= end) {
			if(numbers[j]<numbers[k]){
				temp[i++]=numbers[j++];
			}
			else{
				temp[i++]=numbers[k++];
			}
		}
		//next, remaining elements of array are copied into temp
		if (j > mid) {
			temp[i++] = numbers[k++];
		}
		else{
			if(k > end)
				temp[i++] = numbers[j++];
		}
	}
	//next, (content of) temp is copied back to array
	for (i=0; i< size; ++i) {
		numbers[beg + i] = temp[i];
	}
	delete[] temp;
}
//MergeSort function
void MergeSort(long int numbers[], int beg, int end) {
	int mid = (end+beg)/2; //Find the midpoint
	if (beg < end) {
		// Recursively sort left and right halves
		MergeSort(numbers, beg, mid);
		MergeSort(numbers, mid + 1, end);
		// Merge left and right halves (now sorted)
		Merge(numbers, beg, end);
	}
	return;
}

int main(){
	ifstream infile; //use provided class to create stream object for reading
	ofstream outfile; //use provided class to create stream object for writing
	long int array[MaxSize]; //declare local array
	double begin_time, end_time, cpu_time_used;
	infile.open("lab5_input.txt");
	if (infile.is_open()) //checks if file is really open
	{
		cout << "File successfully opened" << endl;
	}
	else
	{
		cout << "Error opening file";
	}
	int option; //declare variable
	menu(); //user is prompted with menu options printed to screen
	cout << "Select an operation: ";
	cin >> option; //user inputs an option
	while(option != 4){

		switch (option) {		

			case 1: //if option 1,read data from file and store in local array
			for(int i=0;i<MaxSize;++i){
					infile >> array[i];
			}
			cout << "Data has been stored in local array" << endl;
			break;

			case 2: //if option 2, then use bubble sort
			begin_time = clock(); //first call to clock returns 0
			bubbleSort(array,MaxSize); //call bubbleSort
			end_time = clock(); /*returns elapsed cpu time in microseconds
			 * since first call to clock()*/
			cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
			//calculates elapsed cpu time used in seconds
			cout << "CPU time expended is " << cpu_time_used << endl;
			outfile.open("lab5_bubbleout.txt");
			for(int i=0;i<MaxSize;++i){ //store sorted data in an output file
				outfile << array[i] << " ";
			}
			outfile.close();
			break;

			case 3: //if option 3, then use merge sort
			begin_time = clock();
			MergeSort(array,0,MaxSize-1); //call MergeSort
			end_time = clock();
			cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
			cout << "CPU time expended is " << cpu_time_used << endl;
			outfile.open("lab5_mergeout.txt");
			for(int i=0;i<MaxSize;++i){ //store sorted data in an output file
				outfile << array[i] << " ";
			}
			outfile.close();
			break;

			case 4: //exit
				break;

			default: //try again with a valid numerical input
				cout << "Not Valid" << endl;
			break;
		}
		menu(); //print menu options again
		cout << "Select an operation: ";
		cin >> option; //user inputs an option
	}
	infile.close();
	return 0;
}

