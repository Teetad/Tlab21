#include <iostream>
#include <cstdlib>

int main(int num,char* input[]){
    if (num < 2)
    {
        std::cout << "Please input numbers to find average.";
        return 0;
    }else{
        double a;
        double b; 
        for (int i = 1; i < num; i++){
            a = atof(input[i]);
            b += a;
        }
        b = b/(num-1);
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Average of "<< (num-1)<< " numbers = " << b << std::endl;
        std::cout << "---------------------------------" << std::endl;    
    }

}
