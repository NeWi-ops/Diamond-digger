// #pragma once

// #include <vector>

// class MapGenerator {
// public:
//     MapGenerator(int largeur, int hauteur);  // Constructeur qui prend la taille de la carte
//     void genererCarte();                     // Générer la carte
//     void afficherCarte() const;              // Afficher la carte dans la console

// private:
//     int m_largeur;
//     int m_hauteur;
//     std::vector<std::vector<int> > m_carte;  // Représentation de la carte (0 = vide, 1 = plein)
//     void appliquerReglesAutomate();         // Appliquer les règles de l'automate cellulaire
// };


#pragma once
#include <vector>
#include <utility>

class MapGenerator {
public:
    MapGenerator(int largeur, int hauteur);
    void genererCarte();
    void afficherCarte() const;
    
private:
    int m_largeur;
    int m_hauteur;
    std::vector<std::vector<int> > m_carte;  // Carte où 0 = vide et 1 = plein
    
    void appliquerReglesAutomate();
    std::vector<std::pair<int, int> > trouverCasesVides() const;
    void ajouterPieges(int nbPieges);  // Déclaration pour ajouter des pièges
};
