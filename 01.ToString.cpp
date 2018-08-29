// https://gist.github.com/jeb2239/2c816f0bc75f4a823acb1eb3c55fe286

#include <iostream>
#include <string>
#include <locale>
#include <cassert>
#include <list>
#include <vector>

using namespace std::literals;
using namespace std;

// Declaration of the concept "EqualityComparable", which is satisfied by
// any type T such that for values a and b of type T,
// the expression a==b compiles and its result is convertible to bool

template <typename T>
concept bool EqualityComparable = requires(T a, T b) {
	{ a == b } -> bool;
};

// declaration of a constrained function template
template<typename T>
void f(T&&) requires EqualityComparable<T>; // long form of the same
 

// forces you to implement to_string method
template <typename T>
concept bool Stringable = requires(T a)
{
	{ a.to_string()} -> string;
};

template<typename T>
concept bool HasStringFunc = requires(T a)
{
	{ to_string(a)} -> string;  // has a to_string function which returns a string
};

struct Person 
{
	double height;
	int weight;
	
	Person(double a, int b) : height(a), weight(b)
	{
	}

	string to_string()
	{
		return "Weight: " + std::to_string(height) + " Height: " + std::to_string(weight);
	}
};

void pretty_print(Stringable a)
{
	//we know that if the compiler made it this far we are good to go.
	cout << a.to_string() << endl;
}

void pretty_print(HasStringFunc a){
	cout << to_string(a) <<endl;
}

namespace std {

string to_string(list<int> l){
	//better ways to do this but just as example
	string s = "";
	for(int a : l ){
		s+=(" "+to_string(a)+" ");
	}
	return s;
}

string to_string(std::vector<int> v){
	string s = "";
	for(int a : v ){
		s+=(" "+to_string(a)+" ");
	}
	return s;
}

}

int main()
{
	assert(__cpp_concepts >= 201500); // check compiled with -fconcepts
	assert(__cplusplus >= 201500); //check compiled with --std=c++1z

	Person jonathan(5.7, 130);

	pretty_print(jonathan); // uses concept overload pretty_print(Stringable a)
	pretty_print(3); //uses concept overload pretty_print(HasStringFunc a) 

	std::list<int> l { 1, 2, 3 };
	std::vector<int> v { 34, 23, 34, 56, 78 };
	pretty_print(l);
	pretty_print(v);
}
