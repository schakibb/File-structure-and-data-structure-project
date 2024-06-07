#ifndef LOVC
#define LOVC
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAILLE_ID 8
#define TAILLE_NOM 30
#define TAILLE_id_TELEPHONE 10
#define TAILLE_ADRESSE_EMAIL 30
#define B 1000 // Taille du bloc
#define NB 4 

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
const char *colors[] = {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_RESET};

// La sturcture du contact
typedef struct Contact
{
    char id[TAILLE_ID];                       // Identifiant unique (ID) : Sur 8 caractères.
    char nom[TAILLE_NOM];                     // Nom complet sur 30 caractères.
    char id_telephone[TAILLE_id_TELEPHONE];   // Numéro de téléphone sur 10 caractères.
    char adresse_email[TAILLE_ADRESSE_EMAIL]; // Adresse email sur 30 caractères.
    char *observations;                       // Observations champ de taille variable pour des notes supplémentaires.
    char sup;                                 // si 1 allors l'enregistrement est supprimé sinon si 1 allors i n'est pas suprrimé
    char taille[NB];                          // Un champ pour sauvegarder la taille du contact
} Contact;

// La sturcture de l'entete de fichier
typedef struct Entete
{
    int adresse_premier_bloc;      // Adresse du premier bloc du fichier.
    int taille_fichier;            // Taille du fichier.
    int nombre_contacts;           // Nombre de contacts.
    int nombre_contacts_inseres;   // Nombre de contacts insérés.
    int nombre_contacts_supprimes; // Nombre de contacts supprimés.
    int nombre_blocs;              // LE nombre de blocs dans le fichier
    int adresse_queue;             //(LÓVC) @ de la queue de la liste des blocs
    int dernier_posotionQueue;     // la dernier position dans le bloc queue
} Entete;

// La sturcture du Bloc
typedef struct Bloc
{
    char tab[B]; // Un tableau de taille B qui contient les enregistrements
    int svt;     // Un champ pour l'adresse du bloc svt
} Bloc;

// La sturcture Du fichier
typedef struct Fichier
{
    struct Entete entete; // Le champ de l'entete
    FILE *fich;           // Le fichier
} Fichier;


// Affecte à un champ de l'entête une certaine valeur
void Aff_entete(Fichier *fichier, int i, int val)
{
    switch (i)
    {
    case 1:
    {
        // Cas 1 : Adresse du premier bloc du fichier
        fichier->entete.adresse_premier_bloc = val;
        break;
    }
    case 2:
    {
        // Cas 2 : Taille du fichier
        fichier->entete.taille_fichier = val;
        break;
    }
    case 3:
    {
        // Cas 3 : Nombre de contacts
        fichier->entete.nombre_contacts = val;
        break;
    }
    case 4:
    {
        // Cas 4 : Nombre de contacts insérés
        fichier->entete.nombre_contacts_inseres = val;
        break;
    }
    case 5:
    {
        // Cas 5 : Nombre de contacts supprimés
        fichier->entete.nombre_contacts_supprimes = val;
        break;
    }
    case 6:
    {
        // Cas 6 : Le nombre de blocs dans le fichier
        fichier->entete.nombre_blocs = val;
        break;
    }
    case 7:
    {
        // Cas 7 : Adresse de la queue de la liste des blocs
        fichier->entete.adresse_queue = val;
        break;
    }
    case 8:
    {
        // Cas 8 : Dernière position dans le bloc queue
        fichier->entete.dernier_posotionQueue = val;
        break;
    }
    default:
    {
        // Cas par défaut : Affiche un message d'erreur si la position dans l'entête
        // n'existe pas
        printf("\t\t\tERREUR: Cette position dans l'entête n'existe pas\n");
        break;
    }
    }
}

// Renvoie pour chaque id le champ de l'entête qui correspond
// la fonction Entete
int entete(Fichier *fichier, int i)
{
    switch (i)
    {
    case 1:
    {
        // Cas 1 : Adresse du premier bloc du fichier
        return fichier->entete.adresse_premier_bloc;
    }
    case 2:
    {
        // Cas 2 : Taille du fichier
        return fichier->entete.taille_fichier;
    }
    case 3:
    {
        // Cas 3 : Nombre de contacts
        return fichier->entete.nombre_contacts;
    }
    case 4:
    {
        // Cas 4 : Nombre de contacts insérés
        return fichier->entete.nombre_contacts_inseres;
    }
    case 5:
    {
        // Cas 5 : Nombre de contacts supprimés
        return fichier->entete.nombre_contacts_supprimes;
    }
    case 6:
    {
        // Cas 6 : Le nombre de blocs dans le fichier
        return fichier->entete.nombre_blocs;
    }
    case 7:
    {
        // Cas 7 : Adresse de la queue de la liste des blocs
        return fichier->entete.adresse_queue;
    }
    case 8:
    {
        // Cas 8 : Dernière position dans le bloc queue
        return fichier->entete.dernier_posotionQueue;
    }
    default:
    {
        // Cas par défaut : Affiche un message d'erreur si la position dans l'entête
        // n'existe pas
        printf("\t\t\tERREUR: Cette position dans l'entête n'existe pas\n");
        return 0;
    }
    }
}

// Ouvrir le fichier selon le mode
void Ouvrir(Fichier *fichier, char *nom_physique, char mode)
{
    if ((mode == 'N') || (mode == 'n')) // Créer un nouveau fichier (mode nouveau)
    {
        fichier->fich = fopen(nom_physique,
                              "wb+"); // Ouvrir le fichier en mode écriture (écrase
                                      // le contenu du fichier s'il existe)
        // Initialiser tous les champs de l'entête
        Aff_entete(fichier, 1, 1);
        Aff_entete(fichier, 2, 0);
        Aff_entete(fichier, 3, 0);
        Aff_entete(fichier, 4, 0);
        Aff_entete(fichier, 5, 0);
        Aff_entete(fichier, 6, 0);
        Aff_entete(fichier, 7, 1);
        Aff_entete(fichier, 8, 0);
        fwrite(&(fichier->entete), sizeof(Entete), 1,
               fichier->fich); // // Enregistrement l'entête dans le fichier
    }
    else
    {
        if ((mode == 'a') ||
            (mode == 'A')) // Ouvrir un ancien fichier (mode ancien)
        {
            fichier->fich = fopen(
                nom_physique,
                "rb+"); // ouverture du fichier en mode binaire lecture et ecriture //
                        // Ouvrir le fichier en mode lecture/ecriture
            fread(&(fichier->entete), sizeof(Entete), 1,
                  fichier->fich); // Lire l'entête et la charger dans le champ entête
        }
        else
        {
            printf("format invalide");
        }
    }
}

// Ferme le fichier
void Fermer(Fichier *fichier)
{
    fseek(fichier->fich, 0,
          SEEK_SET); // repositionnement du curseur en debut de fichier //
                     // Positionne le curseur au début du fichier
    fwrite(&(fichier->entete), sizeof(Entete), 1,
           fichier->fich); // Sauvegarde l'entête
    fclose(fichier->fich); // Ferme le fichier
}

// Lire le bloc d'adresse i
void LireDir(Fichier *fichier, int i, Bloc *buf)
{
    fseek(fichier->fich, (sizeof(Entete) + sizeof(Bloc) * (i - 1)),
          SEEK_SET);                            // Positionner le curseur à l'adresse i
    fread(buf, sizeof(Bloc), 1, fichier->fich); // Lire le bloc
}

// Ecrire le bloc à l'adresse i
void EcrireDir(Fichier *fichier, int i, Bloc *buf)
{
    fseek(fichier->fich, (sizeof(Entete) + sizeof(Bloc) * (i - 1)),
          SEEK_SET);                             // Positionner le curseur à l'adresse i
    fwrite(buf, sizeof(Bloc), 1, fichier->fich); // Ecrire le bloc
}

// Alloue un nouveau bloc et le chaine avec le reste
void AllocBloc(Fichier *f)
{
    Bloc *buf = malloc(sizeof(Bloc)); // Alocation du Bloc
    LireDir(f, entete(f, 7), buf);    // Lire le dernier bloc de la liste
    buf->svt =
        entete(f, 6) + 1;            // Mettre à jour le champ suivant avec le nombre de
                                     // blocs total de la liste + 1 (une nouvelle adresse)
    EcrireDir(f, entete(f, 7), buf); // Ecriture du bloc de queue dans le fichier
    strcpy(buf->tab, "");            // vider la chaine du Bloc
    buf->svt = -1;                   // mise a jour du svt a null
    EcrireDir(f, entete(f, 6) + 1,buf);                           // ecriture du Bloc dans le bloc representatnt la nouvelle queue
    Aff_entete(f, 6, entete(f, 6) + 1); // Incrémenter le nombre de blocs
    Aff_entete(f, 7, entete(f, 6));     // Mettre à jour le champ qui correspond à
                                        // l'adresse du dernier bloc de la liste
}

// Concatène tous les champs de l'enregistrement en une chaine de caractères
char *ConcatContact(Contact contact)
{
    char *str;
    // Alloue l'espace mémoire pour la chaine de caractères
    str = (char *)malloc(
        sizeof(char) *
        (sizeof(contact) + strlen(contact.observations) +100)); // Alloue l'espace mémoire pour la chaine de caractères

    int j = 0;

    str[j] = '|';
    j++;
    for (int i = 0; i < strlen(contact.taille); i++) // Le champ taille
    {
        str[j] = contact.taille[i];
        j++;
    }
    str[j] = '|';
    j++;
    str[j] = contact.sup; // Le champ suprimer
    j += 1;
    str[j] = '|';
    j++;

    for (int i = 0; i < TAILLE_ID; i++) // Le champ Id
    {
        if (i < strlen(contact.id))
            str[j] = contact.id[i];
        else
            str[j] = '|';
        j += 1;
    }
    str[j] = '|';
    j++;

    for (int i = 0; i < TAILLE_NOM; i++) // Le champ Nom
    {
        if (i < strlen(contact.nom))
            str[j] = contact.nom[i];
        else
            str[j] = '|';
        j += 1;
    }
    str[j] = '|';
    j++;
    for (int i = 0; i < TAILLE_id_TELEPHONE; i++) // Le champ Num Tel
    {
        if (i < strlen(contact.id_telephone))
            str[j] = contact.id_telephone[i];
        else
            str[j] = '|';
        j += 1;
    }
    str[j] = '|';
    j++;
    for (int i = 0; i < TAILLE_ADRESSE_EMAIL; i++) // Le champ @ email
    {
        if (i < strlen(contact.adresse_email))
            str[j] = contact.adresse_email[i];
        else
            str[j] = '|';
        j += 1;
    }
    str[j] = '|';
    j++;
    for (int i = 0; i < strlen(contact.observations);
         i++) // Le champ observations
    {
        str[j] = contact.observations[i];
        j += 1;
    }
    str[j] = '|';
    j++;
    str[j] = '&'; // separer les contact avec le caractere &
    j++;
    str[j] = '\0'; // Le dernier caratère de la chaine
    return str;    // Retourner la chaine conacténée
}

// Fonction qui génère un nombre aléatoire dans la plage spécifiée [min, max].
int generer_nombre_aleatoire(int min, int max)
{
    // Utilisation de la fonction rand() pour obtenir un nombre aléatoire.
    // % (max - min + 1) permet d'obtenir un nombre dans la plage [0, max - min],
    // puis on ajoute min pour obtenir un nombre dans la plage [min, max].
    return rand() % (max - min + 1) + min;
}

// Fonction qui génère une chaîne de caractères aléatoire de la longueur
// spécifiée.
void generer_chaine_aleatoire(int longueur, char *chaine)
{
    // Définition des caractères possibles dans la chaîne.
    const char caracteres[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Boucle pour générer chaque caractère de la chaîne.
    for (int i = 0; i < longueur; i++)
    {
        // Utilisation de la fonction generer_nombre_aleatoire pour obtenir un
        // indice aléatoire dans le tableau de caractères, puis attribution du
        // caractère correspondant à la chaîne.
        chaine[i] = caracteres[generer_nombre_aleatoire(0, 51)];
    }

    // Ajout du caractère de fin de chaîne '\0' à la fin de la chaîne générée.
    chaine[longueur] = '\0';
}

// Foncion pou vérifie si un ID a déjà été généré dans un tableau d'IDs.
int estDejaGenere(char ids[][TAILLE_ID], char id[], int taille)
{
    // Parcours du tableau d'IDs existants pour vérifier si l'ID est déjà présent.
    for (int i = 0; i < taille; i++)
    {
        if (strcmp(ids[i], id) == 0)
            return 1; // Retourner 1 si l'ID est déjà généré
    }
    return 0; // Retourner 0 si l'ID n'est pas encore généré
}

// Une fontion pour creer une fichier avec  des contacts aleatoire
void CreactionFichier(Fichier *f, char *nom_physique, int N)
{

    Ouvrir(f, nom_physique, 'N'); // creation dun fichier mode nouveau

    AllocBloc(f); // allocation du premier bloc du fichier

    Bloc buf;

    int i = 1; // Se positionner au début du fichie premier bloc

    int j = 0;

    srand(time(NULL)); // Pour les fonctions aléatoires

    char tab[N][TAILLE_ID];

    for (int k = 0; k < N; k++) // Creer et Inserer les contacts un par un
    {

        LireDir(f, i, &buf); // Lire le bloc

        Contact contact; // Creer un nouveaux contact

        // Generer l'id du contact aleatoire et different
        do
        {
            sprintf(contact.id, "%08d", generer_nombre_aleatoire(10000, 10000000));
        } while (estDejaGenere(tab, contact.id, N));

        generer_chaine_aleatoire(TAILLE_NOM, contact.nom); // generer le nom de taille 30

        sprintf(contact.id_telephone, "0%d",
                generer_nombre_aleatoire(
                    500000000, 599999999)); // genrer le n num de tel de taille 10

        generer_chaine_aleatoire(
            TAILLE_ADRESSE_EMAIL,
            contact.adresse_email); // Generer l'adresse-email de taille 30

        contact.observations = (char *)malloc(
            250 * sizeof(char)); // Genere une taille aleatoire entrer 50 et 250
                                 // pour observations

        generer_chaine_aleatoire(generer_nombre_aleatoire(50, 250),
                                 contact.observations); // Generer l'observations

        contact.sup =
            '0'; // Initialisation de l'indicateur d'supacement logique à 0

        // Calculer la taille
        int taille = NB + 1 + TAILLE_ID + TAILLE_NOM + TAILLE_id_TELEPHONE +
                     TAILLE_ADRESSE_EMAIL + strlen(contact.observations);

        sprintf(contact.taille, "%04d", taille); // generer la taille

        char *str = ConcatContact(contact); // Concaténer tous les champs

        int index = 0;

        while (index < strlen(str)) // Insérer la donnée caractère par caractère
        {
            if (j < B) // Si la position est inférieure à la taille du bloc
            {
                buf.tab[j] = str[index]; // Insérer le caractère
                index++;
                j++;
            }
            else // Si le caractère doit s'insérer dans le bloc suivant
            {
                j = 0;
                EcrireDir(f, i, &buf); // On écrit le bloc
                AllocBloc(f);          // Alloue un nouveau bloc
                i = entete(f, 7);      // Met à jour l'adresse i
                LireDir(f, i, &buf);   // Lire le nouveau bloc
            }
        }
        EcrireDir(f, i, &buf); // Ecrit le dernier bloc
        Aff_entete(f, 2,
                   entete(f, 2) + strlen(str)); // Met à jour la taille du fichier
        Aff_entete(
            f, 8, j); // Met à jour la dernière position dans la queue dans l'entête
    }
    Aff_entete(f, 3, N); // affecter le nbr de carractere inserer
    Fermer(f);           // Fermer le fichier
}

// Fonction qui Recherche un Contact d'aprés son Id
void Recherche(Fichier *fichier, char *nom_physique, int id, int *i, int *j, bool *trouv)
{

    Ouvrir(fichier, nom_physique,
           'A'); // Ouvrir le fichier en mode ancien pour lecture
    // i: l'adresse du bloc et j: la position dans le bloc
    //(i,j) représentent l'emplacement du contact s'il existe sinon où il est
    // supposé placé
    *i = entete(fichier, 1); // initiliser i a ladress du premier bloc
    *j = 0;                  // initaliser la pos de j a 0
    *trouv = false;          // initaliser trouv a false
    int stop = 0;            // initaliser stop a false (stop pour lla fin du fichier)
    char chaine[500];
    Bloc buf;
    int obj;
    int posJ;
    int posI;
    LireDir(fichier, *i, &buf); // Lire le premier bloc
    int k = 0;
    const char delim[] = "|";
    //  Le cas d'un fichier vide
    if ((*i) >= entete(fichier, 6) && (*j) >= entete(fichier, 8)) // Si on arrive à la fin du fichier
        stop = 1;
    while (*i <= entete(fichier, 6) && !(*trouv) && !(stop))
    {
        if ((*i) >= entete(fichier, 6) && (*j) >= entete(fichier, 8))
            stop = 1;
        else
        {
            while (buf.tab[*j] != '&' && (*j) < B)
            {
                if (k == 0)
                {
                    posJ = *j; // Sauvegarder j(le deplacement dans le bloc)
                    posI = *i; // Sauvegarder i(@ du bloc)
                }
                chaine[k] = buf.tab[*j];
                k++;
                *j = *j + 1;
            }

            if (buf.tab[*j] == '&')
            {
                k = 0;
                char *token = strtok(chaine, delim);
                sprintf(chaine, "%s", "");

                while (token != NULL && !(*trouv))
                {
                    if (atoi(token) == id && (chaine[6] == '0'))
                    {
                        *trouv = true; // L'élément a été trouvé et n'est pas suprimer
                    }
                    else
                    {
                        token = strtok(NULL, delim);
                    }
                }

                if (!(*trouv) &&
                    !((*i) >= entete(fichier, 6) && (*j) >= entete(fichier, 8)))
                {
                    (*j) = (*j) + 1; // Passer au contact suivant s'il n'a pas été trouvé
                                     // et c'est pas la fin du fichier
                }
            }
            if (*j >= B) // En cas où le champ est divisé sur plus d'un bloc
            {
                *i = buf.svt;
                *j = 0;                     // Rénitiliser le j à 0 (au début du nouveau bloc)
                LireDir(fichier, *i, &buf); // Lire le bloc suivant
            }
        }
    }
    *j = posJ;
    *i = posI;
}

// Fonction pour entrer les détails d'un contact et les retourner sous forme de
// chaîne formatée
char *EntrerContact(int id)
{
    Contact contact;
    sprintf(contact.id, "%08d", id);
    // Saisie de l'ID avec une limite de 7 caractères
    scanf(contact.id, "%08d", id);

    // Saisie du nom du contact
    printf(
        "\n\t\t\t\033[1;33mVeuillez entrer le nom du contact que vous voulez inserer : \033[0m");
    scanf("%29s", contact.nom);

    // Saisie de l'adresse e-mail avec une limite de 29 caractères
    printf("\n\t\t\t\033[1;33mVeuillez entrer l'adresse_email du contact que vous voulez "
           "inserer : \033[0m");
    scanf("%29s", contact.adresse_email);

    // Saisie du numéro de téléphone avec une limite de 9 caractères
    printf("\n\t\t\t\033[1;33mVeuillez entrer le numero tel du contact que vous voulez "
           "inserer : \033[0m");
    scanf("%9s", contact.id_telephone);

    // Saisie des observations avec une limite de 249 caractères
    printf("\n\t\t\t\033[1;33mVeuillez entrer l'obseravtion contact que vous voulez "
           "inserer : \033[0m");
    contact.observations = (char *)malloc(250 * sizeof(char));
    scanf(" %249s", contact.observations);

    // Calcul de la taille totale
    int taille = TAILLE_ID + TAILLE_NOM + TAILLE_id_TELEPHONE +
                 TAILLE_ADRESSE_EMAIL + strlen(contact.observations);

    // Formatage de la taille
    sprintf(contact.taille, "%04d", taille);

    // Initialisation de l'indicateur de suppression à '0'
    contact.sup = '0';

    // Retourne le contact formaté sous forme de chaîne
    return ConcatContact(contact);
}

// Fonction pour insérer un nouveau contact dans le fichier
void Insertion(Fichier *fichier, char *nom_physique, char *contact)
{
    // Ouverture du fichier en mode ajout
    Ouvrir(fichier, nom_physique, 'A');

    Bloc buf;
    int stop = 0;
    int i = entete(fichier, 6);
    int j = entete(fichier, 8); // Incrémente la position dans le dernier bloc
    int index = 0;

    // Lecture du dernier bloc
    LireDir(fichier, i, &buf);

    // Insertion des données caractère par caractère
    while (index < strlen(contact))
    {
        if (j < B)
        {
            buf.tab[j] = contact[index];
            index++;
            j++;
        }
        else
        {
            j = 0;

            // Écriture du bloc
            EcrireDir(fichier, i, &buf);

            // Allocation d'un nouveau bloc
            AllocBloc(fichier);

            // Mise à jour de l'adresse i
            i = entete(fichier, 7);

            // Lecture du nouveau bloc
            LireDir(fichier, i, &buf);
        }
    }

    // Mise à jour du nombre de caractères insérés dans l'en-tête
    Aff_entete(fichier, 4, entete(fichier, 4) + 1);

    // Écriture du dernier bloc
    EcrireDir(fichier, i, &buf);

    // Mise à jour de la taille du fichier
    Aff_entete(fichier, 2, entete(fichier, 2) + strlen(contact));

    // Mise à jour de la dernière position dans la file dans l'en-tête
    Aff_entete(fichier, 8, j);

    // Mise à jour du nombre de caractères insérés dans l'en-tête
    Aff_entete(fichier, 3, entete(fichier, 3) + 1);

    // Fermeture du fichier
    Fermer(fichier);
}

// Cette fonction supprime logiquement un contact d'après son id
void SupressionLogique(Fichier *fichier, char *nom_physique, int id)
{
    Ouvrir(fichier, nom_physique, 'A');
    bool trouv;
    int i, j;
    Bloc buf;
    // On effectue d'abord une recherche
    Recherche(fichier, nom_physique, id, &i, &j, &trouv);
    if (!trouv) // Si le contact n'a pas été trouvé
        printf("\n\t\t\t\x1b[31m Le id  '%d' n'existe pas ou deja suprimer \033[0m\n", id);
    else // Si le livret a été trouvé
    {
        LireDir(fichier, i, &buf); // On lie ce bloc
        if (j + 6 < B)             // la position du champ eff est dans le bloc courant
        {
            buf.tab[j + 6] = '1'; // On met à jour le champ à 1 ce qui signifie que le contacte a été effacé
        }
        else
        {
            i = buf.svt;               // On passe au bloc suivant
            LireDir(fichier, i, &buf); // On lie ce bloc
            buf.tab[B - j - 6] = '1';  // On met à jour le champ à 1 ce qui signifie que le contacte a été effacé
        }

        buf.tab[6 + j] = '1';

        Aff_entete(fichier, 5,
                   entete(fichier, 5) + 1); // On met à jour le champ (nombre de caractères supprimés) de l'entête
        EcrireDir(fichier, i, &buf);        // On écrit le bloc
    }
}

// Cette fonction affiche l'entete du fichier
void AfficherEntete(Fichier *fichier)
{
    // Définition des labels pour les différentes informations de l'entête
    char *labels[] = {"Adresse du premier bloc", "Taille de Fichier",
                      "Nombre de Contacts", "Nombre de Contacts inseres",
                      "Nombre de Contacts supprimes", "Nombre de blocs"};
    int labelIndex = 0;

    // Définition des couleurs pour le texte (rouge et vert)
    char *couleurs[] = {"\x1b[31m", "\x1b[32m"}; // Red and Green couleurs for text
    int couleur_indice = 0;

    // Affichage des informations de l'entête
    printf("\n");

    // Itération sur différentes informations de l'entête
    for (int i = 1; i <= 6; i++)
    {
        // Alternance des couleurs pour améliorer la lisibilité
        couleur_indice = (couleur_indice + 1) % 2;

        // Affichage du label et de la valeur correspondante de l'entête
        printf("\t\t\t%s: %s%s%d\x1b[0m\n", labels[labelIndex], couleurs[couleur_indice], (i == 1) ? "" : " ", entete(fichier, i));

        // Incrémentation de l'index du label
        labelIndex++;
    }
}

// Cette fonction affiche le fichier bloc par blooc
void AfficherFichier(Fichier *fichier, char *nom_physique)
{
    Bloc buf;
    Ouvrir(fichier, nom_physique, 'A');
    printf("%s", colors[generer_nombre_aleatoire(0, 6)]);

    // Itération sur les blocs du fichier
    for (int i = 1; i <= entete(fichier, 6); i++)
    {
        // Lecture du contenu du bloc
        LireDir(fichier, i, &buf);

        // Affichage du contenu du bloc
        printf("\n\t\t\t Contenu du bloc %d \n", i);
        for (int j = 0; j < B; j++)
        {
            // Vérification pour ne pas dépasser la dernière position du dernier bloc
            if (i == entete(fichier, 6) && j == entete(fichier, 8))
                break;
            else
            {
                // Affichage du caractère du bloc
                if (buf.tab[j] != '\0')
                {
                    if (buf.tab[j] == '&')
                        printf("%s", colors[generer_nombre_aleatoire(0, 6)]);
                    printf("%c", buf.tab[j]);
                }
            }
        }

        // Affichage de l'adresse du bloc suivant
        printf("\n\t\t\t Le bloc suivant est %d ", buf.svt);
    }
}

#endif
