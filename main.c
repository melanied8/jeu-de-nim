#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//PROJET "ALLUMETTES" ALGORITHME EN C
//Laurie BRAL
//Mélanie DANG

//Prototype des fonctions
void initialisationPlateau(bool[],int);
void affichagePlateau(bool[], int);
void modeHumain(int);
bool partieFinie(bool[],int);
int nbAllumettes(bool[],int);
void enleveAllumettes(bool[],int,int);
void modeOrdiNaif(int);
void modeOrdiExpert(int);


//On remplit le tableau avec des true (true = allumettes)
void initialisationPlateau(bool plateau[],int taille)
{
    for(int i=0; i<taille;i++)
    {
        plateau[i]=true;
    }
}

//Fonction pour afficher le tableau
void affichagePlateau(bool plateau[], int taille)
{
    for(int i=0; i<taille;i++)
    {
        if(plateau[i]==true)
            printf(" | ");
        else
            printf(" ");
    }
    printf("\til reste %d allumettes",nbAllumettes(plateau,taille));
}

//On vérifie qu'une partie est finie = plus d'allumettes
bool partieFinie(bool plateau[],int taille)
{
  int cpt=0;

  for(int i=0; i<taille; i++)
  {
      if(plateau[i]==true)
        cpt++;
  }

  if (cpt==0)
    return true;
  else return false;
}

//Compte le nombre d'allumettes restant
int nbAllumettes(bool plateau[],int taille)
{
  int cpt=0;

  for(int i=0; i<taille; i++)
  {
      if(plateau[i]==true)
        cpt++;
  }
  return cpt;
}

//Enleve les allumettes
void enleveAllumettes(bool plateau[],int taille, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=taille-1; j>=0; j--)
        {
            if(plateau[j]==true)
            {
                plateau[j]=false;
                break;
            }
        }
    }
}

//Mode humain
void modeHumain(int taille)
{
    //true = allumette / false = pas d'allumette
    bool plateau[taille];
    //Nombre d'allumettes que le joueur veut retirer
    int nb=0;
    //Nom du joueur 1
    char nomJ1[20];
    //Nom du joueur 2
    char nomJ2[20];
    //Nom du joueur qui joue ce tour
    char nom[20];
    //compteur
    int i=0;

    //Remplissage du tableau : 30 true (=30 allumettes)
    initialisationPlateau(plateau, taille);

    //On demande le nom des joueurs
    printf("Comment s'appelle le joueur 1 ? ");
    fflush(stdin);
    gets(nomJ1);
    printf("Comment s'appelle le joueur 2 ? ");
    fflush(stdin);
    gets(nomJ2);


    while(partieFinie(plateau, taille)!=true)
    {
        //On détermine qui doit jouer
        if(i%2==0)
            strcpy(nom,nomJ1);
        if(i%2!=0)
            strcpy(nom,nomJ2);

        nb = 0;

        //Affichage du plateau
        affichagePlateau(plateau,taille);

        //On vérifie que le joueur choisit un nombre d'allumettes valide
        //On vérifie qu'il reste assez d'allumettes
        while(nb<1 || nb>3 || nbAllumettes(plateau, taille)<nb)
        {
            printf("\nC'est au tour de %s - ",nom);
            printf("Nombre d'allumettes a enlever : ");
            scanf("%d", &nb);

            if(nb<1 || nb>3)
                printf("Veuillez saisir un nombre entre 1 et 3.\n");
            if(nbAllumettes(plateau, taille)<nb)
                printf("On ne peut pas faire ca.\n");
        }

        //On enlève les allumettes
        enleveAllumettes(plateau,taille,nb);
        printf("\n");
        i++;
    }

    //On détermine qui a perdu
    printf("%s a perdu ! ",nom);
}

void modeOrdiNaif(int taille)
{
    //true = allumette / false = pas d'allumette
    bool plateau[taille];
    //Nombre d'allumettes que le joueur veut retirer
    int nb=0;
    //Nom du joueur
    char nomJ[20];
    //Nom du joueur (humain ou ordi) qui joue ce tour
    char nom[20];
    //compteur
    int i=0;

    //On demande le prénom du joueur
    printf("Comment s'appelle le joueur 1 ? ");
    fflush(stdin);
    gets(nomJ);

    //Remplissage du tableau : 30 true (=30 allumettes)
    initialisationPlateau(plateau,taille);

    //Tant qu'il reste des allumettes
    while(partieFinie(plateau, taille)!=true)
    {
        //On détermine qui doit jouer
        if(i%2==0)
            strcpy(nom,nomJ);
        if(i%2!=0)
            strcpy(nom,"Ordi");

        nb = 0;

        //Affichage du plateau
        affichagePlateau(plateau, taille);

        //Si c'est au tour du joueur humain
        if(strcmp(nom,nomJ)==0)
        {
            //On vérifie que le nombre choisit est compris entre 1 et 3
            //On vérifie qu'il reste suffisamment d'allumettes
            while(nb<1 || nb>3 || nbAllumettes(plateau, taille)<nb)
            {
                printf("\nC'est au tour de %s - ",nom);
                printf("Nombre d'allumettes a enlever : ");
                scanf("%d", &nb);

                if(nb<1 || nb>3)
                    printf("Veuillez saisir un nombre entre 1 et 3.\n");
                if(nbAllumettes(plateau, taille)<nb)
                    printf("On ne peut pas faire ca.\n");
            }
        }

        //Si c'est au tour de l'ordi
        if(strcmp(nom,"Ordi")==0)
        {
            printf("\nC'est au tour de %s - ",nom);
            printf("Nombre d'allumettes a enlever : ");
            while(nb<1 || nb>3 || nbAllumettes(plateau, taille)<nb)
            {
                nb = (rand() % 3) + 1;
            }
            printf("%d\n",nb);
        }

       //On enlève les allumettes
        enleveAllumettes(plateau, taille, nb);
        printf("\n");

        i++;
    }

    //On détermine qui a perdu
    printf("%s a perdu ! ",nom);
}

void modeOrdiExpert(int taille)
{
    //true = allumette / false = pas d'allumette
    bool plateau[taille];
    //Nombre d'allumettes que le joueur veut retirer
    int nb=0;
    //Nom du joueur
    char nomJ[20];
    //Nom du joueur (humain ou ordi) qui joue ce tour
    char nom[20];
    //compteur
    int i=0;

    //On demande le prénom du joueur
    printf("Comment s'appelle le joueur 1 ? ");
    fflush(stdin);
    gets(nomJ);
    //Remplissage du tableau : 30 true (=30 allumettes)
    initialisationPlateau(plateau,taille);

    while(partieFinie(plateau, taille)!=true)
    {
        //On détermine qui doit jouer
        if(i%2==0)
            strcpy(nom,nomJ);
        if(i%2!=0)
            strcpy(nom,"Ordi");

        nb = 0;

        //Affichage du plateau
        affichagePlateau(plateau, taille);


        //Si c'est au tour du joueur humain
        if(strcmp(nom,nomJ)==0)
        {
            while(nb<1 || nb>3 || nbAllumettes(plateau, taille)<nb)
            {
                printf("\nC'est au tour de %s - ",nom);
                printf("Nombre d'allumettes a enlever : ");
                scanf("%d", &nb);

                if(nb<1 || nb>3)
                    printf("Veuillez saisir un nombre entre 1 et 3.\n");
                if(nbAllumettes(plateau, taille)<nb)
                    printf("On ne peut pas faire ca.\n");
            }
        }

        //Si c'est au tour de l'ordi
        if(strcmp(nom,"Ordi")==0)
        {
            printf("\nC'est au tour de %s - ",nom);
            printf("Nombre d'allumettes a enlever : ");

            //Si le nb d'allumettes%4==1 -> random
            if(nbAllumettes(plateau,taille)%4==1)
            {
                nb=1;
            }

            //Si le nb d'allumettes%4!=1 -> on fait en sorte que le nb d'allumettes%4=1
            if(nbAllumettes(plateau,taille)%4!=1)
            {
              while((nbAllumettes(plateau, taille)-nb)%4!=1)
              {
                  nb++;
              }

              //Cas particuliers : lorsqu'il reste 4,3 ou 2 allumettes
              if(nbAllumettes(plateau, taille)==4)
                nb=3;
              if(nbAllumettes(plateau, taille)==3)
                nb=2;
              if(nbAllumettes(plateau, taille)==2)
                nb=1;
              if(nbAllumettes(plateau,taille)==1)
                nb=1;
            }

            printf("%d\n",nb);
        }

       //On enlève les allumettes
        enleveAllumettes(plateau, taille, nb);
        printf("\n");
        i++;
    }

    //On détermine qui a perdu
    printf("%s a perdu ! ",nom);
}

int main()
{
    //Random (pour le mode humain vs ordi naïf)
   srand(time(NULL));
   int saisieMenu;
   int saisieMode;
   int taille;
   printf("Bonjour et bienvenue dans le jeu des allumettes\n");
   printf("\nVous allez avoir 3 menus.\n");
   printf("Vous choisirez d'abord si vous voulez voir les règles du jeu ou non, puis le nombre d'allumettes a utiliser, et enfin le mode de jeu.\n");

   while(saisieMenu!=4)
   {
     saisieMenu=0;
     saisieMode=0;
     taille=0;

     printf("\tQue faire ?\n");
     printf("1 - Jouer\n");
     printf("2 - Voir les regles du jeu\n");
     printf("3 - Voir les credits\n");
     printf("4 - Quitter\n");
     scanf("%d",&saisieMenu);

     //Tant que la saisie n'est pas valide, le programme redemande au joueur une saisie
     while(saisieMenu <1 || saisieMenu>4)
     {
       printf("Erreur. Veuillez reessayer.");
       scanf("%d",&saisieMenu);
     }

     //Jouer
     if(saisieMenu==1)
     {
        //On demande au joueur de sélectionner le nb d'allumettes
        printf("Veuillez selectionner le nombre d'allumettes avec lequel vous voulez jouer : ");
        scanf("%d", &taille);

        //On demande au joueur de choisir le mode de jeu
        printf("Veuillez selectionner le mode de jeu : \n");
        printf("1. Humain vs humain\n");
        printf("2. Humain vs ordi (niveau facile)\n");
        printf("3. Humain vs ordi (niveau expert)\n");
        scanf("%d", &saisieMode);

        //Tant que la saisie n'est pas valide, on redemande au joueur de saisir au clavier
        while(saisieMode <1 || saisieMode >3)
         {
            printf("Erreur. Veuillez reessayer.");
            scanf("%d",&saisieMode);
         }

         switch(saisieMode)
         {
         //Jouer au mode humain vs humain
         case 1:
            modeHumain(taille);
            break;
         //Jouer au mode humain vs IA (mode facile -> random)
         case 2:
            modeOrdiNaif(taille);
            break;
         //Jouer au mode humain vs IA (mode difficile)
         case 3:
            modeOrdiExpert(taille);
            break;
         }
     }

     //Voir les règles du jeu
     if(saisieMenu==2)
     {
       printf("Le but du jeu est simple :\n");
       printf("Ce jeu se joue a deux. Vous avez un nombre n d'allumettes.\n");
       printf("A tour de role, chacun des deux joueurs enleve entre 1 et 3 allumette(s) selon ce qu'il souhaite. Le perdant est celui qui doit enlever la derniere allumette.\n");
       printf("\nAttention, il existe 2 niveaux de difficulte en version humain vs ordi.\n");
       printf("Le 1er est plutot simple a battre donc pour les debutants. Mais le dernier...\n");
       printf("Contactez-moi si vous avez reussi (screenshot evidemment ^^), mon e-mail est dans les credits !\n");
     }

     //Voir les crédits
     if(saisieMenu==3)
     {
       printf("\nCredits : \n");
       printf("Laurie Bral : laurie.bral@efrei.net\n");
       printf("Melanie Dang : melanie.dang-thanh-lan@efrei.net\n");
     }

     //Quitter le programme
     if(saisieMenu==4)
     {
       exit(0);
     }

     printf("\n");
   }
}
