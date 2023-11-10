#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>

using namespace std;

void tokenize(const string& str, unordered_map<string, int>& wordFreq) {
    istringstream iss(str);
    string word;
    while (iss >> word) {
        wordFreq[word]++;
    }
}

double dotProduct(const unordered_map<string, int>& v1, const unordered_map<string, int>& v2) {
    double product = 0;
    for (const auto& entry : v1) {
        if (v2.count(entry.first) > 0) {
            product += entry.second * v2.at(entry.first);
        }
    }
    return product;
}

double magnitude(const unordered_map<string, int>& v) {
    double mag = 0;
    for (const auto& entry : v) {
        mag += entry.second * entry.second;
    }
    return sqrt(mag);
}

double dotProductSimilarity(const unordered_map<string, int>& v1, const unordered_map<string, int>& v2) {
    double dot = dotProduct(v1, v2);
    double mag1 = magnitude(v1);
    double mag2 = magnitude(v2);

    if (mag1 == 0 || mag2 == 0) {
        return 0.0;
    }

    return dot / (mag1 * mag2);
}

int main() {
    string nomFichier1 = "fichier1.txt";
    string nomFichier2 = "fichier2.txt";

    ifstream fichier1(nomFichier1);
    ifstream fichier2(nomFichier2);

    if (!fichier1.is_open() || !fichier2.is_open()) {
        cerr << "Erreur lors de l'ouverture des fichiers." << endl;
        return 1;
    }

    unordered_map<string, int> freqMots1;
    unordered_map<string, int> freqMots2;
    string ligne;

    // Afficher le contenu du 1er fichier
    cout << "Contenu du fichier " << nomFichier1 << ":" << endl;
    while (getline(fichier1, ligne)) {
        cout << ligne << endl;
        tokenize(ligne, freqMots1);
    }
    cout << endl;

    // Afficher le contenu du 2eme fichier
    cout << "Contenu du fichier " << nomFichier2 << ":" << endl;
    while (getline(fichier2, ligne)) {
        cout << ligne << endl;
        tokenize(ligne, freqMots2);
    }
    cout << endl;

    fichier1.close();
    fichier2.close();

    double similarite = dotProductSimilarity(freqMots1, freqMots2);
    cout << "Similarité entre 2 fichier : " << similarite << endl;

    return 0;
}
