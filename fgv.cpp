#include <iostream>
#include <fstream>
#include <cstring>
#include "memtrace.h"
#include "gtest_lite.h"
#include "fgvheader.h"

//K�SZ
Sztring::Sztring(char const *szoveg)
{
    hossz = strlen(szoveg);
    adat = new char[hossz+1];
    strcpy(adat, szoveg);
}
//K�SZ
Sztring::Sztring(Sztring const & orig)
{
    hossz = orig.hossz;
    adat = new char[hossz+1];
    strcpy(adat, orig.adat);
}

//K�SZ
Sztring& Sztring::operator=(Sztring const & orig)
{
    if (this != &orig)
    {
        delete[] adat;
        hossz = orig.hossz;
        adat = new char[hossz+1];
        strcpy(adat, orig.adat);
    }
    return *this;
}
//K�SZ
size_t Sztring:: size() const
{
    return hossz;
}
//K�SZ
char const & Sztring::operator[] (size_t idx) const
{
    return adat[idx];
}

//K�SZ
Sztring Sztring::operator+(Sztring const & rhs) const
{
    Sztring uj;
    delete[] uj.adat;
    uj.hossz = this->hossz + rhs.hossz;
    uj.adat = new char[uj.hossz + 1];
    strcpy(uj.adat, this->adat);
    strcat(uj.adat, rhs.adat);
    return uj;
}

//K�SZ
std::ostream& operator<<(std::ostream & os, const Sztring & s)
{
    for (size_t i = 0; i != s.size(); ++i)
        os << s[i];
    std::cout.flush();
    return os;
}
//K�SZ
std::istream& operator>>(std::istream & is, Sztring & s)
{

    is>>s.getAdat();
    s.setHossz(strlen(s.getAdat()));
    std::cout.flush();
    return is;
}//K�SZ
Lista::Lista()
{
    this->meret = 0;
    this->eleje = new Adat*[0];

}
//K�SZ
Lista::~Lista()
{
    for(size_t i = 0; i < this->meret; ++i) delete this->eleje[i];
}

//K�SZ
void Szemely::kiir(std::ostream& os)
{
    os<<this->getTipus()<<std::endl;
    os<<this->getNev()<<std::endl;
    os<<this->getIszam()<<std::endl;
    os<<this->getVaros()<<std::endl;
    os<<this->getUtca()<<std::endl;
    os<<this->getHszam()<<std::endl;
    os<<this->getMszam()<<std::endl;
    os<<this->getBnev()<<std::endl;
    os<<this->getPszam()<<std::endl;
    os<<std::endl;
    std::cout.flush();

};
//K�SZ
void Ceg::kiir(std::ostream& os)
{
    os<<this->getTipus()<<std::endl;
    os<<this->getNev()<<std::endl;
    os<<this->getIszam()<<std::endl;
    os<<this->getVaros()<<std::endl;
    os<<this->getUtca()<<std::endl;
    os<<this->getHszam()<<std::endl;
    os<<this->getMszam()<<std::endl;
    os<<this->getAlapitas()<<std::endl;
    os<<this->getDszam()<<std::endl;
    os<<std::endl;
    std::cout.flush();

};
/*
* kiir egy adatot egy os re
* a kiir fgv-t haszn�lja mi az adat virtu�lis tagja, �s �gy az adat* t�pus� heterog�n kollekci� adatait k�l�nb�z� m�don �rja ki
*/
std::ostream& operator<< (std::ostream& os, Adat* kiirando)
{

    kiirando->kiir(os);
    std::cout.flush();
    return os;

}
std:: ostream& operator<< (std::ostream& os, Lista& listam)
{

    for (size_t s = 0; s< listam.getMeret(); s++)
    {
        os<<listam[s]<<std::endl;

    }
    std::cout.flush();
};

/*
* a list�hoz �j rekordot ad, ezt haszn�lja a f�menu ujrekord f�ggv�nye
*KESZ
*/
void Lista::ujrekord (Adat* hozzaad)
{
    Adat** uj = new Adat*[this->meret+1];
    if(this->meret >0) for (size_t s =0; s < this->meret; s++) uj[s] = this->eleje[s];
    delete[] this->eleje;
    this->eleje = uj;
    this->eleje[this->meret++] = hozzaad;

}

void Lista::torol(Sztring torolni)
{
    for (size_t s =0; s<=this->meret; s++)
    {
        if (strcmp(torolni.getAdat(),this->eleje[s]->getNev().getAdat()))
        {

            if (this->meret>1)
            {
                Adat** uj = new Adat*[this->meret-1];
                for (size_t t = 0; t<this->meret; t++)
                {
                    if (s == t) t++;
                    uj[t] = this->eleje[t];
                }
                delete[] this->eleje;
                this->eleje = uj;

            }
            else
            {
                delete this->eleje[0];
                this->eleje[0] = new Szemely;
            }
            this->meret--;

        } else {
          //  throw std::exception;
        }
    }

}

/*
* Indexel� oper�tor a Lista haszn�lat�hoz
K�SZ
*/
Adat* Lista:: operator[] (size_t i)
{
    return this->eleje[i];
}
// megadott nev alajan keres a list�n, visszaadja az elso talalatot vagy hibat dob
Adat* Lista::keres (Sztring& keresettneve){

}
void kereses(Lista& listam){
}

/*
* egy bizonyos nev� adatot torol a list�r�l
* K�SZ
*/
void torles(Lista& listam)
{
    Sztring s1;
    std::cout<<"Milyen rekordot szeretne torolni? Adja meg a nevet!"<<std::cout;
    std::cin>>s1;
    std::cout<<"rekord torolve"<<std::endl;


}


/*
*a f�men� egy almen�je, kezeli a felhaszn�l�i bemenetet, �s a megfelel� f�ggv�nyek megh�v�s�val l�trehoz egy �j bejegyz�st a list�ban
* K�SZ
*/

void ujrekord(Lista& listam)
{
    int i1;
    std::cout<<"Ceget (0) vagy szemelyt (1) szeretne felvenni?"<<std::endl;
    std::cin>>i1;
    Sztring s1;
    Adat* hozzaad = new Ceg;
    if (i1)
    {
        delete hozzaad;
        hozzaad = new Szemely;
    }
    hozzaad->setTipus(i1);

    std::cout<<"Nev?"<<std::endl;
    std::cin>>s1;
    hozzaad->setNev(s1);
    std::cout.flush();
    std::cout<<"Iranyitoszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setIszam(i1);
    std::cout.flush();
    std::cout<<"Varos?"<<std::endl;
    std::cin>>s1;
    hozzaad->setVaros(s1);
    std::cout.flush();
    std::cout<<"Utca?"<<std::endl;
    std::cin>>s1;
    hozzaad->setUtca(s1);
    std::cout.flush();
    std::cout<<"Hazszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setHszam(i1);
    std::cout.flush();
    std::cout<<"Telefonszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setMszam(i1);
    std::cout.flush();
// ha a tipus 0, a c�gekhez tartoz� inf�kat k�rj�k be, ha 1 a szem�lyekhez
    if (hozzaad->getTipus())
    {
        std::cout<<"Becenev?"<<std::endl;
        std::cin>>s1;
        hozzaad->setBnev(s1);
        std::cout.flush();
        std::cout<<"Privat telefonszam?"<<std::endl;
        std::cin>>i1;
        hozzaad->setPszam(i1);
        std::cout.flush();
    }
    else
    {
        std::cout<<"Alapitas eve?"<<std::endl;
        std::cin>>i1;
        hozzaad->setAlapitas(i1);
        std::cout.flush();
        std::cout<<"Dolgozok szama?"<<std::endl;
        std::cin>>i1;
        hozzaad->setDszam(i1);
        std::cout.flush();
    }

    listam.ujrekord(hozzaad);

    std::cout.flush();
    std::cout<<"Uj nevjegy letrehozva"<<std::endl;
}
/*
* beolvassa az adatokat a backupfile.txt f�jlb�l �s elt�rolja �ket egy Lista-ban
*/

/*void Lista::beolvas(std::ifstream backupfile )
{
    backupfile.open ("backup.txt");
     if (!backupfile)
     {
         std::cerr << "Nincs mentett telefonk�nyved!";
     }
     else
     {
         Adat* hozzaad;
         char ch = '0';
         char tipus;
         Sztring sz;
         while (backupfile>> noskipws >> tipus)
         {
            if (tipus == '0') // C�get tal�ltunk
            {
                hozzaad = new Ceg;
             } else {
                 hozzaad = new Szemely;
             }
             // n�v beolvas�sa karakterenk�nt endline-ig
                while(ch != '\n'){
                     backupfile>> noskipws >> ch;
                     sz+= Sztring(ch);
                }
                hozzaad.setNev(sz);
                // ir�ny�t�sz�m beolvas�sa
                backupfile>> noskipws >> ch;
                while(ch != '\n'){
                     while(ch != '\n'){

                     backupfile>> noskipws >> ch;

                }
                     backupfile>> noskipws >> ch;

                }
         }

     }
     backupfile.close();
     char ch;


}
*/
