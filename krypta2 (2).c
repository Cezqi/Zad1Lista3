#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <unistd.h>

void encrypt(FILE *ifp, FILE *ofp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
  
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    unsigned char *indata = malloc(fsize);
    unsigned char *outdata = malloc(fsize*2);
  

  
    fread(indata,sizeof(char),fsize, ifp);

  
    EVP_CIPHER_CTX ctx;
    EVP_EncryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_EncryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_EncryptFinal(&ctx,outdata + outLen1,&outLen2);
    fwrite(outdata,sizeof(char),outLen1 + outLen2,ofp);
}

void decrypt(FILE *ifp, FILE *ofp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
   
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    unsigned char *indata = malloc(fsize);
    unsigned char *outdata = malloc(fsize);
   

   
    fread(indata,sizeof(char),fsize, ifp);//Read Entire File


    EVP_CIPHER_CTX ctx;
    EVP_DecryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_DecryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_DecryptFinal(&ctx,outdata + outLen1,&outLen2);
    fwrite(outdata,sizeof(char),outLen1 + outLen2,ofp);
}

char* szukajklucza( char  sciezka[], char id[], char klucz[], char iv[], int n )
{  
 
FILE* keystore1,* fOUT ;  
   keystore1 = fopen(sciezka,"rb");
    static char brak[10];
	 strcpy(brak, "brak");
    if(keystore1==NULL ) {printf("Plik błedny"); return brak;}

    fOUT = fopen("keystore4.txt", "wb");
    decrypt(keystore1,fOUT, klucz, iv);
    fclose(keystore1);
    fclose(fOUT);
	FILE* keystore ;  
	 keystore = fopen("keystore4.txt","rb");
     char idszukane[256];
	 static char szyfr[256];
	 static char wektor[256];
	 
   if (keystore==NULL){printf("Coś z plikiem" ); return 0;}
   else
   {  while (!feof(keystore))   
			{ 
                         fscanf(keystore, "%s", idszukane); 
                           
			  if (feof(keystore))   {printf("Za mało danych1");  return brak;  }
			  fscanf(keystore, "%s", szyfr); 
			  if (feof(keystore))   {printf("Za mało danych2");  return brak;  }
			  fscanf(keystore, "%s", wektor); 
                           // printf( " ff %s  fdddf %s", idszukane, szyfr); 
			  if(strcmp(idszukane,id)==0)  
			          {	
						//fwrite(brak,sizeof(char), sizeof(brak), keystore);
						fclose(keystore);
						
						 keystore = fopen("keystore4.txt","wb");
 						fwrite(brak,sizeof(char), sizeof(brak), keystore);
							fclose(keystore);
					
					  
					   if(n==0)
					   return szyfr;
					   else return wektor;
					  
					  }
			  if (feof(keystore))   {printf("Za mało danych3");  return brak;  }
			
			}
      
   }
    
	//fwrite(brak,sizeof(char), sizeof(brak), fOUT);
	fclose(keystore);
	  
						 keystore = fopen("keystore4.txt","wb");
 						fwrite(brak,sizeof(char), sizeof(brak), keystore);
							fclose(keystore);
					
       printf("Brak w keystore potrzebnych danych");
	return brak;
}




int main(int argc, char *argv[])
{     FILE *fIN, *fOUT; 
// szyfrowanieczynie coszyfrujemydekodujemy gdzieszyfrujemydekodujemy sciezkadokeystora idklucza  
    if(argc != 6){
	
	     if(argc==4)
		 {    if(fIN==NULL ) {printf("Plik błędny"); return 0;}
	//szyfrowanie coszyfrujemy naco	 
			fIN = fopen(argv[2], "rb");
		     fOUT = fopen(argv[3], "wb");
                   if(strcmp(argv[1],"szyfrowanie")==0) 
						encrypt(fIN, fOUT, "smutekizal", "smierctutu");
                  else decrypt(fIN, fOUT, "smutekizal", "smierctutu");
		   
		     fclose(fIN);
			 fclose(fOUT);
			 char brak[10];
	         strcpy(brak, "brak");
		      fOUT = fopen(argv[2], "wb");
			   if(strcmp(argv[1],"szyfrowanie")==0)  fwrite(brak,sizeof(char), sizeof(brak), fOUT);
			  fclose(fOUT);
              return -1;
		}
        printf("Za mało argumentów4");
        return -1;
    }
	
	 char szyfr[52];
    strcpy(szyfr, argv[1]);
	
	char* szyfrek;
	 char*  wektor;
	 
	char* haslo;
	
	
	haslo=getpass("haslo podaj ");
         if( !strncmp(haslo,"czekolada",100)==0 ) {printf("Złe hasło"); return 0;}
	
	 
	 
          char * key2="smutekizal";
 	 char * iv2="smierctutu";
        
	
	 szyfrek=szukajklucza(argv[4],argv[5],key2, iv2,0);
	 wektor=szukajklucza(argv[4],argv[5],key2,iv2,1);
	//printf(" ff %s ",szyfrek);
	
    fIN = fopen(argv[2], "rb");
    if(fIN==NULL ) {printf("Plik błedny"); return 0;}
    fOUT = fopen(argv[3], "wb");
	if(strcmp(szyfr,"szyfrowanie")==0) 
			{ 
			encrypt(fIN, fOUT, szyfrek, wektor);
			}
	else
			{decrypt(fIN, fOUT, szyfrek, wektor);
			}
    fclose(fIN);
    fclose(fOUT);
	
	printf("Zakończono");
    return 0;
}
