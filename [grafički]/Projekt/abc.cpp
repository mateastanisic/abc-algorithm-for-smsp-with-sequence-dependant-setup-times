#include "abc.h"


bool abc::uvjet_1(pair<double, int> i, pair<double, int> j)
{
    return ( i.first < j.first );
}

bool abc::uvjet_2(pair<double, int> i, pair<double, int> j)
{
    return ( i.second < j.second );
}

double abc::dsecnd()
{
    return (double)( clock( ) ) / CLOCKS_PER_SEC;
}

abc::abc(QString file, int N, float epsilon, int limit, int selected, int max, int not_improving, QString &A, QString &B)
{
    //-----INITIALISATION PHASE-----

    //Za scout phase - da znamo u koliko se iteracija raspored Qi nije izmjenio
    vector<int > limits( N ); //inicijalizirano s nulama
    vector<bool > test_limits( N ); //incijalizirano s "nulama" - false

    //Učitavamo problem iz datoteka
    SMSP benchmark;


    QByteArray file_byte;
    file_byte.append(file);

    benchmark.load_benchmark(file_byte.constData());

    //inicijaliziramo početnu populaciju od N rasporeda - nasumično
    //računa tt svakog takvog rasporeda
    Population populacija( N, benchmark.jobs, benchmark );

    //moramo paziti na kriteriji glavne petlje u algoritmu - ne smije se iterirati više od max puta
    //ako se najbolje rješenje nije poboljšalo više od non_improving broja iteracija
    int number_of_iteration = 0, number_not_improving = 0;
    int i_tt, new_tt, best_tt, new_best_tt;
    Permutation best( benchmark.jobs, benchmark ); //incijalizacija rasporeda 1234....


    //-----MAIN LOOP-----

    while( number_of_iteration <= max  &&  number_not_improving <= not_improving ){

        //ušli smo u još jednu iteraciju - povećavamo broj ukupnih iteracija
        number_of_iteration++;
        //povećavamo i broj iteracija u kojima se nije poboljšalo najbolje rješenje -  ako se ipak poboljša na kraju, kada poboljšamo, ipak postavljamo number_not_improving na 0
        number_not_improving++;

        for( int j=0; j<N; j++ ) test_limits[j] = false;

        best = populacija.select_best();
        if( best.total_tardiness()==0 ) break;
        //-----EMPLOYED BEES PHASE-----
        //promatraju sve rasporede podjednako,nešto bolje promatraju najbolji raspored
        for( int i=0; i<N; i++ ){
            //unaprijeđujemo svaki raspored schedules[i]

            //ako je raspored schedules[i] jednak najboljem rasporedu (overall),
            //novi generirani raspored schedules[i]' dobiva se sa neighbourhood_search()-om
            Permutation schedule_i_new( populacija[i] );

            if( populacija[i]==best ) schedule_i_new.neighbourhood_search( benchmark, selected );
            //ako raspored schedules[i] nije jednak najboljem, onda se generira novi raspored schedules[i]' sa križanjem
            //else schedule_i_new.crossover( benchmark, best, populacija[i] );

            else {
                                int b = rand() % 13;
                                if ( b == 0 ) schedule_i_new.PMXcrossover( benchmark, best, populacija[i] );
                                else if ( b == 1 ) schedule_i_new.OXcrossover( benchmark, best, populacija[i] );
                                else if ( b == 2 ) schedule_i_new.OXcrossover_best( benchmark, best, populacija[i] );
                                else if ( b == 3 ) schedule_i_new.heuristic_crossover( benchmark, best, populacija[i] );
                                else if ( b == 4 ) schedule_i_new.heuristic_crossover_best( benchmark, best, populacija[i] );
                                else if ( b == 5 ) {
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.OXcrossover_best(benchmark, best,populacija[i]);
                                    schedule_i_new.heuristic_crossover_best(benchmark, best, temp_schedule);
                                }
                                else if ( b == 6 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.OXcrossover_best(benchmark, best, populacija[i]);
                                    schedule_i_new.heuristic_crossover(benchmark, best, temp_schedule);
                                }
                                else if ( b == 7 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.OXcrossover(benchmark, best,populacija[i]);
                                    schedule_i_new.heuristic_crossover_best(benchmark, best, temp_schedule);
                                }
                                else if ( b == 8 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.OXcrossover(benchmark, best,populacija[i]);
                                    schedule_i_new.heuristic_crossover(benchmark, best, temp_schedule);
                                }
                                else if ( b == 9 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.heuristic_crossover_best(benchmark, best,populacija[i]);
                                    schedule_i_new.OXcrossover_best(benchmark, best, temp_schedule);
                                }
                                else if ( b == 10 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.heuristic_crossover_best(benchmark, best,populacija[i]);
                                    schedule_i_new.OXcrossover(benchmark, best, temp_schedule);
                                }
                                else if ( b == 11 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.heuristic_crossover(benchmark, best,populacija[i]);
                                    schedule_i_new.OXcrossover_best(benchmark, best, temp_schedule);
                                }
                                else if ( b == 12 ){
                                    Permutation temp_schedule(populacija[i]);
                                    temp_schedule.heuristic_crossover(benchmark, best,populacija[i]);
                                    schedule_i_new.OXcrossover_best(benchmark, best, temp_schedule);
                                }
                        }


            i_tt = populacija[i].total_tardiness(); //da ne moramo stalno pozivati funkcije
            best_tt = best.total_tardiness(); //da ne moramo stalno pozivati funkcije
            new_tt = schedule_i_new.total_tardiness(); //da ne moramo stalno pozivati funkcije

            //ako novo-izgenerirani raspored ima manje tt od trenutno najboljeg ili je njihova relativna razlika manja od epsilon
            //novi raspored se generira ( i to sa lokalnim pretraživanjem )
            float dif = (float) ( (float)(new_tt - best_tt) / new_tt );
            if( ( new_tt <= best_tt ) || ( dif < epsilon ) ) schedule_i_new.local_search( benchmark );

            //na kraju jedne iteracije ove petlje gleda se je li novo izgenerirani raspored schedules[i]' bolji od početnog rasporeda schedules[i]
            //ako je,mjenja se, inače ne
            new_tt = schedule_i_new.total_tardiness(); //treba update-ati new_tt u slucaju da se izvrtio local search
            if( new_tt < i_tt ) {
                populacija[i] = schedule_i_new;
                limits[i] = 0;
                test_limits[i] = true;
            }
        }



        //CALCULATING PROBABILITIES
        populacija.probability();

        //CALCULATING "NECTAR" ON EACH FOOD SOURCE
        vector< pair<double, int> > onlook_num(N);
        bool test = true;

        for (int i=0; i<N; i++){
            pair <double, int> par = make_pair (N*populacija.probability_i(i), i+1);
            onlook_num[i] = par;
            if( test && N*populacija.probability_i(i) != 1 ) test = false;
        }

        //ako su sve N*prob jednake 1 ne trebamo zaokruživati na najbliže
        if( !test ){
            //sortirano po vrijednosti N*prob
            sort (onlook_num.begin(), onlook_num.end(), uvjet_1 );

            //pomoćni vektor
            vector <pair<double, int> > help(N);
            double lower_sum = 0;
            for( int j=0; j<N; j++ ){
                double result = (int) floor( onlook_num[j].first ); //donje cijelo
                double difference = onlook_num[j].first - result; //pogreška kod "zaokruživanja"
                pair <double, int> par = make_pair ( difference, onlook_num[j].second );
                help[j] = par;
                lower_sum += result;
            }

            //sortira po pogrešci za zaokruživanje
            sort( help.begin(), help.end(), uvjet_1 );
            //postavljamo prave vrijednosti na onlook_num[j].first
            for( int j=0; j<N; j++ ){
                if( j<lower_sum ) (onlook_num[j]).first = (int)(floor( onlook_num[j].first )) ;
                else  (onlook_num[j]).first = ((int) floor( onlook_num[j].first ))+1;
            }

            sort (onlook_num.begin(), onlook_num.end(), uvjet_2);
        }


        //ONLOOK BEES PHASE
        //dodatno promatraju bolje rasporede
        for( int i=0; i<N; i++ ){

            for( int j=0; j<onlook_num[i].first; j++ ){

                //za svaki takav raspored koji je odabran u ovoj fazi generiramo novi raspored sa neighbourhood_search() tj. IG-om

                Permutation schedule_i_new(populacija[i]);
                i_tt = populacija[i].total_tardiness(); //da ne moramo stalno pozivati funkcije

                schedule_i_new.neighbourhood_search( benchmark, selected );
                new_tt = schedule_i_new.total_tardiness(); //da ne moramo stalno pozivati funkcije

                //ako je takav novi raspored sličan ili bolji starom detaljnije ga prouči - LS
                if( ( new_tt <= best_tt ) || ( ( (new_tt-best_tt) / new_tt ) < epsilon ) ) schedule_i_new.local_search( benchmark );


                //ako smo našli neki bolji raspored od početnog, zamjeni ih
                if( new_tt < i_tt ) {
                    populacija[i] = schedule_i_new;
                    limits[i] = 0;
                    test_limits[i] = true;
                }
            }
        }




        //SCOUT BEES PHASE
        for( int i=0; i<N; i++ ){
            //niti u EBP niti u OBP raspored Qi se nije izmjenio te je potrebno povećati broj limits[i] koji označava u koliko se iteracija za redom raspored Qi nije izmjenio
            if( !test_limits[i] ) limits[i]++;

            //ako se neki od rasporeda schedules[i] nije izmjenio u više od 'limit' iteracija glavne petlje (zadana konst. na početku)
            //onda nasumično izgeneriraj novi schedules[i]
            if( limits[i] >= limit ) {
                populacija[i].random();
                populacija[i].calculate_tt( benchmark );
            }
        }



        //pamti se najbolji raspored - s najmanjom TT
        //ako je neki od novih rasporeda bolji od trenutnog najboljeg, updejta se najbolji raspored i number_not_improving=0
        Permutation new_best(populacija.schedule_size());
        new_best = populacija.select_best();
        new_best_tt = new_best.total_tardiness();

        if( (new_best != best) ) {
            best = new_best;
            number_not_improving = 0;
        }

        if( best.total_tardiness()==0 ) break;
    }
    //-----END OF MAIN LOOP-----

    //ispišemo najbolje riješenje

    cout<<file_byte.constData()<<endl<<best<<endl<<"ABC: "<<best.total_tardiness()<<endl<<"B&B: "<<benchmark.solution<<endl<<endl<<endl;

    for (int i=0; i<best.number_of_jobs(); i++){
        A.append(QString::number(best[i]));
        A.append(" ");
    }

    QString B_;
    B = B_.setNum(best.total_tardiness());

    // cout<<a<<" "<<best.total_tardiness()<<endl;
    a++;
}

