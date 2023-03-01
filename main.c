#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 200000

/* tout d'abord on veut créer une liste chainée avec chaque ligne du fichier.c
chaque ligne sera un pointeur sur une char char *s
*/

/*creation des elements de la liste*/
typedef struct elem
{
  char *ligne;
  struct elem *next;
} elem;

/* creation de la liste */
typedef struct liste
{
  elem *first;
} liste;

/*initialisation de la liste */

liste *init_liste(void) // O(1)
{
  liste *liste = malloc(sizeof(liste));
  //elem *elem = malloc(sizeof(elem));

  if(liste==NULL /*|| elem==NULL  */)
  {
    exit(EXIT_FAILURE);
  }
  //elem->ligne=NULL;
  //elem->next =NULL;
  liste->first =NULL;
  return liste;
}
/*fonction empilement: pour ajouter des nvx elements*/

void insertion(liste *liste, char *nvligne) // O(1)
{
  elem *new =malloc(sizeof(elem));
  if(liste ==NULL || new ==NULL)
  {
    exit(EXIT_FAILURE);
  }
  new->ligne = strdup(nvligne);
  new->next = liste->first;
  liste->first =new;
}

//suppresion
// liberer l'espace mémoire de la liste

void supression(liste *liste) //O(1)
{
  if(liste==NULL)
  {
    exit(EXIT_FAILURE);
  }
  while (liste->first !=NULL)
  {
    elem *top =liste->first;
    liste->first = liste->first->next;
    free(top->ligne);
    free(top);
  }
  //free(liste->first);
  free(liste);
}

/* une fonction pour afficher la liste que je vais supprimer après*/
//cette fonction donne une bonne indication de comment parcourir la liste chainée
void affiche(liste *liste) //O(n)
{
  if (liste==NULL)
  {
    exit(EXIT_FAILURE);
  }
  elem *current = liste->first;
  while(current !=NULL)
  {
    printf("%s \n",current->ligne);
    current = current->next;
  }
    printf("NULL\n");
}

/* On veut effectuer un pré-traitement de chaque ligne */

/*On supprime les espaces*/
void suprEspace(char *expr, char *res) //O(n)
{
  char *P=expr,*Q=res;
  while(*P!='\0')
  {
    if(*P!=' '&& *P!='\t')
    {
      *Q=*P;
      Q++;
    }
    P++;
  }
  *Q=0;
}
//deux fonctions pour remplacer un mot par un w//
void suprWord(char *expr, char *res) //O(n)
{
  char *P=expr,*Q=res;
  while(*P!='\0')
  {
    if ((*P<'a'|| *P>'z')&&(*P<'A'|| *P>'Z')&&(*P<'0'|| *P>'9')&&(*P!='_')&&(*P!='\\'))
    {
      *Q=*P;
      Q++;
    }
    else
    {
      *Q='w';
      Q++;
    }

    P++;
  }
  *Q=0;
}

void fillWord(char *expr, char *res)//O(n)
{
  char *P=expr,*Q=res;
  while(*P!='\0')
  {
    if (!(*P=='w' && *(P+1)=='w'))
    {
      *Q =*P;
      Q++;
    }
     P++;
  }
  *Q=0;
}

//supprimer les commentaires
void suppCom(char *expr,char *res) //O(n)
{
  char *P=expr, *Q=res;
  while(*P!='\0')
  {
    if ((*(P-2)=='/'&& *(P-1)=='/')||(*(P-2)=='/'&& *(P-1)=='*') )
    {
      break;
    }
    *Q=*P;
    Q++;
    P++;
  }
  *Q=0;
}
//le contenu des chaines de caractères//

void suppStr2(char *expr, char *res) //0(n)
{
  while (*expr != '\0')
  {
    *res++ = *expr++;
    if (*(expr-1) == '"')
    {
      while (*expr != '"')
        expr++;
      *res++ = *expr++;
    }
  }
  *res = 0;
}






//voici la fonction de prétraitement//

 void nettoyage1(liste *l, liste *l_clean) // O(n^2)
{
  if (l==NULL)
 {
    exit(EXIT_FAILURE);
 }
  elem *current = l->first;
  //char *l1;//= malloc(sizeof(char)*strlen(current->ligne)+1); erreur qui nous a fait perdre beaucoup de temps
  //char *l2;//= malloc(sizeof(char)*strlen(current->ligne)+1);
  while(current->next !=NULL)
  {
    char *l1=strdup(current->ligne);
    char *l2=strdup(l1);
    suppStr2(current->ligne,l1);
    suppCom(l1,l2);
    suprWord(l2,l1);
    fillWord(l1,l2);
    suprEspace(l2,l1);
    if ((l1[0]!='\n')&& (l1[0]!='\0'))
    {
        insertion(l_clean,l1);
    }
    //l_clean est la liste chainée après formatage//
    current = current->next;
    free(l1);
    free(l2);
  }
  //free(l1):  erreur;
  //free(l2);
}


float digrammeC(char ch1[],char ch2[]) //O(n^2)
{
  if (strlen(ch2)<strlen(ch1)) return digrammeC(ch2,ch1);
  else
  {
    int p=strlen(ch1)-1;     /*nombre de digramme possible dans une chaine (resultat par denombrement)*/
    int m=strlen(ch2)-1;
    float c=0;
    for(int i=0; i<p;i++)
    {
      for(int j=0;j<m;j++)
      {
        if((ch1[i]==ch2[j])&&(ch1[i+1]==ch2[j+1]))
        { /*comparaison des digrammes caractère par caractère et incrémentation*/
          c++;
          break;
        }
      }
    }
  return c;
  }
}

float dist(char ch1[],char ch2[]) //O(n^2)
{  /*calcule la distance de Dice [n-gramme](float pour obtenir un resultat compris entre 0 et 1)*/
  float n1=strlen(ch1)-1;
  float n2=strlen(ch2)-1;
  float nc=digrammeC(ch1,ch2);
  // gestion des chaines vides
  if (n1+n2==0) return 1;
  return (1-((2*nc)/(n1+n2)));
}

float **mat(liste *L1, liste*L2, int n, int m) // O(n^3)
{/*créer une matrice contenant les distances entre chaque segment contenu dans les listes chainés des 2 fichiers*/
  float ** mat=malloc(sizeof(float*)*n);
  for (int e = 0; e < n; e++)
  {
    mat[e] = malloc (sizeof(float)*m);
  }
  int i=0;
  int j=0;
  elem *segment=L1->first;
  for(i=0;i<n;i++)
  {
    elem *segment2=L2->first;
    for(j=0;j<m;j++)
    {
      mat[i][j]=dist((segment->ligne),(segment2->ligne));
      segment2=segment2->next;
    }
    segment=segment->next;
  }
  return mat;
}


void free_mat( float **mat, int n)
{
  for(int i=0; i<n; i++)
  {
    free(mat[i]);
  }
  free(mat);
}


void affich(float **mat,int n, int m) //O(n^2)
{  /*affiche la matrice des distances*/
  for(int i=0; i<n;i++)
  {
    for (int j=0; j<m; j++)
    {
      printf("%.2f\t",mat[i][j]);
    }
    printf("\n");
  }
}

int l_size(liste *L) // O(n)
{   /*renvoie la taille d'une liste chainé*/
  elem *current=L->first;
  int i=0;
  while ((current->next)!=NULL)
  {
    i++;
    current=current->next;
  }
  return i;

}


void fmat(char ch[],float **mat,int n,int m)// O(n*m)
{
  FILE *fmat=fopen(ch,"w");
  fprintf(fmat,"P2\n");
  fprintf(fmat,"%d %d\n",m,n);
  fprintf(fmat,"100\n");
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      if (!strcmp(ch,"filtrage.pgm"))
      {
        int a=100-100*mat[i][j];
        fprintf(fmat,"%d ",a);
      }
      else
      {
        int a=100*mat[i][j];
        fprintf(fmat,"%d ",a);
      }
    }
    fprintf(fmat,"\n");
  }
  fclose(fmat);
  //return fmat;
}

//calcul de la nouvelle matrice F à partir de celle contenant les distances de Dice et traitée par l'algo glouton
 float **matF(float **mat, int n, int m) // O(n*m)
{
  float **matF = malloc(sizeof(float*)*n);       //initialise la matrice
  for (int i = 0; i < n; i++)
  {
    matF[i] = malloc(sizeof(float)*m);
    for (int j = 0; j < m; j++)
    {
      matF[i][j] = 0;
      float compteur_denominateur=0.0;
      for(int k =-2; k<=2; k++)
      {
        if((i + k >= 0) && (i + k < n) && (j + k >= 0) && (j + k < m))
        {
          compteur_denominateur ++;
          matF[i][j] += mat[i + k][j+k];

        }
      }
      matF[i][j]= (matF[i][j]/compteur_denominateur);

    }
  }
    for (int i=0; i<n;i++)
    {
      for(int j=0;j<m;j++)
      {
        if (matF[i][j]>=0.7)
        {
          matF[i][j]=1;
        }
      }
    }

  return matF;
}


 /*structure pour l'algorithme glouton:
 on veut stocker  l'indice de la ligne, de la colonne et la valeur du min dij à chaque étape*/
typedef struct trio_seg
{
  int numligne;
  int numcolonne;
  float value;
} trio_seg;

int min(int a, int b) // O(1)
{
  int min = a;
  if (min >b) min= b;
  return min;
}

trio_seg init_trouple(void)
{
  trio_seg init_trouple = {-1,-1,2023.00};
  return init_trouple;
}

void glouton(float **matrix,int n, int m) // O(n^2 * m) ou O(m^2 * n)
{
  int u = min(n,m);
  // je crée un tableau de u trouples
  trio_seg *T=malloc(sizeof(trio_seg)*u);
  int c = 0;
  int i =0;
  int j = 0;
  int flag_ligne =2023;
  int flag_colonne =2023;
  while(c<u)
  {
    //voici mon sentinel
    float dij = 2023.00;
    i =0;
    for(i=0; i<n;i++)
    {
      j=0;
      for(j=0;j<m;j++)
      {
        if(dij> matrix[i][j])
        {
          dij = matrix[i][j];
          flag_ligne=i;
          flag_colonne=j;
        }
      }
    }
    // a la fin de cette boucle for j'ai le min de ma matrice
    //je stock ses indices et sa valeur  dans une case de mon tableau
    T[c].numligne =flag_ligne;
    T[c].numcolonne=flag_colonne;
    T[c].value = dij;
    i=0;
    // je refais un  tour de la matrice pour mettre tous les coefficients de la flagligne et flag colonne à 1
    for(i=0;i<n;i++)
    {
      j=0;
      for(j=0;j<m;j++)
      {
        if((i==(T[c].numligne))||(j==(T[c].numcolonne)))
        {
          matrix[i][j]=1;
        }
      }
    }
    c++;
    //puis je passe à la case suivante
  }
  //enfin je remet les valeurs des min dans ma matrice
  int c1=0;
  while(c1<u)
  {
    matrix[(T[c1].numligne)][(T[c1].numcolonne)]=T[c1].value;
    c1++;
  }
  free(T);
}


float output_final(float **F,int n,int m)
{
  int u = min(n,m);
  float s = 0.0;
  int i =0;
  int j;
  for(i=0; i<n; i++)
  {
    j =0;
    for(j=0;j<m;j++)
    {
      s += (1-F[i][j]);
    }
  }
  return 1 - (s/(u));

}





int main(int argc, char *argv[])
{
  FILE *fichier=NULL;
  FILE *fichier2=NULL;
  liste *l=init_liste();
  liste *l2=init_liste();
  char ligne[TAILLE_MAX]="";
  char ligne2[TAILLE_MAX]="";
  fichier =fopen(argv[1],"r");
  fichier2=fopen(argv[2],"r");
  while(fgets(ligne,TAILLE_MAX,fichier)!=NULL)
  {
    if ((ligne[0]!='\0')||(ligne[0]!='\n'))
    {
    insertion(l,ligne);
    }
  }
  fclose(fichier);
  while(fgets(ligne2,TAILLE_MAX,fichier2)!=NULL)
  {
    //if(ligne2[0]==0) continue;
    //insertion(l2,ligne2);
    if ((ligne2[0]!='\0')||(ligne2[0]!='\n'))
    {
    insertion(l2,ligne2);
    }
  }
  fclose(fichier2);
  liste *l_clean =init_liste();
  liste *l_clean2=init_liste();
  nettoyage1(l,l_clean);
  nettoyage1(l2,l_clean2);
  supression(l);
  supression(l2);
  //l_clean est la liste chainée après pré-traitement//
  float **matrix=mat(l_clean,l_clean2,l_size(l_clean),l_size(l_clean2)); //creer la matrice contenant les distances//
  //affich(matrix,l_size(l_clean),l_size(l_clean2));
  //affiche(l_clean);
  //affiche(l_clean2);
  fmat("dice.pgm",matrix,l_size(l_clean),l_size(l_clean2));
  //printf("%s",sendme_thisline(l_clean,l_size(l_clean)-2));
  glouton(matrix,l_size(l_clean),l_size(l_clean2));
  //affich(matrix,l_size(l_clean),l_size(l_clean2));
  float **F=matF(matrix,l_size(l_clean),l_size(l_clean2));
  free_mat(matrix,l_size(l_clean));
  //affich(F,l_size(l_clean),l_size(l_clean2));
  fmat("filtrage.pgm",F,l_size(l_clean),l_size(l_clean2));
  float delta = output_final(F,l_size(l_clean),l_size(l_clean2));
  printf("La distance entre les documents est de %.2f \n",delta);
  //On libère l'espace mémoire
  free_mat(F,l_size(l_clean));
  supression(l_clean);
  supression(l_clean2);


  return 0;
}
