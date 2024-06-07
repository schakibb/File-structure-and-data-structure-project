#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "LOVC.h"
// on a utiliser vscode
//Haddadi chakib
//Baslimane lokmane Elhakim
int main()
{
    int choix1, choix2;
    int fin = 0;
    int N;
    Fichier fichier;
    FILE *fichierTest;
    int id;
    Bloc buf;

    printf("\033[1;34m"); // Set text color to blue
    printf("\n\n\t\t\t\t Bienvenue au Projet de SFSD : Gestion des Contacts\n\n\n");
    printf("\033[0m");
    while (fin == 0)
    {
        printf("\033[1;36m"); // Set text color to cyan
        printf("\t\t\t\033[1;33mManuel:\033[0m\n");
        printf("\033[1;36m");
        printf("\t\t\t1-Creation du fichier avec des contacts aleatoire\n");
        printf("\t\t\t2-Recherche d'un contacts\n");
        printf("\t\t\t3-Insertion d'un contact \n");
        printf("\t\t\t4-Supprimer un contact (Suppresion logique)\n");
        printf("\t\t\t5-Quitter\n\n");
        printf("\033[0m");
        printf("\t\t\tVotre choix : ");
        scanf("%d", &choix1);
        switch (choix1)
        {
        case 1:
            printf("\n\n\t\t\t\033[1;32mVeuillez entrer le nombre de Contacts: \033[0m");
            scanf("%d", &N);
            CreactionFichier(&fichier, "Contacts.bin", N);
            printf("\n\t\t\t Creation effectuee avec succes\n");
            break;

        case 2:

            if (fichierTest = fopen("Contacts.bin", "rb"))
            {
                fclose(fichierTest);
                int id;
                int i;
                int j;
                bool trouv;
                Ouvrir(&fichier, "Contacts.bin", 'A');
                printf("\n\n\t\t\t\033[1;35mVeuillez entrer le Id du Contact que vous recherchiez : \033[0m");
                scanf("%d", &id);
                Recherche(&fichier, "Contacts.bin", id, &i, &j, &trouv);
                if (trouv)
                {
                    printf("\n\t\t\t*Le Contact se trouve dans le bloc %d a la position %d*\n", i, j);
                }
                else
                {
                    printf("\n\t\t\t\x1b[31mLe Id que vouz avez entre n'existe pas\n\033[0m");
                }
            }
            else
            {
                printf("\n\n\t\t\t\x1b[31mLe fichier n'existe pas, veuillez d'abord Creez un fichier avec des Contacts Aleatoires au choix 1\n\033[0m");
            }

            break;
        case 3:
            if (fichierTest = fopen("Contacts.bin", "rb"))
            {
                fclose(fichierTest);
            }
            else
            {
                Ouvrir(&fichier, "Contacts.bin", 'N');
                Fermer(&fichier);
            }
            int i, j;
            bool trouv;
            do
            {
                printf("\n\n\t\t\t\033[1;33m Veuillez entrer le Id du contact que vous voulez inserer : \033[0m");
                scanf("%d", &id);
                Recherche(&fichier, "Contacts.bin", id, &i, &j, &trouv);
            } while (trouv);
            char *contact = EntrerContact(id);
            Insertion(&fichier, "Contacts.bin", contact);
            Fermer(&fichier);

            break;
        case 4:
            if (fichierTest = fopen("Contacts.bin", "rb"))
            {
                fclose(fichierTest);
                printf("\n\n\t\t\t\033[1;33m Veuillez entrer le Id du Contacts que vous voulez supprimer : \033[0m");
                scanf("%d", &id);
                Ouvrir(&fichier, "Contacts.bin", 'A');
                SupressionLogique(&fichier, "Contacts.bin", id);
                Fermer(&fichier);
            }
            else
            {
                printf("\n\n\t\t\tLe fichier n'existe pas, veuillez d'abord generer les Contactss alÃ©atoires au choix 1\n");
            }
            break;
        default:
        {
            fin = 1;
            break;
        }
        }
        if (fichierTest = fopen("Contacts.bin", "rb"))
        {
            printf("\n\n\t\t\tContenu de l'Entete : \n");
            AfficherEntete(&fichier);
            printf("\n\n\t\t\tTu veux Afficher le fichier?\n\t\t\t1-Oui 2-Non\n\t\t\tChoix : ");
            scanf("%d", &choix2);
            if (choix2 == 1)
            {
                AfficherFichier(&fichier, "Contacts.bin");
                Fermer(&fichier);
                printf("\033[0m");
            }
        }

        if (fin == 0)
        {
            printf("\n\t\t\tVoulez vous quitter?\n\t\t\t1-Oui 2-Non\n\t\t\tChoix : ");
            scanf("%d", &choix1);
        }
        if (choix1 == 1)
            fin = 1;
    }
}
