#include "smsp.h"

//Konstruktor
SMSP::SMSP(){
	strcpy(name, "");
	jobs = 0;
	solution = -1; //nema poznatog b&b rješenja

	//vektori imaju konstruktore sami po sebi
	// process_time = NULL;
	// due_date = NULL;

	setup_times = NULL;
}

//Destruktor
SMSP::~SMSP(){
	if( !( process_time.empty() ) ) {
		process_time.clear();
		process_time.shrink_to_fit();
	}
	if( !( due_date.empty() ) ) {
		due_date.clear();
		due_date.shrink_to_fit();
	}
	if( setup_times!=NULL ) {
		for( int i=0; i<=jobs; i++ ) delete[] setup_times[i];
		delete[] setup_times;
	}

	setup_times = NULL;
}

//Copy-konstruktor 
SMSP::SMSP( const SMSP& problem ){
	if( jobs!=0 || !process_time.empty() || !due_date.empty() || setup_times!=NULL ) throw runtime_error("Error in SMSP copy-constructor: SMSP problem is already initialed!");
	
	if( problem.jobs==0 ){
		jobs = 0;
		solution = -1;
		setup_times = NULL;
	}
	else{
		jobs = problem.jobs;
		strcpy( name, problem.name );
		
		solution = problem.solution;
		ptv = problem.ptv;
		tf = problem.tf;
		ddr = problem.ddr;

		//rezerviraj prostor za vektore i matricu
		setup_times = new int*[ jobs+1 ];
		for( int k=0; k <= jobs; k++ ) setup_times[k] = new int[jobs+1];
				
		process_time.reserve( jobs+1 );
		due_date.reserve( jobs+1 );
		//prvi stupac je uvijek -1 - zbog indeksa koji u vektoru kreću od 0
		process_time[0] = -1;
		due_date[0] = -1;

		for ( int i=0; i<=jobs; i++ ) {

			setup_times[i][0] = -1; //flag- nemamo nulti posao
			for ( int j=1; j<=jobs; j++ ){
				setup_times[i][j] = problem.setup_times[i][j];
			}

			if( i==0 ) continue;
			process_time[i] = problem.process_time[i] ; //proširuje vektor za jedno mjesto i na to mjesto stavlja ono što je u zagradi
			due_date[i] = problem.due_date[i];	
		}
	}
}

//Operator pridruživanja (=)
SMSP& SMSP::operator=( const SMSP& problem ){
	if( problem.jobs!=jobs ) throw runtime_error("Error in SMSP operator= : curent problem and problem to be assigned are not same length!");

	if( this->name!=problem.name ){ //Pridružujemo samo kada su problemi zaista različiti 
		//ime datoteke u kojoj se nalazi problem je različit od imena datoteke u kojoj se nalazi problem 'problem'
		
		jobs = problem.jobs;
		strcpy( name, problem.name );
		solution = problem.solution;
		ptv = problem.ptv;
		tf = problem.tf;
		ddr = problem.ddr;
		
		for ( int i=0; i<=jobs; i++ ) {
			process_time[i] = problem.process_time[i];
			due_date[i] = problem.due_date[i];

			for ( int j=0; j<=jobs; j++ ){
				setup_times[i][j] = problem.setup_times[i][j];
			}
		}
	}
	return *this;	
}

//Operatori uspoređivanja
bool SMSP::operator==( const SMSP& problem ){
	for ( int i=0; i<=jobs; i++ ) {
		if( process_time[i]!=problem.process_time[i] ) return false;
		if( due_date[i]!=problem.due_date[i] ) return false;
		
		for ( int j=0; j<=jobs; ++j ) if( setup_times[i][j]!=problem.setup_times[i][j] ) return false;
	}
	return true;
}

bool SMSP::operator!=( const SMSP& problem ){
	for ( int i=0; i<=jobs; i++ ) {
			if( process_time[i]!=problem.process_time[i] ) return true;
			if( due_date[i]!=problem.due_date[i] ) return true;

			for ( int j=0; j<=jobs; ++j ) if( setup_times[i][j]!=problem.setup_times[i][j] ) return true;
	}
	return false;
}


//Učitavanje nekog problema iz datoteke s imenom 'file'
void SMSP::load_benchmark( const char* file ){

	ifstream in_file;
	in_file.open(file);
	if( !in_file ) throw runtime_error("Can't load file!");

	//Učitaj prvu liniju iz datoteke - br.poslova, rješenje b&b, (G)ime problema=filename, (G)karakteristike problema = tri znaka 
	int second_bb; //not clear what first row represents 
	in_file >> jobs >> solution >> second_bb;
	if( jobs>=55 ) in_file >> name >> ptv >> tf >> ddr;

	int i,j;
	int x;

	//rezerviraj memoriju
	process_time.reserve(jobs+1);
	due_date.reserve(jobs+1);
	setup_times = new int*[jobs+1];
	for( int k=0; k <= jobs; k++ ) setup_times[k] = new int[jobs+1];

	//Učitavamo processing_time
	process_time.push_back(-1); //prvi stupac je -1 (flag)
	for( i=1; i<=jobs; i++ ) {
		in_file >> x;
		process_time[i] = x;
	}
	//Učitavamo due_date
	due_date.push_back(-1); //prvi stupac je -1 (flag)
	for( i=1; i<=jobs; i++ ) {
		in_file >> x;
		due_date[i] = x;
	}
	//Učitavamo sve setup_times
	for( i=0; i<=jobs; i++ ){
		setup_times[i][0] = -1;
		for( j=1; j<=jobs; j++ ) in_file >> setup_times[i][j];
	}

	in_file.close();
}

void SMSP::print_problem(){
	if( jobs!=0 ){
		cout<<"Problem name: "<< name <<endl;
		cout<<"Number of jobs: "<< jobs <<endl;
		cout<<"Solution by b&b method: "<< solution <<endl;
		cout<<"Processing times: "<<endl;
		for( int i=0; i<jobs; i++ ) cout<< process_time[i]<<" ";
		cout<<endl;

		cout<<"Due dates: "<<endl;
		for( int i=0; i<=jobs; i++ ) cout<< due_date[i]<<" ";
		cout<<endl;

		cout<<"Setup times: "<<endl;
		for(int i=0; i<=jobs ; i++ ){
			for( int j=0; j<=jobs; j++ ) cout<<setup_times[i][j]<<" ";
			cout<<endl;
		}
	}
}
