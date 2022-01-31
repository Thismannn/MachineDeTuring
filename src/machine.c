
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "machine.h"


/** 
Dans ce code, nous avons tester avec la machine de Turing en utilisant la table de transition 
une structure de données MT qui permet de représenter une machine de Turing
ainsi que sa configuration (´etat courant, ´etat de la bande, position de la tˆete de lecture).
Ecrire une fonction qui initialise une structure MT à partir d’un mot d’entrée et d’un fichier 
contenant une description d’une machine de Turing.

**/


int nombre_line = 0;

char *strrpc(char* ,char* ,char* );
TuringMachine initMT(char word[20], char file[100])
{
    TuringMachine tm;
//tm=  malloc(sizeof ( *struct MT));

    strcpy(tm.BANDE,word);

    tm.Alphabet = "01_";
    tm.EnsState = "ABCDEFGHIJKLMNOPKRSTUVWXYZ";
    tm.Cap = strlen(tm.BANDE);
    tm.CurrentState = tm.EnsState[0];

    tm.RdHeadPos = 0;
//    tm.stateBande = 0;
    tm.readSb = word[0];

    for(int i=strlen(word); i<nbrMaxBande; i++)
    {
       strcat(tm.BANDE,"_");
    }
    char *line_buf = NULL;
    //line_buf = malloc(sizeof (struct TuringMachine));
    int line_count = 0;
    ssize_t line_size;
    size_t line_buf_size = 0;
    
     
    char* FILENAME = "Palindrome.txt";
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
      {
        fprintf(stderr, "Error opening file '%s'\n", FILENAME);
        //return EXIT_FAILURE;
      }

      line_size = getline(&line_buf, &line_buf_size, fp);
      tm.table_transition[0].currentState = line_buf[0];
      tm.table_transition[0].readSymb = line_buf[2];
      tm.table_transition[0].nextState = line_buf[4];
      tm.table_transition[0].writeSymb = line_buf[6];
      tm.table_transition[0].direction = line_buf[8];

      while (line_size >= 0)
      {
        line_count++;
        printf("%s\n", line_buf);

        line_size = getline(&line_buf, &line_buf_size, fp);
        tm.table_transition[line_count].currentState = line_buf[0];
        tm.table_transition[line_count].readSymb = line_buf[2];
        tm.table_transition[line_count].nextState = line_buf[4];
        tm.table_transition[line_count].writeSymb = line_buf[6];
        tm.table_transition[line_count].direction = line_buf[8];
      }

      nombre_line = line_count;
      free(line_buf);
      line_buf = NULL;

      fclose(fp);

      return tm;

}

void affiche_action(TM_ptr tm)
{
    printf("%c",tm.currentState);
    printf("%c",tm.readSymb);
    printf("%c",tm.nextState);
    printf("%c",tm.writeSymb);
    printf("%c\n",tm.direction);
}

TuringMachine onePasCalculate(TuringMachine tm)
{
    TuringMachine tmp;
    tmp = tm;
    int number = 0;
    // lire l'état) et l'identifier 

    tmp.readSb = tmp.BANDE[0];
    printf("Turing Machine read symbole %c\n",tm.readSb);

    for(int i=0; i<nombre_line; i++)
    {

        if(tmp.table_transition[i].currentState == tmp.CurrentState && tmp.table_transition[i].readSymb == tmp.readSb)
        {
            number = i;
            break;
        }

    }
    tmp.BANDE[tmp.RdHeadPos] = tmp.table_transition[number].writeSymb;
    tmp.CurrentState = tmp.table_transition[number].nextState;

    if(tmp.table_transition[number].direction == '<')
    {
        //tmp.RdHeadPos = tmp.RdHeadPos + 1;
        char x = tmp.BANDE[strlen(tmp.BANDE)-1];
        for (int i = strlen(tmp.BANDE)-1; i > 0; i--)
        {
            tmp.BANDE[i] = tmp.BANDE[i-1];
        }
        tmp.BANDE[0] = x;

    }

    else if(tmp.table_transition[number].direction == '>')
        {

            {
                char x = tmp.BANDE[0];
                for(int i = 0; i < strlen(tmp.BANDE)-1; i++)
                {
                    tmp.BANDE[i] = tmp.BANDE[i+1];
                }

                tmp.BANDE[strlen(tmp.BANDE)-1] = x;
            }
        }
    else
    {
        printf("__________________");
    }
    tmp.CurrentState = tmp.table_transition[number].nextState;



    return tmp;
}

TuringMachine simulateTM(TuringMachine tm)
{
    TuringMachine tmp;

    tmp = tm;

    for(int i = 0; i<100; i++)
    {
//
        tmp = onePasCalculate(tmp);
        if(tmp.CurrentState == 'A' && tmp.readSb == '_')
            break;
    }

    return tmp;
}

TuringMachine simulateTMa(TuringMachine tm)
{
    TuringMachine tmp;

    tmp = tm;

    for(int i=0; i<9;i++)
    {
        printf("******** CURRENT CONFIGURATION TM *********\n");
        printf("CurrentState: %c\t",tmp.CurrentState); printf("Position Read: %d\n",tmp.RdHeadPos);
        printf("Symbole Read: %c\n",tmp.readSb);
        printf("%s\n",tmp.BANDE);
        tmp = onePasCalculate(tmp);
        // Ici on travaille avec un seul etat final pour la simplication du code
        /*if(tmp.CurrentState == 'D' && tmp.readSb == '_')
            break; */

    }
    printf("Final State Current: CurrentState: %c\t,Symbole Read: %c\n ", tmp.CurrentState, tmp.readSb);

    return tmp;
}

//
/****
*Ecrire une fonction qui lit dans un fichier le code d'une machine de Turing qui travaille sur
*l'alphabet d'entrée {a, b, c, d} et qui écrit dans un autre fichier le code d'une machine équivalente sur
*l'alphabet {0, 1} avec le codage code(a) = 00, code(b) = 01, code(c) = 10, code(d) = 11

***/

int createmechineequi(char* file)
{
     FILE *fpw = fopen("machinecode_created.txt", "wb");
     FILE *fpr = fopen(file, "r");

     if (!fpw)
      {
        fprintf(stderr, "Error opening file '%s'\n", "machinecode_created.txt");
        return EXIT_FAILURE;
      }

      if (!fpr)
      {
        fprintf(stderr, "Error opening file '%s'\n", file);
        return EXIT_FAILURE;
      }

      char *line_buf = NULL;
      int line_count = 0;
      ssize_t line_size;
      size_t line_buf_size = 0;

      line_size = getline(&line_buf, &line_buf_size, fpr);
      line_buf = strrpc(line_buf,"a,","00,"); strrpc(line_buf,"b,","01,"); strrpc(line_buf,"c,","10,"); strrpc(line_buf,"d,","11,");

      strcat(line_buf, "\n");
      fputs(line_buf, fpw);
      while(line_size>0)
      {
          line_count++;
          line_size = getline(&line_buf, &line_buf_size, fpr);
          line_buf = strrpc(line_buf,"a,","00,"); strrpc(line_buf,"b,","01,"); strrpc(line_buf,"c,","10,"); strrpc(line_buf,"d,","11,");
          strcat(line_buf, "\n");
          fputs(line_buf, fpw);
      }

      free(line_buf);
      line_buf = NULL;
      fclose(fpr);
      fclose(fpw);

      return 0;

}

/***
*Cette fonction permet de remplacer une chaine par une autre chaine de caractères

***/

char *strrpc(char *str,char *oldstr,char *newstr){
    char bstr[strlen(str)];
    memset(bstr,0,sizeof(bstr));
    int i;
    for(i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
                strncat(bstr,str + i,1);
            }
    }

    strcpy(str,bstr);
    return str;
}
