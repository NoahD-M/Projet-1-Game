#include <iostream>
#include <cstdlib>
#include <conio.h>



int niveau = 1;

enum class TileType {
    Basicground,
    Water,
    Mountain,
    Hero,
    Ennemy

};

struct Map {
    char Basicground = '.';
    char Water = '~';
    char Mountain = 'A';
    char Hero = 'H';
    char Ennemy = 'X';
    char Exit = 'E';

};


struct Hero {
    int x = 0;
    int y = 0;
    int hp = 1;
};
struct Ennemy {
    int x = 0;
    int y = 0;
    int hp = -1;
};

bool est_traversable(int x, int y, const Map& map) {       //Collision
    // basicground
    if (x < 0 || x >= 20 || y < 0 || y >= 10) return false;

    if (niveau == 1) {
        // Obstacles Niveau 1
        if ((y == 1 && x >= 5 && x <= 8) || (y == 2 && x >= 5 && x <= 8) || (y == 6 && (x == 16 || x == 17)))
            return false;
        if ((y == 2 && x >= 12 && x <= 14) || (y == 6 && x >= 2 && x <= 4))
            return false;
    }
    else if (niveau == 2) {
        // Obstacles Niveau 2 
        if ((y == 4 && x >= 5 && x <= 8) || (y == 5 && x >= 5 && x <= 8) || (y == 8 && (x == 11 || x == 12)))
            return false;
        if ((y == 5 && x >= 12 && x <= 14) || (y == 3 && x >= 2 && x <= 4))
            return false;
    }
    return true;
}

void deplacer_hero(Hero& hero, char direction, Map& map) {
    int nx = hero.x;
    int ny = hero.y;

    if (direction == 'z' || direction == 'Z') ny--;
    if (direction == 's' || direction == 'S') ny++;
    if (direction == 'q' || direction == 'Q') nx--;
    if (direction == 'd' || direction == 'D') nx++;

    // Collision avec les bordures de la carte
    if (est_traversable(nx, ny, map)) {
        hero.x = nx;
        hero.y = ny;
    }

};

void deplacer_ennemis(int ennemis[][2], int nb_ennemis, const Map& map) {
    for (int i = 0; i < nb_ennemis; ++i) {
        int nx = ennemis[i][0];
        int ny = ennemis[i][1];

        // Choisit une direction au hasard : 0=haut, 1=bas, 2=gauche, 3=droite
        int random_direction = rand() % 4;

        if (random_direction == 0) ny--;
        else if (random_direction == 1) ny++;
        else if (random_direction == 2) nx--;
        else if (random_direction == 3) nx++;

        // Applique le mouvement seulement si la case est franchissable
        if (est_traversable(nx, ny, map)) {
            ennemis[i][0] = nx;
            ennemis[i][1] = ny;
        }
    }
}
bool est_touche_par_ennemi(const Hero& hero, const int ennemis[][2], int nb_ennemis) {
    for (int i = 0; i < nb_ennemis; ++i) {
        int ex = ennemis[i][0]; // Coordonnée X de l'ennemi i
        int ey = ennemis[i][1]; // Coordonnée Y de l'ennemi i

        if (hero.x == ex && hero.y == ey) {
            return true; // Collision détectée !
        }
    }
    return false;
}


bool victoire(const Hero& hero) {
    if (hero.x == 19 && hero.y == 9) {
        return true;
    }
    return false;
}


void afficher_map(const Map& map, const Hero& hero, const int ennemis[][2], int nb_ennemis) {

    system("cls");
    

    if (niveau == 1) {
        int grille[10][20] = {};

        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 20; ++x) {
                grille[y][x] = map.Basicground;
            }
        }

        for (int x = 5; x <= 8; ++x) {
            grille[1][x] = map.Water;
            grille[2][x] = map.Water;
        }
        grille[6][16] = map.Water;
        grille[6][17] = map.Water;

        for (int x = 12; x <= 14; ++x) {
            grille[2][x] = map.Mountain;
        }
        for (int x = 2; x <= 4; ++x) {
            grille[6][x] = map.Mountain;
        }

        grille[hero.y][hero.x] = map.Hero;
        grille[9][19] = map.Exit;

        // Placement des ennemis à partir du tableau 2D
        for (int i = 0; i < nb_ennemis; ++i) {
            int ex = ennemis[i][0];
            int ey = ennemis[i][1];
            if (ey >= 0 && ey < 10 && ex >= 0 && ex < 20) {
                grille[ey][ex] = map.Ennemy;
            }
        }


        for (int ligne = 0; ligne < 10; ++ligne) {
            for (int colonne = 0; colonne < 20; ++colonne) {
                if (grille[ligne][colonne] != (map.Water)
                    && grille[ligne][colonne] != (map.Mountain)
                    && grille[ligne][colonne] != (map.Hero)
                    && grille[ligne][colonne] != (map.Ennemy)
                    && grille[ligne][colonne] != (map.Exit)) {
                    grille[ligne][colonne] = map.Basicground;
                }

                std::cout << static_cast<char>(grille[ligne][colonne]);


                grille[hero.y][hero.x] = map.Hero;
            }
            std::cout << '\n';
        }
    }
    if (niveau == 2) {
        int grille[10][20] = {};

        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 20; ++x) {
                grille[y][x] = map.Basicground;
            }
        }

        for (int x = 5; x <= 8; ++x) {
            grille[4][x] = map.Water;
            grille[5][x] = map.Water;
        }
        grille[8][11] = map.Water;
        grille[8][12] = map.Water;

        for (int x = 12; x <= 14; ++x) {
            grille[5][x] = map.Mountain;
        }
        for (int x = 2; x <= 4; ++x) {
            grille[3][x] = map.Mountain;
        }

        grille[hero.y][hero.x] = map.Hero;
        grille[9][19] = map.Exit;

        // ennemis placement
        for (int i = 0; i < nb_ennemis; ++i) {
            int ex = ennemis[i][0];
            int ey = ennemis[i][1];
            if (ey >= 0 && ey < 10 && ex >= 0 && ex < 20) {
                grille[ey][ex] = map.Ennemy;
            }
        }


        for (int ligne = 0; ligne < 10; ++ligne) {
            for (int colonne = 0; colonne < 20; ++colonne) {
                if (grille[ligne][colonne] != (map.Water)
                    && grille[ligne][colonne] != (map.Mountain)
                    && grille[ligne][colonne] != (map.Hero)
                    && grille[ligne][colonne] != (map.Ennemy)
                    && grille[ligne][colonne] != (map.Exit)) {
                    grille[ligne][colonne] = map.Basicground;
                }

                std::cout << static_cast<char>(grille[ligne][colonne]);


                grille[hero.y][hero.x] = map.Hero;
            }
            std::cout << '\n';
        }
    }



}



int main() {
    Map map{};
    Hero hero{ 0, 0, 1 };

    char commande = ' ';

    // Tableau C classique à 2 dimensions [nombre_d_ennemis][x, y]
    const int nb_ennemis = 5;
    int ennemis[nb_ennemis][2] = {
        {10, 4},
        {12, 7},
        {5, 3},
        {2, 8},
        {7, 8}
    };

    bool jeu_en_cours = true;

    while (commande != 'e' && jeu_en_cours) { // 'e' pour quitter
        afficher_map(map, hero, ennemis, nb_ennemis);
        std::cout << "Deplacement (Z = haut, Q = gauche, S = bas, D = droite, E = quitter) : ";
        commande = _getch();

        deplacer_hero(hero, commande, map);
        deplacer_ennemis(ennemis, nb_ennemis, map);

        if (est_touche_par_ennemi(hero, ennemis, nb_ennemis)) {
            afficher_map(map, hero, ennemis, nb_ennemis);
            std::cout << "\n==============================\n";
            std::cout << " GAME OVER ! Tu es mort.";
            std::cout << "\n==============================\n";
            jeu_en_cours = false;
        }

        if (victoire(hero)) {
            if (niveau == 1) {
                afficher_map(map, hero, ennemis, nb_ennemis);
                std::cout << "\n==============================\n";
                std::cout << " NIVEAU 1 TERMINE ! Ta cru que c'etait fini?";
                std::cout << "\n==============================\n";

                niveau = 2;       
                hero.y = 0;
                hero.x = 0;

                system("pause");  
            }
            else if (niveau == 2) {
                afficher_map(map, hero, ennemis, nb_ennemis);
                std::cout << "\n==============================\n";
                std::cout << " VICTOIRE ! T'es chaud!";
                std::cout << "\n==============================\n";
                jeu_en_cours = false; 
            }
        }

    }
    return 0;
}