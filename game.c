#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void printboard(int array[], int n, int idx1, int idx2, int paired[]);
void fillboard(int arr[], int area);
void shuffleboard(int arr[], int area);
void userturn(int board[], int memidx[], int memsayi[], int paired[], int *memiterator, int *n, int *mem, int *score, int *pcscore, int *guesscounter, int *pcguesscounter);
void pcturn(int board[], int memidx[], int memsayi[], int paired[], int *memiterator, int *n, int *mem, int *score, int *pcscore, int *guesscounter, int *pcguesscounter);
void menu();

int main() {
   int i, j, n, area, mem, diff, idx1, idx2, satirtahmin, sutuntahmin, score=0, pcscore=0, guesscounter=0, pcguesscounter=0, board[64], paired[64], memsayi[200], memidx[200], memiterator=-1;
   
	srand(time(NULL));
   
   for(i=0;i<200;i++){
   	memsayi[i] = -1;
   	memidx[i] = -1;
   }
   for(i=0;i<64;i++){
   	paired[i] = 0;
   }
   

   menu();
   
	do{
	system("cls");
	printf("Devam etmek icin lutfen zorluk seciniz.\n1-Kolay (Boyut:4x4 / Hafiza:2)\n2-Orta (Boyut:6x6 / Hafiza:6)\n3-Zor (Boyut:8x8 / Hafiza:16)\nSeceneginiz:");
	scanf("%d", &diff);
	if(diff!=1 && diff!=2 && diff!=3){
		printf("Lutfen seceneklerden birini seciniz.");
		sleep(2);
	}
	}while(diff!=1 && diff!=2 && diff!=3);
	
	switch(diff){
      case 1:
         n = 4;
         mem = 2;
         break;
      case 2:
         n = 6;
         mem = 6;
         break;
      case 3:
         n = 8;
         mem = 16;
         break;
	}
	system("cls");
	
	fillboard(board, n*n);
	shuffleboard(board, n*n);
	
	// acik tahtayi gosterir
	printf(" ");
	for(i=0;i<n;i++){
		printf("%3d", i+1);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d", i+1);
		for(j=0;j<n;j++){
			printf("%3d", board[i*n+j]);
		}
		printf("\n");
	}
	sleep(5);
	
	userturn(board, memidx, memsayi, paired, &memiterator, &n, &mem, &score, &pcscore, &guesscounter, &pcguesscounter);
	
	printf("Oyun bitti.\n");
	
	if(score==n*n/4){
		printf("Kazandiniz!\n");
		printf("Toplam Tahmin Sayiniz: %d", guesscounter);
	}
	else{
		printf("Bilgisayar kazandi.\n");
		printf("Bilgisayarin toplam tahmin sayisi: %d", pcguesscounter);
	}
	system("pause");
	return 0;
}


void printboard(int board[], int n, int idx1, int idx2, int paired[]){
	int i, j;
	printf(" ");
	for(i=0;i<n;i++){
		printf("%3d", i+1);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d", i+1);
		for(j=0;j<n;j++){
				if(paired[i*n + j] == 1){
					printf("  -");
				}
				else if(idx1 == i*n + j || idx2 == i*n + j){
					printf("%3d", board[i*n+j]);
				}
				else{
					printf("  *");
				}
		}
		printf("\n");
	}
	return;
}

void fillboard(int arr[], int area){
	int i;
	for(i=0; i < area; i++){
		if(i < area/2){
			arr[i] = i+1;
		}
		else{
			arr[i] = i+1-area/2;
		}
	}
}

void shuffleboard(int arr[], int area){
	int i, idx, temp;
	
	for(i=0;i<area;i++){
		idx = ( rand() % (area-i) ) + i;
		temp = arr[i];
		arr[i] = arr[idx];
		arr[idx] = temp;
	}
	return;
}

void userturn(int board[], int memidx[], int memsayi[], int paired[], int *memiterator, int *n, int *mem, int *score, int *pcscore, int *guesscounter, int *pcguesscounter){
	
	int satirtahmin, sutuntahmin, idx1, idx2, i, finished;
	
	system("cls");
	printboard(board, *n, -1, -1, paired);
	printf("Oyun sirasi sizde!");
	sleep(2);
	system("cls");
	do{
		system("cls");
		printboard(board, *n, -1, -1, paired);
		printf("Koordinatlar:");
		scanf("%d,%d", &satirtahmin, &sutuntahmin);
		idx1 = (satirtahmin-1) * (*n) + (sutuntahmin-1);
		if(paired[idx1]==1){
			printf("\nKart zaten eslesmis! Eslesmemis bir kart girmeniz gerekiyor.");
			sleep(3);
		}
		if(satirtahmin>*n || sutuntahmin>*n || satirtahmin<1 || sutuntahmin<1){
			printf("Koordinatlar tahtanin disindan secilemez!\n");
			sleep(3);
		}
	}while(paired[idx1]==1 || satirtahmin>*n || sutuntahmin>*n || satirtahmin<1 || sutuntahmin<1);
	
	printf("%d", idx1);
	(*memiterator)++;
	memidx[*memiterator] = idx1;
	memsayi[*memiterator] = board[idx1];
	
	do{
		system("cls");
		printboard(board, *n, idx1, -1, paired);
		printf("Actiginiz kart: %d\nBir kart daha seciniz:", board[idx1]);
		scanf("%d,%d", &satirtahmin, &sutuntahmin);
		idx2 = (satirtahmin-1) * (*n) + (sutuntahmin-1);
		if(paired[idx2]==1){
			printf("Kart zaten eslesmis! Eslesmemis bir kart girmeniz gerekiyor.\n");
			sleep(3);
		}
		if(idx1 == idx2){
			printf("Farkli koordinatlar giriniz.");
			sleep(3);
		}
	}while(paired[idx2]==1 || idx1==idx2);
	
	(*memiterator)++;
	memidx[*memiterator] = idx2;
	memsayi[*memiterator] = board[idx2];
	
	//tahmin sayisini artirir
	(*guesscounter)++;
	
	system("cls");
	printboard(board, *n, idx1, idx2, paired);
	printf("Actiginiz kart: %d\n", board[idx2]);
	
	if(board[idx1]==board[idx2]){
		printf("Tebrikler! Kartlar Eslesti!\n");
		paired[idx1]=1;
		paired[idx2]=1;
		(*score)++;
		printf("Skor:%d\n", *score);
		sleep(3);
		
		// skorların yarısına ulasılmadıysa kullanıcıya tekrar oynama hakkı verir
		if(*score<(*n)*(*n)/4){
			userturn(board, memidx, memsayi, paired, memiterator, n, mem, score, pcscore, guesscounter, pcguesscounter);
		}
	}
	else{
		printf("Kartlar eslesmedi.\n");
		sleep(2);
		system("cls");
		pcturn(board, memidx, memsayi, paired, memiterator, n, mem, score, pcscore, guesscounter, pcguesscounter);
	}
	
	return;
}

void pcturn(int board[], int memidx[], int memsayi[], int paired[], int *memiterator, int *n, int *mem, int *score, int *pcscore, int *guesscounter, int *pcguesscounter){
	int i, j, idx1, idx2, found=0, closedcardcount=0, kacincikapalikart, iterator=0, finished;
	
	system("cls");
	printboard(board, *n, -1, -1, paired);
	printf("Oyun Sirasi Bilgisayarda!");
	sleep(2);
	system("cls");
	// hafızasından kartlara bakar
	for(i=*memiterator; i>(*memiterator-*mem) && i>=0 && found==0; i--){
		for(j=i-1; j>(*memiterator-*mem) && j>=0 && found==0; j--){
			if(memsayi[i]==memsayi[j] && memidx[i]!=memidx[j] && paired[memidx[i]]==0){
				found=1;
				idx1=memidx[i];
				idx2=memidx[j];
				printboard(board, *n, idx1, -1, paired);
				sleep(1);
				system("cls");
				printboard(board, *n, idx1, idx2, paired);
				printf("Bilgisayar kart eslestirdi!\n");
				(*pcscore)++;
				(*pcguesscounter)++;
				printf("Bilgisayarin skoru:%d", *pcscore);
				sleep(4);
				
				paired[memidx[i]]=1;
				paired[memidx[j]]=1;
				(*memiterator)++;
				memidx[*memiterator] = idx1;
				memsayi[*memiterator] = board[idx1];
				(*memiterator)++;
				memidx[*memiterator] = idx2;
				memsayi[*memiterator] = board[idx2];
				system("cls");
				
				if(*pcscore<(*n)*(*n)/4){
					pcturn(board, memidx, memsayi, paired, memiterator, n, mem, score, pcscore, guesscounter, pcguesscounter);
				}
				
				return;
			}
		}
	}
	
	if(found==0){
		// tahtadaki kapalı kartları sayar
		for(i=0; i< (*n)*(*n); i++){
			if(paired[i]==0){
				closedcardcount++;
			}
		}
		
		// 5 kapali kart varsa 0 la 5 arasında rastgele bir sayı çağırır ve mesela 4 geldiyse 4. kapalı kartı idx1 yapar.
		kacincikapalikart = (rand()%closedcardcount);
		for(i=0; iterator<=kacincikapalikart;i++){
			if(paired[i]==0){
				iterator++;
			}
		}
		idx1=i-1;
		// bu idx'i hafızasındakilerle karşılaştıracak denk gelirse ikisini de açacak denk gelmezse tekrar rastgele idx bakacak ve iki kartı açacak eşleşirse tekrar pcturn çağıracak.
		for(i=*memiterator; i>(*memiterator-*mem) && i>=0 && found==0; i--){
			if(memsayi[i]==board[idx1] && paired[memsayi[i]]==0 && memidx[i]!=idx1){
				found=1;
				idx2=memidx[i];
			}
		}
		if(found==0){
			do{
				iterator=0;
				kacincikapalikart = (rand()%closedcardcount);
				for(i=0; iterator<=kacincikapalikart;i++){
					if(paired[i]==0){
						iterator++;
					}
				}
				idx2=i-1;	
			}while(idx1==idx2);
		}
		printboard(board, *n, idx1, -1, paired);
		sleep(1);
		system("cls");
		printboard(board, *n, idx1, idx2, paired);
		sleep(2);
		
		(*memiterator)++;
		memidx[*memiterator] = idx1;
		memsayi[*memiterator] = board[idx1];
		(*memiterator)++;
		memidx[*memiterator] = idx2;
		memsayi[*memiterator] = board[idx2];
		(*pcguesscounter)++;
		
		if(board[idx1]==board[idx2]){
			printf("Bilgisayar kart eslestirdi!\n");
			paired[idx1]=1;
			paired[idx2]=1;
			(*pcscore)++;
			printf("Bilgisayarin skoru:%d", *pcscore);
			sleep(3);
			system("cls");
			
			if(*pcscore<(*n)*(*n)/4){
					pcturn(board, memidx, memsayi, paired, memiterator, n, mem, score, pcscore, guesscounter, pcguesscounter);
				}
			}
		else{
			printf("Bilgisayar kartlari eslestiremedi.\n");
			sleep(3);
			system("cls");
			userturn(board, memidx, memsayi, paired, memiterator, n, mem, score, pcscore, guesscounter, pcguesscounter);
		}
	}
		
	return;
}

void menu(){
	int secim=0, basla=0;
	while(basla!=1){
		system("cls");
		printf("Hafiza oyununa hos geldiniz. Lutfen asagidaki seceneklerden birini seciniz.");
		printf("\n1-Basla");
		printf("\n2-Nasil Oynanir");
		printf("\n3-Iletisim");
		printf("\n4-Cikis");
		printf("\nSeceneginiz:");
		scanf("%d", &secim);
		
		if(secim == 1){
			basla=1;
		}
		else if(secim==2){
			system("cls");
			printf("Oyuna baslarken zorluk secersiniz. Zorluk kolay ise kartlar 4x4 boyutunda olur ve bilgisayarin hafizasi 2 olur. Zorluk orta ise kartlar 6x6 olur ve bilgisayarin hafizasi 6 olur. Zorluk zor ise kartlar 6x6 boyutunda olur ve bilgisayarin hafizasi 16 olur. Oyun bilgisayar karsi oynanir. Kullanici ve bilgisayar sirayla ikiser kart acar. iki kart eslesirse iki kart daha acma hakki kazanilir. Kartlarin koordinatlari 2,3 seklinde girilir. Once satir, sonra sutun numarasi yazilir. Rakamlar arasinda virgul olur ve bosluk bulunmaz. Tum kartlar acildiginda en cok karti acmis olan kazanir.\n\n");
			printf("Ornek:\n     1  2  3  4\n  1  *  *  *  *\n  2  *  *  *  *\n  3  *  *  *  *\n  4  *  *  *  *\n");
			printf("Ornek koordinat girisi:2,3\n\n");
			printf("Girilen koordinat acilir:\n     1  2  3  4\n  1  *  *  *  *\n  2  *  *  5  *\n  3  *  *  *  *\n  4  *  *  *  *\n");
			printf("Acilan kart:5\n\n");
			system("pause");
		}
		else if(secim==3){
			system("cls");
			printf("Mail:alperkalamanoglu@gmail.com\nTel:05538062046\n\n");
			system("pause");
		}
		else if(secim==4){
			exit(0);
		}
		else{
			printf("\nLutfen seceneklerden birini seciniz.\n");
			sleep(2);
		}
	}
}
