// TODO: implement Sieve of Eratosthenes
#include <vector>
#include <error.h>
#include <chrono>
#include <string.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <omp.h>

using std::vector;


//find whether the number is Prime
bool isPrime(int n){
    for(int i=2;i<n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}



int main(int argc, char * argv[]){
    //added time to find out how fast the program runs
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    start_time = std::chrono::high_resolution_clock::now();

    if (argc < 2) error(1, 0,
                        "Missing argument. "
                        "Please supply the number up to which you want to find prime numbers.");
    //get ahold of the number                    
     int num = std::stoi(argv[1]);


    //create a boolean aray with all "true" values
    bool prime[1000009];
    memset(prime,true,sizeof(prime));

    int p=2;
    for(p =2; p*p<num; p++){
        //find prime numbers before square root of num
        prime[p]=isPrime(p);
    }

    //parallelize with pragma the process of finding 
    //not prime numbers with the help of seed 
    #pragma omp parallel for num_threads(8) schedule(static)
    for(int i=p;i<=num;i++){
        
        //for cycle for the seed
        for(int j =2; j*j<num; j++){
            if(prime[j] && i%j==0){
                prime[i]=false;
            }
        }
    }
    
    
    
    for (int i = 2; i<num;i++){
        //print prime numbers
        if(prime[i]==true) std::cout<<i<<" ";
    }
    //print the duration
    end_time = std::chrono::high_resolution_clock::now();
    std::cout<<std::endl<<"Duration: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count()<<" ms"<<std::endl;
}