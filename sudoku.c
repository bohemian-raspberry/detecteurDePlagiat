#include <stdio.h>
#include <stdlib.h>


#define TailleMat 9
#define nb_execution_algorithme 10
int ecrire_mat(int  mat[TailleMat][TailleMat],int x,int y,int val)
{
if(((0<=x)&&(x<TailleMat))&&((0<=y)&&(y<TailleMat))&&((0<=val)&&(val<=9)))
{
mat[x][y]=val;
return 0;
}
else return -1;

}

int lire_mat(int  mat[TailleMat][TailleMat],int x,int y)
{
if(((0<=x)&&(x<TailleMat))&&((0<=y)&&(y<TailleMat)))
return mat[x][y];
else  return -1;
}



int init_mat(int mat[TailleMat][TailleMat],char *NomFichier)
{

FILE *F;
int c;
char stTemp[2];
int x=0;
int y=0;
int drap=0;
int drapcolone=0;
int drapligne=0;

F=fopen(NomFichier,"r");//on ouvre le fichier en lecture
if(F!=NULL)
{
c=fgetc(F);
if(c==EOF)
{
printf("%s est vide\n",NomFichier);
exit(0);
}
	
	while (c!=EOF )//on parcour le fichier 
		{
	
			if(drap!=0)
			{
				y++;
				x=0;
				drap=0;
			}
			if(c=='\n')
			drap++;
			if(c!='\n')
			{	
				sprintf(stTemp,"%c",c);
				ecrire_mat(mat,x,y,atoi(stTemp));// on converti la valeur lue en int et on l'ecrit dans la grille aux coordonnes x,y 	
				x++;
			if(x==9)
			{
				drapligne++;
			}	
			}		
			c=fgetc(F);
	
		}

drapcolone=y;
if(drapcolone!=8||drapligne!=9)//Si le fichier ne contient pas le bon nombre de lignes ou de colones alors on quitte
{
printf("%s est au mauvais format\n",NomFichier); 
exit(0);
}


fclose(F);//on ferme le fichier 
}
else if(F==NULL)
{
printf("erreur d'ouverture du fichier %s\n",NomFichier);
exit(0);
}

return 0;
}

int ChercheValeur(int mat[TailleMat][TailleMat],int x, int y)
{
int i;
int j;
int k;
int l;
int test=0;
int drap=0;
int drapv;
int tab[9];
for(i=0;i<9;i++)
{
tab[i]=i+1;//on initialise le tableau avec toute les valeurs possibles pour la case x,y (1 Ã  9) et tab[0]=1,tab[1]=2...tab[8]=9
}


for(i=0;i<TailleMat;i++)
{
	
		
	if(lire_mat(mat,i,y)>0)
	tab[lire_mat(mat,i,y)-1]=0;// on parcour la ligne sur laquelle est le point x,y, on elimine les valeurs possibles en mettant la valeur correspondante de tab Ã  0	
		
	
}




	for(i=0;i<TailleMat;i++)
	{
		
			
		if(lire_mat(mat,x,i)>0)// on parcour la colone sur laquelle est le point x,y, on elimine les valeurs possibles dans tab comme pour le parcour de la ligne
		tab[lire_mat(mat,x,i)-1]=0;	
		
	}
/*On determine la region dans laquelle se trouve le point x,y*/


if(((0<=x)&&(x<3))&&((0<=y)&&(y<3)))
	{
		k=0;
		l=0;
	
}
	
	else if(((3<=x)&&(x<6))&&((0<=y)&&(y<3)))
	{
		k=3;
		l=0;
	}

	else if(((6<=x)&&(x<9))&&((0<=y)&&(y<3)))
	{
		k=6;
		l=0;		

	}

       else if(((0<=x)&&(x<3))&&((3<=y)&&(y<6)))
	{
		k=0;
		l=3;
	}
	
	else if(((3<=x)&&(x<6))&&((3<=y)&&(y<6)))
	{
		k=3;
		l=3;
	}

	else if(((6<=x)&&(x<9))&&((3<=y)&&(y<6)))
	{
		k=6;
		l=3;
	}

else if(((0<=x)&&(x<3))&&((6<=y)&&(y<9)))
	{
		k=0;
		l=6;
	}
	
	else if(((3<=x)&&(x<6))&&((6<=y)&&(y<9)))/*bas centre*/
	{
		k=3;
		l=6;
	}

	else if(((6<=x)&&(x<9))&&((6<=y)&&(y<9)))/*bas droit*/
	{
		k=6;
		l=6;
	}



for(i=k;i<k+3;i++)/*on parcour la region*/
{
	for(j=l;j<l+3;j++)
		{
	if(lire_mat(mat,i,j)>0)				
{		
				tab[lire_mat(mat,i,j)-1]=0;		
}		
}
	


}




for(i=0;i<9;i++)/*on vÃ©rifie combien il reste de valeurs possibles pour la case*/
{
if(tab[i]!=0)
drap++;
}




if(drap==1)/*si il ne reste qu'une valeur alors on l'Ã©crit dans la grille*/
{
	for(i=0;i<9;i++)
	{
		
		if(tab[i]!=0)
		ecrire_mat(mat,x,y,tab[i]);
	}
}

if(drap>1)/*Si il reste plus d'une valeur alors on utilise un nouvel algorithme implementÃ© par la fonction ChercheValeurVoisine*/
{
	for(i=0;i<9;i++)
	{
			if(tab[i]!=0)	
			{
			drapv=ChercheValeurVoisine(mat,x,y,k,l,tab[i]);/*renvoi 0 si la valeur ne peut aller sur aucune case voisine de la region*/		
				if(drapv==0)/*si la valeur ne vas sur aucune case voisine alors elle juste pour la case x,y*/			
				ecrire_mat(mat,x,y,tab[i]);
			}
		}
}

return 0;
}


int ChercheValeurVoisine(int mat[TailleMat][TailleMat], int x, int y, int k, int l, int val)/*Cherche la valeur des cases voisines de x,y.renvoi 0 si les cases voisines sont bloques par val(6em param) 1 sinon*/
{
int h,i,j;
int d;
int nbcasevide=0;
int drap=0;
int drapc,drapl;
for(i=k;i<k+3;i++)
{
	for(j=l;j<l+3;j++)
	{
	if(lire_mat(mat,i,j)==0)/*on applique l'algorithme uniquement sur les cases voisines vides*/	
	{
		
		d=0;
		if(i==x)
		{
			if(j==y)
			d=1;
		}	
		if(d==0)/*test pour eviter de parcourir ligne et colone correspondant Ã  x,y*/
		{
		nbcasevide++;
			drapc=0;
			drapl=0;
			for(h=0;h<9;h++)
			{	
				if(lire_mat(mat,h,j)!=val)//on parcour la ligne de la case voisine
				drapl++;	//si la ligne de la case voisine ne contient pas val alors on incremente drapl++
			}			
			for(h=0;h<9;h++)
			{	
			if(lire_mat(mat,i,h)!=val)//on parcour la colone de la case voisine
			drapc++;//si la colone de la case voisine ne contient pas val alors on incremente drapc++
			}
			if(drapc<9)//drapc ou drapl<9 implique que la ligne ou la colone est bloquÃ©e par val
			drap++;
			
			else if (drapl<9)
			drap++;			
		}
	}
	}
}
if(nbcasevide!=drap)/*le nombre de cases non bloquees par val doit etre identique au nombre de cases vide de la region si il est different on retourne 1*/
return 1;
else return 0;

}








int main(int argc, char *argv[])
{
int x,y;
int i,j;
char buf[2];
int n;
int mat [TailleMat][TailleMat];  /*Doit etre initialiser avec TailleMat*/
FILE * e;


for(i=0;i<argc;i++)//argc a la valeur du nombre d'arguments saisi en parametre par l'utilisateur+1
{
if(strcmp(argv[i],"?")==0)//si l'utilisateur a saisi comme argument ? alors il accede a une explication sur l'utilisation du programme puis on termine par exit(0)
{
printf("\n");
printf("Ce programme resoud des sudokus de niveau facile, le 1er parametre du programme est le nom de fichier contenant la grille a resoudre\nle 2em parametre est le nom de fichier qui contiendra la grille resolue.\nExemple d'utilisation: ./sudoku sudoku.txt solution.txt\nChaque case vide de la grille aura pour valeur 0");
printf("\n"); 
printf("Exemple de grille a taper dans un fichier texte:\n");
printf("906080000\n000090764\n073000000\n204100095\n350060047\n160004803\n000000910\n695010000\n000020506\n");
exit(0);
}
}


if(argc!=3)/*si le nombre d'argument est different de 2 alors on averti l'utilisateur et on termine le programme par exit(0)*/
{
//printf("argc =%d",argc);
printf("\n"); 
printf("nombre d'arguments insuffisant tapez ./sudoku ? pour plus d'informations\n"); 
printf("\n"); 
exit(0);
}

e=fopen(argv[2],"w");/*on ouvre le fichier saisi par l'utilisateur en ecriture*/
if(e==NULL)
{ 
printf("erreur d'ouverture du fichier %s\n",argv[2]);
exit(0);
}


init_mat(mat,argv[1]);//on initialise la grille avec le fichier passÃ© en argument

for(i=0;i<nb_execution_algorithme;i++)/*on applique l'algorithme pour chaque case de la grille qui est differente de 0 jusqu'a ce que le compteur de boucle soit Ã©gal Ã  nb_execution_algorithme */
{
	for(x=0;x<TailleMat;x++)
	{
		for(y=0;y<TailleMat;y++)
		{
			if(lire_mat(mat,x,y)==0)
			ChercheValeur(mat,x,y);
		}
	y=0;
	}

}
/*on ecrit la grille dans le fichier passÃ© en parametre par l'utilisateur*/
for(y=0;y<TailleMat;y++)
{
for(x=0;x<TailleMat;x++)
{
n=lire_mat(mat,x,y);
sprintf(buf,"%d",n);
fwrite(buf,sizeof(char),1,e);
}
fwrite("\n",sizeof(char),1,e);
}
fclose(e);
return 0;
}

