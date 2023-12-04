#include "DesDecryption.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int INTIAL_PERM[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };
int INVERSE_PERM[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };

int S1[4][16] = { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} };
int S2[4][16] = { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10}, {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}, {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15}, {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} };
int S3[4][16] = { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8}, {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1}, {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}, {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} };
int S4[4][16] = { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}, {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}, {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}, {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} };

int S5[4][16] = { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}, {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}, {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}, {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} };
int S6[4][16] = { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11}, {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8}, {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6}, {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} };
int S7[4][16] = { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}, {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6}, {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2}, {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} };
int S8[4][16] = { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}, {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}, {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8}, {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} };

void DesDecryption::split(int* bigarr, int bigarrSize, int* left, int* right, int partArrSize) {
    //Split into 2 Parts
    for (int j = 0; j < partArrSize; j++)
        left[j] = bigarr[j];

    int counter = 0;
    for (int j = partArrSize; j < bigarrSize; j++, counter++)
        right[counter] = bigarr[j];
}
void DesDecryption::merge(int* bigarr, int bigarrSize, int* left, int* right, int partArrSize) 
{
    //Merge  2 Parts into 1 array
    for (int j = 0; j < partArrSize; j++)
        bigarr[j] = left[j];

    int counter = 0;
    for (int j = partArrSize; j < bigarrSize; j++, counter++)
        bigarr[j] = right[counter];

}

void DesDecryption::txtpermute(int* pc, int* cipherdtxt, int size1, int* return_arr)
{
    for (int i = 0; i < size1; i++)
    {
        int index = pc[i] - 1; //58 ==> 57  'zerobased'
        return_arr[i] = cipherdtxt[index]; // permutation 

        //cipherdtxt[57] = 0       // return_arr[0] = 0
        //cipherdtxt[49] = 0      // return_arr[1] = 0
       // cipherdtxt[41] = 0     // return_arr[2] = 0
       // cipherdtxt[33] = 0     // return_arr[3] = 0
    }
}
void DesDecryption::rot(int* X)
{
    int temp = X[0];
    for (int i = 0; i < 28; i++)
    {
        X[i] = X[i + 1]; //move all element to the left except first one
    }
    X[27] = temp;
}
int** DesDecryption::New_keys(int key[])
{
    //Initialzation of 2d array to store all keys inside
    int** All_Keys = 0;
    All_Keys = new int* [16];
    for (int h = 0; h < 16; h++)
    {
        All_Keys[h] = new int[48];
        for (int w = 0; w < 48; w++)
            All_Keys[h][w] = 0;
    }

    int arr[56] = { 0 };
    int pm2[] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };
    int round = 1;
    int C[56 / 2] = { 0 };
    int D[56 / 2] = { 0 };

    //first permutation to make key 56
    int pm[] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
    int size1 = sizeof(pm) / sizeof(pm[0]);
    int size2 = sizeof(key) / sizeof(key[0]);
    txtpermute(pm, key, size1, arr);

    int finalkeyArray[48] = {};
    while (round <= 16) {
        //divide key into 2 parts to shift each part
        split(arr, 56, C, D, 28);
        //shift rotate once  for both parts
        rot(C); rot(D);
        //shift rotate both parts again  only when
        if (round != 1 && round != 2 && round != 9 && round != 16)
        {
            rot(C);
            rot(D);
        }
        // merge both parts to make new key
        merge(arr, 56, C, D, 28);
        txtpermute(pm2, arr, 48, finalkeyArray);
        // save each key in the 2d array
        for (int h = round - 1; h < 16; h++)
        {
            All_Keys[h] = new int[48];

            for (int w = 0; w < 48; w++)
                All_Keys[h][w] = finalkeyArray[w];
        }

        round++;
    }

    return All_Keys;
}
void DesDecryption::swapp(int* arr1, int* arr2) {
    int temp[32] = { 0 };

    for (int j = 0; j < 32; j++)
        temp[j] = arr1[j];

    for (int j = 0; j < 32; j++)
        arr1[j] = arr2[j];

    for (int j = 0; j < 32; j++)
        arr2[j] = temp[j];

}
void DesDecryption::dectobinary(int value, int* binaryArr, int arrsize) {
    int size = arrsize - 1;
    int total = value;
    int counter = 0;
    int x;

    while (size >= 0) {


        if (size < 0)
            break;
        x = pow(2, size);

        if (total >= x) {
            total = total - pow(2, size);
            binaryArr[counter] = 1;
        }
        else {
            binaryArr[counter] = 0;

        }
        size--;
        counter++;
    }

}
void DesDecryption::S_BOX(int rows[], int cols[], int* ret_arr)
{
    int arr_S_Box[8] = { 0 };
    int binaryArr[4] = { 0 };
    int start = 0;
    for (int i = 0; i < 8; i++)
    {
        switch (i)
        {
        case 0:
            arr_S_Box[i] = S1[rows[i]][cols[i]];
            break;
        case 1:
            arr_S_Box[i] = S2[rows[i]][cols[i]];
            break;
        case 2:
            arr_S_Box[i] = S3[rows[i]][cols[i]];
            break;
        case 3:
            arr_S_Box[i] = S4[rows[i]][cols[i]];
            break;
        case 4:
            arr_S_Box[i] = S5[rows[i]][cols[i]];
            break;
        case 5:
            arr_S_Box[i] = S6[rows[i]][cols[i]];
            break;
        case 6:
            arr_S_Box[i] = S7[rows[i]][cols[i]];
            break;
        case 7:
            arr_S_Box[i] = S8[rows[i]][cols[i]];
            break;
        }
        dectobinary(arr_S_Box[i], binaryArr, 4);
        for (int l = 0; l < 4; l++)
        {

            ret_arr[start] = binaryArr[l];
            /*  cout << ret_arr[start];*/
            start++;
        }
        //cout << endl;
    }


}
void DesDecryption::cols(int arr[], int* cols)
{
    int temp[4] = { 0 };
    int counter = 0;
    for (int i = 0; i < 48; i += 6)
    {

        temp[3] = arr[i + 1];
        temp[2] = arr[i + 2];
        temp[1] = arr[i + 3];
        temp[0] = arr[i + 4];

        int sum = 0;
        int num = 1;

        for (int k = 0; k < 4; k++)
        {
            if (temp[k] == 1)
            {
                sum += num;
            }
            num = num * 2;


        }
        cols[counter] = sum;
        // cout << cols[counter] << " ";
        counter++;

        //cout << i << " " << 5 + i << " ";
    }
}
void DesDecryption::rows(int arr[], int* row)
{

    int temp[2] = { 0 };
    int counter = 0;
    for (int i = 0; i < 48; i += 6)
    {
        int start = 0;
        temp[start + 1] = arr[i];
        temp[start] = arr[i + 5];

        int sum = 0;
        int num = 1;

        for (int k = 0; k < 2; k++)
        {
            if (temp[k] == 1)
            {
                sum += num;
            }
            num = num * 2;


        }
        row[counter] = sum;
        // cout << row[counter]<<" ";
        counter++;

        //cout << i << " " << 5 + i << " ";
    }


}
void DesDecryption::Fn(int* arr, int* key_arr, int* returnedarray) {


    //1 expansion for 32 bit to be 48 bit , to XOR it with key
    int E_arr[48] = { 0 };

    int E_table[] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
    txtpermute(E_table, arr, 48, E_arr);
    int XORED_Arr[48] = { 0 };
    int SBOXED_Arr[32] = { 0 };

    //XOR KEY & Right part
    for (int i = 0; i < 48; i++)
        XORED_Arr[i] = E_arr[i] ^ key_arr[i];


    //S-BOX 
    int row_no[8] = { 0 };
    int col_no[8] = { 0 };
    rows(XORED_Arr, row_no);
    cols(XORED_Arr, col_no);
    int Out_SBox[32] = { 0 };
    S_BOX(row_no, col_no, Out_SBox);//////////////////////////////

    // Premutation After Sbox
    int sboxed_premute[] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
    txtpermute(sboxed_premute, Out_SBox, 32, returnedarray);

}
string DesDecryption::Encrypt(string hexplaintext, string hexkey) {

    transform(hexplaintext.begin(), hexplaintext.end(), hexplaintext.begin(), ::toupper);
    transform(hexkey.begin(), hexkey.end(), hexkey.begin(), ::toupper);

    //Input Validation

    bool Invalid_input1 = false;
    bool Invalid_input2 = false;
    bool Invalid_input3 = false;
   
    Invalid_input1 = Check_Hex(hexplaintext);
    Invalid_input2 = Length_input(hexkey, 18);
    Invalid_input3 = Check_Hex(hexkey);
    //Invalid_input = Check_Hex();
    if (Invalid_input2 == false || Invalid_input3 == false || Invalid_input1 == false)
    {
        cout << "Wrong Input" << endl;;
        return "";
    }
    string key_bin = "";
    key_bin = hex_to_bin(hexkey);
    int key_binaryArr[64];
    binstr_to_binarr(key_bin, key_binaryArr);

    int** All_Keys = 0;
    All_Keys = new int* [16];

    for (int h = 0; h < 16; h++)
    {
        All_Keys[h] = new int[48];
        for (int w = 0; w < 48; w++)
            All_Keys[h][w] = 0;
    }
    All_Keys = New_keys(key_binaryArr);


    string str_hex[100];
    int counter_hex = 0;
    int len = (hexplaintext.length() - 2) % 16;
    if (len != 0)
    {
        int append = 16 - len;
        for (int i = 0; i < append; i++)
        {
            hexplaintext += '0';
        }
    }
   
    int counter_16 = 2; //skip "0x"
    int num_16 = (hexplaintext.length() - 2) / 16; //number of blocks (16)
    for (int i = 0; i < num_16; i++)
    {
        str_hex[counter_hex] += "0x";
        for (int j = 0; j < 16; j++)
        {
            str_hex[counter_hex] += hexplaintext[counter_16];
            counter_16++;
        }
        counter_hex++;
    }

    string result = "0x";
    for (int O = 0; O < num_16; O++)
    {
        string plainText_bin = "";
        plainText_bin = hex_to_bin(str_hex[O]);
        int plaintext_binaryArr[64];
        binstr_to_binarr(plainText_bin, plaintext_binaryArr);

        //step - 1   Make Initial Permute
        int MsgAfterPermute[64] = { 0 };
        txtpermute(INTIAL_PERM, plaintext_binaryArr, 64, MsgAfterPermute);


        // 2 var for left to keep IT'S value of current round 
        int L_OLD[32];
        int L[32];
        int R[32] = { 0 };
        //step - 2 Split into Left , Right
        split(MsgAfterPermute, 64, L_OLD, R, 32);
        //step - 3 Get Next Left  [ L_n+1 = R_current ]
        for (int i = 0; i < 32; i++)
            L[i] = R[i];
        //step - 4 Get Next Right  [ R_n+1 = L_current XOR  Fn( R_current , Kn  )

            // x_arr is result from function xor R_current and key 
        int X_Arr[32] = { 0 };
        Fn(R, All_Keys[0], X_Arr);
        //XOR Lcurrent With X_Arr to get R_n+1
        for (int i = 0; i < 32; i++)
            R[i] = L_OLD[i] ^ X_Arr[i];


        // Now we finally have R1,L1 
       //  step - 5  By Repeating Step 3,4  for 15 time we can get  R16,L16
        int round = 2; //becasue we got result of round1 outside of the loop so we start from 2nd round till 16th round
        // cout << "Rouund 1 " << endl;
        while (round <= 16) {
            // Get Next Left 
          /*  std::cout << "Rouund " << round  << endl;*/

            //We have to store L_OLD   to use it to get R_New
            for (int i = 0; i < 32; i++)
                L_OLD[i] = L[i];

            // GET NEXT L
            for (int i = 0; i < 32; i++)
                L[i] = R[i];

            // Get Next Right 
            Fn(R, All_Keys[round - 1], X_Arr);
            for (int i = 0; i < 32; i++)
                R[i] = L_OLD[i] ^ X_Arr[i];

            round++;

        }


        // step - 6 swap the 2 parts 
        swapp(L, R);
        // step - 7 Merge the 2 parts 
        int cipherd_text[64] = { 0 };
        merge(cipherd_text, 64, L, R, 32);

        // step 8 Apply Inverse Permutation
        static int final_cipherd_text[64] = { 0 };
        txtpermute(INVERSE_PERM, cipherd_text, 64, final_cipherd_text);

        string s = "";
        for (int i = 0; i < 64; i++)
        {
            //std::cout << final_cipher[i];
            s += to_string(final_cipherd_text[i]);

        }


        
        result += bin_to_hex2(s);
    }
    
    return result;
}
string DesDecryption::Decrypt(string hexcipher, string hexkey)
 {

    transform(hexcipher.begin(), hexcipher.end(), hexcipher.begin(), ::toupper);
    transform(hexkey.begin(), hexkey.end(), hexkey.begin(), ::toupper);

    //Input Validation
    bool Invalid_input1 = false;
    bool Invalid_input2 = false;
    bool Invalid_input3 = false;
    Invalid_input1 = Check_Hex(hexcipher);
    Invalid_input2 = Length_input(hexkey, 18);
    Invalid_input3 = Check_Hex(hexkey);
    if (Invalid_input1 == false || Invalid_input2 == false || Invalid_input3 == false)
    {
        cout << "Wrong Input" << endl;;
        return "";
    }


    string key_bin = "";
    key_bin = hex_to_bin(hexkey);
    int key_binaryArr[64];
    binstr_to_binarr(key_bin, key_binaryArr);

    /* int key_binaryArr[64];
     key_binaryArr = stringToBinary(hexkey);*/


    int** All_Keys = 0;
    All_Keys = new int* [16];

    for (int h = 0; h < 16; h++)
    {
        All_Keys[h] = new int[48];
        for (int w = 0; w < 48; w++)
            All_Keys[h][w] = 0;
    }
    All_Keys = New_keys(key_binaryArr);


    string str_hex[100];
    int counter_hex = 0;
    int len = (hexcipher.length() - 2) % 16;
    if (len != 0)
    {
        int append = 16 - len;
        for (int i = 0; i < append; i++)
        {
            hexcipher += '0';
        }
    }

    int counter_16 = 2; //skip "0x"
    int num_16 = (hexcipher.length() - 2) / 16; //number of blocks (16)
    for (int i = 0; i < num_16; i++)
    {
        str_hex[counter_hex] += "0x";
        for (int j = 0; j < 16; j++)
        {
            str_hex[counter_hex] += hexcipher[counter_16];
            counter_16++;
        }
        counter_hex++;
    }

    string result = "0x";
    for (int O = 0; O < num_16; O++)
    {
        string cipher_bin = "";
        cipher_bin = hex_to_bin(str_hex[O]);

        int hexcipher_binaryArr[64];
        binstr_to_binarr(cipher_bin, hexcipher_binaryArr);

        //1-  make inverse of inverse premuitation which is intial permutiation
        int cipher_aft_permute[64] = { 0 };
        txtpermute(INTIAL_PERM, hexcipher_binaryArr, 64, cipher_aft_permute);

        // make 2 variables for rightside to keep  IT'S value of current round and next round
        int L[32], R_OLD[32], R[32] = { 0 };

        // 2- dived 64 bits into  2 parts , left , right
        split(cipher_aft_permute, 64, L, R_OLD, 32);

        // 3- SWAP TO Get L16 , R16
        swapp(L, R_OLD);

        //step - 4 Get Next Right  [ R_n-1 = L_current ]
        for (int i = 0; i < 32; i++)
            R[i] = L[i];

        //step - 5 Get Next Left  [ L_n-1 = R_current XOR  Fn( R_n-1 , Kn  )

            // x_arr is result from function xor R_current and key 
        int X_Arr[32] = { 0 };
        Fn(R, All_Keys[15], X_Arr);
        //XOR Rcurrent With X_Arr to get L_n-1
        for (int i = 0; i < 32; i++)
            L[i] = R_OLD[i] ^ X_Arr[i];

        // Now we finally have R15,L15
        //  
       //  step - 6  By Repeating Step 4,5  for 15 time we can get  R16,L16
        int round = 15; //becasue we already got  round16 result
        while (round >= 1) {

            //We have to store old R  to use it to get next L
            for (int i = 0; i < 32; i++)
                R_OLD[i] = R[i];

            // Get Next Right
            for (int i = 0; i < 32; i++)
                R[i] = L[i];

            // Get Next Left 
            Fn(R, All_Keys[round - 1], X_Arr);
            for (int i = 0; i < 32; i++)
                L[i] = R_OLD[i] ^ X_Arr[i];

            round--;

        }

        // step - 8 Merge the 2 parts 
        int plain_text[64] = { 0 };
        merge(plain_text, 64, L, R, 32);

        // step 9 Apply Inverse Permutation
        static int final_plain_text[64] = { 0 };
        txtpermute(INVERSE_PERM, plain_text, 64, final_plain_text);

        string s = "";
        for (int i = 0; i < 64; i++)
        {
            //std::cout << final_cipher[i];
            s += to_string(final_plain_text[i]);

        }

        result += bin_to_hex2(s);
    }

    return result;
}


string DesDecryption::bin_to_hex2(string key)
{
    string key_hex = "";
    string sub_Str = "";
    for (int i = 0; i < key.length(); i += 4)
    {
        sub_Str = key.substr(i, 4);

        if (sub_Str == "1010")
            key_hex += "A";

        else if (sub_Str == "1011")
            key_hex += "B";

        else if (sub_Str == "1100")
            key_hex += "C";

        else if (sub_Str == "1101")
            key_hex += "D";

        else if (sub_Str == "1110")
            key_hex += "E";

        else if (sub_Str == "1111")
            key_hex += "F";

        else
        {
            int size = sub_Str.length();
            int bit = 0, decimal = 0;
            int power_index = 0;
            for (int i = size - 1; i >= 0; i--)
            {
                bit = sub_Str[i] - '0';
                if (bit != 0)
                    decimal += bit * pow(2, power_index);
                power_index++;
            }
            power_index = 0;
            key_hex += to_string(decimal);
        }

        sub_Str.clear();
    }
    return key_hex;
}
string DesDecryption::hex_to_bin(string sb_wrod)
{
    transform(sb_wrod.begin(), sb_wrod.end(), sb_wrod.begin(), ::toupper);
    string binary = "";
    int counter = 0;
    for (int i = 2; i < sb_wrod.length(); i++)
    {
        switch (sb_wrod[i])
        {
        case 'A':
            binary += "1010";
            break;

        case 'B':
            binary += "1011";
            break;

        case 'C':
            binary += "1100";
            break;

        case 'D':
            binary += "1101";
            break;

        case 'E':
            binary += "1110";
            break;

        case 'F':
            binary += "1111";
            break;

        default:
            /*int num=plain[i], bin;
            cout << plain[i] << endl;
            while (num > 0)
            {
                bin = num % 2;
                binary += to_string(bin);
                num /= 2;
            }
            binary += '|';*/
            char d = sb_wrod[i] - '0';
            string output = "0000";

            for (int i = 0; d > 0; i++)
            {
                output[3 - i] = d % 2 + '0';
                d = d / 2;
            }
            binary += output;
            break;
        }
    }
    return binary;
}
void DesDecryption::binstr_to_binarr(string plainText_bin, int* arr)
{
    for (int i = 0; i < 64; i++)
    {
        arr[i] = 0;
    }
    for (int i = 0; i < plainText_bin.length(); i++)
    {
        if (plainText_bin[i] == '0')
        {
            arr[i] = 0;
        }
        else
            arr[i] = 1;
    }
}
bool DesDecryption::Length_input(string txt, int size)
{
    if (txt.length() <= size)
    {
        return 1;
    }
    return 0;
}
bool DesDecryption::Check_Hex(string hex_string)
{
    int Len = hex_string.length();
    //transform(hex_string.begin(), hex_string.end(), hex_string.begin(), ::toupper);
    if (hex_string[0] != '0' || hex_string[1] != 'X')
    {
        return 0;
    }

    // Iterate over string
    for (int i = 2; i < Len; i++)
    {
        char ch = hex_string[i];

        // Check if the character
        // is invalid
        if ((ch < '0' || ch > '9') &&
            (ch < 'A' || ch > 'F'))
        {

            return 0;
        }
    }


    return 1;

}
