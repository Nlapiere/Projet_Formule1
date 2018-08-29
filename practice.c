#include "utilitaire.h"
#include "practice.h"

double time1 = 5400;
double time2 = 5400;
double time3 = 3600;

void practice(int index, int p)
{
	semop(id_sem, &semWait, 1);//on bloque le sem
	semop(id_sem, &semDo, 1);
	double time = getCurrTime();//on récupère l'heure
	semop(id_sem, &semPost, 1);//on débloque le sem
	
	double timePractice;//détermination du temps d'essai
	if(p==1){
		timePractice = time1;
	}
	if(p==2){
		timePractice = time2;
	}
	if(p==3){
		timePractice = time3;
	}
	//fonction d'actualisation de la variable globale
	while(time<timePractice && (cars[index].isOut == 0)){
		generateTimeS1(index);//premier secteur
		if(cars[index].bestS1 < smv[7]){//si c'est le meilleur temps, actualisation
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			semop(id_sem, &semPost1, 1);
		}		
		generateTimeS2(index);//deuxième secteur
		if(cars[index].bestS2 < smv[8]){//si c'est le meilleur temps, actualisation
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			semop(id_sem, &semPost1, 1);
		}
		generateTimeS3(index);//troisième secteur
		if(cars[index].bestS3 < smv[9]){//si c'est le meilleur temps, actualisation
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			semop(id_sem, &semPost1, 1);
		}
		if(cars[index].bestCircuit>smv[10]){//si c'est le meilleur temps, actualisation
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			semop(id_sem, &semPost1, 1);
		}
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		time = getCurrTime();//actualisation du temps
		semop(id_sem, &semPost, 1);
	}
	//actualisation, signal que la voiture a fini ses essais au parent
	if(p==1){
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[0]++;
		semop(id_sem, &semPost1, 1);
	}
	else if(p==2){
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[1]++;
		semop(id_sem, &semPost1, 1);
	}
	else{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[2]++;
		semop(id_sem, &semPost1, 1);
	}
}
//générer une feuile de récap pour les essais
void generateRecapFilePractice(){
	FILE *fichier = NULL;
	fichier = fopen("Résultats essais.txt", "a");
	structCar temp = cars[0];
	temp.bestCircuit=10000;
	if(fichier != NULL){
		
		fprintf(fichier,"\n| Numéro voiture |     Meilleur temps S1    |     Meilleur temps S2    |     Meilleur temps S3    |    Meilleur tour     |\n");
		
		for(int i = 0; i < 20; i++){
			if((temp.bestCircuit>cars[i].bestCircuit)&&(cars[i].bestCircuit != 0)){temp=cars[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit);
		}
		fprintf(fichier,"\n Vainqueur : %2d avec %9f s\n",temp.name, temp.bestCircuit);
		fclose(fichier);
	}
	else{
		printf("Erreur d'ouverture");
	}	
	for(int i=0; i<20; i++){//on réinitialise les temps des voitures au même niveau
		reset(i);
	}
}
