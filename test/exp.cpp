#include <iostream>

int fibo(int initial_1, int initial_2, int iter_num);

int main()
{
    std::cout << "hello world" << std::endl;
    int input_1 = 0;
    int input_2 = 0;
    int input_3 = 0;
    std::cin >> input_1 >> input_2 >> input_3;
    std::cout << fibo(input_1, input_2, input_3) << std::endl;
    return 0;
};
int fibo(int initial_1, int initial_2, int iter_num)
{
    int x = initial_1;
    int x_next = initial_2;
    for (int i = 0; i < iter_num; ++i)
    {
        int sum = x + x_next;
        x = x_next;
        x_next = sum;
        std::cout << x << std::endl;
    }
    return x_next;
}