#include "permutation.h"

//Konstruktor
Permutation::Permutation() {
	length = 0;
	tt = -1; //ako ne postoji još nikakav raspored poslova -  tt=-1
	jobs = NULL;
}

//Konstruktor s parametrima
Permutation::Permutation( int n, SMSP& problem ){
	length = n;
	jobs = new int[length];

	for( int i=0; i<n; i++ ) jobs[i] = i+1;
	calculate_tt(problem);
}

//Konstruktor s parametrima
//Koristi se u neigh_serachu - bez postavljanja tt - dodatna složenost
//Stvara raspored duljine n : 1 2 3 4 ... n
Permutation::Permutation( int n ){
	if( n<1 ) throw runtime_error("Error in constructor for Permutation! No jobs to schedule!");
	length = n;

	jobs = new int[ n ];
	for( int i=0; i<n; i++ ) jobs[i] = i+1; 

	tt = -1; //još nije postavljeno
}

//Destruktor
Permutation::~Permutation(){
	if( jobs!=NULL ) delete[] jobs;
	jobs = NULL;
}

//Copy-konstruktor
Permutation::Permutation( Permutation& src ){
	//ako imamo što kopirati
	if( (src.number_of_jobs()>0) && (src.jobs!=NULL) ){ //može li se pristupiti src.jobs?
		length = src.number_of_jobs();
		tt = src.total_tardiness();

		jobs = new int[ length ];
		for( int i=0; i<length; i++ ) jobs[i] = src[i]; 
	}
	else { //nemamo što iskopirati
		length = 0;
		tt = -1;
	}
}

//Operator pridruživanja
Permutation& Permutation::operator=( const Permutation& src ){
	if( length!=src.number_of_jobs() ){
		cout<<"length="<<length<<" and src.length="<<src.number_of_jobs()<<endl;
		throw runtime_error("Error in Permutation operator= : Different sizes of schedules!");
	} 

	length = src.number_of_jobs();
	tt = src.total_tardiness();
	for( int i=0; i<length; i++ ) jobs[i] = src[i];

	return *this;
}

//Operator uspoređivanja 
//Dvije permutacije, odnosno rasporedi su isti akko je broj poslova isti i ako jobs[i] = src[i] za svaki i
bool Permutation::operator==( const Permutation& src ){
	if(length!= src.number_of_jobs() ) return false;
	for( int i=0; i<length; i++ ) if( jobs[i] != src[i] ) return false;
	return true;		
}

//Operator uspoređivanja
bool Permutation::operator!=( const Permutation& src ){
	return !( *this==src );		
}

//Operator indeksiranja
const int& Permutation::operator[]( int i ) const{
	if( i <length || i >= 0 ) return jobs[i];
    else throw runtime_error("Error in operator[] in Permutation: Job does not exist in schedule!");
}


//Ispisivanje rasporeda - permutacije
ostream& operator<<( ostream& os, Permutation& src ){
	for( int i = 0; i < src.number_of_jobs(); i++ ) os << src[i] << " ";
	return os;
}

//Vraća broj poslova u rasporedu -permutaciji
int Permutation::number_of_jobs() const {
	return length;
}

//Vraća TT trenutnog rasporeda - permutacije
int Permutation::total_tardiness() const {
	return tt;
}


//Ukupno zakašnjenje rasporeda u trenutnom rasporedu - mijenja i tt
void Permutation::calculate_tt( SMSP& problem ){
	//sum je tt
	//tempsum je zakašnjenje posla S[i]
	//sum_setup_times je suma svih vremena pripreme - da ne moramo u svakoj petlji imati još jednu petlju koja računa vrijeme pripreme svih poslova do tada
	int sum = 0, tempsum, dif;
	tempsum = problem.setup_times[ 0 ][ (jobs[0]) ]; 

	for( int i=0; i<length ; i++ ){
		tempsum += problem.process_time[ (jobs[i]) ];
		if( i!=0 ) tempsum += problem.setup_times[ (jobs[i-1]) ][ (jobs[i]) ];
		dif = tempsum - problem.due_date[ (jobs[i]) ];
		if( dif>0 ) sum += dif;
	}
	tt = sum;
}

//Postavljanje tt na vrijednost x
void Permutation::set_tt( int x ){
	tt = x;
}

//Postavlja duljinu rasporeda - odnosno broj poslova u rasporedu- permutaciji 
void Permutation::set_length( int n ){
	length = n;
}




//Inicijalizira raspored-permutaciju duljine n sa '-1' : zastavice - potrebno posebno za crossover
void Permutation::initial( int n ){
	if( jobs!=NULL ) delete[] jobs;
	length = n;
	
	jobs = new int[ length ];
	for( int i=0; i<length; i++ ) jobs[i] = -1; //zastavica da na toj poziciji još nije postavljen posao
	tt = -1;
}

//Postavljanje poslova u dijetetu kod crossovera
void Permutation::set_job_on_position( int q, int i ){
	if( i >=length || i<0 ) throw runtime_error("Position is not in the range!");
	jobs[i] = q; 
}

//Pronalazi poziciju posla 'q' u trenutnom rasporedu - permutaciji
int Permutation::position( int q ){
	if( q<=0 || q>length ) throw runtime_error("Job does not exist in schedule!");
	else{
		for( int i=0; i<length; i++ ){
			if( q == jobs[i] ) return i;
		}
		cout << "Job does not exist in schedule!";
		exit(0);
	}
}

//Mijenja raspored - permutaciju tako da mijenja pozicije 'i' i 'j', tj poslove koje se na njima nalaze
void Permutation::reverse( SMSP& problem, int i, int j ){
	if( i>=length || j>=length || i<0 || j<0 ) throw runtime_error("Error in Permutation::reverse(). 'i' or 'j' are not in the range!" );
	int job_i = jobs[i];
	jobs[i] = jobs[j];
	jobs[j] = job_i;
	calculate_tt( problem );
}

//Lokalno pretraživanje susjedstva danog rasporeda - permutacije
void Permutation::local_search( SMSP& problem ){
	Permutation temp( problem.jobs );
	for( int i=0; i<length; i++ ){
		for( int j=i+1; j<length; j++ ){
			temp = *this;
			//mjenjamo poredak poslova na pozicijama 'i' i 'j' pa se pri tome mijenja i ukupno zakašnjenje
			//koje također mijenjamo u rasporedu temp
			temp.reverse( problem, i, j ); 
			if( temp.total_tardiness() < tt ) reverse( problem, i, j );
		}
	}
}

//Employed bees - generiranje izvora hrane u susjedstvu
//Za sada (način generiranja susjedstva): destruction and construction phase of the IG(iterative greedy) algorithm
//'select' nam predstavlja broj poslova koje ćemo, nasumičnim odabirom, "izvući" iz jobsa - destruction phase
void Permutation::neighbourhood_search( SMSP& problem, int number_of_removed ){
	//removed_jobs će sadržavati sve poslove koje ćemo izbaciti iz rasporeda jobs - destruction phase
	vector<int> removed_jobs(number_of_removed);
	int x;

	//DESTRUCTION PHASE
	for( int i=0; i<number_of_removed; i++ ){
		x = rand() % length + 1 ; //raspon od 1 do 'length' (uključujući) jer poslove označavamo sa 1 2 3 ... length

		//Tražimo neku random poziciju u rasporedu jobs koju ćemo "izbaciti" iz rasporeda a poslije ih ponovno postavljati -  pri tome pazimo da se pozicije ne ponavljaju
		while ( !(removed_jobs.empty()) && find( removed_jobs.begin(), removed_jobs.end(), x ) != removed_jobs.end() )  x = rand() % length + 1;
		removed_jobs[i] = x;
	}

	//sub_schedule je raspored jobs bez 'removed_jobs' poslova
	int* sub_schedule = new int[ length ];
	int p=0;

	for( int i=0; i<length; i++ ){
		if( find( removed_jobs.begin(), removed_jobs.end(), jobs[i]) != removed_jobs.end() ) continue;
		sub_schedule[p] = jobs[i]; //sub_schedule je za number_of_removed manji od jobs-a
		p++;
	}

	//CONSTRUCTION PHASE
	int best_tt, help_tt, best_index ;
	//sada stavljamo natrag 'removed_jobs' u 'sub_schedule' na sve moguće načine 
	//i tražimo onaj način na koji dobijemo najmanje ukupno zakašnjenje ( tt )
	for( int i=0; i<number_of_removed; i++ ) { 

		int size = length-number_of_removed+i+1 ; //duljina help rasporeda
		Permutation help( size ); // dobijemo raspored (1 2 3 ... size) bez postavljenje tt

		//moramo izračunati prvi primjerak da imamo s čime uspoređivati 
		//prvi primjerak - na početak stavimo removed_jobs[i]
		help.set_job_on_position( removed_jobs[i], 0 );
		for( int k=1; k<size; k++ ){
			help.set_job_on_position( sub_schedule[k-1], k );
		}

		help.calculate_tt( problem ); //ovdje se računa tt rasporeda help
		best_tt = help.total_tardiness();
		best_index = 0;

		for( int j=1; j<size; j++ ){
			
			//insert
			for( int k=0; k<size; k++ ){
				if( k<j ) help.set_job_on_position( sub_schedule[k], k );
				else if( k>j ) help.set_job_on_position( sub_schedule[k-1], k );
				else if( k==j ) help.set_job_on_position( removed_jobs[i], k );
			}
			help.calculate_tt( problem );
			help_tt = help.total_tardiness(); 
			
			if( help_tt < best_tt ) { 
				best_index = j;
				best_tt = help_tt;
			}
		}

		//update raspored sub_schedule
		for( int k=size-1; k>best_index; k-- ) sub_schedule[k] = sub_schedule[k-1];
		sub_schedule[best_index] = removed_jobs[i];

	}
	 
	//izmjenjujemo raspored - permutaciju jobs 
	for( int i=0; i<length; i++ ) jobs[i] = sub_schedule[i];
	//best_tt nakon petlji je tt novog rasporeda jobs
	tt = best_tt;

	delete[] sub_schedule;
}

//Križanje - PMX - partially mapped crossover - odabrali smo ovaj jer se koristio za TSP, a naš problem je vrlo sličan TSP-u 
//trgovački putnik je zapravo stroj koji mora izvršiti sve poslove, odnosno posjetiti sve gradove
/*void Permutation::crossover( SMSP& problem, Permutation& mom, Permutation& dad ){
	if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");

	//inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
	initial( mom.number_of_jobs() );

	//odaberemo dvije točke prekida slučajnim izborom
	//ovo su pozicije prekida  - mogućnosti su od 0 do length-1
	int i = rand() % length; 
	int j = rand() % length;

	while( i == j ) j = rand() % length;
	if( j<i ){
		int swap = i;
		i = j;
		j = swap;
	}

	for( int k=i; k<=j; k++ ) jobs[k] = mom[k];
	
	//gledamo poslove u rasporedu 'dad' na pozicijama između 'i' i 'j'
	bool test,done;
	int p, a, b, index;
	for( int k=i; k<=j; k++ ){
		//pronađemo sve poslove u rasporedu 'dad' koji još nisu u rasporedu 'child' -treuntni raspored, odnosno permutacija
		test = false;
		p = i;
		while( p<=j && !test ){
			if( mom[p] == dad[k] ) test = true;
			p++;
		}

		//ako se posao na poziciji 'k' u rasporedu 'dad' već nalazi u rasporedu 'child' nastavi dalje
		if( test ) continue;

		//ako se posao na poziciji 'k' u rasporedu 'dad' ne nalazi u rasporedu 'child'

		//posao kojeg moramo postaviti negdje u rasporedu 'child'
		a = dad[k];
		//gledaj koji posao se nalazi na toj istoj poziciji u rasporedu 'child'
		b = jobs[k];
		//pronađi poziciju posla b u rasporedu 'dad'
		index = dad.position( b );
		done = false;

		//dok ga ne smjestimo negdje
		while( !done ){
			//ako se na poziciji posla 'bk' u rasporedu 'child' još ne nalazi neki posao
			if( jobs[index] == -1 ) {
				jobs[index] = a;
				done = true;
			}
			else{
				b = jobs[index];
				index = dad.position( b );
			}
		}
	}

	//ostale poslove samo premjestimo iz 'dad' u 'child'
	for( int k=0; k<length; k++ ){
		if( jobs[k] == -1 ) jobs[k] = dad[k];
	}

	calculate_tt(problem);
}
*/



//Križanje - PMX - partially mapped crossover - odabrali smo ovaj jer se koristio za TSP, a naš problem je vrlo sličan TSP-u
//trgovački putnik je zapravo stroj koji mora izvršiti sve poslove, odnosno posjetiti sve gradove
void Permutation::PMXcrossover( SMSP& problem, Permutation& mom, Permutation& dad ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");

    //inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
    initial( mom.number_of_jobs() );

    //odaberemo dvije točke prekida slučajnim izborom
    //ovo su pozicije prekida  - mogućnosti su od 0 do length-1
    int i = rand() % length;
    int j = rand() % length;

    while( i == j ) j = rand() % length;
    if( j<i ){
        int swap = i;
        i = j;
        j = swap;
    }

    for( int k=i; k<=j; k++ ) jobs[k] = mom[k];

    //gledamo poslove u rasporedu 'dad' na pozicijama između 'i' i 'j'
    bool test,done;
    int p, a, b, index;
    for( int k=i; k<=j; k++ ){
        //pronađemo sve poslove u rasporedu 'dad' koji još nisu u rasporedu 'child' -treuntni raspored, odnosno permutacija
        test = false;
        p = i;
        while( p<=j && !test ){
            if( mom[p] == dad[k] ) test = true;
            p++;
        }

        //ako se posao na poziciji 'k' u rasporedu 'dad' već nalazi u rasporedu 'child' nastavi dalje
        if( test ) continue;

        //ako se posao na poziciji 'k' u rasporedu 'dad' ne nalazi u rasporedu 'child'

        //posao kojeg moramo postaviti negdje u rasporedu 'child'
        a = dad[k];
        //gledaj koji posao se nalazi na toj istoj poziciji u rasporedu 'child'
        b = jobs[k];
        //pronađi poziciju posla b u rasporedu 'dad'
        index = dad.position( b );
        done = false;

        //dok ga ne smjestimo negdje
        while( !done ){
            //ako se na poziciji posla 'bk' u rasporedu 'child' još ne nalazi neki posao
            if( jobs[index] == -1 ) {
                jobs[index] = a;
                done = true;
            }
            else{
                b = jobs[index];
                index = dad.position( b );
            }
        }
    }

    //ostale poslove samo premjestimo iz 'dad' u 'child'
    for( int k=0; k<length; k++ ){
        if( jobs[k] == -1 ) jobs[k] = dad[k];
    }

    calculate_tt(problem);
}


void Permutation::OXcrossover( SMSP& problem, Permutation& mom, Permutation& dad ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");

    //inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
    initial( mom.number_of_jobs() );
    vector<bool > help( length+1, false );

    //odaberemo dvije točke prekida slučajnim izborom
    //ovo su pozicije prekida  - mogućnosti su od 0 do length-1
    int i = rand() % length;
    int j = rand() % length;

    while( 1 ){
        if( i!=j && ( i!=0 || j!=(length-1) ) && ( j!=0 || i!=(length-1) ) ) break;
        j = rand() % length;
    }

    if( j<i ){
        int swap = i;
        i = j;
        j = swap;
    }

    for( int k=i; k<=j; k++ ){
        jobs[k] = mom[k];
        help[ jobs[k] ] = true;
    }

    int r = j+1, br = 0;
    if( r >= length ) r = 0;
    int k = r;
    int no = length - (j-i+1);

    while( br<no ){
        if( !help[ dad[r] ] ){
            jobs[k] = dad[r];
            br++;
            k++;
            if( k>= length ) k = 0;
        }
        r++;
        if( r>=length ) r = 0;
    }

    calculate_tt( problem );
}

void Permutation::OXcrossover( SMSP& problem, Permutation& mom, Permutation& dad, int l, int r ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");
    if( l>=r || l<0 || r>length-1 || ( l==0 && r==length-1) ) throw runtime_error("Points of break in crossover are not good!");

    //inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
    initial( mom.number_of_jobs() );
    vector<bool > help( length+1, false );

    for( int k=l; k<=r; k++ ){
        jobs[k] = mom[k];
        help[ jobs[k] ] = true;
    }

    int j = r+1, br = 0;
    if( j >= length ) j = 0;
    int k = j;
    int no = length - (r-l+1);

    while( br<no ){
        if( !help[ dad[j] ] ){
            jobs[k] = dad[j];
            br++;
            k++;
            if( k >= length ) k = 0;
        }
        j++;
        if( j>=length ) j = 0;
    }

    calculate_tt( problem );
}

void Permutation::OXcrossover_best( SMSP& problem, Permutation& mom, Permutation& dad ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");

    int num = mom.number_of_jobs();
    int min_tt;
    Permutation best = (*this);

    for( int l=0; l<num-1; l++ ){
        for( int r=l+1; r<num; r++ ){
            if( l==0 && r==num-1 ) continue;
            OXcrossover( problem, mom, dad, l, r );
            if( l==1 && r==2 ) min_tt = tt; //početni uvijet
            if( tt < min_tt ){
                min_tt = tt;
                best = (*this);
            }
            OXcrossover( problem, dad, mom, l, r );
            if( tt < min_tt ){
                min_tt = tt;
                best = (*this);
            }
        }
    }
    (*this) = best;
}



void Permutation::heuristic_crossover( SMSP& problem, Permutation& mom, Permutation& dad ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");
    if( mom.number_of_jobs()==0 ) return;

    initial( mom.number_of_jobs() ); 	//inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
    int a = rand() % length + 1; // odabiremo prvi posao nasumičnim odabiremo
    jobs[0] = a;
    int num = 1, cm, cd, i, j ;
    bool testm, testd;

    int sum_times = problem.setup_times[0][a] + problem.process_time[a]; //varijabla koja će računati ukupno vrijeme koje je do sada prošlo

    vector<bool> help(length+1,true); //duljine len+1 jer indeksi predstavljaju poslove, a poslove numeriramo od 1 do 'n'
    help[ a ] = false; //zastavica, ostali imaju vrijednost 1(ok)

    while( num<length ){

        testm = false;
        testd = false;

        //tražimo pozicije posla 'a' u roditeljima da vidimo tko ima manji setup time do slj. posla u svome rasporedu
        i =  mom.position( a );
        if( i==(length-1) ) i = 0; //jer gledamo koji posao dolazi nakon posla 'a' u mom, a ako se posao 'a' u mom nalazi na posljednjoj poziciji, potrebno je gledati "sljedeći" posao na poziciji 0 u mom
        else i++;
        j = dad.position( a );
        if( j==(length-1) ) j = 0;
        else j++;

        //provjeri jesu li poslovi mom[i] ili dad[i] već u child
        if( help[ mom[i] ]==false ) testm = true;
        if( help[ dad[j] ]==false ) testd = true;

        //ako jesu oba
        if( testm && testd ){
            a = rand() % length + 1; //nasumičnim odabirom odaberemo novi posao
            while( help[a]==false ) a = rand()% length + 1; //sve dok ne nađemo posao koji još nije u child
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }
        else if( testm ){ //ako je samo mom[i] unutar child
            a = dad[j];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }
        else if( testd ){ //ako je samo dad[j] unutar child
            a = mom[i];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }

        //niti mom[i] niti dad[j] nisu u child
        cm = problem.due_date[ mom[i]] - (sum_times + problem.setup_times[ jobs[ num-1] ][ mom[i] ] + problem.process_time[ mom[i] ]);
        cd = problem.due_date[ dad[j]] - (sum_times + problem.setup_times[ jobs[num-1] ][ dad[j] ] + problem.process_time[ dad[j] ]);

        //uzimamo onaj koji ima veću razliku između du_date i vremena izvršavanja do sada - da ga se što prije riješimo
        //ovo funkcionira i kad su oba cm i cd negativni->uzmemo manje po abs vr, ili kad je jedan od njih neg a drugi poz->uzmemo poz
        if( cm>=cd ){
            a = mom[i];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }

        a = dad[j];
        jobs[ num ] = a;
        help[ a ] = false;
        sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
        num++;
        continue;
    }

    calculate_tt( problem );
}

void Permutation::heuristic_crossover( SMSP& problem, Permutation& mom, Permutation& dad, int a ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");
    if( mom.number_of_jobs()==0 ) return;
    if( a<=0 || a>length ) throw runtime_error("Job is not in the range!");

    initial( mom.number_of_jobs() ); 	//inicijaliziramo rasporedu za 'child' (duljina,tt=-1,Q[i]=-1 - zastavice)
    jobs[0] = a;
    int num = 1, cm, cd, i, j ;
    bool testm, testd;

    int sum_times = problem.setup_times[0][a] + problem.process_time[a]; //varijabla koja će računati ukupno vrijeme koje je do sada prošlo

    vector<bool> help(length+1,true); //duljine len+1 jer indeksi predstavljaju poslove, a poslove numeriramo od 1 do 'n'
    help[ a ] = false; //zastavica, ostali imaju vrijednost 1(ok)

    while( num<length ){

        testm = false;
        testd = false;

        //tražimo pozicije posla 'a' u roditeljima da vidimo tko ima manji setup time do slj. posla u svome rasporedu
        i =  mom.position( jobs[num-1] );
        if( i==(length-1) ) i = 0; //jer gledamo koji posao dolazi nakon posla 'a' u mom, a ako se posao 'a' u mom nalazi na posljednjoj poziciji, potrebno je gledati "sljedeći" posao na poziciji 0 u mom
        else i++;
        j = dad.position( jobs[num-1] );
        if( j==(length-1) ) j = 0;
        else j++;

        //provjeri jesu li poslovi mom[i] ili dad[i] već u child
        if( help[ mom[i] ]==false ) testm = true;
        if( help[ dad[j] ]==false ) testd = true;

        //ako jesu oba
        if( testm && testd ){
            a = rand() % length + 1; //nasumičnim odabirom odaberemo novi posao
            while( help[a]==false ) a = rand()% length + 1; //sve dok ne nađemo posao koji još nije u child
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }
        else if( testm ){ //ako je samo mom[i] unutar child
            a = dad[j];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }
        else if( testd ){ //ako je samo dad[j] unutar child
            a = mom[i];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }

        //niti mom[i] niti dad[j] nisu u child
        cm = problem.due_date[ mom[i]] - (sum_times + problem.setup_times[ jobs[ num-1] ][ mom[i] ] + problem.process_time[ mom[i] ]);
        cd = problem.due_date[ dad[j]] - (sum_times + problem.setup_times[ jobs[num-1] ][ dad[j] ] + problem.process_time[ dad[j] ]);

        //uzimamo onaj koji ima veću razliku između du_date i vremena izvršavanja do sada - da ga se što prije riješimo
        //ovo funkcionira i kad su oba cm i cd negativni->uzmemo manje po abs vr, ili kad je jedan od njih neg a drugi poz->uzmemo poz
        if( cm>=cd ){
            a = mom[i];
            jobs[ num ] = a;
            help[ a ] = false;
            sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
            num++;
            continue;
        }

        a = dad[j];
        jobs[ num ] = a;
        help[ a ] = false;
        sum_times += problem.setup_times[ jobs[num-1] ][a] + problem.process_time[a];
        num++;
        continue;
    }

    calculate_tt( problem );
}

void Permutation::heuristic_crossover_best( SMSP& problem, Permutation& mom, Permutation& dad ){
    if( mom.number_of_jobs() != dad.number_of_jobs() ) throw runtime_error("Can't preform crossover on parents with different sizes!");
    int num = mom.number_of_jobs();
    if( num==0 ) return;

    Permutation best = (*this);
    heuristic_crossover( problem, mom, dad, 1);
    int min_tt = tt;

    for( int a=2; a<=num; a++ ){
        heuristic_crossover( problem, mom, dad, a);
        if( tt < min_tt ) {
            min_tt = tt;
            best = (*this);
        }
    }
    (*this) = best;
}


//Stvaranje nasumične permutacije iz postojeće - odnosno rasporeda
void Permutation::random(){
	if( (jobs==NULL) || length<1 ) throw runtime_error("Schedule is empty. You can't make random permutation!");
	int k = 0, l = 0;
	int swap;
	for( int i=0; i<(length+1)/2; i++ ){
		k = rand() % length;
		l = rand() % length;
		swap =  jobs[k];
		jobs[k] = jobs[l];
		jobs[l] = swap;
	}		
}

//Stvara nasumičnu permutaciju - odnosno raspored duljine 'size' "permutiranjem" postojeće
void Permutation::random( int n ){
	if( n < 0 ) throw runtime_error("Size is too small!");
	
	length = n;
	if( jobs!=NULL ) delete[] jobs;
	jobs = new int[n];
	//postavimo neke vrijednosti u raspored
	for( int i=0; i<length; i++ ) jobs[i] = i+1;

	if( jobs!=NULL && length>0 ){
		int k = 0, l = 0;
		int swap;
		for( int i=0; i<(length+1)/2; i++ ){
			k = rand() % length;
			l = rand() % length;
			swap =  jobs[k];
			jobs[k] = jobs[l];
			jobs[l] = swap;
		}		
	}
}
