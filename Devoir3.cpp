#include <iostream>
#include <fstream>
#include <sstream>
#include "abr.h"
using namespace std;

int main()
{
    ABR arbre(nullptr);

    ifstream fichier("operations.txt");
    if (!fichier) {
        cerr << "Erreur : impossible d'ouvrir le fichier operations.txt" << endl;
        return 1;
    }
    string ligne;

    //pour faire en sorte qeu mon affichage soit plus clean un peu 
    bool premierAffichage = true;

    while (getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        char op;
        char virgule;
        int valeur;

        //si ya une virgule on parse op valeur
        if (ligne.size() >= 3 && (ligne[1] == ',' || ligne[1] == ';')) {
            op = ligne[0];
            stringstream ss(ligne.substr(2));
            ss >> valeur;

            switch (op) {
            case 'I':
                arbre.Inserer(valeur);
                break;
            case 'S':
                arbre.Supprimer(valeur);
                break;
            case 'G':
                if (!premierAffichage) {
                    cout << endl;
                }
                premierAffichage = false;
                arbre.Afficher_Ascendant(valeur);
                break;
            default:
                cout << "Operation inconnue : " << op << endl;
                break;
            }
        }
        else {
            //operation sans valeu
            op = ligne[0];
            switch (op) {
            case 'A':
                if (!premierAffichage) {
                    cout << endl;
                }
                premierAffichage = false;
                arbre.Afficher_Arbre(arbre.getRacine());
                break;
            case 'H':
                if (!premierAffichage) {
                    cout << endl;
                }
                premierAffichage = false;
                arbre.Afficher_hauteur(arbre.getRacine());
                break;
            default:
                cout << "Operation inconnue : " << op << endl;
                break;
            }
        }
    }

    fichier.close();
    return 0;
}

