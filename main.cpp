#include <iostream>
using std::cout;

template <typename T>
struct Cvor{
    T element;
    Cvor *sljedeci;

    Cvor (const T &element1, Cvor *sljedeci1 ):
            element(element1),sljedeci(sljedeci1){}
    Cvor(const Cvor &cvor){
        element=cvor.element;
        sljedeci=cvor.sljedeci;
    }


};

template <typename T> class Red{
private:
    Cvor<T> *pocetak;
    Cvor<T> *kraj;
    int velicina;
    void Unisti();
    void Kopiraj(const Red<T>& red );
public:
    Red() : pocetak(nullptr) ,kraj(nullptr) , velicina(0){}
    Red(const Red<T> &s){Kopiraj(s);}
    ~Red(){ Unisti(); }
    Red &operator = (const Red<T> &s);
    void stavi(const T &element);
    T skini();
    T &celo()const;
    void brisi();
    bool JeLiPrazan() const ;
    int brojElemenata()const {return  velicina;}
    template<typename T1>
    friend void ispisiRed ( Red<T1> lista);

};

template<typename T>
void ispisiRed(Red<T> red) {
    std::cout << "Podaci reda ispod " << std::endl <<
              "duzina : " << red.brojElemenata() <<std::endl ;
    if(red.brojElemenata() == 0) {
        std::cout << "Prazan red nista za prikazati" << std::endl;
        throw std::domain_error("Prazan red nista za prikazati");
    }
    std::cout <<  "Elementi :" << std::endl;
    Cvor<T>* privremeni = red.pocetak;
    while (privremeni != nullptr){
        std::cout << privremeni->element << " ";
        privremeni = privremeni->sljedeci;
    }
    std::cout << "\n" << "Element na vrhu : " << red.celo() << "\n";
}

template<typename T>
void Red<T>::Kopiraj(const Red<T> &red ) {
    pocetak =nullptr;
    Cvor<T>* pomocni(red.pocetak);
    while (pomocni != nullptr){
        stavi(pomocni->element);
        pomocni = pomocni->sljedeci;
    }
    velicina = red.velicina;
}

template<typename T>
void Red<T>::Unisti() {
    while (!JeLiPrazan() ){
        skini();
    }
    pocetak = kraj = nullptr;
}

template<typename T>
void Red<T>::stavi(const T &element) {
    Cvor<T> *novi(new Cvor<T>(element, nullptr));
    if(pocetak == nullptr)
        pocetak = kraj = novi;
    else{
        kraj->sljedeci = novi;
        kraj = kraj->sljedeci;
    }
    velicina++;
}

template<typename T>
T Red<T>::skini() {
    if(pocetak == nullptr){
        throw std::domain_error ("Prazan red!");
    }
    T element = pocetak->element;
    Cvor<T> *pomocni = pocetak;
    if(pocetak == kraj)
        pocetak = kraj = nullptr;
    else{
        pocetak = pocetak->sljedeci;
    }
    delete pomocni;
    velicina--;
    return element;
}

template<typename T>
T &Red<T>::celo() const {
    if(pocetak == nullptr){
        throw std::domain_error ("Prazan red!");
    }
    return pocetak->element;
}

template<typename T>
void Red<T>::brisi() {
    Unisti();
}

template<typename T>
bool Red<T>::JeLiPrazan() const {
    return pocetak == 0;
}

template<typename T>
Red<T> &Red<T>::operator=(const Red<T> &red) {
    if(this == &red) return  *this;
    brisi();
    pocetak = nullptr;
    Cvor<T>* pomocni(red.pocetak);
    while (pomocni != nullptr){
        stavi(pomocni->element);
        pomocni = pomocni->sljedeci;
    }
    velicina = red.velicina;
    return *this;
}


//testtne FUNKCIJE

template <typename T>
bool testKonstruktoraReda(){
    Red<int> testniRed = Red<int>();
    ispisiRed<int>(testniRed);
    return true;
}

template<typename T>
bool testStaviNaRed_i_brojElemenata(){
    Red<int> testniRed ;
    testniRed.stavi(1);
    testniRed.stavi(2);
    testniRed.stavi(3);
    testniRed.stavi(4);
    ispisiRed<int>(testniRed);
    return true;
}

template<typename T>
bool testSkiniSaReda() {
    Red<int> testniRed ;
    testniRed.stavi(1);
    testniRed.stavi(2);
    testniRed.stavi(3);
    testniRed.stavi(4);
    ispisiRed<T>(testniRed);
    testniRed.skini();
    testniRed.skini();
    ispisiRed<T>(testniRed);
    return true;
}

template<typename T>
bool testBrisiRed() {
    Red<T> testniRed ;
    testniRed.stavi(1);
    testniRed.stavi(2);
    testniRed.stavi(3);
    testniRed.stavi(4);
    ispisiRed<T>(testniRed);
    testniRed.brisi();
    ispisiRed<T>(testniRed);
    return true;
}
int main() {

    testKonstruktoraReda<int>();
    testStaviNaRed_i_brojElemenata<int>();
    testSkiniSaReda<int>();
    testBrisiRed<int>();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
