#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// definition des jours
#define jour 7
int capacite[jour];

//definition des capacités minimun et maximun
#define capMin 125
#define capMax 250
#define colonne 6

void premierChoix(int nblignes,int matrice[nblignes][colonne],int resultat[nblignes],int repartition[jour]){
    // on vas parcourir la liste en donnant le choix 1 à toutes les familles
    int nombrePersonne = 0;
    int k;
    for(k=0;k<nblignes;k++){
        int choix = matrice[k][1];
        resultat[k] = choix;
        repartition[choix] += matrice[k][0];
        nombrePersonne +=matrice[k][0];
    }
    printf("Nombre de Personne : %d\n",nombrePersonne);


}

int attribution(int nblignes,int matrice[nblignes][colonne],int resultat[nblignes],int repartition[jour]){

        int k;
        double choix2 = 0;
        double choix3 = 0;
        double choix4 = 0;
        double choix5 = 0;
        // dans le même temps on vas calculer les cout qui sont à 0 au début car tout le monde a son premier choix
        int cout = 0;
        while(repartition[0]>capMax || repartition[1]>capMax|| repartition[2]>capMax || repartition[3]>capMax || repartition[4]>capMax || repartition[5]>capMax || repartition[6]>capMax ){
           for(k=0;k<nblignes;k++){
                // On regarde le jour d'attributation de la famille et si c'est dans dans une journée remplis on la change
                if(repartition[resultat[k]] >capMax){
                    // on vas regarder les autres choix de la famille et lui donner le meilleur choix en prenant en compte son nombre
                    int nbPersonne = matrice[k][0];
                    // on regarde son choix 2 et si on peut lui donner ce choix on le fait
                    if(repartition[matrice[k][2]]+nbPersonne < capMax){
                            // on l'enleve de son choix precedent
                            repartition[resultat[k]] = repartition[resultat[k]] - nbPersonne;
                            // on change son choix
                            resultat[k] = matrice[k][2];
                            // et on reatribut son choix
                            repartition[resultat[k]] = repartition[resultat[k]] + nbPersonne;
                            printf("la famille %d a eu son choix 2 c'est a dire le jour %d\n",k,resultat[k]);
                            cout += 50;
                            choix2 ++;
                            break;
                    }
                    // on regarde son choix 3 et si on peut lui donner ce choix on le fait
                    if(repartition[matrice[k][3]]+nbPersonne < capMax){
                            // on l'enleve de son choix precedent
                            repartition[resultat[k]] = repartition[resultat[k]] - nbPersonne;
                            // on change son choix
                            resultat[k] = matrice[k][3];
                            // et on reatribut son choix
                            repartition[resultat[k]] = repartition[resultat[k]] + nbPersonne;
                            printf("la famille %d a eu son choix 3 c'est a dire le jour %d\n",k,resultat[k]);
                            cout += 50 + 9*nbPersonne;
                            choix3 ++;
                            break;
                    }
                    // on regarde son choix 4 et si on peut lui donner ce choix on le fait
                    if(repartition[matrice[k][4]]+nbPersonne < capMax){
                            // on l'enleve de son choix precedent
                            repartition[resultat[k]] = repartition[resultat[k]] - nbPersonne;
                            // on change son choix
                            resultat[k] = matrice[k][4];
                            // et on reatribut son choix
                            repartition[resultat[k]] = repartition[resultat[k]] + nbPersonne;
                            printf("la famille %d a eu son choix 4 c'est a dire le jour %d\n",k,resultat[k]);
                            cout += 100 + 9*nbPersonne;
                            choix4 ++;
                            break;
                    }
                    // on regarde son choix 4 et si on peut lui donner ce choix on le fait
                    if(repartition[matrice[k][5]]+nbPersonne < capMax){
                            // on l'enleve de son choix precedent
                            repartition[resultat[k]] = repartition[resultat[k]] - nbPersonne;
                            // on change son choix
                            resultat[k] = matrice[k][5];
                            // et on reatribut son choix
                            repartition[resultat[k]] = repartition[resultat[k]] + nbPersonne;
                            printf("la famille %d a eu son choix 5 c'est a dire le jour %d\n",k,resultat[k]);
                            cout += 200 + 9*nbPersonne;
                            choix5 ++;
                            break;
                    }

                }
            }
        }
        choix2 = (choix2/nblignes)*100;
        choix3 = (choix3/nblignes)*100;
        choix4 = (choix4/nblignes)*100;
        choix5 = (choix5/nblignes)*100;

        printf("Pourcentage de choix 1 : %f\n",100-choix2-choix3-choix4-choix5);
        printf("Pourcentage de choix 2 : %f\n",choix2);
        printf("Pourcentage de choix 3 : %f\n",choix3);
        printf("Pourcentage de choix 4 : %f\n",choix4);
        printf("Pourcentage de choix 5 : %f\n",choix5);
        return cout;
}

double penalites(int repartition[jour]){
    int i;
    double penalite =0;
    for (i=0;i<6;i++){
            double pop = repartition[i];
            double popt = repartition[i+1];
            penalite += ((pop-125)/400)*pow(pop,abs(pop-popt)/50);
    }
    double popfin = repartition[6];
    penalite += (popfin-125)/400;
    return penalite;

}

void nouvelleFamille(int repartition[jour]){
    //création des 3 famille aleatoirement
    int famille[3];
    famille[0] = rand() % 4 + 3;
    famille[1] = rand() % 4 + 3;
    famille[2] = rand() % 4 + 3;

    printf("La premiere Famille est de taille : %d\n",famille[0]);
    printf("La deuxieme Famille est de taille : %d\n",famille[1]);
    printf("La troisieme Famille est de taille : %d\n",famille[2]);

    // affectation des familles dans le jour ou il y a le moins de personne
    int i;
    for(i=0;i<3;i++){
        int jourmin = minimun(repartition);
        repartition[jourmin] += famille[i];
        printf("La famille %d vas dans le jour %d\n",i,jourmin);
    }
}

int minimun(int repartition[jour]){
    int minimun = 0;
    int i;
    for(i=0;i<jour;i++){

        if(repartition[minimun]>repartition[i]){
            minimun = i;
        }
    }
    return minimun;
}

int main()
{

    FILE *fichier = fopen("pb50.csv", "r");
    int nblignes = 0;
    char ligne[1024];
    // On vas lire le fichier une première fois afin de determiner le nombre de famille
    // Déterminer la taille de la matrice
    while (fgets(ligne, 1024, fichier))
    {
        char *valeur;
        valeur = strtok(ligne, "\n");
        nblignes++;
    }

    //printf("Nombre de lignes : %d\n", nblignes);
    int matrice[nblignes][colonne];

    rewind(fichier);

    int ligne_actuelle = 0;
    // On relit la fichier et on stocke tout dans une matrice
    while (fgets(ligne, 1024, fichier))
    {
        char *valeur;
        int colonne_actuelle = 0;
        valeur = strtok(ligne, "\n;");

        while (valeur != NULL)
        {
            matrice[ligne_actuelle][colonne_actuelle] = atof(valeur);
            colonne_actuelle++;
            valeur = strtok(NULL, "\n;");
        }

        ligne_actuelle++;
    }
    fclose(fichier);

    // On print la matrice pour verifier le résultat
    int i,j;
//    for(i=0; i<nblignes; i++){
//        for(j=0; j<colonne; j++){
//            printf("%d",matrice[i][j]);
//            printf(j<colonne-1?"\t":"\n");
//        }
//    }

    //liste donnant le nombre de personne par jour (initialisé à 0)
    int repartition[jour] = {0,0,0,0,0,0,0};
    //liste donnant le numéro du choix donnée au famille ( allant de 1 à 5)
    int resultat[nblignes];

    //Dans un premier temps on vas attribuer le premier choix a toutes les familles sans se préocuper de la capacité
    premierChoix(nblignes,matrice,resultat,repartition);

    // On affiche la premiere répartition
    printf("Premiere Repartition : ");
    for(i=0;i<jour;i++){
        printf("%d ",repartition[i]);
    }
    printf("\n");
    //Pour l'instant on ne respecte pas les capacité ce qu'on vas faire c'est qu'on vas réattribuer un autre choix au famille dans des journée pleines
    int cout = attribution(nblignes,matrice,resultat,repartition);
    printf("Nouvelle attribution : ");
    for(i=0;i<jour;i++){
        printf("%d ",repartition[i]);
    }
    printf("\nle cout est de : %d\n",cout);

    // Maintenant l'objectif est de calculer les pénalité
    float penalite = penalites(repartition);
    printf("Penalites: %f\n ",penalite);
    // On affiche le cout total
    printf ("Cout Final : %f\n",cout+penalite);

    // On vas maintenant generer 3 familles aléatoirement et les repartir la ou il y a le plus de place
    nouvelleFamille(repartition);
    printf("Derniere attribution apres les nouvelles familles : ");
    for(i=0;i<jour;i++){
        printf("%d ",repartition[i]);
    }
    // On recalcule les pénalités
    penalite = penalites(repartition);
    printf("\nNouvelle Penalites: %f\n ",penalite);
    // la compensation des cout seras expliquer dans le rapport
    printf ("Cout Final après l'ajout des dernieres familles : %f\n",cout+penalite);




}
