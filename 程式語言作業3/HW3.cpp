#include <iostream>
using namespace std;

class int_array_cell
{
private:
    int _counter;
    int* _memory;

public:
    int_array_cell(int* _memory)
    {
        this->_memory = _memory;
        this->_counter = 1;
    }

    int decrease()
    {
        this->_counter--;
        if (this->_counter == 0)
        {
            cout << "int_array_cell counter " << this->_counter << ": deleted" << endl;
            delete[] this->_memory;  
            return 0;
        }
        return 1;
    }

    void increase()
    {
        this->_counter++;
    }

    int getCounter()
    {
        return this->_counter;
    }

    int& getMemory(int index)
    {
        return this->_memory[index];
    }
};

class counter_ptr
{
private:
    char* _name;
    int_array_cell* _cell_ptr;

public:
    counter_ptr(char* _name, int* memory)
    {
        this->_name = _name;
        this->_cell_ptr = new int_array_cell(memory);
        cout << "int_array_cell is allocated" << endl;
        cout << "counter_ptr " << this->_name << " is assigned to an int_array_cell: counter " << this->_cell_ptr->getCounter() << endl;
    }

    ~counter_ptr()
    {
        cout << "counter_ptr " << this->_name << " is deleted" << endl;
        int count;
        if (this->_cell_ptr)
        {
            count = this->_cell_ptr->decrease();
        }
        if(count)
        {
        	cout << "int_array_cell counter is decreased: counter " << this->_cell_ptr->getCounter() << endl;       	
		}
        this->_cell_ptr = nullptr;
    }

    counter_ptr(char* _name)
    {
        this->_name = _name;
        this->_cell_ptr = nullptr;
        cout << "counter_ptr " << this->_name << " is not assigned to an int_array_cell" << endl;
    }

    void release()
    {
        if (this->_cell_ptr)
        {
            this->_cell_ptr->decrease();
            cout << "int_array_cell counter is decreased: counter " << this->_cell_ptr->getCounter() << endl;
            this->_cell_ptr = nullptr;
            cout << "counter_ptr " << this->_name << " is not assigned to an int_array_cell" << endl;
        }
    }

    counter_ptr& operator=(int* new_Memory)
    {
        if (this->_cell_ptr)
        {
            this->_cell_ptr->decrease();
        }
        this->_cell_ptr = new int_array_cell(new_Memory);
        cout << "int_array_cell is allocated" << endl;
        cout << "counter_ptr " << this->_name << " is assigned to an int_array_cell: counter " << this->_cell_ptr->getCounter() << endl;
        return *this;
    }

    counter_ptr& operator=(const counter_ptr& other)
    {
        if (this != &other)
        {
            if (this->_cell_ptr)
            {
                this->_cell_ptr->decrease();
            }
            this->_cell_ptr = other._cell_ptr;
            this->_cell_ptr->increase();
            cout << "int_array_cell counter is increased: counter " << this->_cell_ptr->getCounter() << endl;
            cout << "counter_ptr " << this->_name << " is assigned to an int_array_cell: counter " << this->_cell_ptr->getCounter() << endl;
        }
        return *this;
    }

    int& operator[](int index)
    {
        return this->_cell_ptr->getMemory(index);
    }
};
 
int main()
{

// PART 一  (35分)
 
      counter_ptr b("b", new int[10]);  //需要撰寫 counter_ptr constructor(建構子) 接受兩個參數
	// stdout 輸出: int_array_cell is allocated
	// stdout 輸出: counter_ptr b is assigned to an int_array_cell: counter 1

			{

				b = new int[100]; 	//需要撰寫 counter_ptr operator=
				// stdout 輸出: int_array_cell counter 0: deleted
				// stdout 輸出: int_array_cell is allocated
				// stdout 輸出: counter_ptr b is assigned to an int_array_cell: counter 1

				counter_ptr a("a");	//需要撰寫 counter_ptr constructor(建構子) 接受一個參數
				// stdout 輸出: counter_ptr a is not assigned to an int_array_cell

				a = b;			//需要撰寫 counter_ptr operator= 
				// stdout 輸出: int_array_cell counter is increased: counter 2
				// stdout 輸出: counter_ptr a is assigned to an int_array_cell: counter 2

			}
			// a leaves it scope:	//需要撰寫 counter_ptr destructor
			// stdout 輸出: counter_ptr a is deleted
			// stdout 輸出: int_array_cell counter is decreased: counter 1


// PART 二  (35分)

			for(int i=0; i<10; i++)
				b[i] = i;  //需要撰寫 counter_ptr operator[] 寫值(回傳資料的參考 return type: int &)

			for(int i=0; i<10; i++)      
				cout << b[i] << ' ';    //需要撰寫 counter_ptr operator[] 讀值(回傳資料)
				cout << endl;    
 			// stdout 輸出: 0 1 2 3 4 5 6 7 8 9

      			counter_ptr c("c");
			// stdout 輸出: counter_ptr c is not assigned to an int_array_cell

			c = b;
			// stdout 輸出: int_array_cell counter is increased: counter 2
			// stdout 輸出: counter_ptr c is assigned to an int_array_cell: counter 2

			b.release();			//需要撰寫 counter_ptr release function: 不使用記憶體
			// stdout 輸出: int_array_cell counter is decreased: counter 1
			// stdout 輸出: counter_ptr b is not assigned to an int_array_cell

}
			// c leaves it scope:	//需要撰寫 counter_ptr destructor
			// stdout 輸出: counter_ptr c is deleted
			// stdout 輸出: int_array_cell counter 0: deleted
			// stdout 輸出: counter_ptr b is deleted





/*
PART 三 (30分)
	1) 用 template 改寫 class counter_ptr int_array_cell
	2) 重覆 PART 一  二 的測試
*/








