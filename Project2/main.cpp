#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <fstream>


using namespace sf;

using namespace std;

class Atom {
public:
    float x;
    float y;
    float mass = 0.001;
    float vx = 0;
    float vy = 0;
    int Max_speed = 2;
    Atom(float cord_x, float cord_y) {
        x = cord_x;
        y = cord_y;
        }
    Atom() {}
};


const int windowWidth = 1000;
const int windowHeight = 700;
const int noa = 2000;
RenderWindow window{VideoMode(1000, 1000), "Atoms" };

Atom list_atoms[noa];
RectangleShape list_atom_shapes[noa];


int main() {
    ofstream out;
    out.open("hh1.txt");
    window.setFramerateLimit(60);
    for (int i{0}; i < noa; i++) {
        
        Atom atm = Atom(rand()%1000-2, rand()%1000-2);
        list_atom_shapes[i] = RectangleShape({3,3});        
        float x = atm.x;
        float y = atm.y;
        list_atom_shapes[i].setPosition(x, y);
        list_atom_shapes[i].setFillColor(Color::Color(0, 0, 0, 255));
        list_atoms[i] = atm;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (int i{ 0 }; i < noa; i++) {
            float x = list_atoms[i].x;
            float y = list_atoms[i].y;
            float mass = list_atoms[i].mass;
            float vx = list_atoms[i].vx;
            float vy = list_atoms[i].vy;
            float dx = 0;
            float dy = 0;
            for (int h{ 0 }; h < noa; h++) {
                if (i!=h){
                    float dist_x = (list_atoms[h].x-x);
                    float dist_y = (list_atoms[h].y-y);
                    float dist = sqrt(dist_x * dist_x + dist_y * dist_y);
                    if (dist_x and dist_y and dist>0) {
                        float F = mass / dist/2;
                        dy += F*dist_y;
                        dx += F*dist_x;
                    }
                    

                }

            }
            
            vy += dy;
            vx += dx;
            int mx_spd = list_atoms[i].Max_speed;
            if (x > 1000 - mx_spd) {
                vx = -vx-1;
                x = 1000 - mx_spd;
            }
            else if (x < mx_spd) {
                vx = -vx+1;
                x = mx_spd*2;
            }
            if (y > 1000- mx_spd) {
                vy = -vy-1;
                y = 1000 - mx_spd;
            }
            else if (y < mx_spd) {
                vy = -vy+1;
                y = mx_spd;
            }
            
            list_atoms[i].x = x+vx;
            list_atoms[i].y = y+vy;
            list_atoms[i].vx = vx/1.01;
            list_atoms[i].vy = vy/1.01;

            list_atom_shapes[i].setPosition(x, y);
            
        }
        window.clear(sf::Color::Color(150, 150, 150, 255));

        for (int i{ 0 }; i < noa; i++) {
            window.draw(list_atom_shapes[i]);
        }
        window.display();
    }
    out.close();
};
