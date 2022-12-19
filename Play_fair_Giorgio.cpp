#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int i, j, k, n; // dichiaro le variabili
    cout << "Scrivi il messaggio da criptare..." << endl;
    string s, origin;
    getline(cin, origin); // permette di ottenere anche gli spazi
    cout << "Inserisci la chiave di criptazione" << endl;
    string key;
    cin >> key;
    for (i = 0; i < origin.size(); i++) // usando .size riesco ad ottenere la lunghezza della stringa
    {
        if (origin[i] != ' ') //stampo in s origin senza spazi
            s += origin[i];
    }
    vector<vector<char>> a(5, vector<char>(5, ' ')); // entra in gioco la libreria vector
    // creo un vettore bidimensionale = matrice 5x5
    n = 5; 
    map<char, int> mp; // qui dichiaro il contenitore (char per la chiave, int per l'indice di scorrimento)
    k = 0; 
    int pi, pj;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)// i for iterati servono per scorrere righe e colonne del vettore 2D
        {
            while (mp[key[k]] > 0 && k < key.size()) 
            {                                       
                k++;
            }
            if (k < key.size())// carico in 'a' e 'mp' i valori della
            {                  // chiave di criptazione nelle prime celle disponibli
                a[i][j] = key[k];
                mp[key[k]]++;
                pi = i;
                pj = j;
            }
            if (k == key.size())
                break;
        }
        if (k == key.size())
            break;
    }
    k = 0;
    for (; i < n; i++)// carico il resto dell'alfabeto tranne la j
    {
        for (; j < n; j++)// i for iterati servono per scorrere righe e colonne del vettore 2D
        {
            while (mp[char(k + 'a')] > 0 && k < 26)
            {
                k++;
            }
            if (char(k + 'a') == 'j')//escludo la j (in mp lascio 0)
            {
                j--;
                k++;
                continue;
            }
            if (k < 26)
            {
                a[i][j] = char(k + 'a');
                mp[char(k + 'a')]++;
            }
        }
        j = 0;
    }
    string ans;
    if (s.size() % 2 == 1)//se il n. di caratteri nella frase e' dispari
        s += "x";         //aggiungi x alla fine della frase
    for (i = 0; i < s.size() - 1; i++)
    {
        if (s[i] == s[i + 1])//se trova una doppia sosituisci con x
            s[i + 1] = 'x';
    }
    map<char, pair<int, int>> mp2;//creo la matrice dove andro' a caricare i valori di 'a'
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mp2[a[i][j]] = make_pair(i, j); //assegna a first ("colonne") e second ("righe") i valori da 0 a 4 
        }                                   //per posizionare i valori nella matrice
    }

    for (i = 0; i < s.size() - 1; i += 2) //inizia l'effettiva criptazione
    {
        int y1 = mp2[s[i]].first; //prendi le coordinate della 1^ lettera della frase
        int x1 = mp2[s[i]].second; 
        int y2 = mp2[s[i + 1]].first; //prendi le coordinate della 2^ lettera della frase
        int x2 = mp2[s[i + 1]].second; 
        if (y1 == y2) //se i 2 valori sono nella stessa colonna 
        {
            ans += a[y1][(x1 + 1) % 5];//carica nella soluzione 'ans' il carattere
            ans += a[y1][(x2 + 1) % 5];// della riga successiva
        }
        else if (x1 == x2) //se i 2 valori sono nella stessa riga
        {
            ans += a[(y1 + 1) % 5][x1];// carica nella soluzione 'ans' il carattere
            ans += a[(y2 + 1) % 5][x2];// della colonna successiva
        }
        else
        {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }
    cout << ans << '\n'; //stampo il risultato
    system("pause");
    return 0;
}