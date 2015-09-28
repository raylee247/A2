#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "scoreText.h"

#define TEMP 20
#define STEP 0.2
#define COUNT 10000

char *playfairDecipher(char *key, char *in,char *out, int len);
float playfair(char *text,int len, char* maxKey);

int main(int argc, char *argv[])
{
    double score = 0;
    double maxscore= -99999999999;
    
    char key[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    char cipher[]  = "ULZHGZAMISKLAINBDQAKNSULYGYITOHLDNSLRAKLBAEFSRGMXANILMBSCMILPSELOFNHMLLCLGNDWFEFLEDQNAWMLGKEGOGPYICMWFKPAZCMIHIOOLYGIMKLUPVEELMZDSKHIOOLOXETPKULLWLGTODMWFKPAZUIBHOLYGGSQNEVLRMNBDYUGLEUUIBHOLELEOOAELIYQWGOOHNCICMIQNAIQTPYKLPSUQNHMLBNLGYMMGULYGYIULZHGZKEGHZURAKLSPGLOKLEBOKSQHGSSPTQELLKMZOKPURLSQADQNMLQSELVEULEKHGGMXALKLCBOCMEUDQAKAODWBDSPBDXUSKPUOHNCICSNESGLEUSEYMKLSPKEDQNCAIEFKHGSANABSFQNLHKEDQNKELHLGPANLRMGEFDNUGLWDQLKFBKHESLCBOSPKTBUIMGSSPTQELNDYELWWUAOSQDZOIRLQWAIEKIOSECMAZUMSQQNTSETOAEVYKEDBDYABSLXOKXUBDDQQCGMREOKUPHLELDNAIEFKHGLENKLGSSPTQELMIQNDQAKSFOPMLQKBSLGQKELYGSLKQLGEIOAAGQWELYGGSQNEFQSSNEUOUYMNCAIEFOUYMLCOUYMIKIOOLSQDESPRLOXWFEFKLLGEIOAKAYIABEKKPYLPSEXGAEFLHKMKOQVPSESGLHLGICULGGZMIWFESHELGGZIYNQPSHLUIZABYSEELOLAWGPYKKLPSEFWLNSIODQEUGSESNCAIWFEFKRRTHYOAELIKIOOLESIKGLEUKLBDEFSRLGLKLXLGGZEUSLNKOAKTBOOBAZAIEFOUYMIKIOOLELHLMTQSKLKEFOYIDRUIBHOLDQLCOKWDWHSKOXKDMLNCAIWFEFWLWHWFEFBDRUSWLWKXIOOLELSNEACYAZBACMWODUSIBNULQTLMEQYDKHSACMBAKUIOOLKBEFNOHGDBAZKSAWQSBIDBLXOKYMOWDQLYOYFELGILPSCMEOOKKOAZSPPSUFULNIWHWLHLYGBSQNPSEFSKUDGMLXOKUPHLELDNSNWUKEMDQEEHIPPBAZAIEFOUYMLCSMMTLWLCOKKRSKDQAKNSEFQSELSNEACYAZBAOAPUDOQDAXQXLOMDODYHIOOLADOMDMEKPKKPAZGMIOAIEFOKGHKDAOKDADGIQWELHQBUMGOAUMVEIYKEDQHKNSDGUIBHOLTSSQQNOHNCICAISQUQMYULMYKLUIBHOLPBZOLMDMKLOLBNOASNKFCMAZULZHGZDQCBGSEACIPSULYGYITUBDKHIOOLAGDXIOOLAOYIEFLRDQUIBHOLEFSTPCSKKSKMAZSPCMBLBSAIEFBSLGKRGSHTLMBDUODZEFBDRSAEWMGMWSDBRTCPHWICGSZHYMOWUIBHOLGIHGSPPSUXIOOLDQICGSGLHRAIKPPEKLUIBHOLIZEFSTDGUIBHOLESQKBAWKAIGLTUQSELYLPSULZHGZAOSFVQBUPACOKDDRAIEQOYFETOIMMTIYQXGMQWPUCMKSRKAOQNELHTQEKOKDDQAYYIICAIQFMALKOIVESLKGUIBHOLABKXIOOLAOYIESQKBAWKUIBHOLMQDUBDUOULQNBAULZHGZWUEUGSANLHDQQISACMAZCMOPDUSDUOBDKEEFKHSACMBAKAPSEFQSSNAOQDKECKGLEUGICOSAEFDNAIETULEFQOMTLWIKIOOLDQZKDGAGRLEFBDZUUGEZBAZSPKFEELPBWSLGEFHGTSOAMLGIRTGEEVSEXUCMOELMUQUOBDUIBHOLCMOLQNCMEOSURAKHBAEVQOKPBAWAIUIOOLAOYIULZHGZUIBHOLOACMWUKULGOFAEKLDMWSDQIMWLSBXANCAIKQSLEFSLESGEUIBHOLAMDNAGTQELBESTLHKHULKSNCLKQSELQSLHWUAOYIESAKULVMDRAIETULKQGIHOSLDXIOOLLKQSELQSLHKOEFGSRUWFEFKRIYNQEWABKZGSTSHLMWBDROPGKLSPDBRUKFIOOLPKUMSUFEEFKRWDSTUIBHOLAOYIULZHGZAIWFESQKBAWKAMISKLFOQSEFKHKMDMAZOAEFGSRUELUIHAAKWHSEEHGSRUPKSPEFSKDCNOPGKLPSTSNHDHIOOLTSWDBSGSVMGMESFKPYKHULHREUMAIKIOOLEFWLUIBHOLAIQWTSEFKREUGSANQWMWNOMLSPRSETPKCMQDUCQNHLICLGAKPUEFTMADHKBDDQCIMYKHKPBAAIWQBSULZHGZXALKGESPIAEXZRMALKOIVEULQYDQOKELIYEFDNMWWLQSEFTMIBQWEXWLEFLRPSMGPBWSHYGAKSQKELONZHYMLHPUEFSMYLLHKUULHRKAPSELBADRUMMTQKELZKGSANUIQWBDHSSPSBYEAIEFKMOLYOLWQYMALKOIVEUIBHOLLUXALYKLGDYLAOPIRTEFLROAEFKRTOISKHIOOLAMISBDVUMGNSDGSPMTLWEVQSSTULEFLGGZYPASDABYKLOAOUHLQSEVDQTOLGWLWPXOMNKLPSELKTXARUOKMLUAPUTQELAGUQELLWKLKLSPKSLEOUYMNKPKUFCMAGNBKRSKMWUPHLELSBHANILMMKRTEFQSELSNAODMRT";
    
    int len = strlen(cipher);  
    char *out = malloc(sizeof(char)*(len+1));

    printf("Running...\n");

    int i=0;
    // run until user kills it
    while(1){
        i++;
        score = playfair(cipher,len,key);
        if(score > maxscore){
            maxscore = score;
            printf("score: %f, Key: %s\n",score,key);
            playfairDecipher(key, cipher,out, len);
            printf("plaintext: '%s'\n",out);
        }
    }
    return 0;
}

//swap 2 letters
void swap2letters(char *key){
    int i = rand()%25;
    int j = rand()%25;
    char temp = key[i];
    key[i]= key[j];
    key[j] = temp;
}

//swap 2 rows
void swap2rows(char *key){
    int i = rand()%5;
    int j = rand()%5;
    char temp;
    int k;
    for(k=0;k<5;k++){
        temp = key[i*5 + k];
        key[i*5 + k] = key[j*5 + k];
        key[j*5 + k] = temp;
    }
}

//swap 2 columns
void swap2cols(char *key){
    int i = rand()%5;
    int j = rand()%5;
    char temp;
    int k;
    for(k=0;k<5;k++){
        temp = key[k*5 + i];
        key[k*5 + i] = key[k*5 + j];
        key[k*5 + j] = temp;
    }
}


//inverse the key
void inversekey(char *outkey, char *inkey){
    int x;
    for(x=0;x<25;x++){
        outkey[x] = inkey[24-x];
        outkey[25] = '\0';
    }
}

//make new key
void childKey(char *newKey,char *oldKey){
    int k,j,i = rand()%50;
    switch(i){
        case 0:
            strcpy(newKey,oldKey);
            swap2rows(newKey);
            break;
        case 1:
            strcpy(newKey,oldKey);
            swap2cols(newKey);
            break;
        case 2:
            strcpy(newKey, oldKey);
            inversekey(newKey, oldKey);
            break; // reverse whole keysquare
        case 3: for(k=0;k<5;k++) for(j=0;j<5;j++) newKey[k*5 + j] = oldKey[(4-k)*5+j]; // swap rows up-down
                newKey[25] = '\0';
                break;
        case 4: for(k=0;k<5;k++) for(j=0;j<5;j++) newKey[j*5 + k] = oldKey[(4-j)*5+k]; // swap cols left-right
                newKey[25] = '\0';
                break;
        default:strcpy(newKey,oldKey); 
                swap2letters(newKey);
    }
}

//Actual playfair piece
float playfair(char *text,int len, char* bestKey){
    int i,j,count;
    float T;
    char *deciphered = malloc(sizeof(char) * (len+1));
    char testKey[26]; //empty key
    char maxKey[26];
    size_t myarray_size = 1000;
    char* myarray = malloc(myarray_size * sizeof(char));
    double prob,dF,maxscore,score;
    double bestscore;
    strcpy(maxKey,bestKey);
    playfairDecipher(maxKey,text,deciphered,len);
    maxscore = scoreTextQgram(deciphered,len); //check score of master key before entering loop
    bestscore = maxscore;
    for(T = TEMP; T >= 0; T-=STEP){//once in this loop keep going till terminate, temp(20) goes down by 0.2
        for(count = 0; count < COUNT; count++){ 
            childKey(testKey,maxKey);    //test for new key
            playfairDecipher(testKey,text,deciphered,len);
            score = scoreTextQgram(deciphered,len);
            dF = score - maxscore;
            if (dF >= 0){
                maxscore = score;
                strcpy(maxKey,testKey);
            }else if(dF < 0){
                //store the key
                //printf("key testing: %s\n", testKey);
                int storage;
                //storing test keys so no duplicates ever tested
                for(storage = 0; storage < (sizeof(myarray) / sizeof(myarray[0])); storage++){
                    if(storage == (sizeof(myarray) / sizeof(myarray[0]))){
                        //reallocating new memory if running out
                        char* myrealloced_array = realloc(myarray, myarray_size);
                        if (myrealloced_array) {
                            myarray = myrealloced_array;
                        }else{
                            printf("Out of memory");
                            break;
                        }
                    }
                    int checkindex;
                    int saved = 0;
                    for (checkindex = 0; checkindex < storage; checkindex ++){
                        if(myarray[checkindex] == testKey){
                            saved = 1;
                        }
                    }
                    if(saved != 1){
                        myarray[storage] = testKey;
                    }
                }
            }
            // keep track of best score we have seen so far
            if(maxscore > bestscore){
                bestscore = maxscore;
                strcpy(bestKey,maxKey);
            } 
        }
    }
    free(deciphered);
    return bestscore;
}

//this is just replacing the letters in the cipher text with the letters in the matrix
char *playfairDecipher(char *key, char *text, char *result, int len){
    int i;
    char a,b; /* the digram we are looking at */
    int a_ind,b_ind;
    int a_row,b_row;
    int a_col,b_col;
    
    for (i = 0; i < len; i += 2){
        a = text[i];
        b = text[i+1];
        a_ind = (int)(strchr(key,a) - key);
        b_ind = (int)(strchr(key,b) - key);
        a_row = a_ind / 5;
        b_row = b_ind / 5;
        a_col = a_ind % 5;
        b_col = b_ind % 5;
        if(a_row == b_row){
            if(a_col == 0){
                result[i] = key[a_ind + 4];
                result[i+1] = key[b_ind - 1];
            }else if(b_col == 0){
                result[i] = key[a_ind - 1];
                result[i+1] = key[b_ind + 4];
            }else{
                result[i] = key[a_ind - 1];
                result[i+1] = key[b_ind - 1];
            }
        }else if(a_col == b_col){
            if(a_row == 0){
                result[i] = key[a_ind + 20];
                result[i+1] = key[b_ind - 5];
            }else if(b_row == 0){
                result[i] = key[a_ind - 5];
                result[i+1] = key[b_ind + 20];
            }else{
                result[i] = key[a_ind - 5];
                result[i+1] = key[b_ind - 5];
            }
        }else{
            result[i] = key[5*a_row + b_col];
            result[i+1] = key[5*b_row + a_col];
        }
    }
    result[i] = '\0';
    return result;
}




