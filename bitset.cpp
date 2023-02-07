#include <iostream>
#include <cmath>

int bitset_arr_size(int &len);
unsigned long int* dynamic_bitset(int& len);

class Bitset {
public:
	//set function will change a value of single bit to 1
	void set(int index,unsigned long int* ptr) {
		int index_of_arr_element = index / (sizeof(unsigned long int) * 8);
		ptr[index_of_arr_element] |= (1 << (index % (sizeof(unsigned long int) * 8)));
	
	}


	// reset function will reset value of singl bit to 0
	void reset(int index, unsigned long int* ptr){
		int index_of_arr_elements = index/(sizeof(unsigned long int)*8);
		ptr[index_of_arr_elements] &= ~(1 << (index % (sizeof(unsigned long int)*8)));		
	
	}
	
	// flip function will reset all elements value to 0
	void flip (unsigned long int* ptr, int &len){
		int size = bitset_arr_size(len);
		while(size > 0) {
			*(ptr+size-1)&=0;
			--size;
		}
	}
};

int main() {
	std::cout << "Please, enter the length of bitvector" << std::endl;
	int len = 0;
	std::cin >> len;

	unsigned long int* bitset = dynamic_bitset(len);//memory allocation
	Bitset b;
	b.set(64, bitset);
	b.set(65, bitset);
	b.set(10,bitset);
 	b.reset(65,bitset);
	b.flip(bitset, len);

	
	delete[] bitset; //free memory 

	return 0;
}

//this function represents amount of array elements for making bitset conteiner
int bitset_arr_size(int &len) {
	return ceil((double)len / (sizeof(unsigned long int) * 8));
}


//dynamic bitset conteiner maker
unsigned long int* dynamic_bitset(int &len) {
	int size = bitset_arr_size(len);
	unsigned long int* bitset = new unsigned long int[size] {0};
	return bitset;
}
