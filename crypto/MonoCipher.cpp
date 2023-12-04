#include "MonoCipher.h"

string MonoCipher::encrypt(string plaintext, string key)
{
    int* index = new int[plaintext.length()];
    for (int i = 0; i < plaintext.length(); i++)
    {
        //cout << plain_text.at(i);
        char letter = tolower(plaintext.at(i));
        char x = 'a';
        for (int j = 0; j < 26; j++)
        {
            if (x == letter)
            {
                index[i] = j;
                break;
            }
            x++;
        }
    }
    for (int i = 0; i < plaintext.length(); i++)
    {
        plaintext[i] = key.at(index[i]);
    }
    delete[] index;
    return plaintext;
}

string  MonoCipher::decrypt(string ciphertext, string key)
{
    int* index = new int[ciphertext.length()];

    for (int i = 0; i < ciphertext.length(); i++)
    {
        //cout << plain_text.at(i);
        char letter = tolower(ciphertext.at(i));
        char x = tolower(key.at(0));
        for (int j = 0; j < 26; j++)
        {
            if (x == letter)
            {
                index[i] = j;
                break;
            }
            x = tolower(key.at(j));
        }
    }
    for (int i = 0; i < ciphertext.length(); i++)
    {
        ciphertext[i] = char('a' + index[i] - 1);
    }
    delete[] index;
    return ciphertext;
}

void  MonoCipher::AnalyseUsingCharFrequency(string ciphertext)
{
    float freq[] = { 0.0817,0.0150,0.0278,0.0425,0.1270,0.0223,0.0202,0.0609,0.0697,0.0015,0.0077,0.0403,0.0241,0.0675,0.0751,0.0193,0.0010,0.0599,0.0633,0.0906,0.0276,0.0098,0.0236,0.0015,0.0197,0.0007 };
    float* freq_index = new float[ciphertext.length()];

    for (int i = 0; i < ciphertext.length(); i++)
    {
        char x = ciphertext.at(i);
        freq_index[i] = 0;
        for (int j = 0; j < ciphertext.length(); j++)
        {
            if (x == ciphertext.at(j))
            {
                freq_index[i]++;
            }
        }
        freq_index[i] /= ciphertext.length();
        cout << freq_index[i];
        cout << "\n";
    }

    for (int i = 0; i < ciphertext.length(); i++)
    {
        int nearest_neighbor = 0;
        float gap = 1000000;
        for (int j = 0; j < 26; j++)
        {
            float temp = abs(freq_index[i] - freq[j]);
            if (gap > temp)
            {
                nearest_neighbor = j;
                gap = temp;
            }
        }
        ciphertext[i] = 'a' + nearest_neighbor;
        cout << char('a' + nearest_neighbor);
    }
}