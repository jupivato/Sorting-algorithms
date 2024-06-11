#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
#include<fstream> 

#define MAX 10

using namespace std;

void bubble (string *vet) 
{
    string aux;
    for(int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX-i-1; ++j)
            if(vet[j+1] < vet[j])
            {
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }    
}

void selection (string *vet) 
{
    string aux;
    int menor;
    for(int i = 0; i < MAX-1; ++i)
    {
        menor = i;
        for (int j = (i+1); j < MAX; ++j)
            if (vet[j] < vet[menor]) menor = j;
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}

void insertion (string *vet) 
{
    string aux;
    int j;
    for (int i = 1; i < MAX; ++i)
    {
        aux = vet[i];
        for (j = i-1; (j >= 0) && (vet[j] > aux); --j) vet[j+1] = vet[j];
        vet[j+1] = aux;
    }
}

void shell (string *vet) 
{
    string aux;
    int j, h;
    h = MAX / 2;
    while (h >= 1)
    {
        for (int i = 1; i < MAX; ++i)
        {
            aux = vet[i];
            for (j = i - h; (j >= 0) && (vet[j] > aux); j = j - h)
                vet[j + h] = vet[j];
            vet[j+h] = aux;
        }
        h = h/2;
    }
}

void intercala(string *v, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    string *left = new string[n1];
    string *right = new string[n2];

    for (int i = 0; i < n1; i++) left[i] = v[p + i];
    for (int j = 0; j < n2; j++) right[j] = v[q + 1 + j];

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j]) v[k++] = left[i++];
        else v[k++] = right[j++];
    }
    while (i < n1) v[k++] = left[i++];
    while (j < n2) v[k++] = right[j++];
    delete[] left;
    delete[] right;
}

void merge(string *v, int p, int r) 
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge(v, p, q);
        merge(v, q + 1, r);
        intercala(v, p, q, r);
    }
}


int particiona(string *v, int p, int r)
{
    int i = p, j = r + 1; 
    string piv = v[p];
    while(1)
    {
        while(v[++i] < piv) if(i == r) break;
        while(piv < v[--j]) if(j == p) break;
        if(i >= j) break;
        string aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
    string aux = v[p];
    v[p] = v[j];
    v[j] = aux;
    return j;
}

void quick(string *v, int p, int r) 
{
    int q;
    if(p < r)
    {
        q = particiona(v, p, r);
        quick(v, p, q - 1);
        quick(v, q + 1, r);
    }
}


int main()
{
    int k = 0;
    string vet[MAX], palavra;
    ifstream arquivo("aurelio40000.txt");
    if (!arquivo.is_open()) return 1;
    while (k < MAX && arquivo >> palavra) vet[k++] = palavra;
    arquivo.close();
    cout << "[VETOR DESORDENADO] = ";
    for (int i= 0; i < MAX; ++i) cout << vet[i] << " ";
    cout << endl;
    //bubble(vet);
    //selection(vet);
    //insertion (vet);
    //shell(vet);
    //merge(vet, 0, MAX-1);
    //quick(vet, 0, MAX-1);
    cout << "[VETOR ORDENADO]    = ";
    for (int i= 0; i < MAX; ++i) cout << vet[i] << " ";
    cout << endl;
    return 0;
}