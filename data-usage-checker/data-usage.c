/* ------------------------------------------------------------------------
   Author   : Tifan Dwi Avianto (github.com/ifananvity)
   Version  : 1.2 - 25/11/2017
              - break codes intos function for more readible
                easily-maintained code
              - changed a few variable name to be more simplified
              - removed some unnecessary variable
              - changed some integer varibale to char for less memory
              - added loop when prompting, invalid input will re-prompt
                instead of closing the program.
              1.1 - 19/10/2017
              - minor changes
   ------------------------------------------------------------------------ */

/* 
 * Problem:
 * saya pemakai paket XTRA Combo dari XL. setiap saya mau bandingin 
 * 'kuota internet' dengan 'sisa hari', biasanya saya hitung manual pake
 *  kalkulator (keduanya dijadikan persentase 0-100)
 * 
 * supaya saya dapet kesimpulan:
 * if persentase kuota internet < persentase sisa hari then
 *     berarti pemakaian saya boros.
 *     ATAU memang paket yang saya pake tidak sesuai dengan pemakaian sehari2 
       saya (kuota nya sedikit)
 *     dan saya harus naik paket yang kuota nya lebih banyak dan lebih mahal.
 * else
 *     pemakaian saya hemat.
 *     ATAU paket yang saya gunakan kuotanya melebihi pemakaian sehari2 saya
 *     (kuota terlalu banyak) dan saya bisa turun paket yang kuota nya lebih
 *     sedikit dan lebih murah
 * 
 * kenapa tidak pake aplikasi bawaan 'myXL' saja?
 * karena interfacenya menunjukan 'sisa kuota 4g' dan 'sisa kuota 2g/3g/4g' 
 * dengan bar yang terpisah dan bahkan sisa hari nya ga pake bar, melainkan 
 * hanya teks "Valid until: 29 days"
 */

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>
#include <conio.h>

//Globals
char planSelection;
char includeYoutubeOption;
int dataYoutubePercentage;
int dataInternetPercentage;
int remainingDays, remainingDaysPercentage;
float data4G, remainingData4G;
float data2G3G4G, remainingData2G3G4G;
float dataYoutube, remainingDataYoutube;

//Prototypes
void selectPlan(void);
void assignQuotaAmount(void);
void displayPlanDetail(void);
void promptAndCalculateRemainingQuota(void);
void promptAndCalculateRemainingDays(void);
void conclusion(void);
void progressBar(char label[], int step, int total);

int main(void) {
    selectPlan();
    assignQuotaAmount();
    displayPlanDetail();
    promptAndCalculateRemainingQuota();
    promptAndCalculateRemainingDays();
	conclusion();

	printf ("\nPress any key to exit . . .");getch();
	return EXIT_SUCCESS;
}

/* ------------------------------ FUNCTIONS ------------------------------ */

void selectPlan() {
    int flag = 0;
    while (!flag) {
        fflush(stdin);
        printf("1. XTRA Combo 40 GB, Rp. 179k\n");
        printf("2. XTRA Combo 24 GB, Rp. 129k\n");
        printf("3. XTRA Combo 16 GB, Rp. 89k\n");
        printf("4. XTRA Combo 8  GB, Rp. 59k\n");
        printf("Choose data plan you're currently on: ");
        planSelection = getchar();
        if (planSelection == '1' || planSelection == '2' || 
            planSelection == '3' || planSelection == '4') {
            flag = 1;
        }
    }
}

void assignQuotaAmount() {
    switch (planSelection) {
        case '1' : {
            remainingData4G = data4G = 20;
            remainingData2G3G4G = data2G3G4G = 10;
            remainingDataYoutube = dataYoutube = 10;
            break;
        }
        case '2' : {
            remainingData4G = data4G = 12;
            remainingData2G3G4G = data2G3G4G = 6;
            remainingDataYoutube = dataYoutube = 6;
            break;
        }
        case '3' : {
            remainingData4G = data4G = 8;
            remainingData2G3G4G = data2G3G4G = 4;
            remainingDataYoutube = dataYoutube = 4;
            break;
        }
        case '4' : {
            remainingData4G = data4G = 3;
            remainingData2G3G4G = data2G3G4G = 2;
            remainingDataYoutube = dataYoutube = 2;
            break;
        }
        default : {
            printf("\nInvalid input!\n");
        }
    }
    remainingData4G++;
    remainingData2G3G4G++;
    remainingDataYoutube++;
}

void displayPlanDetail() {
    printf("\nPlan detail:\n");
    printf("- 4G        %.0f GB\n", data4G);
    printf("- 2G/3G/4G  %.0f GB\n", data2G3G4G);
    printf("- Youtube   %.0f GB\n\n", dataYoutube);
}

void promptAndCalculateRemainingQuota() {
    while (remainingData4G > data4G) {
        printf("4G data remaining: ");
        scanf("%f", &remainingData4G);
    }
    while (remainingData2G3G4G > data2G3G4G) {
        printf("2G/3G/4G data remaining: ");
        scanf("%f", &remainingData2G3G4G);
    }

    printf("\n");
    while (!(includeYoutubeOption == 'y' || includeYoutubeOption == 'n')) {
        fflush(stdin);
        printf("Include Youtube data? (y/n) ");
        includeYoutubeOption = getchar();
        if (includeYoutubeOption == 'y') {
            while (remainingDataYoutube > dataYoutube) {
                printf("Youtube data remaining: ");
                scanf("%f", &remainingDataYoutube);
            }
        }
    }

    //Menentukan persentase kuota internet
    dataInternetPercentage = ((remainingData4G + remainingData2G3G4G) / 
                              (data4G + data2G3G4G)) * 100.0;
    dataYoutubePercentage =  (remainingDataYoutube / dataYoutube) * 100.0;
}

void promptAndCalculateRemainingDays() {
    printf("\n");
    remainingDays = 30;
    while (remainingDays >= 30) {
        printf("Days remaining(1-29): ");
        scanf("%d", &remainingDays);
    }
    //Menentukan persentase sisa hari
    remainingDaysPercentage = ( remainingDays / 30.0 ) * 100.0;
}

void conclusion() {
    printf("\n+-----------------------------------------------------------------+\n\n");
    //Persentase Kuota & Sisa Hari dengan progress bar
    progressBar("Internet Data ", dataInternetPercentage, 100);
    printf("\n");
    if (includeYoutubeOption == 'y') {
        progressBar("Youtube Data  ", dataYoutubePercentage, 100);
        printf("\n");
    }
    progressBar("Active Period ", remainingDaysPercentage, 100);
    printf("\n\n");

    if (dataInternetPercentage < remainingDaysPercentage) {
        printf("\"Boros\"\n");
    } else {
        printf("\"Hemat\"\n");
    }
}

void progressBar(char label[], int step, int total) {
    //width
    const int pWidth = 60;

    //minus length label
    int lebar = pWidth - strlen(label);
    int pos = (step * lebar) / total;

    int percentage = (step * 100) / total;

    printf( "%s[", label );

    //fill progress bar with =
    for ( int i = 0; i < pos; i++ )  printf("%c", '=');

    //fill progress bar with spaces
    printf("% *c", lebar - pos + 1, ']');
    printf(" %3d%%\r", percentage);
}