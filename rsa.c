#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*NOTE: current random generation not cryptographically secure
 * because... this is just to see if I can write this actual security
 * isn't a high priority */

/* returns the gcd of the given numbers */
long gcd(long,long,long*);

/* O(log(pow)) moduler exponentiation;
 * cannot mandle negative exponents */
long powMod(long base, long pow, long mod);

/* modular multiplicaiton;
 * implement karatsuba's */
long mulMod(long, long, long mod);

/* returns the two keys, , generated based on the given primes
 * use ints so we can fit the product in a long
 * takes the array to put answers into */
void makeKeys(long* keys, int p, int q);


//MAIN
int main(int argc, char* argv[]){
    //random setup
    srand(time(NULL));
    //vars
    long keys[3];
    makeKeys(keys, 49979693, 613651369); //currently just makes new keys for every sim
    long ms = 1951997; //message sent
    //run a simulation
    long c = powMod(ms,keys[0],keys[2]); //cyphertext
    long mr = powMod(c,keys[1],keys[2]); //message recieved
    //output
    printf("Using keys: %ld, %ld, %ld\n", keys[0], keys[1], keys[2]);
    printf("Sent: %ld\nCyphertext: %ld\nRecieved: %ld\n",ms,c,mr);
    //cleanup
    return 0;
}


//FUNCTION IMPLEMENTATIONS
void makeKeys(long* keys, int p, int q){
    long pl = p; long ql = q; //convert to long for upcoming arithmatic
    keys[2] = pl*ql; //n
    long phi_n = (pl-1)*(ql-1); 
    do{
        //generate a long random number < phi_n and > 0
        do{
            keys[0] = rand();
            keys[0] = (keys[0] << sizeof(int)) | rand();
            keys[0] %= phi_n;
        }while(keys[0] <= 0); //prevents landing on 0 (an illegal key), while keeping even distrobution
        printf("Trying keys: %ld, %ld; Phi(n): %ld\n", keys[0], keys[2], phi_n);
    }while(gcd(phi_n,keys[0],keys+1) != 1); //test that is mutually prime to phi
                                            //if it is, capture the inverse in the correct place
    printf("Found keys\n");
}

long gcd(long a, long b, long* inverse){
    if(b > a){ //a will always be bigger; kinda actually problematic having this... :S
        long swap = a;
        a = b;
        b = swap;
    }
    long a_i = a; //save the intiial vlaue of a for finding the inverse
    long inv[2] = {1l,0l}; //inverse of b mod a
    long r = 1; //remainder; start with > 0 placeholder
    //run the algorithm
    while(r){
        r = a%b; 
        long swap = inv[0];
        inv[0] = inv[1] - (a/b)*inv[0];
        inv[1] = swap;
        //printf("%ld,%ld\n",inv[0],inv[1]);
        a = b;
        b = r;
    }
    if(inverse){
        *inverse = inv[1] % a_i;
        if(*inverse < 0) *inverse += a_i; //prevent negative outcomes
    }
    //printf("%ld %% %ld -> %ld, %ld\n",inv[1],  a_i, inv[1] % a_i, *inverse);
    return a; //because the algorithm gives us one last shift over
}

long powMod(long base, long pow, long mod){
    long r = 1; //acculator; starts at the identity
    long a = base; //accumates the current power
    long p; //just a copy of pow we can play with
    for(p = pow; p; p >>= 1){ //for each power of two
        //printf("working...%ld\n",p); 
        if(1 & p){
            r = mulMod(r,a,mod); //if this power adds into the number, account for it
            printf("r: %ld\n",r);
        }
        a = mulMod(a,a,mod); //move up to 2^the next power
        printf("a: %ld\n",a);
    }
    return r;
}

long mulMod(long a, long b, long mod){
    long m = 1 << (sizeof(long)/2 - 1);
    long a1 = a / m;
    long a2 = a % m;
    long b1 = b / m;
    long b2 = b % m;
    long f = (a1 * b1) % mod;
    long g = (a2 * b2) % mod;
    long h = ((a1+a2) * (b1+b2)) % mod;
    long k = h - f - g;
    printf("f %ld, g %ld, h %ld, k %ld\n", f, g, h, k);
    return (f*m*m + k*m + g) % mod;
}
