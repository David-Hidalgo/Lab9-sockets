#include <iostream>
#include <print>



int main(int argc, char const *argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]: " << argv[i] << "\n";
    }
    std::cout << "Hello, from lab9-sockets!\n";
    std::println("Hello, from lab9-sockets! {}", 123);
    return 0;
}
