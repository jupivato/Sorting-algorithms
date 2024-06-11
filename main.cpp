#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void preenche(string *vet, int tam);
void imprime(string *vet, int tam);
void bubble(string *vet, int tam);
void selection(string *vet, int tam);
void insertion(string *vet, int tam);
void shell(string *vet, int tam);
void intercala(string *v, int p, int q, int r);
void merge(string *v, int p, int r);
int particiona(string *v, int p, int r);
void quick(string *v, int p, int r);

int main() 
{
    int tam;
    int op = 0;
    while (op != 7) 
    {
        cout << "Tamanho do vetor:" << endl;
        cin >> tam;
        string *vet = new string[tam];
        preenche(vet, tam);
        cout << "[VETOR DESORDENADO] = ";
        //imprime(vet, tam);
        cout << "Qual algoritmo de ordenacao?" << endl;
        cout << "1 - BubbleSort\n";
        cout << "2 - SelectionSort\n";
        cout << "3 - InsertionSort\n";
        cout << "4 - ShellSort\n";
        cout << "5 - MergeSort\n";
        cout << "6 - QuickSort\n";
        cout << "6 - Sair\n";
        cin >> op;
        float tempo_ini, tempo_fin, tempo_ms;
        tempo_ini = (float)clock();
        switch (op)
        {
            case 1:
                bubble(vet, tam);
                cout << "BubbleSort\n";
                break;
            case 2:
                selection(vet, tam);
                cout << "SelectionSort\n";
                break;
            case 3:
                insertion(vet, tam);
                cout << "InsertionSort\n";
                break;
            case 4:
                shell(vet, tam);
                cout << "ShellSort\n";
                break;
            case 5:
                merge(vet, 0, tam-1);
                cout << "MergeSort\n";
                break;
            case 6:
                quick(vet, 0, tam-1);
                cout << "QuickSort\n";
                break;
            default:
                break;
        }
        tempo_fin = (float)clock();
        tempo_ms = (tempo_fin - tempo_ini) / CLOCKS_PER_SEC * 1000.0;
        cout << "Vetor de tamanho " << tam << " apos ordenacao" << endl;
        cout << "Tempo gasto para ordenacao: " << tempo_ms << " ms" <<
        endl;
        delete[] vet;
    }
    return 0;
}

void preenche (string *vet, int tam)
{
    string palavra;
    ifstream arq ("aurelio40000.txt");
    if (arq.is_open())
    {
        int k = 0;
        while (k < tam)
        {
            getline (arq, palavra);
            vet[k] = palavra;
            k++;
        }
    }
    else cout << "falha ao abrir o arquivo" << endl;
}

void imprime (string *vet, int tam)
{
    for (int i = 0; i < tam; ++i) cout << vet[i] << " ";
    cout << endl;
}

void bubble (string *vet, int tam)
{
    string aux;
    for (int i = 0; i < tam; ++i)
        for (int j = 0; j < tam - 1; ++j)
            if (vet[j+1] < vet[j])
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j+1] = aux;
            }
}

void selection (string *vet, int tam)
{
    string aux;
    int menor;
    for (int i = 0; i < tam - 1; ++i)
    {
        menor = i;
        for (int j = (i + 1); j < tam; ++j)
            if (vet[j] < vet[menor]) menor = j;
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}

void insertion (string *vet, int tam)
{
    string aux;
    int j;
    for (int i = 1; i < tam; ++i)
    {
        aux = vet[i];
        for (j = i - 1; (j >= 0) && (vet[j] > aux); --j) 
            vet[j + 1] = vet[j];
        vet [j + 1] = aux;
    }
}

void shell(string *vet, int tam) 
{
    string aux;
    int j, h;
    for (h = 1; h < tam / 3; h = 3 * h + 1);
    while (h >= 1) 
    {
        for (int i = h; i < tam; ++i) 
        {
            aux = vet[i];
            for (j = i; (j >= h) && (vet[j - h] > aux); j -= h) vet[j] =
            vet[j - h];
            vet[j] = aux;
        }
        h /= 3;
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
    while (1) 
    {
        while (v[++i] < piv) if (i == r) break;
        while (piv < v[--j]) if (j == p) break;
        if (i >= j) break;
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
    if (p < r) 
    {
        q = particiona(v, p, r);
        quick(v, p, q - 1);
        quick(v, q + 1, r);
    }
}
