#include "permutation.h"

class Population {

private:

	int size; //velicina populacije
	Permutation* schedules; //populacija
	int schlen; //duljina jednog rasporeda

	vector<double > prob; 
	//vektor vrijednosti vjerojatnosti da će neka onlooker bee odabrati taj raspored, 
	//u odnosu na sve rasporede u trenutnoj populaciji
	//duljina vektora vjerojatnosti će biti ista kao i veličina populacije jer će toliko biti i onlooker bees

public:

	Population();
	Population( int s, int n, SMSP& problem);
	Population( Permutation& );
	Population( Population& );
	~Population();

	const Population& operator=( Population& ); //pridruzivanje
	bool operator==( Population& ); //usporedivanje
	bool operator!=( Population& ); //usporedivanje
	Permutation& operator[]( int ) const; //vraca i-ti raspored
	friend ostream& operator<<( ostream& os, Population& p ); //ispisivanje populacije

	int population_size(); //vraća broj rasporeda u populaciji
	int schedule_size(); //vraća broj poslova u rasporedima
	double& probability_i( int i ); //vraća vjerojatnost odabira rasporeda i iz populacije

	bool have( Permutation& ); //provjerava je li trenutna populacija sadržava neki raspored
	Permutation& select_best(); //vraća raspored s najmanjim tt

	void probability(); //računanje vjerojatnosti svakog rasporeda u nekoj populaciji
};
