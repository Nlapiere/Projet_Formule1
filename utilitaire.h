/*
 * Commencer les essais
 */
void practice(int index, int p);
/*
 * Créer une feuille de résultats
 */
void generateRecapFilePractice();
/*
 * Trie les voitures en fonction de leur temps et du nombre de tour
 * @pre : carsRace not null
 * @post : modifie carsRace (nouvel ordre)
 */
void sortCarsByCurrTime(structCar carsRace[]);

/*
 * Lance la course sur carsRace
 * @pre : carsRace not  null
 * @post : modifie carsRace
 */
void race(int index);

/*
 * Créé un fichier avec le récap de la course
 * @pre : carsRace not null
 * @post : crée un fichier avec le récap de la course
 */
void generateRecapFileRace();

#endif /* race_h */
