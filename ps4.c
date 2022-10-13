#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void afficheGrille(int a, int b, char tab[a][b]){
    for(int j = 0; j < b; j++){
        if(j < 10){
            printf(" %d ", j+1);
        }
        else{
            printf("%d ", j+1);
        }
    }
    printf("\n");
    for(int i = 0; i < a; i++){
        for(int j = 0; j < b; j++){
            printf(" %c ", tab[i][j]);
        }
        printf("\n");
    }
}

void remplir(int a, int b, char tab[a][b], int colonne, int joueur, int *position, char joueurs[]){
    int rempli = 0;
    for(int i = a-1; i >= 0; i--){
        if(tab[i][colonne] == '_'){
            tab[i][colonne] = joueurs[joueur-1];
            *position = i;
            rempli = 1;
            break;
        }
    }
    if(rempli == 0){
        *position = -1;
    }

}
int changerJoueur(int a, int* b ){
    if(a == *b){
        a = 1;
    }
    else{
        a++;
    }
    return a;
}

int aGagne(int a, int b,int ligne,  int colonne, char tab[][colonne], char c, int point){
    int gagne = -1;
    int i = 1;

    int droite = 0;
    int gauche = 0;
    int haut = 0;
    int bas = 0;
    int diagHautD = 0;
    int diagHautG = 0;
    int diagBasD = 0;
    int diagBasG = 0;

    while(tab[a][b+i] == c){
        if(b+i < colonne){
            droite++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a][b-i] == c){
        if(b-i > 0){
            gauche++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;
    
    while(tab[a+i][b] == c){
        if(a+i < ligne){
            bas++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a-i][b] == c){
        if(a-i > 0){
            haut++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a+i][b+i] == c){
        if(b+i < colonne && a+i < ligne){
            diagBasD++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a+i][b-i] == c){
        if(b-i > 0 && a+i < ligne){
            diagBasG++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a-i][b+i] == c){
        if(b+i < colonne && a-i > 0){
            diagHautD++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    while(tab[a-i][b-i] == c){
        if(b-i > 0 && a-i > 0){
            diagHautG++;
            i++;
        }
        else{
            break;
        }
    }
    i = 1;

    if((droite + gauche + 1) == point  || (haut + bas + 1) == point  || (diagBasD + diagHautG + 1) == point  || (diagBasG + diagHautD + 1) == point ){
        gagne = 0;
    }


    return gagne;
}


int main(){

int rejouer = 1;
//si rejouer alors le score est conservé ainsi que le nombre de partie et que les paramètres de la grille sont conservés (nombre de ligne, colonne, point pour gagner) 

while(rejouer == 1){
    //Ajouter un point au score du joueur qui a gagné
    int score[4] = {0, 0, 0, 0};


    int point = 0;
    int colonne = 0;
    int ligne = 0;
    int nbJoueur = 0;

    while(ligne < 4){
        printf("choisissez le nombre de lignes: ");
        scanf("%d",&ligne);
    }
    printf("\n");
    while(colonne < 4){
        printf("choisissez le nombre de colonnes: ");
        scanf("%d",&colonne);
    }
    printf("\n");
    while(nbJoueur < 2 || nbJoueur > 4){
        printf("choisissez le nombre de joueurs: ");
        scanf("%d", &nbJoueur);
    }
    printf("\n");
    while(point < 2 || point > colonne){
        printf("choisissez le nombre de points pour gagner: ");
        scanf("%d", &point);
    }


    int joueur = 1;

    char tab[4] = {'X', 'O', 'N', 'Z'};

    int choix = -1;
    int position = -2;

    int tour = 0;

    char tableau[ligne][colonne];
    for(int i = 0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
            tableau[i][j] = '_';
        }
    }

    afficheGrille(ligne, colonne, tableau);
    while(tour < ligne*colonne){
        printf("Joueur %d: ", joueur);

            scanf("%d", &choix);
            if(choix < 1 || choix > colonne){
                while(choix < 1 || choix > colonne){
                    printf("Colonne hors du tableau\nJoueur %d: ", joueur);
                    scanf("%d", &choix);
                }
            }
            choix--;
            remplir(ligne, colonne, tableau, choix, joueur, &position, tab);
            if(position == -1){
                printf("Colonne remplie, veuillez en choisir une autre\n");
                continue;
            }
            else{
                if(aGagne(position, choix, ligne, colonne, tableau, tab[joueur-1], point) == 0){
                    break;
                }
                joueur = changerJoueur(joueur, &nbJoueur);
                afficheGrille(ligne, colonne, tableau);
                tour++;
            }
        
    }
    if(tour == ligne*colonne){
        printf("Match nul");
    }
    else{
            afficheGrille(ligne, colonne, tableau);
            printf("\nJOUEUR %d A GAGNE !!!\n\n", joueur); 
   
            
    }
    printf("Voulez-vous rejouer ?\n1: Oui\n2: Non\n");
    scanf("%d", &rejouer);
    while(rejouer != 1 && rejouer != 2){
        printf("Veuillez choisir 1 ou 2\n");
        scanf("%d", &rejouer);
    }

}

    return 0;

}
