#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
int main(){
    int puffer[11];
    std::cout << "please enter 11 numbers" << std::endl;
    for(int i = 0; i< 11; i++){
        std::cin>> puffer[i];
    }
    for(int i = 10; i>=0; i--){
        double result = pow(abs(puffer[i]), 0.5) + 5* pow(puffer[i], 3);

        if(result > 400){
            std::cout << puffer[i] << "\t" << "too big" << std::endl;
        }
        else if(result <=400){
            std::cout << puffer[i]<< ":\t" << result << std::endl;
        }
    }


}
