#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool arrayPartition(vector<int> v)
{
    /**
    Cand impartim elementele primului vector in ceilalti doi vectori astfel incat media sa ramane aceeasi,
    mediile celor trei vectori vor fi egale.
    Asadar, daca gasim un subvector care sa aiba media egala cu vectorul de intrare, atunci am rezolvat problema.
    **/
    int len = v.size(); // Obtinem numarul de elemente din vector
    int arraySum = 0;

    for(int i = 0; i < len; i++)
        arraySum += v[i]; // Calculam suma tuturor elementelor din vector

    bool k = false;
    int halfLen = len / 2;

    for (int i = 1; i <= halfLen && k == false; i++) {
        if ((arraySum * i) % len == 0) // Verificam daca putem imparti suma totala a vectorului in i parti egale
            k = true;                  // Daca gasim ca se poate, atunci ne oprim
    }

    if (k == false)    // Daca nu am reusit sa impartim suma totala a vectorului, atunci nu vom gasi niciun set de partitii
        return false;

    vector<vector<bool>> u(arraySum + 1, vector<bool>((len / 2) + 1));
    //Folosim o matrice pentru a salva starea curenta a problemei
    //Cu u[i][j] indicam daca putem forma suma i din j elemente ale vectorului de intrare
    u[0][0] = true; // Setam u[0][0] pe true, deoarece putem scrie 0 ca suma de 0 elemente
    int a;

    //Folosim formula de recurenta u[j][l] = u[j][l] || u[j-a][l-1], deoarece cu u[j][l] verificam daca putem obtine suma j din l elemente,
    //fara a introduce si elementul curent a in subvector, iar u[j-a][l-1] presupune ca putem scrie suma j-a cu l-1 elemente,
    //daca introducem si elementul curent a in subvector
    for(int i = 0; i < len; i++) {
        a = v[i];
        for(int j = arraySum; j >= a; j--) {
            for(int l = 1; l <= len / 2; l++) {
                u[j][l] = u[j][l] || u[j-a][l-1];
            }
        }
    }

    //Daca gasim un i pentru care u[(arraySum*i)/len][i] e true, asta inseamna ca putem imparti vectorul in doi subvectori care
    //sa aiba mediile egale
    //Daca nu gasim nicio valoare de true, atunci insemna ca partitia nu este posibila si returnam false
    //Putem verifica cu i pana la len/2 deoarece daca exista o partitie a vectorului cu i elemente, atunci exista si o partitie cu n-i elemente
    for(int i = 1 ; i <= len/2; i++) {
        if((arraySum * i) % len == 0 && u[(arraySum * i) / len][i])
            return true;
    }

    return false;
}


int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8};

    if(arrayPartition(v) == 1)
        cout << "True!";
    else
        cout << "False!";

    return 0;
}
