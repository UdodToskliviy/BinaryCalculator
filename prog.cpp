#include<iostream>
class number{
	public:
		int value;
		int binValue;

		void printValue(){
			std::cout << value << std::endl;
		}

		void printBinValue(int depth = sizeof(int) * 8){
			for(int i = depth - 1; i >= 0; --i){
                		std::cout << ((binValue >> i) & 1);
        		}
        		std::cout << std::endl;
		}

		void setValues(int a, int depth){
			try{
				value = a;
				binValue = convertToBin(a, depth);
			}
			catch(int err2){
				if(err2 == 2){
					throw 2;
				}
			}
		}

                int convertToDecimal(int num, int depth){
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
                                        throw 3;
                                }
                                if(((a >> bitSize - 1) & 1) == 1 && ((res >> bitSize - 1) & 1) == 0){
                                        throw 3;
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
                       		if(bBit == 1){
                               		res = add(res, (a << i), bitSize);
                       		}
        		}
        		if(sign == 1){
                		res = signChange(res, bitSize);
        		}
        		return res;
		}

	private:
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
                		throw 2;
        		}
        		if(sign == 1){
                		return signChange(res, depth);
        		}
        		return res;
		}
};



class calculator{
	public:
		const int bitDepth = 8;

		void setExpression(int n1, int n2, char op){
			a.setValues(n1, bitDepth);
			b.setValues(n2, bitDepth);
			if(op == '*' || op == '-' || op == '+'){
				operation = op;
			}
			else{
				throw 1;
			}
		}

		void printOfInput(){
			a.printValue();
			a.printBinValue();
			b.printValue();
			b.printBinValue();
			std::cout << operation << std::endl;
		}

		void calculate(){
			if(operation == '*'){
				a.binValue = a.multiply(a.binValue, b.binValue, bitDepth);
			}
			if(operation == '-'){
                                a.binValue = a.subtract(a.binValue, b.binValue, bitDepth);
                        }
			if(operation == '+'){
                                a.binValue = a.add(a.binValue, b.binValue, bitDepth);
                        }
			a.value = a.convertToDecimal(a.binValue, bitDepth);
		}

		void printResult(){
			std::cout << "Result of calculations is ";
			a.printValue();
			std::cout << "In binary, it is ";
			a.printBinValue(bitDepth);
		}
	private:
		number a;
		number b;
		char operation;
};

int main(){
	try{
		int a;
		int b;
		char operation;
		std::cout << "Please enter the expression \n";
		std::cin >> a >> operation >> b;
		if(std::cin.fail()){
			throw 1;
		}
		calculator c;
		c.setExpression(a, b, operation);
		c.calculate();
		c.printResult();
	}
	catch(int err){
		if(err == 1){
			std::cout << "Incorrect typpe of input. Please restart the programm with correct data \n";
		}
                if(err == 2){
                        std::cout << "Invalid size of input. Please give another expression \n";
                }
                if(err == 3){
                        std::cout << "Invalid size of answer. Please give another expression \n";
                }
	}
	catch(...){
		std::cout << "unknown error occured" << std::endl;
	}
	return 0;
}
