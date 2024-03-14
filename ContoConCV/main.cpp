#include <iostream>

#include "random"
#include "thread"
#include "mutex"
#include "condition_variable"
#include "chrono"



using namespace std;


condition_variable cv;
mutex ml;
int conto = 0;



void AggiungiSoldi(){

    this_thread::sleep_for(chrono::seconds(2));
    lock_guard<mutex> lock(ml);

    conto += 1000;

    cout << "ho aggiunto un milli al conto" << endl;
    cout << "saldo attuale: " << conto << endl;

    cv.notify_one();

}

void Preleva(int conto, int soldi){
    unique_lock<mutex> lock(ml);
    cv.wait(lock,  [conto] {
        if(conto <= 0){
            cout << "POVERIIII" << endl;
            return true;
        }
        else{
            cout << "prelevo: " << soldi << " euro" << endl;
            conto -= soldit;
            return false;
        }


    });

    


}



int main() {


    int n = random()%1000 + 1;
    
    thread th1(AggiungiSoldi);
    thread th2(Preleva, ref(conto), n);

    th1.join();
    th2.join();
    return 0;
}

