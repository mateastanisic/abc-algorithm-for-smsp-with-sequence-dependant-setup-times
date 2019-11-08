// #include "smsp.h"
// #include "permutation.h"
#include "population.h"

//Ovo je glavni program u kojemu ćemo implementirati naš pseudokod za rješavanje problema SMSP WITH SEQ.DEP. SETUP TIMES pomoću pčelinjeg algoritma
/*Na početku su nam poznate konstante (fiksirane su):
>>N 			// početni broj pčela, odnosno broj raporeda u populaciji
>>epsilon 		// neki vrlo mali broj, veći od 0 - ako su novo izgenenrirano rješenje i staro najbolje slični (po TT)
>>limit			//za svaki raspored schedules[i] promatraj koliko dugo se nije promjenio, akko je prošlo više ili jednako od limit onda izgeneriraj novi nasumičan raspored schedules[i]
>>selected		//broj koji nam je potreban za neighbourhood_search - iterative greedy algorithm - koliko poslova ćemo "izvaditi" u "fazi uništenja"
>>max			//maksimalan broj iteracija u glavnoj petlji, tj maksimalan broj puta koliko smijemo izgenerirati nove rasporede
>>not_improving	//maksimalan broj iteracija u kojima se najbolji raspored nije poboljšao - pronašli smo najbolji raspored, ili neki vrlo sličan njemu
*/

bool uvjet_1(pair<double, int> i, pair<double, int> j){
	return (i.first < j.first);
}
bool uvjet_2(pair<double, int> i, pair<double, int> j){
	return (i.second < j.second);
}
double dsecnd(void){
	return (double)(clock()) / CLOCKS_PER_SEC;
}

void ABC(const char *file, int N, float epsilon, int limit, int selected, int max, int not_improving)
{

	//-----INITIALISATION PHASE-----

	//Za scout phase - da znamo u koliko se iteracija raspored Qi nije izmjenio
	vector<int> limits(N);		 //inicijalizirano s nulama
	vector<bool> test_limits(N); //incijalizirano s "nulama" - false

	//Učitavamo problem iz datoteka
	SMSP benchmark;

	benchmark.load_benchmark(file);

	//inicijaliziramo početnu populaciju od N rasporeda - nasumično
	//računa tt svakog takvog rasporeda
	Population populacija(N, benchmark.jobs, benchmark);

	//moramo paziti na kriteriji glavne petlje u algoritmu - ne smije se iterirati više od max puta
	//ako se najbolje rješenje nije poboljšalo više od non_improving broja iteracija
	int number_of_iteration = 0, number_not_improving = 0;
	int i_tt, new_tt, best_tt, new_best_tt;
	Permutation best(benchmark.jobs, benchmark); //incijalizacija rasporeda 1234....

	//-----MAIN LOOP-----

	while (number_of_iteration <= max && number_not_improving <= not_improving)
	{

		//ušli smo u još jednu iteraciju - povećavamo broj ukupnih iteracija
		number_of_iteration++;
		//povećavamo i broj iteracija u kojima se nije poboljšalo najbolje rješenje -  ako se ipak poboljša na kraju, kada poboljšamo, ipak postavljamo number_not_improving na 0
		number_not_improving++;

		for (int j = 0; j < N; j++) test_limits[j] = false;

		best = populacija.select_best();
		if (best.total_tardiness() == 0) break;

		//-----EMPLOYED BEES PHASE-----
		//promatraju sve rasporede podjednako,nešto bolje promatraju najbolji raspored
		for (int i = 0; i < N; i++)
		{
			//unaprijeđujemo svaki raspored schedules[i]

			//ako je raspored schedules[i] jednak najboljem rasporedu (overall),
			//novi generirani raspored schedules[i]' dobiva se sa neighbourhood_search()-om
			Permutation schedule_i_new(populacija[i]);
			if (populacija[i] == best) schedule_i_new.neighbourhood_search(benchmark, selected); //cout<<"and after IG: tt="<<schedule_i_new.total_tardiness()<<endl;}
			//ako raspored schedules[i] nije jednak najboljem, onda se generira novi raspored schedules[i]' sa nekim križanjem
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

			i_tt = populacija[i].total_tardiness();	//da ne moramo stalno pozivati funkcije
			best_tt = best.total_tardiness();		   //da ne moramo stalno pozivati funkcije
			new_tt = schedule_i_new.total_tardiness(); //da ne moramo stalno pozivati funkcije

			//ako novo-izgenerirani raspored ima manje tt od trenutno najboljeg ili je njihova relativna razlika manja od epsilon
			//novi raspored se generira ( i to sa lokalnim pretraživanjem )

			float dif = (float) ( (float)(new_tt - best_tt) / new_tt );
			if ((new_tt <= best_tt) || (dif < epsilon)) schedule_i_new.local_search(benchmark);

			//na kraju jedne iteracije ove petlje gleda se je li novo izgenerirani raspored schedules[i]' bolji od početnog rasporeda schedules[i]
			//ako je,mjenja se, inače ne
			new_tt = schedule_i_new.total_tardiness(); //treba update-ati new_tt u slucaju da se izvrtio local search
			if (new_tt < i_tt){
				populacija[i] = schedule_i_new;
				limits[i] = 0;
				test_limits[i] = true;
			}
		}

		//CALCULATING PROBABILITIES
		populacija.probability();

		//CALCULATING "NECTAR" ON EACH FOOD SOURCE
		vector<pair<double, int>> onlook_num(N); //vektor parova -
		//double vrijednosti koja sadrži br.rasporeda*vjerojatnost da se izabere taj raspored ( u odnosu na sve rasporede koje trenutno imamo )
		//a druga vrijednost para je int - broj posla - potrebno pamtiti zbog sortiranja poslije
		bool test = true; //provjerava jesu li svi rasporedi jednako vjerojatni

		for (int i = 0; i < N; i++){
			pair<double, int> par = make_pair(N * populacija.probability_i(i), i + 1);
			onlook_num[i] = par;
			if (test && (N * populacija.probability_i(i) != 1) ) test = false;
		}

		//ako su sve N*prob jednake 1 ne trebamo zaokruživati na najbliže
		if (!test){
			//sortirano po vrijednosti N*prob
			sort(onlook_num.begin(), onlook_num.end(), uvjet_1);

			double lower_sum = 0;
			for (int j = 0; j < N; j++)
			{
				double result = (int)floor(onlook_num[j].first);  //donje cijelo
				double difference = onlook_num[j].first - result; //pogreška kod "zaokruživanja"
				pair<double, int> par = make_pair(difference, onlook_num[j].second);

				lower_sum += result;
			}

			//postavljamo prave vrijednosti na onlook_num[j].first
			for (int j = 0; j < N; j++){
				if (j < lower_sum) (onlook_num[j]).first = (int)(floor(onlook_num[j].first));
				else (onlook_num[j]).first = ((int)floor(onlook_num[j].first)) + 1;
			}

			sort(onlook_num.begin(), onlook_num.end(), uvjet_2);
		}

		//ONLOOK BEES PHASE
		//dodatno promatraju bolje rasporede
		for (int i = 0; i < N; i++){

			for (int j = 0; j < onlook_num[i].first; j++)
			{

				//za svaki takav raspored koji je odabran u ovoj fazi generiramo novi raspored sa neighbourhood_search() tj. IG-om

				Permutation schedule_i_new(populacija[i]);
				i_tt = populacija[i].total_tardiness(); //da ne moramo stalno pozivati funkcije

				schedule_i_new.neighbourhood_search(benchmark, selected);
				new_tt = schedule_i_new.total_tardiness(); //da ne moramo stalno pozivati funkcije

				//ako je takav novi raspored sličan ili bolji starom detaljnije ga prouči - LS
				float dif = (float)((float)(new_tt - best_tt) / new_tt);
				if ((new_tt <= best_tt) || (dif < epsilon) )
					schedule_i_new.local_search(benchmark);

				//ako smo našli neki bolji raspored od početnog, zamjeni ih
				if (new_tt < i_tt)
				{
					populacija[i] = schedule_i_new;
					limits[i] = 0;
					test_limits[i] = true;
				}
			}
		}

		//SCOUT BEES PHASE
		for (int i = 0; i < N; i++){
			//niti u EBP niti u OBP raspored Qi se nije izmjenio te je potrebno povećati broj limits[i] koji označava u koliko se iteracija za redom raspored Qi nije izmjenio
			if (!test_limits[i])
				limits[i]++;

			//ako se neki od rasporeda schedules[i] nije izmjenio u više od 'limit' iteracija glavne petlje (zadana konst. na početku)
			//onda nasumično izgeneriraj novi schedules[i]
			if (limits[i] >= limit)
			{
				populacija[i].random();
				populacija[i].calculate_tt(benchmark);
			}
		}

		//pamti se najbolji raspored - s najmanjom TT
		//ako je neki od novih rasporeda bolji od trenutnog najboljeg, updejta se najbolji raspored i number_not_improving=0
		Permutation new_best(populacija.schedule_size());
		new_best = populacija.select_best();
		new_best_tt = new_best.total_tardiness();

		if ((new_best != best)){
			best = new_best;
			number_not_improving = 0;
		}

		if (best.total_tardiness() == 0) break;
	}
	//-----END OF MAIN LOOP-----

	//ispišemo najbolje riješenje
	//cout<<file<<endl<<best<<endl<<"ABC: "<<best.total_tardiness()<<endl<<"B&B: "<<benchmark.solution<<endl<<endl<<endl;
	cout << best.total_tardiness()<<endl;
}

int main(){


	return 0;
}
