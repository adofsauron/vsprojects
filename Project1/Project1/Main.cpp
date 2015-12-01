#include <iostream>
using namespace std;

class animal
{
protected:
	int age_;
	animal(int age) : age_(age) { }

public:
	virtual void print_age(void) = 0;
	virtual void print_kind() = 0;
	virtual void print_status() = 0;
};

class dog : public animal
{
public:
	dog() : animal(2) { }
	~dog() { }

	virtual void print_age(void) {
		cout << "Woof, my age = " << age_ << endl;
	}

	virtual void print_kind() {
		cout << "I'm a dog" << endl;
	}

	virtual void print_status() {
		cout << "I'm barking" << endl;
	}
};

class cat : public animal
{
public:
	cat() : animal(1) { }
	~cat() { }

	virtual void print_age(void) {
		cout << "Meow, my age = " << age_ << endl;
	}

	virtual void print_kind() {
		cout << "I'm a cat" << endl;
	}

	virtual void print_status() {
		cout << "I'm sleeping" << endl;
	}
};

void print_random_message(void* something) {
	cout << "I'm crazy" << endl;
}

int main(void)
{
	cat kitty;
	dog puppy;
	animal* pa = &kitty;

	intptr_t* cat_vptr = *((intptr_t**)(&kitty));
	intptr_t* dog_vptr = *((intptr_t**)(&puppy));

	intptr_t fake_vtable[] = {
		dog_vptr[0],         // for dog::print_age
		cat_vptr[1],         // for cat::print_kind
		(intptr_t)print_random_message
	};
	*((intptr_t**)pa) = fake_vtable;

	pa->print_age();    // Woof, my age = 1
	pa->print_kind();   // I'm a cat
	pa->print_status(); // I'm crazyg

	getchar();

	return 0;
}
