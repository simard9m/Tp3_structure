/*
 * Devoir 3 – Arbres binaires de recherche
 *
 * Fait par : Émile Simard          (SIME09050100)
 *            Xavier Boivin-Thibeault (BOIX19050400)
 */
#ifndef ABR_H
#define ABR_H

#include <iostream>
#include <queue>

//Strucuture pour les noeuds
struct noeud
{
	int valeur;
	noeud *gauche;
	noeud *droit;
};

class ABR {
private:
	//On keep la racine dans une var pour la garder proche
	noeud* racine;

	//Fonction recursives internes qui vont me servir plus tard
	void detruire(noeud *n);
	noeud* insererRec(noeud *n, int d);
	noeud* supprimerRec(noeud *n, int d);
	noeud* TrouverMin(noeud *n);
	int hauteurRec(noeud *n);
	bool afficherAscendantRec(noeud *n, int d);

public:
	ABR(noeud* r = nullptr);
	~ABR();

	//Je ne passerai pas la racine elle est deja presente dans la structure
	void Inserer(int d);      
	void Supprimer( int d);
	void Afficher_Arbre(noeud* r);
	int  Afficher_hauteur(noeud* r);
	void Afficher_Ascendant(int d);

	//Fonction pour acceder a la racine au cas ou
	noeud* getRacine() const { return racine; }
};




#endif // !ABR_H

