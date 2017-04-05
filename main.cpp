#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
void Wyswietl (double **tab, int n);
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
void Zamien (double **tab, int n, int nr, double *result, bool &nieobliczalny) {
    int mx = nr;
   // int mx2 =nr;
    double suma=0;
    double kolumna=0;
    double suma2=0;
  //  if(mx>=3) mx=0;
        for(int i=0; i<n; i++)
        {
                suma+=abs(tab[nr][i]);
                kolumna += abs(tab[i][nr]);
        }
    std::cout<<"Suma: "<<suma-abs(tab[nr][nr])<<"tab[nr][nr]"<<abs(tab[nr][nr])<<std::endl;
    std::cout<<"Suma: "<<kolumna - abs(tab[nr][nr])<<"tab[nr][nr]"<<abs(tab[nr][nr])<<std::endl;
    if(!(suma-abs(tab[nr][nr]) <= abs(tab[nr][nr]) || kolumna - abs(tab[nr][nr]) <= abs(tab[nr][nr])))
    {

        bool notover=true;
        int iteracje=0;
        while(notover) {

            if (kolumna - abs(tab[mx][nr]) <= abs(tab[mx][nr])) {
                notover = false;
                std::cout<<" Kolumna jest w porzadku, koncze"<<std::endl;
            } else {
                suma2=0;
                for (int i = 0; i < n; i++) {

                    suma2 += abs(tab[mx][i]);

                }
                if(suma2-abs(tab[mx][nr]) <= abs(tab[mx][nr]))
                {
                    notover=false;
                    std::cout<<" Rzad jest w porzadku, koncze"<<std::endl;
                }
                else
                {

                    std::cout<<" Nic nie dziala, wtf czemu to sie robi w nieskonczonosc: "<<mx<<std::endl;
                    std::cout<<"Suma = "<<suma2<<std::endl<<"tab[mx][nr] = "<<abs(tab[mx][nr])<<"A numer to: "<<nr<<std::endl;
                    Wyswietl(tab,n);
                    mx++;
                    if(mx>=3) mx=0;
                    iteracje++;
                    if (iteracje >20)
                    {
                        nieobliczalny=true;
                        return;
                    }
                }
            }
        }
    }
    std::cout<<" Nic nie dziala, wtf czemu to sie robi w nieskonczonosc: "<<mx<<std::endl;
    std::cout<<"Suma = "<<suma2<<std::endl<<"tab[mx][nr] = "<<abs(tab[mx][nr])<<"A numer to: "<<nr<<std::endl;
    Wyswietl(tab,n);
    double *tab1 = new double [n + 1];
    double tab2;
    tab2 = result[mx];
    result[mx]=result[nr];
    result[nr]=tab2;
    for (int i = 0; i <= n; i++) {
        tab1[i] = tab[mx][i];
        tab[mx][i] = tab[nr][i];
        tab[nr][i] = tab1[i];
    }
    delete []tab1;
}
void Wyswietl (double **tab, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << setw(10) << tab [i][j] << '\t';
        }
        cout << endl;
    }
}
void Jacobi(double **tab, int n, bool &sprzeczny, bool &nieoznaczony, double *result, int iteracje, double dokladnosc) {
    int k=0;

  //  if (iteracje==0) iteracje = INFINITY;
    bool osiagnieta_dokladnosc=false;
    double pomocnicza;
 //   bool niemoznaliczyc=false;
    for(int i=0; i<n; i++) {
    Zamien(tab,n,i,result,sprzeczny);
    }
    if(sprzeczny) return;
//    do
//    {
//       niemoznaliczyc=false;
//        for(int i=0;i<n; i++)
//        {
//            double suma=0;
//            double kolumna=0;
//            int j=0;
//            for(;j<n;j++)
//            {
//                if(i!=j)
//                {
//                    suma+=abs(tab[i][j]);
//                    kolumna+=abs(tab[j][i]);
//                }
//            }
//            if(tab[i][i]>=suma || tab[i][i]>=kolumna)
//            {
//
//            }
//            else
//            {
//                niemoznaliczyc=true;
////                int help;
////                if(i>0) help=i-1;
////                else help = 2;
//                Zamien(tab,n,i, result);
//            }
//        }
        Wyswietl(tab,n);
        std::cout<<std::endl<<std::endl;

//    }  while(niemoznaliczyc);
    while(k<iteracje || !osiagnieta_dokladnosc)
    {
        osiagnieta_dokladnosc=true;
        for(int i=0;i<n;i++)
        {
            std::cout << result[i]<<"   ";
        }
        std::cout<<std::endl;
        for(int i=0;i<n;i++)
        {
            if(tab[i][i]==0) std::cout<<"Jestesmy zgubieni"<<std::endl;
            if(tab[i][i]==0) Zamien(tab,n,i,result,sprzeczny);
        }
        for(int i=0;i<n;i++)
        {
            if(tab[i][i]==0) std::cout<<"Jestesmy zgubieni"<<std::endl;
            double z=0;
            for(int j=0;j<n;j++)
            {
                if(i!=j)z=z+tab[i][j]*result[j];
            }
            pomocnicza= result[i];
            result[i]=(1.0/tab[i][i])*(tab[i][n] -z);
            if(abs(pomocnicza-result[i])>dokladnosc) osiagnieta_dokladnosc=false;
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
        int iteracje = 0;
        double dokladnosc = 0;
        cout << "Czy program ma liczyc okreslona ilosc iteracji (1) czy do okreslonej dokladnosci(2).\n" << endl;
        int v;
        while (!(cin >> v)) {
            cin.clear();
            cin.sync();
        }
        cout<<"Podaj ilosc iteracji/dokladnosc" << endl;

        if(v==1)
        {
            int z;
            while (!(cin >> z)) {
                cin.clear();
                cin.sync();
            }
            iteracje = z;

        }
        else if(v==2)
        {
            double x;
            while (!(cin >> x)) {
                cin.clear();
                cin.sync();
            }
            dokladnosc = x;
        }
        else EXIT_FAILURE;
        system("cls");
        cout<<iteracje<<endl;
        cout << "Uklad ten w postaci macierzowej wyglada nastepujaco:" << endl;
        Wyswietl(tab,n);
        cout << endl;
        //----
        double *result=new double[n];
        for(int i=0;i<n;i++)
        {
            result[i]=0;
        }
        Jacobi(tab, n, sprzeczny, nieoznaczony,result,iteracje, dokladnosc);

        //-----
        Wyswietl(tab, n);
        cout << endl;
        cout << "Rozwiazanie ukladu rownan:" << endl;
        if (sprzeczny == true) {
            //cout << "Uklad rownan jest sprzeczny" << endl;
            cout<< "Nie mozna policzyc ukladu rownan" << endl;
//        } else if (nieoznaczony == true) {
//            cout << "Uklad rownan jest nieoznaczony." << endl;
        } else {
            cout << "Rozwiazania ukladu rownan sa nastepujace:" << endl;
//            for (int i = 0; i < n; i++) {
//                cout << "x" << i + 1 << " = " << result[i] << endl;
//            }
            for(int i=0;i<n;i++)
            {
                cout<<result[i]<<endl;
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
