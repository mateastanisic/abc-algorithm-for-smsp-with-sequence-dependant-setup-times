/*
SMSP WITH SEQUENCE DEPENDANT SETUP TIMES --- SMSP

-------------

OPIS PROBLEMA
Zadano nam je n nezavisnih poslova koji se trebaju izvršiti na nekom 
stroju bez prekida. Za svaki taj posao Ji zadani su nam:

>>vrijeme izvšravanja posla 'pi'
>>vrijeme do kada se treba taj posao izvršiti 'di' 
>>vrijeme pripreme stroja za određeni posao 's ij'

Cilj nam je pronaći raspored Q t.d. je ukupno zakašnjenje(TT) poslova
minimalno. Ukupno zakašnjenje je suma svih zakašnjenja, a zakašnjenje nekog posla
definirano je kao:

	0; ako se posao izvršio prije svog roka
	Ci-di; ako se posao izvršio nakon svog roka izrade, gdje nam je Ci suma svih pj i skj poslova Jj koji su se izvršili prije posla Ji

-------------

FORMAT DATOTEKA S TESTNIM PODACIMA
>>prvi red: -broj poslova
			-rješenje dobiveno b&b (u Gagnovim testovima nema podataka - nule su)
			-(Gagne) ime datoteke
			-(Gagne) karakteristike problema (processing time variance, tardiness factor and due date range - npr. L L N)
>>drugi red: -vrijeme pripreme svih poslova 1,...,n
>>treći red: -rok izrade svakog posla 1,...,n (može biti i negativno -> posao je već prešao rok izrade)
>>ostali redovi: -matrica (n+1)x(n) koja sadržava vrijeme pripreme svakog posla u odnosu na prethodni posao
					(prvi redak je vrijeme pripreme stroja za prvi posao-nema prethodnoga posla)

--------------

*/
#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<cmath>
#include<ctime>

using namespace std;

//single machine scheduling problem with sequence dependant setup times
class SMSP { 
private:
public:
	char name[50]; //ime datoteke s problemom
	int jobs; //broj poslova (n)
	int solution; //rješenje b&b metodom
	char ptv, tf, ddr; //karakteristike problema - processing time variance; tardiness factor; due date range
	vector<int> process_time; //vrijeme izvršavanja svakog posla
	vector<int> due_date; //rok izrade svakog posla
	int** setup_times; //matrica dim((n+1)x(n)) koja sadrži podatke o vremenima pripreme svakog posla u odnosu na prethodni

	/*
	OSNOVNE FUNKCIJE
	Za svaku klasu potrebno je implementirati funkcije:
	>>konstruktor
	>>destruktor
	>>copy-konstruktor i ostale konstruktore
	>>operatore (=,==,<,<=,>,>=,!=)
	*/

	SMSP(); //konstruktor
	SMSP( const SMSP& ); //copy-konstruktor
	~SMSP(); //destruktor

	SMSP& operator=( const SMSP& );
	bool operator==( const SMSP& );
	bool operator!=( const SMSP& );

	void load_benchmark( const char* ); //učitavanje podataka iz datoteke
	void print_problem(); //printa podatke; za test


};

