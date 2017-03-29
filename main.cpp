#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

void wczytaj (double **tab, int n) {
    char plik[30];
    bool CzyOtworzono = true;
    do {
        cout << "Podaj nazwe pliku, w ktorym zawarte sa wspolczynniki ukladu rownan:" << endl;
        cin >> plik;
        fstream source;
        source.open(plik, ios_base::in);
        if (source.good()) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n + 1; j++)
                    source >> tab[i][j];
            source.close();
            CzyOtworzono = true;
        } else {
            cout << "Blad. Nie znaleziono pliku. Prosze podac inna nazwe pliku." << endl;
            CzyOtworzono = false;
        }
    } while(!CzyOtworzono);
}
//void Zamien (double **tab, int n, int nr) {
//    int mx = nr;
//    for (int i = nr; i < n; i++) {
//        if (abs(tab[mx][nr]) < abs(tab[i][nr])) mx = i;
//    }
//    double *tab1 = new double [n + 1];
//    for (int i = 0; i <= n; i++) {
//        tab1[i] = tab[mx][i];
//        tab[mx][i] = tab[nr][i];
//        tab[nr][i] = tab1[i];
//    }
//    delete []tab1;
//}
void Wyswietl (double **tab, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << setw(10) << tab [i][j] << '\t';
        }
        cout << endl;
    }
}
//void Przybl (double **tab, int n) {
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j <= n; j++) {
//            if (abs(tab[i][j]) < 0.000000001)
//                tab[i][j] = 0;
//        }
//    }
//}
void Jacobi(double **tab, int n, bool &sprzeczny, bool &nieoznaczony, double *result) {
    bool end=false;
    int k=0;
    while(k<1000)
    {
        for(int i=0;i<n;i++)
        {
            double z=0;
            for(int j=0;j<n;j++)
            {
                if(i!=j)z=z+tab[i][j]*result[j];
            }
            result[i]=(1.0/tab[i][i])*(tab[i][n] -z);
        }
        k++;
    }
}

int main()
{
    char wybor;
    int n;
    double **tab;
    do {
        bool sprzeczny = false;
        bool nieoznaczony = false;
        cout << "Program rozwiazuje uklad dowolnej ilosci rownan za pomoca metody Jacobiego. Wspolczynniki poszczegolnych rownan sa wczytywane z pliku.\n" << endl;
        cout << "Wprowadz liczbe rownan: ";
        while (!(cin >> n)) {
            cin.clear();
            cin.sync();
        }
        tab = new double* [n];
        for (int i = 0; i < n; i++)
            tab[i] = new double [n + 1];
        wczytaj(tab, n);
        system("cls");
        cout << "Uklad ten w postaci macierzowej wyglada nastepujaco:" << endl;
        Wyswietl(tab,n);
        cout << endl;
        //----
        double *result=new double[n];
        for(int i=0;i<n;i++)
        {
            result[i]=0;
        }
        Jacobi(tab, n, sprzeczny, nieoznaczony,result);
        for(int i=0;i<n;i++)
        {
            cout<<result[i]<<endl;
        }
        //-----
        cout << "Po sprowadzeniu do postaci macierzy jednostkowej przy uzyciu metody Gaussa-Jordana, macierz ta ma nastepujaca postac:"<<endl;
        Wyswietl(tab, n);
        cout << endl;
        cout << "Rozwiazanie ukladu rownan:" << endl;
        if (sprzeczny == true) {
            cout << "Uklad rownan jest sprzeczny" << endl;
        } else if (nieoznaczony == true) {
            cout << "Uklad rownan jest nieoznaczony." << endl;
        } else {
            cout << "Rozwiazania ukladu rownan sa nastepujace:" << endl;
            for (int i = 0; i < n; i++) {
                cout << "x" << i + 1 << " = " << tab[i][n] << endl;
            }
        }
        //------------------------------------------------------------------------
        cout << "Czy chcesz wykonac obliczenia dla innego ukladu rownan? (t/n)" << endl;
        cin >> wybor;
        system("cls");
    }
    while (wybor == 't' or wybor == 'T');
    for (int i = 0; i < n; i++) {
        delete []tab[i];
    }
    delete []tab;
}
