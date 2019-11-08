#include "population.h"


//Konstruktor
Population::Population(){
	size = 0;
	schedules = NULL;
	schlen = 0;
	//vektor vjerojatnosti ima sam svoj konstruktor
}

//Stvara slucajnu populaciju velicine s, s duljinama rasporeda n
Population::Population( int s, int n, SMSP& problem ){
	size = s;
	schlen = n;
	schedules = new Permutation[size];

	for ( int i=0; i<size; i++ ){
		schedules[i].random(schlen);
		schedules[i].calculate_tt(problem);
	}
	probability();
}

//Stvara populaciju od jednog rasporeda
Population::Population( Permutation& r ){
	if ( r.number_of_jobs() == 0 ){
		schedules = NULL;
		size = 0;
		schlen = 0;
	}
	else{
		size = 1;
		schlen = r.number_of_jobs();
		schedules = new Permutation[size];
		schedules[0] = r;
		prob.reserve( 1 );
		prob.push_back( 1 );
	}
}

//Copy-konstruktor
Population::Population( Population& src ){
	size = src.population_size();
	schlen = src.schedule_size();
	schedules = new Permutation[size];

	prob.clear();
	prob.shrink_to_fit();
	prob.reserve(size);

	for ( int i=0; i<size; i++){
		schedules[i] = src[i];
		prob.push_back( src.probability_i( i ) );
	}
}

//Destruktor
Population::~Population(){

	if (schedules != 0) delete[] schedules;
	schedules = NULL;

	// if( !( prob.empty() ) ) {
	// 	prob.clear();
	// 	prob.shrink_to_fit();
	// }
}

//Operator pridruzivanja
const Population& Population::operator=( Population& second ){
	if (schedules != NULL) delete[] schedules;
	size = second.population_size();
	schlen = second.schedule_size();
	schedules = new Permutation[size];

	//očistimo vektor sa vjerojatnostima
	prob.clear();
	prob.shrink_to_fit();
	prob.reserve(size);

	for (int i=0; i<size; i++){
		schedules[i].random(schlen); 
		//teorija: zelimo stvoriti bilokakav raspored na i-tom mjestu duljine 
		//schlen tako da operator pridruzivanja permutacija prode bez greske
		schedules[i] = second[i];
		prob.push_back( second.probability_i( i ) );
	}

	return (*this);
}

//Operator usporedivanja
bool Population::operator==( Population& second ){
	if ((schlen != second.schedule_size()) || (size != second.population_size()) ) return false;
	else{
		for (int i=0; i<size; i++){
			if (!have(second.schedules[i])) return false;
		}
		for (int i=0; i<size; i++){
			if (!second.have(schedules[i])) return false;
		}
		//ne provjerava vjerojatnosti jer ako su isti rasporedi onda imaju i iste tt -> iste vjerojatnosti
		//uz pretpostavku da se radi o ISTOM PROBLEMU (?!?) - maybe fix later
	}
	return true;	
}

//Operator uspoređivanja
bool Population::operator!=( Population& second ){
	return (!( (*this) == second ));
}

//Operator indeksiranja
Permutation& Population::operator[]( int i ) const{
	if( i < size || i >= 0 ) return schedules[i];
	else throw runtime_error("Error in Population:operator[]! Job does not exist in schedule!");
}

//Ispisivanje populacija
ostream& operator<<( ostream& os, Population& p ){
	int m = p.population_size();
	for (int i=0; i<m-1; i++){
		os << p[i] << "\t" << p[i].total_tardiness() << ",\n";
	}
	os << p[m-1] << "\t" << p[m-1].total_tardiness() << "!\n\n";
	return os;
}



//Vraća veličinu populacije
int Population::population_size(){
	return size;
}

//Vraća broj poslova u rasporedima
int Population::schedule_size(){
	return schlen;
}

//Vraća vjerojatnost rasporeda i iz populacije
double& Population::probability_i( int i ){
	return prob[i];
}



//Provjerava sadrzi li populacija neki raspored
bool Population::have( Permutation& raspored ){
	if ( schlen != raspored.number_of_jobs() ) return false;

	for ( int i=0; i<size; i++ ){
		if ( raspored == schedules[i] ) return true;
	}
	return false;
}

//Najbolji raspored u populaciji
Permutation& Population::select_best(){
	int best = schedules[0].total_tardiness();
	int best_index=0,temp;
	for ( int i=1; i<size; i++ ){
		temp=schedules[i].total_tardiness();
		if ( temp < best ){
			best_index = i;
			best = temp;
		}
	}
	return schedules[best_index];
}



//Računanje vjerojatnosti svakog rasporeda u nekoj populaciji
void Population::probability(){
	int suma = 0;
	for( int i=0; i<size; i++ ) suma += schedules[i].total_tardiness();

	prob.reserve( size );
	if( suma==0 ){
		cout<<schedules[0]<<endl<<"ABC: "<<endl<<endl<<endl;
		exit(1);
	}
	//želimo da veću vjerojatnost imaju oni rasporedi koji imaju manji tt pa radimo skaliranje:
	//prob[i] = 1 - tt/suma -> dodali smo (size-1) previše jedinica -> prob[i] = prob[i]*(1/(size-1)) 
	for( int i=0; i<size; i++ ) {
		prob[i] = ( 1 - ( (double) schedules[i].total_tardiness() / (double) suma  ) ) ;
		prob[i] = (double)(prob[i]/(size-1));
	}

}
