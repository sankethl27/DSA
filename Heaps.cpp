#include<bits/stdc++.h>
using namespace std;
#define ll long long

class Heap{
	public : 
		vector<int> a;
		int size;

		Heap(vector<int> arr){
			a=arr;
			size = a.size();
		}

		int leftChild(int index){
			return 2*index + 1;
		}

		int rightChild(int index){
			return 2*index + 2;
		}

		int getMin(){
			return a[0];
		}


		//if we insert a element at the end of the array 
		//and we comapare the element with its parent
		// if its smaller than its parent then we swap them
		//we do this untill index reaches 0 i.e it becomes Root of tree
		void shiftUp(int index){
			int parent = (index-1)/2;
			while(index!=0 && a[parent] > a[index]){
				swap(a[parent],a[index]);
				index = parent;
				parent = (index-1)/2;
			}
		}



		/*We Comapre index/parent with its childs and 
		if parent element is greater than its children 
		then we swap parent and children */
		/* if we need to extract min number 
		then we swap root number with right most leaf element
		After that we need to send root element to its correct position
		Then we apply shiftDown on that index */
		void shiftDown(int index){
			int lc = leftChild(index);
			int rc = rightChild(index);
			while((lc < a.size() && a[index] > a[lc]) || ( rc < a.size() && a[index] > a[rc])){
				int smallest = index;
				if(lc < a.size() && a[lc] < a[smallest]){
					smallest = lc;
				}
				if( rc < a.size() && a[rc] < a[smallest]){
					smallest = rc;
				}
				if(smallest == index) break;
				swap(a[index],a[smallest]);
				index = smallest;
				lc = leftChild(index);
				rc = rightChild(index);

			}
		}

	
		int extractMin(){
			int size= a.size();
			if(a.size() == 0 ) {
				cout<<"\nArray is Empty ,size : ";
				return -1;
			}
			int minimum = a[0];
			swap(a[0],a[size-1]);
			size--;
			a.resize(size);
			shiftDown(0);
			return minimum;
		}

		void insert(int num){
			a.push_back(num);
			size++;
			int index = size-1;
			shiftUp(index);
		}

		// if new value is lesser than oldvalue then we shiftUp
		// if new value os greater than oldvalue than we shiftDown
		//log(n) time complexity
		void updateByIndex(int newValue , int index){
			int oldValue = a[index];
			a[index] = newValue;
			if(newValue < oldValue) shiftUp(index);
			else if(newValue > oldValue) shiftDown(index);
		}

		//update by value
		// nlog(n) time complexity
		void update(int newValue ,int oldValue){
			int index;
			for(int i=0;i<size;i++){
				if(a[i] == oldValue){
					index = i;
					break;
				}
			}
			updateByIndex(newValue,index);
		}

		//Heapify is done in order to convert arbitary Binarytree
		//or arbitary array into BinaryHeap
		//O(nlog(n)) time complexity using shiftUp
		//O(n) time complexity using shiftDown
		void heapify(){
			for(int i = (size/2)-1 ;i>=0;i--){
				shiftDown(i);
			}
		}

		void deleteKey(int i){
			a[i] = INT_MIN;
			shiftUp(i);
			extractMin();

		}

		void printHeap(){
			for(auto& ele : a){
				cout<<ele<<" ";
			}
			cout<<"\n";
		}
		//O(nlog(n)) n for heapify and logn for extracting min
		void heapSort(){
			heapify(); // first heapify the given arbitary array
			vector<int> sortedArray;
			//since we are extracting min size will be 
			//decreemnted dynamically and can affect loops range, so store it separately and use that
			int s = a.size();
			for(int i=0;i<s;i++){
				sortedArray.push_back(extractMin());
			} 
			cout<<"Sorted Array : ";
			for(auto& ele : sortedArray){
				cout<<ele<<" ";
			}

		}
};




int main(){
	vector<int> a = {20,30,40,25,15};
	Heap h(a);
	h.heapify();
	// h.deleteKey(0);	
	cout<<"Extract Min : " << h.extractMin()<<endl;
	h.heapSort();
}
