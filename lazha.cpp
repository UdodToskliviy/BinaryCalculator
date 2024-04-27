#include<iostream>

void printBin(int num){
        for(int i = sizeof(int) * 8 - 1; i >= 0; --i){
                std::cout << ((num >> i) & 1);
                //std::cout << bit;
        }
        std::cout << std::endl;
}

int invert(int num, int depth){
        int mask = 1;
        for(int i = 0; i < depth; i++){
                num ^= (mask << i);
        }
        return num;
}


int signChange(int num, int depth){
        if((num << (depth - 1) & 1) == 1){
                return invert(num - 1, depth);
        }
        return invert(num, depth) + 1;
}

int convertToBin(int num, int depth){;
	int res = 0;
	bool sign = false;
	if(num < 0){
		sign = true;
		num = signChange(num, sizeof(int) * 8);
	}
	int mask = 1;
	for(int i = 0; i < depth - 1; i++){
		if(num % 2 == 1){
			res ^= mask;
		}
		mask = (mask << 1);
		num /= 2;
	}
	if(num != 0){
		std::cout << "ERR" << std::endl;
	}
	if(sign == 1){
		return signChange(res, depth);
	}
	return res;
}

int convertToDecimal(int num, int depth){
	bool sign = false;
	int res = 0;
	if((num >> depth - 1) == 1){
		sign = true;
	}
	if(sign){
		num = signChange(num, depth);
		num = signChange(num, sizeof(int) * 8);
		return num;
	}
	return num;
}

int altConvert(int num, int depth){
	bool sign = false;
	int res = 0;
	if((num >> depth - 1) == 1){
		sign = true;
		num = signChange(num, depth);
	}
	for(int i = depth - 2; i >=0; --i){
		res += ((num >> i) & 1);
		res *= 2;
	}
	res /= 2;
	if(sign){
		return signChange(res, sizeof(int) * 8);
	}
	return res;
}

int add(int a, int b, int bitSize){
	int carry = 0;
	int res = 0;

	for(int i = 0; i < bitSize; i++){
		int aBit = ((a >> i) & 1);
		int bBit = ((b >> i) & 1);
		int sumBit = aBit ^ bBit ^ carry;
		carry = (aBit & bBit) | (aBit & carry) | (bBit & carry);
		res |= (sumBit << i);
	}
	if((a >> bitSize - 1) == (b >> bitSize - 1)){
		if(((a >> bitSize - 1) & 1) == 0 && ((res >> bitSize - 1) & 1) == 1){
			throw "owerflow ERR";
		}
		if(((a >> bitSize - 1) & 1) == 1 && ((res >> bitSize - 1) & 1) == 0){
			throw "owerflow ERR";
		}
	}
	return res;
}

int subtract(int a, int b, int bitSize){
	b = signChange(b, bitSize);
	return add(a, b, bitSize);
}

int multiply(int a, int b, int bitSize){
	int res = 0;
	int sign = ((a >> bitSize - 1) & 1) ^ ((b >> bitSize - 1) & 1);
	if(((a >> bitSize - 1) & 1) == 1){
		a = signChange(a, bitSize);
	}
	if(((b >> bitSize - 1) & 1) == 1){
		b = signChange(b, bitSize);
	}
	for(int i = 0; i < bitSize; i++){
		int bBit = ((b >> i) & 1);
		try{
			if(bBit == 1){
				res = add(res, (a << i), bitSize);
			}
		}
		catch(...){
			throw "another err";
			break;
		}
	}
	if(sign == 1){
		res = signChange(res, bitSize);
	}
	return res;
}


int main(){
	const int depth = 8;
	const int reserve = 0;
	int a = -10;
	int b = 12;
	printBin(a);
	printBin(b);
	a = convertToBin(a, depth + reserve);
	printBin(a);
	b = convertToBin(b, depth + reserve);
	printBin(b);
	try{
		std::cout << altConvert(multiply(b, a, depth), depth) << std::endl;
	}
	catch(...){
		std::cout << "err occured" << std::endl;
	}
/*	printBin(subtract(b, a, 6));
	std::cout << multiply(a, b, 6) << std::endl;
	printBin(multiply(a, b, 6));
	*/
}
