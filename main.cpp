#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;
//double factor(int n);
void words(int mindim, int maxdim, string alphabet, int oldcounts[]);

int main(int argc, char ** argv)
{
    int mindim = 1;
    int maxdim = 3;
    string alphabet = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_.";

    if (argc>=3) {
        mindim = atoi(argv[1]);
        maxdim = atoi(argv[2]);
    }

    int counts[mindim]; //contains the charachter I'm working on for every element of the string
    for (int c = 0; c<mindim; c++){
        counts[c] = 0;
    }

    if (argc>=4) {
        string startstr = string(argv[3]);
        for (int c = 0; c<mindim; c++){
            counts[c] = alphabet.find_first_of(startstr[c]);
        }
    }

    if (argc>=5) {
        alphabet = string(argv[4]);
    }

    if (argc<3) {
        cout << "Usage: bf-words mindim maxdim startingstring alphabet operations" << endl;
        cout << "The first two arguments are mandatory, the others not." << endl;
        cout << "Startingstring is the word from which you would like to start generating other words. This is useful to resume a process: you can start generating words, stop the process, and then resume it from the last generated word. It is also useful to distribuite the work over different computers." << endl;
        cout << "The operations argument is used to do some. For example, if it is 'calc' then the program will tell you something about the number of words that will be generated." << endl;
        cout << "Examples: " << endl;
        cout << "./bf-words 1 5 > temp.txt " << endl;
        cout << "./bf-words 6 6 jtuuaq > temp.txt " << endl;
        cout << "./bf-words 1 3 jtuuaq qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_. > temp.txt " << endl;
        cout << "./bf-words 1 4 jtuuaq qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_. calc " << endl;
    } else {
        if (argc < 6) words(mindim, maxdim, alphabet, counts);
    }

    if (argc>=6) {
        string operation = string(argv[5]);
        if (operation == "calc"){
            int n = alphabet.length();
            double total = 0;
            for (int k = mindim; k<(maxdim+1); k++){
                double iters = pow(n,k);
                cout << "With " << n << " symbols will be created " << iters << " words of " << k << " characters." << endl;
                double dim = (iters*(k+1)); //the dimension of the file is done multipling the number of characters for every line, included the endl char.
                cout << "With " << dim << " bytes of data." << endl;
                total = total + dim;
            }
            cout << "In total, there will be " << total << " bytes of data (which are " << (total/(1024*1024)) << "MB)." << endl;
        }
    }


    return 0;
}

void words(int mindim, int maxdim, string alphabet, int oldcounts[]){
    int n = alphabet.length();
    for (int k = mindim; k<(maxdim+1); k++){
        double iters = 0;
        //iters = factorD(n)/factorD(n-k);  //this is if we do not consider repetitions
        iters = pow(n,k); //this is if we consider repetitions
        int counts[k]; //contains the charachter I'm working on for every element of the string
        if (k != mindim) {
            for (int c = 0; c<k; c++){
                counts[c] = 0;
            }
        } else {
            for (int c = 0; c<k; c++){
                counts[c] = oldcounts[c];
            }
        }
        for (double l = 0; l<iters; l++){
            //executing for every possible disposition
            string temp;
            temp.resize(k);
            //changing only the first char, then I ++ the second one, and change again the first. So on.
            for (int c = 0; c<k; c++){
                temp[c] = alphabet[counts[c]];
            }
            int augment = 0;
            for (int c = 0; c<k; c++){
                if (c==0) {
                    if (counts[c]==(n-1)) augment = 1;  //the first char have been changed with every alphabet simbol, so we need to change the next char
                    counts[c] = ((counts[c]+1)%n);
                } else {
                    int chain = 0;
                    if (counts[c]==(n-1) && augment == 1) chain = 1;
                    counts[c] = ((counts[c]+augment)%n);
                    augment = 0;
                    if (chain == 1) augment = 1;
                }
            }
            cout << temp.c_str() << endl;
        }
    }



}

/*
double factor(int n) {
    double temp = 1;
    for (int i = 1; i<(n+1); i++) {
        temp = temp*i;
    }
    return temp;
}
*/
