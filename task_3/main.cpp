#include <iostream>
#include "Character.h"
#include "Knight.h"
#include "Mage.h"
#include "Archer.h"
#include "Necromancer.h"

Character* create_hero() {
    std::string name;
    int type;
    
    std::cout << "\n1. Knight  \n2. Mage  \n3. Archer  \n4. Necromancer" << std::endl;
    std::cout << "Choice: ";
    std::cin >> type;
    std::cin.ignore();
    
    std::cout << "Name: ";
    getline(std::cin, name);
    
    if (type == 1) 
        return new Knight(name, 120, 3, 5);
    if (type == 2) 
        return new Mage(name, 85, 5, 50, 10, 10);
    if (type == 3) 
        return new Archer(name, 100, 4, 8, 2);
    if (type == 4) 
        return new Necromancer(name, 70, 6, 2, 10, 10, 5);
    
    return new Knight(name, 120, 3, 5);
}

void show_status(Character* hero) {
    std::cout << hero->get_name() << " | HP: " << hero->get_health();
    
    Mage* m = dynamic_cast<Mage*>(hero);
    if (m) 
        std::cout << " | Mana: " << m->get_mana();
    
    Necromancer* n = dynamic_cast<Necromancer*>(hero);
    if (n && n->has_skeleton()) {
        std::cout << " | Skeleton HP: " << n->get_skeleton_health();
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Battle begins";
    
    Character* p1 = create_hero();
    Character* p2 = create_hero();
    
    Character* cur = p1;
    Character* opp = p2;
    
    int round = 1;
    
    while (p1->get_health() > 0 && p2->get_health() > 0) {
        std::cout << "\nRound " << round << std::endl;
        std::cout << "Turn: " << cur->get_name() << std::endl;
        show_status(cur);
        show_status(opp);
        
        std::cout << "\n1. Attack";
        
        Mage* m = dynamic_cast<Mage*>(cur);
        if (m) 
            std::cout << "  2. Restore mana";
        
        Necromancer* n = dynamic_cast<Necromancer*>(cur);
        if (n && !n->has_skeleton()) 
            std::cout << "  3. Summon skeleton";
        if (n && n->has_skeleton()) 
            std::cout << "  4. Skeleton attack";
        
        std::cout << "\nChoice: ";
        int choice;
        std::cin >> choice;
        
        if (choice == 2 && m) {
            m->restore_mana();
        }
        else if (choice == 3 && n && !n->has_skeleton()) {
            n->summon_skeleton();
        }
        else if (choice == 4 && n && n->has_skeleton()) {
            n->skeleton_attack(opp);
        }
        else {
            cur->attack(opp);
        }
        
        if (opp->get_health() <= 0) {
            std::cout << cur->get_name() << " won!\n";
            break;
        }
        
        std::swap(cur, opp);
        round++;
    }
    
    delete p1;
    delete p2;
    
    std::cout << "\nBatlle is over!" << std::endl;
    return 0;
}