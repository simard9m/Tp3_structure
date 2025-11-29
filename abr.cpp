/*
 * Devoir 3 – Arbres binaires de recherche
 *
 * Fait par : Émile Simard          (SIME09050100)
 *            Xavier Boivin-Thibeault (BOIX19050400)
 */

#include "abr.h"
using namespace std;

ABR::ABR(noeud *r) : racine(r){}

ABR::~ABR() {
	detruire(racine);
}

//On vas detrure recursivement tout l'arbre
void ABR::detruire(noeud *n) {
	if (n == nullptr)
		return;

	detruire(n->gauche);
	detruire(n->droit);
	delete(n);
}

//Insertion recursive dans l'arbre
noeud* ABR::insererRec(noeud *n, int d) {

	//Insere le nouveau quand on a trouve sa position
	if (n == nullptr) {
		noeud *nouveau = new noeud;
		nouveau->valeur = d;
		nouveau->gauche = nullptr;
		nouveau->droit = nullptr;
		return nouveau;
	}

	//Les calls recursifs si la vlaeur de d est plus grande ou plus petite que n->valeur
	if (d < n->valeur) {
		n->gauche = insererRec(n->gauche, d);
	}
	else if (d > n->valeur) {
		n->droit = insererRec(n->droit, d);
	}

	//si d == n->valeur pas de doublons donc rien ne se passe
	return n;

}

void ABR::Inserer(int d) {
	if (d < 0) {
		std::cout << "Valeur negative non permise : " << d << std::endl;
		return; // on ne modifie pas l'arbre
	}

	racine = insererRec(racine, d);
}

// trouver le noeud mininmum d<un arbre
noeud* ABR::TrouverMin(noeud *n) {
	while (n != nullptr && n->gauche != nullptr) {
		n = n->gauche;
	}
	return n;
}

//supression recursive dnans l<arbre
noeud* ABR::supprimerRec(noeud* n, int d) {
	if (n == nullptr) return nullptr;

	//Cherche le noeud a surpimmer
	if (d < n->valeur) {
		n->gauche = supprimerRec(n->gauche, d);
	}
	else if (d > n->valeur) {
		n->droit = supprimerRec(n->droit, d);
	}
	else {
		//On a trouve le noeuds a delete
		//Cas 1 pas d'enfants (ez) on save l<enfant et le renplace
		if (n->gauche == nullptr && n->droit == nullptr) {
			delete n;
			return nullptr;
		}
		//cas 2 Un enfant (mid)
		else if (n->gauche == nullptr) {
			noeud* tmp = n->droit;
			delete n;
			return tmp;
		}
		else if (n->droit == nullptr) {
			noeud* tmp = n->gauche;
			delete n;
			return tmp;
		}
		else {
			//cas 3 deux enfants (ish) trouve le min su sous arbre droit, le mets dans le noeuds courant, supprimme lle sucesseur recursivement
			noeud* minDroit = TrouverMin(n->droit);
			n->valeur = minDroit->valeur; // copier la valeur du successeur
			n->droit = supprimerRec(n->droit, minDroit->valeur);
		}
		

	}
	//retourne le noeud courant
	return n;
}

void ABR::Supprimer(int d) {
	racine = supprimerRec(racine, d);
}

//Afficahge par niveau
void ABR::Afficher_Arbre(noeud *r) {
	if (racine == nullptr) {
		cout << "Arbre vide" << endl;
		return;
	}

	//on vas utiliser une file 
	queue<noeud*> q;
	q.push(racine);


	while (!q.empty()) {
		int nbNoeudsNiveau = q.size();

		//afficher un niveau
		for (int i = 0; i < nbNoeudsNiveau; ++i) {
			noeud* courant = q.front();
			q.pop();

			cout << courant->valeur << " ";

			if (courant->gauche != nullptr) q.push(courant->gauche);
			if (courant->droit != nullptr) q.push(courant->droit);
		}
		//nouvelle ligne pour séparer les niveaux
		cout << endl; 
	}
}

//Hauteur en recursive
//heuteur est le plus long chemin avant un feuille
//convention nullptr = -1 hauteur nulle
int ABR::hauteurRec(noeud* n) {
	//pas de noeuds = -1
	if (n == nullptr) 
		return -1; 
	//Recusion - calcul les hauteur a gauche t a droite
	int hg = hauteurRec(n->gauche);
	int hd = hauteurRec(n->droit);

	//hauteur finale 1+ le max e gauche ou droite
	return 1 + (hg > hd ? hg : hd);
}

int ABR::Afficher_hauteur(noeud *r) {
	int h = hauteurRec(racine);
	cout << "Hauteur = " << h << endl;
	return h;
}

//affiche les ascendantss de la valeur d
//retroune true si on la trouve
bool ABR::afficherAscendantRec(noeud* n, int d) {
	//pas trouve
	if (n == nullptr) {
		return false;
	}
	
	//Trouve la valeur
	if (n->valeur == d) {
		return true;
	}

	//Si d est dans le sous-arbre gauche ou droit
	if (afficherAscendantRec(n->gauche, d) ||
		afficherAscendantRec(n->droit, d)) {
		cout << n->valeur << " ";
		return true;
	}

	return false;
}

void ABR::Afficher_Ascendant(int d) {
	if (!afficherAscendantRec(racine, d)) {
		cout << "Valeur " << d << " non trouvee dans l'arbre.";
	}
	cout << endl;
}