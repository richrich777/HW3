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

// PART �@  (35��)
 
      counter_ptr b("b", new int[10]);  //�ݭn���g counter_ptr constructor(�غc�l) ������ӰѼ�
	// stdout ��X: int_array_cell is allocated
	// stdout ��X: counter_ptr b is assigned to an int_array_cell: counter 1

			{

				b = new int[100]; 	//�ݭn���g counter_ptr operator=
				// stdout ��X: int_array_cell counter 0: deleted
				// stdout ��X: int_array_cell is allocated
				// stdout ��X: counter_ptr b is assigned to an int_array_cell: counter 1

				counter_ptr a("a");	//�ݭn���g counter_ptr constructor(�غc�l) �����@�ӰѼ�
				// stdout ��X: counter_ptr a is not assigned to an int_array_cell

				a = b;			//�ݭn���g counter_ptr operator= 
				// stdout ��X: int_array_cell counter is increased: counter 2
				// stdout ��X: counter_ptr a is assigned to an int_array_cell: counter 2

			}
			// a leaves it scope:	//�ݭn���g counter_ptr destructor
			// stdout ��X: counter_ptr a is deleted
			// stdout ��X: int_array_cell counter is decreased: counter 1


// PART �G  (35��)

			for(int i=0; i<10; i++)
				b[i] = i;  //�ݭn���g counter_ptr operator[] �g��(�^�Ǹ�ƪ��Ѧ� return type: int &)

			for(int i=0; i<10; i++)      
				cout << b[i] << ' ';    //�ݭn���g counter_ptr operator[] Ū��(�^�Ǹ��)
				cout << endl;    
 			// stdout ��X: 0 1 2 3 4 5 6 7 8 9

      			counter_ptr c("c");
			// stdout ��X: counter_ptr c is not assigned to an int_array_cell

			c = b;
			// stdout ��X: int_array_cell counter is increased: counter 2
			// stdout ��X: counter_ptr c is assigned to an int_array_cell: counter 2

			b.release();			//�ݭn���g counter_ptr release function: ���ϥΰO����
			// stdout ��X: int_array_cell counter is decreased: counter 1
			// stdout ��X: counter_ptr b is not assigned to an int_array_cell

}
			// c leaves it scope:	//�ݭn���g counter_ptr destructor
			// stdout ��X: counter_ptr c is deleted
			// stdout ��X: int_array_cell counter 0: deleted
			// stdout ��X: counter_ptr b is deleted





/*
PART �T (30��)
	1) �� template ��g class counter_ptr int_array_cell
	2) ���� PART �@  �G ������
*/








