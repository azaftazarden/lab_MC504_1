/* Problema do Papai Noel */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

sem_t sem_elfos; //semaforo dos elfos
volatile int count_elfos;
volatile int count_renas;
volatile int lock;
volatile int acordado;


/*************************Animacoes******************/
void logP(){ //papai noel
  int i;
  if(!lock){
    lock = 1;
    
    system("clear");
    printf(" [Ajudando Elfos]\n");
    if(acordado){
      printf(" ~~~~~  \n");
      printf("  o.o  \n");
      printf(" \\___/ \n");
    }
    else{
      printf("\tzzzzzzzzzzzzzz\n");
      printf(" ~~~~~  \n");
      printf("  -.-   \n");
      printf(" \\___/ \n");
    }
    
    count_elfos--;
    if(count_elfos==0) acordado = 0;
    printf("Elfos pedindo ajuda: %d\tRenas: %d\n", count_elfos, count_renas);
    printf("ELFOS: ");for(i=0; i<count_elfos; i++) printf(" & "); putchar(10);putchar(10);
    printf("RENAS: ");for(i=0; i<count_renas; i++) printf(" § "); putchar(10);
    sleep(2);
    lock =0;
  } 
} 

void logFim(){
  if(!lock){
    lock = 1;
    
    system("clear");
    printf("                    _...\n");
    printf("              o_.-\"`    `\n");
    printf("       .--.  _ `'-._.-'\"\"-;     _\n");
    printf("     .'    \\`_\\_  {_.-a\"a-}  _ / \\ \n");
    printf("   _/     .-'  '. {c-._o_.){\\|`  |\n");
    printf("  (@`-._ /       \\{    ^  } \\\\ _/\n");
    printf("   `~\\  '-._      /'.     }  \\}  .-.\n");
    printf("     |>:<   '-.__/   '._,} \\_/  / ()) \n ");
    printf("    |     >:<   `'---. ____'-.|(`\"`\n");
    printf("     \\            >:<  \\\\_\\\\_\\ | ;\n");
    printf("      \\                 \\\\-{}-\\/  \\ \n");
    printf("       \\                 '._\\\\'   /)\n");
    printf("        '.                       /(\n");
    printf("          `-._ _____ _ _____ __.'\\ \\ \n");
    printf("            / \\     / \\     / \\   \\ \\ \n");
    printf("     jgs _.'/^\\'._.'/^\\'._.'/^\\'.__) \\ \n");
    printf("     ,=='  `---`   '---'   '---'      )\n");
    printf("     `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`\n");

    getchar();
    exit(0);

  }
  
}

void logR(int id){ //renas
  
  int i;
  //if(!lock){
    lock = 1;
    system("clear");
    printf(" [rena ]\n");
    if(acordado){
      printf(" ~~~~~  \n");
      printf("  o o  \n");
      printf(" \\___/ \n");
    }
    else{
      printf("\tzzzzzzzzzzzzzz\n");
      printf(" ~~~~~  \n");
      printf("  - -   \n");
      printf(" \\___/ \n");
    }
    
    count_renas++;
    printf("Elfos pedindo ajuda: %d\tRenas: %d\n", count_elfos, count_renas);
    printf("ELFOS: ");for(i=0; i<count_elfos; i++) printf(" & "); putchar(10);putchar(10);
    printf("RENAS: ");for(i=0; i<count_renas; i++) printf(" § "); putchar(10);
    sleep(2);
    lock =0;
  //} 
    
}

void logE(){ //elfos
  int i;
  if(!lock){
    lock = 1;
    system("clear");
    printf(" [Papai Noel dormindo]\n");
  
      printf("\tzzzzzzzzzzzzzz\n");
      printf(" ~~~~~  \n");
      printf("  -.-   \n");
      printf(" \\___/ \n");
    
    
    count_elfos++;
    printf("Elfos pedindo ajuda: %d\tRenas: %d\n", count_elfos, count_renas);
    printf("ELFOS: ");for(i=0; i<count_elfos; i++) printf(" & "); putchar(10);putchar(10);
    printf("RENAS: ");for(i=0; i<count_renas; i++) printf(" § "); putchar(10);
    sleep(2);
    lock =0;
  } 
} 

/**********************Threads************************/
void* Renas(void * v){
  pthread_mutex_lock(&mutex);
  int id = *(int*)v;

  sleep(1);
  printf("Rena %d chegou!\n",id);
  count_renas++;
  
  if(count_renas==9){
    printf("********todas as renas chegaram********\n"); 
    sleep(2);
    acordado = 1;
    return NULL;
  }
  sleep(2);
  
  pthread_mutex_unlock(&mutex);
  
 return NULL; 
}


void * Papai_noel(void* v){  
 
  while(1){
    while(!acordado) ; 
  
    if(count_renas==9){
      acordado = 1;
      logFim();
      printf("\tPreparar treno e partir!\n");
      return NULL;
    }else if(count_elfos==3){
      printf("Acordei! Vou ajudar os elfos!\n");
      while(count_elfos>0 && acordado){
	if(count_renas==9) break;
	sleep(2);
	logP();    
      }
      
      //printf("\tvolta a dormir...\n");
    }
    
  } 
  
  return NULL;
  
}

void * elfoo(void* v){  
  while(1){
    
    if(count_renas==9) return NULL;
    sleep(2);
    logE();
    
    if(count_elfos==3){
      sem_post(&sem_elfos);
      acordado = 1;
      while(count_elfos>0){
	if(count_renas==9) return NULL;
      }
      acordado = 0;
    }
    
  }
  
}

void Explicacao(){
  fputs("Elfo= &\nRena= £\n", stdout);
  fputs("Papai Noel dormindo= -.-\nPapai Noel acordado= o.o\n\n", stdout);
  fputs("Aperte uma tecla para continuar", stdout);
  getchar();
  
}

int main(){
  /*************Variaveis****************/
  pthread_t noel;
  pthread_t rena[9];
  pthread_t elfo;
  
  int id_rena[9];
  int id_elfo = 0;
  
  int i;
  count_elfos=0;
  count_renas=0;
  lock = 0;
  acordado = 0;
  
  /**************Semaforos***************/
  //inicializa mutex
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);
  
  //inicializa semaforo
  sem_init(&sem_elfos, 0, 0);  
  
  /********************Explicação**********************/
  Explicacao();
  
  /*********************Threads************************/

  //cria a thread do Papai Noel
  pthread_create(&noel, NULL, Papai_noel, NULL);  
  
  //cria a thread dos elfos
  pthread_create(&elfo, NULL, elfoo, (void*)&id_elfo);
  
  //cria a thread da Renas
  for(i=0; i<9; i++){
    id_rena[i] = i;
    pthread_create(&rena[i], NULL, Renas, (void*)&id_rena[i]);
  }
  
  //Join no Papai Noel
  pthread_join(noel, NULL);
  
  //Join nos elfos
  //for(i=0; i<n_elfos; i++)
  pthread_join(elfo, NULL);
    
  //Join nas Renas
  for(i=0; i<9; i++)
    pthread_join(rena[i], NULL);
    

    while(1){

      }
  
  return 0;
}
