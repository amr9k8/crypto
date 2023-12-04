#include "DesEncryption.h"

int SBOX1[4][16] = { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} };
int SBOX2[4][16] = { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10}, {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}, {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15}, {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} };
int SBOX3[4][16] = { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8}, {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1}, {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}, {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} };
int SBOX4[4][16] = { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}, {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}, {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}, {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} };

int SBOX5[4][16] = { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}, {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}, {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}, {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} };
int SBOX6[4][16] = { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11}, {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8}, {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6}, {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} };
int SBOX7[4][16] = { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}, {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6}, {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2}, {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} };
int SBOX8[4][16] = { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}, {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}, {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8}, {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} };

int plain_txt[64] = { 0,0,0,0, 0,0,0,1, 0,0,1,0, 0,0,1,1, 0,1,0,0, 0,1,0,1, 0,1,1,0, 0,1,1,1, 1,0,0,0, 1,0,0,1, 1,0,1,0, 1,0,1,1, 1,1,0,0, 1,1,0,1, 1,1,1,0, 1,1,1,1 };
//Lab{ 0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,3,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1 };
//Website{ 0,0,0,0, 0,0,0,1, 0,0,1,0, 0,0,1,1, 0,1,0,0, 0,1,0,1, 0,1,1,0, 0,1,1,1, 1,0,0,0, 1,0,0,1, 1,0,1,0, 1,0,1,1, 1,1,0,0, 1,1,0,1, 1,1,1,0, 1,1,1,1 };

int IP[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };

int E_table[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };

int sboxed_premute[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };

int INVERSE_PERMM[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };

int KEY[64] = { 0,0,0,1,0,0,1,1, 0,0,1,1,0,1,0,0, 0,1,0,1,0,1,1,1, 0,1,1,1,1,0,0,1, 1,0,0,1,1,0,1,1, 1,0,1,1,1,1,0,0, 1,1,0,1,1,1,1,1, 1,1,1,1,0,0,0,1 };

//{ 0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0 };
//WebSite { 0,0,0,1,0,0,1,1, 0,0,1,1,0,1,0,0, 0,1,0,1,0,1,1,1, 0,1,1,1,1,0,0,1, 1,0,0,1,1,0,1,1, 1,0,1,1,1,1,0,0, 1,1,0,1,1,1,1,1, 1,1,1,1,0,0,0,1 };
// Doc//{ 0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1 };

int pm2[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };




string DesEncryption::Encrypt(string plainText_hex, string key_hex)
{
    transform(plainText_hex.begin(), plainText_hex.end(), plainText_hex.begin(), ::toupper);
    transform(key_hex.begin(), key_hex.end(), key_hex.begin(), ::toupper);

    //Input Validation
    bool Invalid_input1 = false;
    bool Invalid_input2 = false;
    bool Invalid_input3 = false;
    bool Invalid_input4 = false;
    Invalid_input1 = Length_input(plainText_hex, 18);
    Invalid_input2 = Check_Hex(plainText_hex);
    Invalid_input3 = Length_input(key_hex, 18);
    Invalid_input4 = Check_Hex(key_hex);
    //Invalid_input = Check_Hex();
    if (Invalid_input1 == false || Invalid_input2 == false || Invalid_input3 == false || Invalid_input4 == false)
    {
        cout << "Wrong Input" << endl;;
        return "";
    }


    int plainText[64];
    string plainText_bin = "";
    plainText_bin = hex_to_bin(plainText_hex);
    binstr_to_binarr(plainText_bin, plainText);

    int key[64];
    string key_bin = "";
    key_bin = hex_to_bin(key_hex);
    binstr_to_binarr(key_bin, key);


    int initial_C1[64] = {};

    //1)intial perm(IP)
    permute(IP, plainText, 64, 64, initial_C1);
    int** subs = new int* [16];
    for (int i = 0; i < 16; i++)
    {
        subs[i] = new int[56];
    }

    subs[0] = keys(key, 1);
    int arr2[48] = {};
    permute(pm2, subs[0], 48, 56, arr2);

    ENC_arr(arr2, initial_C1, initial_C1);

    for (int i = 1; i < 16; i++)
    {
        //cout << endl << "subkey" << i + 1 << endl;
        subs[i] = keys(subs[i - 1], i + 1);
        int arr2[48] = {};
        permute(pm2, subs[i], 48, 56, arr2);
        ENC_arr(arr2, initial_C1, initial_C1);
    }
    //Last Swap
    Last_swap(initial_C1);

    int final_cipher[64] = { 0 };
    permute(INVERSE_PERMM, initial_C1, 64, 64, final_cipher);
    //int testarr[] = { 0,1,1,1,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,0,0,1,1,0,1,1,1,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,0,0,1,0,1,0, };

    //here final_cipher

    //std::cout << "\Encryption in BinaryFormat: \n";
    string s = "";
    for (int i = 0; i < 64; i++)
    {
        //std::cout << final_cipher[i];
        s += to_string(final_cipher[i]);

    }


    string result = "";
    result = bin_to_hex2(s);
    /* stringstream sstream(s);
     string output;
     while (sstream.good())
     {
         bitset<8> bits;
         sstream >> bits;
         char c = char(bits.to_ulong());
         output += c;
     }*/

    delete[] subs;
    return result;
}
void DesEncryption::ENC_arr(int* round_keyN, int round_CipherN[], int ret_new_Cipher[])
{
    // new_Cipher[64] = { 0 };
    //cout << o << " goooo" << endl;

    /////////////////////////////////////encryption//////////////////////////////
    //split into Right And left(32-bit each)
    int L[32] = { 0 };
    int R[32] = { 0 };
    int start = 0;
    for (int i = 0; i < 64; i++)
    {
        if (i < 32)
        {
            L[i] = round_CipherN[i];


        }
        else
        {
            R[start] = round_CipherN[i];
            //cout << R[start];
            start++;
        }
    }

    // cout << endl;

     //right will be left 
    // int new_Left[32] = {0};
    Right_to_Left(R, ret_new_Cipher);
    /* for (int i = 0; i < 64; i++)
     {
         cout << new_Cipher[i];
     }
     cout << endl;*/

     //Expansion right side
    int E_arr[48] = { 0 };
    permute(E_table, R, 48, 32, E_arr);//right
    /*  for (int i = 0; i < 48; i++)
       {
           cout << E_arr[i];
       }*/


       //Xor Expansion Table with Key in 1st round
    int Exp_XOR_Key[48] = { 0 };
    XoR_arr(E_arr, round_keyN, 48, Exp_XOR_Key);//////////////////////////////////////
    /*  for (int i = 0; i < 48; i++)
     {
         cout << Exp_XOR_Key[i];
     }*/


     /////S-Box
    int row_no[8] = { 0 };
    int col_no[8] = { 0 };
    rows(Exp_XOR_Key, row_no);
    cols(Exp_XOR_Key, col_no);


    int Out_SBox[32] = { 0 };
    S_BOX(row_no, col_no, Out_SBox);//////////////////////////////
    // cout << endl;
     /*  for (int i = 0; i < 32; i++)
       {
           cout << Out_SBox[i];
       }*/


       //cout << endl;

    permute(sboxed_premute, Out_SBox, 32, 32, R);
    /* for (int i = 0; i < 32; i++)
     {
         cout << R[i];
     }*/

     //cout << endl;
    XoR_arr(R, L, 32, R);
    /* for (int i = 0; i < 32; i++)
     {
         cout << R[i];
     }*/

    int count = 0;
    for (int i = 32; i < 64; i++)
    {
        //if (i < 32)
        //{

        //    arr_plain[i] = new_Left[i];
        //   // cout << arr_plain[i];
        //   
        //    
        //}
       /* if (i == 0)
        {
            cout << "ss";
        }*/
        //else
        //

        ret_new_Cipher[i] = R[count];
        //cout << new_Cipher[i];
        count++;
        //}
    }
    //for (int z = 0; z < 64; z++)
    //{
    //    cout << new_Cipher[z];
    //}

    /*cout<< endl << "LEFT:" << endl;
    for (int i = 0; i < 32; i++)
    {

        cout << new_Cipher[i];
    }
    cout << endl;*/
    /* cout << new_Cipher;
     cout << endl;*/

}

void DesEncryption::Last_swap(int* arr1)
{
    int temp_left[32] = { 0 };
    int temp_R[32] = { 0 };
    int start = 0;

    for (int j = 0; j < 32; j++)
        temp_left[j] = arr1[j];//save left

    int count = 0;
    for (int j = 32; j < 64; j++)
    {
        temp_R[count] = arr1[j];
        count++;
    }
    start = 0;
    for (int i = 0; i < 64; i++)
    {
        if (i < 32)
        {
            arr1[i] = temp_R[i];
        }
        else
        {
            arr1[i] = temp_left[start];
            start++;
        }
    }

}

void DesEncryption::dectobinary(int value, int* binaryArr) {

    int total = value;
    bool a = 0, b = 0, c = 0, d = 0;
    while (total > 0) {
        //std::cout << total << endl;
        if (total >= 8) {
            a = true;
            total = total - 8;
        }
        else if (total >= 4) {
            b = true;
            total = total - 4;
        }
        else if (total >= 2) {
            c = true;
            total = total - 2;
        }
        else if (total >= 1) {
            d = true;
            total = total - 1;
        }

    }
    binaryArr[3] = d == true ? 1 : 0;
    binaryArr[2] = c == true ? 1 : 0;
    binaryArr[1] = b == true ? 1 : 0;
    binaryArr[0] = a == true ? 1 : 0;


}

void DesEncryption::S_BOX(int rows[], int cols[], int* ret_arr)
{
    int arr_S_Box[8] = { 0 };
    int binaryArr[4] = { 0 };
    int start = 0;
    for (int i = 0; i < 8; i++)
    {
        switch (i)
        {
        case 0:
            arr_S_Box[i] = SBOX1[rows[i]][cols[i]];
            break;
        case 1:
            arr_S_Box[i] = SBOX2[rows[i]][cols[i]];
            break;
        case 2:
            arr_S_Box[i] = SBOX3[rows[i]][cols[i]];
            break;
        case 3:
            arr_S_Box[i] = SBOX4[rows[i]][cols[i]];
            break;
        case 4:
            arr_S_Box[i] = SBOX5[rows[i]][cols[i]];
            break;
        case 5:
            arr_S_Box[i] = SBOX6[rows[i]][cols[i]];
            break;
        case 6:
            arr_S_Box[i] = SBOX7[rows[i]][cols[i]];
            break;
        case 7:
            arr_S_Box[i] = SBOX8[rows[i]][cols[i]];
            break;
        }
        dectobinary(arr_S_Box[i], binaryArr);
        for (int l = 0; l < 4; l++)
        {

            ret_arr[start] = binaryArr[l];
            /*  cout << ret_arr[start];*/
            start++;
        }
        //cout << endl;
    }

}


void DesEncryption::cols(int arr[], int* cols)
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
void DesEncryption::rows(int arr[], int* row)
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

void DesEncryption::Right_to_Left(int arr[], int* ret_arr)
{

    for (int i = 0; i < 32; i++)
    {
        ret_arr[i] = arr[i];
    }

}

void DesEncryption::XoR_arr(int arr[], int arr2[], int size, int* ret_arr)
{
    //end(arr) - begin(arr);

    for (int i = 0; i < size; i++)
    {
        ret_arr[i] = arr[i] ^ arr2[i];
        //cout << ret_arr[i];
    }

}

void DesEncryption::permute(int* pc, int* key, int size1, int size2, int* return_arr)
{
    for (int i = 0; i < size1; i++)
    {
        int x = pc[i] - 1;
        return_arr[i] = key[x];
    }
}

void DesEncryption::rot(int* X)
{
    int temp = X[0];
    for (int i = 0; i < 28; i++)
    {
        X[i] = X[i + 1]; //move all element to the left except first one
    }
    X[27] = temp;
}

int* DesEncryption::keys(int key[], int round)
{
    /*
    for (int i = 0; i < 64; i++)
    {
        cout << key[i];
    }
    cout << endl;
    */

    static int arr[56] = { 0 };
    if (round > 16)
    {
        cout << "max rounds are 16";
        exit(0);
    }
    if (round == 1)
    {
        //key 64
        int pm[] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
        //Website { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
        int size1 = sizeof(pm) / sizeof(pm[0]);
        int size2 = 64;
        permute(pm, key, size1, size2, arr);
        /* for (int i = 0; i < 56; i++)
         {
             cout << arr[i];
         }
         cout << "---------------------------------------------------------" << endl;*/
    }
    if (round != 1)
    {
        for (int i = 0; i < 56; i++)
            arr[i] = key[i];
    }
    if (round == 1 || round == 2 || round == 9 || round == 16)
    {
        int C[56 / 2] = { 0 };
        for (int i = 0; i < 56 / 2; i++)
        {
            C[i] = arr[i];
        }
        int D[56 / 2] = { 0 };
        int j = 0;
        for (int i = 56 / 2; i < 56; i++, j++)
        {
            D[j] = arr[i];
        }
        rot(C);
        rot(D);
        for (int i = 0; i < 56 / 2; i++)
        {
            arr[i] = C[i];
        }
        j = 0;
        for (int i = 56 / 2; i < 56; i++, j++)
        {
            arr[i] = D[j];
        }
        return arr;
    }
    else
    {
        int C[56 / 2] = { 0 };
        for (int i = 0; i < 56 / 2; i++)
        {
            C[i] = arr[i];
        }
        int D[56 / 2] = { 0 };
        int j = 0;
        for (int i = 56 / 2; i < 56; i++, j++)
        {
            D[j] = arr[i];
        }
        rot(C);
        rot(D);
        rot(C);
        rot(D);
        for (int i = 0; i < 56 / 2; i++)
        {
            arr[i] = C[i];
        }
        j = 0;
        for (int i = 56 / 2; i < 56; i++, j++)
        {
            arr[i] = D[j];
        }

        return arr;
    }
}
string DesEncryption::bin_to_hex2(string key)
{
    string key_hex = "0x";
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
string DesEncryption::hex_to_bin(string sb_wrod)
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
void DesEncryption::binstr_to_binarr(string plainText_bin, int* arr)
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
bool DesEncryption::Length_input(string txt, int size)
{
    if (txt.length() == size)
    {

        return 1;
    }
    return 0;
}
bool DesEncryption::Check_Hex(string hex_string)
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
