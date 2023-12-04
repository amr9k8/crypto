#include "PlayFair.h"
#include <String>
#include <algorithm> 
#include <iostream>
using namespace std;
char matrix[5][5];
char new_plain_txt[100] = { '0' };
char new_decryption[100] = { '0' };
//////////////////////////////////////////////////build Key Matrix///////////////////////////////////////////////////////////////////////
void PlayFair::create_matrix(string key)
{
    string alph = "abcdefghiklmnopqrstuvwxyz";
    transform(alph.begin(), alph.end(), alph.begin(), toupper);
    char final_key[25];
    int count_finalkey = 0;


    bool repeated = false;
    bool repeated2 = false;

    //change lower case to upper case in key
    transform(key.begin(), key.end(), key.begin(), toupper);
    //convert j to i in key
    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] == 'J')
        {
            key[i] = 'I';
        }
    }

    //final key
    for (int i = 0; i < key.length(); i++)
    {

        for (int j = i + 1; j < key.length(); j++)
        {

            if (key[i] == key[j])
            {
                // repeated = true;
                key[j] = '2';
            }

        }
        if (key[i] != '2')
        {

            final_key[count_finalkey] = key[i];
            count_finalkey++;
        }

    }

    //prepare matrix
    //delete key letters from alphabet
    for (int i = 0; i < count_finalkey; i++)
    {

        for (int j = 0; j < alph.length(); j++)
        {
            if (alph[j] == final_key[i])
            {
                repeated2 = true;
                alph[j] = '0';

            }
            ///continue
        }

        repeated2 = false;
    }


    // alph[10] = '0';
    // alph[9]='0';
    for (int i = 0; i < 25; i++)
    {
        if (alph[i] != '0')
        {
            final_key[count_finalkey] = alph[i];
            count_finalkey++;
        }
    }


    //fill matrix
    int start = 0;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            matrix[row][col] = final_key[start];
            start++;
            //cout << matrix[row][col] << ' ';
        }
        //cout << '\n';
    }
}




//////////////////////////////////////////////////Encryption////////////////////////////////////////////////////////////////////////
void PlayFair::encrypt(string plain_txt)
{
    int count_new_plain_txt = 0;

    //change lower case to uppercase in PT
    transform(plain_txt.begin(), plain_txt.end(), plain_txt.begin(), toupper);

    //convert j to i in PT
    for (int i = 0; i < plain_txt.length(); i++)
    {
        if (plain_txt[i] == 'J')
        {
            plain_txt[i] = 'I';
        }
    }

    //Split and check repeated 2 letters
    for (int i = 0; i < plain_txt.length(); i += 2)
    {
        if (plain_txt[i] == plain_txt[i + 1])
        {
            new_plain_txt[count_new_plain_txt] = plain_txt[i];
            new_plain_txt[count_new_plain_txt + 1] = 'X';
            new_plain_txt[count_new_plain_txt + 2] = plain_txt[i];
            i = i - 1;
            count_new_plain_txt += 2;
        }
        else
        {



            if (plain_txt[i + 1] != 0)//if max 
            {
                new_plain_txt[count_new_plain_txt] = plain_txt[i];
                new_plain_txt[count_new_plain_txt + 1] = plain_txt[i + 1];
                count_new_plain_txt += 2;
            }
            else
            {
                new_plain_txt[count_new_plain_txt] = plain_txt[i];
                count_new_plain_txt++;
            }
        }
    }

    //check odd or even and append 'z'
    if (count_new_plain_txt % 2 != 0)
    {
        new_plain_txt[count_new_plain_txt] = 'Z';
        count_new_plain_txt++;
    }


    //Maping
    int x1, y1, x2, y2;
    char encr[100];
    for (int i = 0; i < count_new_plain_txt; i += 2)
    {

        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                if (new_plain_txt[i] == matrix[row][col])
                {
                    x1 = row;
                    y1 = col;

                }
                if (new_plain_txt[i + 1] == matrix[row][col])
                {
                    x2 = row;
                    y2 = col;
                }

            }

        }

        if (x1 == x2)
        {

            if (y1 == 4)
            {
                encr[i] = matrix[x1][0];
                encr[i + 1] = matrix[x2][y2 + 1];
            }
            if (y2 == 4)
            {
                encr[i] = matrix[x1][y1 + 1];
                encr[i + 1] = matrix[x2][0];
            }
            if (y1 != 4 && y2 != 4)
            {
                encr[i] = matrix[x1][y1 + 1];
                encr[i + 1] = matrix[x2][y2 + 1];
            }


        }
        else if (y2 == y1)
        {
            if (x1 == 4)
            {
                encr[i] = matrix[0][y1];
                encr[i + 1] = matrix[x2 + 1][y2];
            }
            if (x2 == 4)
            {
                encr[i] = matrix[x1 + 1][y1];
                encr[i + 1] = matrix[0][y2];
            }
            if (x1 != 4 && x2 != 4)
            {
                encr[i] = matrix[x1 + 1][y1];
                encr[i + 1] = matrix[x2 + 1][y2];
            }

        }
        else if (x1 != x2 && y1 != y2)
        {
            encr[i] = matrix[x1][y2];
            encr[i + 1] = matrix[x2][y1];
        }

    }
    cout << "Cipher Text : ";
    for (int i = 0; i < count_new_plain_txt; i++)
    {
        cout << encr[i];
    }
    cout << '\n';
}




////////////////////////////////////////////////Decryption/////////////////////////////////////////////////////////////////////////////////
void PlayFair::decrypt(string cipher_txt)
{
    //change lower case to uppercase in PT
    transform(cipher_txt.begin(), cipher_txt.end(), cipher_txt.begin(), toupper);
    //convert j to i in PT
    for (int i = 0; i < cipher_txt.length(); i++)
    {
        if (cipher_txt[i] == 'J')
        {
            cipher_txt[i] = 'I';
        }
    }
    //map between points of pair
    char decrypt[100];
    int x1, x2, y1, y2;
    for (int i = 0; i < cipher_txt.length(); i += 2)
    {

        for (int rows = 0; rows < 5; rows++)
        {
            for (int columns = 0; columns < 5; columns++)
            {
                if (cipher_txt[i] == matrix[rows][columns])
                {
                    x1 = rows;
                    y1 = columns;

                }
                if (cipher_txt[i + 1] == matrix[rows][columns])
                {
                    x2 = rows;
                    y2 = columns;
                }

            }

        }
        if (x1 == x2)
        {

            if (y1 == 0)
            {
                decrypt[i] = matrix[x1][4];
                decrypt[i + 1] = matrix[x2][y2 - 1];
            }
            if (y2 == 0)
            {
                decrypt[i] = matrix[x1][y1 - 1];
                decrypt[i + 1] = matrix[x2][4];
            }
            if (y1 != 0 && y2 != 0)
            {
                decrypt[i] = matrix[x1][y1 - 1];
                decrypt[i + 1] = matrix[x2][y2 - 1];
            }

        }
        else if (y2 == y1)
        {
            if (x1 == 0)
            {
                decrypt[i] = matrix[4][y1];
                decrypt[i + 1] = matrix[x2 - 1][y2];
            }
            if (x2 == 0)
            {
                decrypt[i] = matrix[x1 - 1][y1];
                decrypt[i + 1] = matrix[4][y2];
            }
            if (x1 != 0 && x2 != 0)
            {
                decrypt[i] = matrix[x1 - 1][y1];
                decrypt[i + 1] = matrix[x2 - 1][y2];
            }

        }
        else if (x1 != x2 && y1 != y2)
        {
            decrypt[i] = matrix[x1][y2];
            decrypt[i + 1] = matrix[x2][y1];
        }
    }


    bool x_deleted = false;
    //delete x between duplicate
    int counter = 0;
    for (int i = 0; i < cipher_txt.length(); i++)
    {
        if (decrypt[i] == decrypt[i + 2] && decrypt[i + 1] == 'X')
        {
            new_decryption[counter] = decrypt[i];
            new_decryption[counter + 1] = decrypt[i];
            counter += 2;
            i += 2;
            x_deleted = true;
        }
        else
        {

            new_decryption[counter] = decrypt[i];
            counter++;

        }
    }


    //delete last index if = z
    if (x_deleted == true && counter % 2 != 0)
    {
        new_decryption[counter - 1] = '0';
        counter--;
    }

    //convert to lowercase
    for (int i = 0; i < counter; i++)
    {
        if (isupper(new_decryption[i]))
        {
            new_decryption[i] = tolower(new_decryption[i]);
        }
    }

    //print final decryption
    cout << "Plain Text : ";
    for (int i = 0; i < cipher_txt.length(); i++)
    {
        if (new_decryption[i] != '0')
            cout << new_decryption[i];
    }
    cout << "\n";
}