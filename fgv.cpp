#include <iostream>
#include <fstream>
#include <cstring>
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
    return os;
}
//K�SZ
std::istream& operator>>(std::istream & is, Sztring & s)
{

    is>>s.getAdat();
    s.setHossz(strlen(s.getAdat()));
    return is;
}//K�SZ
Lista::Lista(size_t defmeret)
{   this->meret = defmeret;
    this->eleje = new Adat*[1];

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

};
/*
* kiir egy adatot egy os re
* a kiir fgv-t haszn�lja mi az adat virtu�lis tagja, �s �gy az adat* t�pus� heterog�n kollekci� adatait k�l�nb�z� m�don �rja ki
*/
std::ostream& operator<< (std::ostream& os, Adat* kiirando){

    kiirando->kiir(os);
    return os;

}
std:: ostream& operator<< (std::ostream& os, Lista& listam){

    for (size_t s = 0; s<= listam.getMeret(); s++){
         os<<listam[s]<<std::endl;

    }
};

/*
* a list�hoz �j rekordot ad, ezt haszn�lja a f�menu ujrekord f�ggv�nye
*KESZ
*/
void Lista::ujrekord (Adat* hozzaad)

{
    if (this->meret)
    {
        Adat** uj = new Adat*[this->meret+1];
        for (size_t s =0; s < this->meret; s++)
        {

            uj[s] = this->eleje[s];
        }
        delete[] this->eleje;
        this->eleje = uj;
        this->eleje[this->meret++] = hozzaad;
    } else {
        delete this->eleje[0];
        this->eleje[0] = hozzaad;
        ++this->meret;
    }


}

bool Lista::torol(Sztring torolni)
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
            return 1;
        }
    }
    return 0;
}

/*
* Indexel� oper�tor a Lista haszn�lat�hoz
K�SZ
*/
Adat* Lista:: operator[] (size_t i)
{
    return this->eleje[i];
}

/*
* beolvassa az adatokat a backupfile.txt f�jlb�l �s elt�rolja �ket egy Lista-ban
*/

void Lista::beolvas(std::ifstream backupfile )
{
   /* backupfile.open ("backup.txt");
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
    */

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
    if(listam.torol(s1)) std::cout<<"rekord torolve"<<std::endl;
    else std::cout<<"nincs ilyen rekord"<<std::endl;

}

/*
* egy std::ostream t�pus� objektumra �rja a lista tartalm�t
*
*/
/* void Lista::kiir(std::ostream& os)
{
    for (size_t s = 0; s <= this->meret ; s++)
    {
        os<<this->eleje[s];
    }
}
*/

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
    Adat* hozzaad;
    if (i1)
    {
        hozzaad = new Szemely;
    }
    else
    {
        hozzaad = new Ceg;
    }
    hozzaad->setTipus(i1);

    std::cout<<"Nev?"<<std::endl;
    std::cin>>s1;
    hozzaad->setNev(s1);

    std::cout<<"Iranyitoszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setIszam(i1);

    std::cout<<"Varos?"<<std::endl;
    std::cin>>s1;
    hozzaad->setVaros(s1);

    std::cout<<"Utca?"<<std::endl;
    std::cin>>s1;
    hozzaad->setUtca(s1);

    std::cout<<"Hazszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setHszam(i1);

    std::cout<<"Telefonszam?"<<std::endl;
    std::cin>>i1;
    hozzaad->setMszam(i1);

// ha a tipus 0, a c�gekhez tartoz� inf�kat k�rj�k be, ha 1 a szem�lyekhez
    if (hozzaad->getTipus())
    {
        std::cout<<"Becenev?"<<std::endl;
        std::cin>>s1;
        hozzaad->setBnev(s1);

        std::cout<<"Privat telefonszam?"<<std::endl;
        std::cin>>i1;
        hozzaad->setPszam(i1);
    }
    else
    {
        std::cout<<"Alapitas eve?"<<std::endl;
        std::cin>>i1;
        hozzaad->setAlapitas(i1);

        std::cout<<"Dolgozok szama?"<<std::endl;
        std::cin>>i1;
        hozzaad->setDszam(i1);
    }

    listam.ujrekord(hozzaad);

    std::cout<<"Uj nevjegy letrehozva";
}
