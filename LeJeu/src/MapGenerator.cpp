// #include "MapGenerator.hpp"
// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>

// // Constructeur de la carte
// MapGenerator::MapGenerator(int largeur, int hauteur)
//     : m_largeur(largeur), m_hauteur(hauteur) {
//     // Initialisation de la carte avec des cases vides (0) et pleines (1) de manière aléatoire
//     m_carte.resize(m_hauteur, std::vector<int>(m_largeur, 0));
// }

// // Générer la carte en appliquant l'algorithme des automates cellulaires
// void MapGenerator::genererCarte() {
//     // Initialisation aléatoire de la carte
//     std::srand(static_cast<unsigned int>(std::time(0)));

//     for (int y = 0; y < m_hauteur; ++y) {
//         for (int x = 0; x < m_largeur; ++x) {
//             m_carte[y][x] = (std::rand() % 100) < 50 ? 1 : 0;  // 50% de chances pour chaque case
//         }
//     }

//     // Appliquer l'algorithme des automates cellulaires pendant un certain nombre d'itérations
//     for (int i = 0; i < 4; ++i) {  // 4 itérations pour affiner la carte
//         appliquerReglesAutomate();
//     }
// }

// // Appliquer les règles des automates cellulaires
// void MapGenerator::appliquerReglesAutomate() {
//     std::vector<std::vector<int> > nouvelleCarte = m_carte;  // Copie de la carte actuelle

//     for (int y = 0; y < m_hauteur; ++y) {
//         for (int x = 0; x < m_largeur; ++x) {
//             int voisinsPlein = 0;

//             // Vérifier les voisins autour de la case (y, x)
//             for (int dy = -1; dy <= 1; ++dy) {
//                 for (int dx = -1; dx <= 1; ++dx) {
//                     int nx = x + dx;
//                     int ny = y + dy;

//                     if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
//                         voisinsPlein += m_carte[ny][nx];  // On compte les cases pleines
//                     }
//                 }
//             }

//             // Appliquer les règles de l'automate cellulaire
//             if (m_carte[y][x] == 1 && voisinsPlein < 5) {
//                 nouvelleCarte[y][x] = 0;  // La case devient vide
//             }
//             if (m_carte[y][x] == 0 && voisinsPlein >= 5) {
//                 nouvelleCarte[y][x] = 1;  // La case devient pleine
//             }
//         }
//     }

//     m_carte = nouvelleCarte;  // Mise à jour de la carte
// }

// // Afficher la carte dans la console
// void MapGenerator::afficherCarte() const {
//     for (int y = 0; y < m_hauteur; ++y) {
//         for (int x = 0; x < m_largeur; ++x) {
//             std::cout << (m_carte[y][x] == 1 ? "#" : ".") << " ";  // Affiche "#" pour les cases pleines et "." pour les cases vides
//         }
//         std::cout << std::endl;
//     }
// }

#include "MapGenerator.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

MapGenerator::MapGenerator(int largeur, int hauteur)
    : m_largeur(largeur), m_hauteur(hauteur) {
    m_carte.resize(m_hauteur, std::vector<int>(m_largeur, 0));  // Initialisation de la carte avec des cases vides (0)
}

void MapGenerator::genererCarte() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Initialisation aléatoire de la carte
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            m_carte[y][x] = (std::rand() % 100) < 50 ? 1 : 0;  // 50% de chances pour chaque case d'être pleine (1) ou vide (0)
        }
    }

    // Appliquer l'algorithme des automates cellulaires pendant un certain nombre d'itérations
    for (int i = 0; i < 4; ++i) {  // 4 itérations pour affiner la carte
        appliquerReglesAutomate();
    }

    // Ajouter des pièges sur certaines cases vides
    ajouterPieges(10);  // Ajouter 10 pièges

    // Vous pouvez ajouter d'autres éléments comme des gemmes, des ennemis, etc.
}

void MapGenerator::appliquerReglesAutomate() {
    std::vector<std::vector<int> > nouvelleCarte = m_carte;  // Copie de la carte actuelle

    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            int voisinsPlein = 0;

            // Vérifier les voisins autour de la case (y, x)
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
                        voisinsPlein += m_carte[ny][nx];  // On compte les cases pleines
                    }
                }
            }

            // Appliquer les règles de l'automate cellulaire
            if (m_carte[y][x] == 1 && voisinsPlein < 5) {
                nouvelleCarte[y][x] = 0;  // La case devient vide
            }
            if (m_carte[y][x] == 0 && voisinsPlein >= 5) {
                nouvelleCarte[y][x] = 1;  // La case devient pleine
            }
        }
    }

    m_carte = nouvelleCarte;  // Mise à jour de la carte
}

std::vector<std::pair<int, int> > MapGenerator::trouverCasesVides() const {
    std::vector<std::pair<int, int> > vides;
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            if (m_carte[y][x] == 0) {  // Case vide
                vides.emplace_back(x, y);  // Ajouter la position de la case vide
            }
        }
    }
    return vides;
}

void MapGenerator::ajouterPieges(int nbPieges) {
    std::vector<std::pair<int, int> > casesVides = trouverCasesVides();  // Trouver toutes les cases vides
    std::random_shuffle(casesVides.begin(), casesVides.end());  // Mélanger aléatoirement les cases vides

    int compteur = 0;
    for (auto& caseVide : casesVides) {
        if (compteur >= nbPieges) break;  // Arrêter quand on a ajouté assez de pièges

        int x = caseVide.first;
        int y = caseVide.second;

        m_carte[y][x] = 2;  // Placer un piège (représenté par 2)

        ++compteur;
    }
}

void MapGenerator::afficherCarte() const {
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            if (m_carte[y][x] == 0)
                std::cout << ". ";  // Case vide
            else if (m_carte[y][x] == 1)
                std::cout << "# ";  // Case pleine
            else if (m_carte[y][x] == 2)
                std::cout << "X ";  // Piège
        }
        std::cout << std::endl;
    }
}
