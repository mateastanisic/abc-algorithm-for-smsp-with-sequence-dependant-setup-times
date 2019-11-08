# abc-algorithm-for-smsp-with-sequence-dependant-setup-times

Opis problema

● Skup N nezavisnih poslova {J1,J2,…,JN} koji se trebaju izvršiti na nekom stroju bez prekida

● Za svaki posao Ji zadani su nam:
    – Processing time pi
    – Due date di
    – Setup times sij
    
● Pronaći raspored Q = {Q(0),Q(1),…,Q(N)} za poslove {J1,J2,…,JN} takav da je ukupno zakašnjenje ( total tardiness TTQ(i) ) poslova
minimalno

● 1 | sij | ΣTi

● Zakašnjenje TQ(i)= max{0,CQ(i)-di}  -- CQ(i) vrijeme završetka posla Ji

● 1990. Du J, Leung JY  --> 1 | ΣTi je NP-težak problem



Za rješavanje problema koristili smo:
     - Pčelinji algoritam

Rezultate smo usporedili sa algoritmima:
     - RSPI
     - Mravlji algoritam
     - Hibrid tabu search / vns
     - Hibrid simulirano kaljenje / tabu search
     

