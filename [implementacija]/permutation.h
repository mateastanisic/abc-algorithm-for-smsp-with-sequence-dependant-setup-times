/*Ovdje inicijaliziramo jedan raspored Q.
Njih ćemo inicijalizirati pomoću klase - permutacija. 
Svaka permutacija,odnosno raspored Q  sadržavati će:
>>polje poslova, odnosno gena
>>duljinu tog rasporeda, odnosno jedinke 
>>vrijednost TT (total tardiness) -  ukupno zakašnjenje posla
*/
#include "smsp.h"

class Permutation {

private:

	int length; //duljina rasporeda - odnosno broj poslova u rasporedu
	int tt; //total tardiness - ukupno zakašnjenje
	int* jobs; //raspored Q

public:

	Permutation(); //konstruktor
	Permutation( int, SMSP& );
	Permutation(int ); //konstruktor s parametrima - posebno za heigh_search
	Permutation( Permutation& ); //copy-konstruktor
	~Permutation(); //destruktor

	Permutation& operator=( const Permutation& ); //operator pridruživanja
	bool operator==( const Permutation& ); //operator uspoređivanja
	bool operator!=( const Permutation& ); //operator uspoređivanja
	const int& operator[]( int i ) const; //operator koji postavlja poziciju u raporedu na posao i  
	friend ostream& operator<<( ostream& , Permutation&  ); //ispisivanje rasporeda


	int number_of_jobs() const; //broj poslova
	int total_tardiness() const; //total tardiness - ukupno zakašnjenje

	void calculate_tt( SMSP& ); //računa i postavlja tt trenutne permutacija
	void set_tt( int ); //postavlja tt na određeni broj
	void set_length( int  ); //postavlja broj poslova u rasporedu


	void initial( int ); //postavlja duljinu rasporeda i svi su poslovi -1 - zastavice
	void set_job_on_position( int , int ); //postavlja posao 'q' na poziciju 'i'
	int position( int ); //vraća poziciju posla q u rasporedu
	

	void reverse( SMSP& , int , int  ); //stvara novi raspored tako da zamjenimo poredak posla na i-toj i j-toj poziciji - koristi se u LS-u
	void local_search( SMSP& ); //lokalno pretraživanje
	void neighbourhood_search( SMSP& , int  ); //pretraživanje susjedstva

	void PMXcrossover( SMSP& , Permutation& , Permutation& );
	void OXcrossover( SMSP& , Permutation& , Permutation& ); //križanje (PMX) dva rasporeda - 'mom' i 'dad' - rezultat je 'child', odnosno trenutno pozvani raspored
	void OXcrossover( SMSP& , Permutation& , Permutation& , int , int );
	void OXcrossover_best( SMSP& , Permutation& , Permutation& );
	void heuristic_crossover( SMSP& , Permutation& , Permutation& );
	void heuristic_crossover( SMSP& , Permutation& , Permutation&, int );
	void heuristic_crossover_best( SMSP& , Permutation& , Permutation& );

	void random(); //stvara nasumične permutacije iz postojeće
	void random( int  ); //stvara nasumične permutacije duljine 'size'
};