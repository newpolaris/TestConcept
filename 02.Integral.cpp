// https://blogs.msdn.microsoft.com/vcblog/2017/02/22/learn-c-concepts-with-visual-studio-and-the-wsl/

#include <iostream>
#include <type_traits>

template <class T>
concept bool Integral = std::is_integral<T>::value;

template <class T>
concept bool SignedIntegral = Integral<T> && T(-1) < T(0);

template <class T>
concept bool UnsignedIntegral = Integral<T> && T(0) < T(-1);

template <class T>
void f(T const& t) {
	std::cout << "Not integral: " << t << '\n';
}

void f(Integral) = delete;
 
void f(SignedIntegral i) {
    std::cout << "SignedIntegral: " << i << '\n';
}
 
void f(UnsignedIntegral i) {
    std::cout << "UnsignedIntegral: " << i << '\n';
}
 
int main() {
    f(42);
    f(1729u);
    f("Hello, World!");
    enum { bar };
    f(bar);
    f('a');
    f(L'a');
    f(U'a');
    f(true);
}
