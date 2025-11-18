#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <vector>
#include <cstdlib>

std::mt19937 rng(std::random_device{}());

int randomNumber(int min, int max) {
    /*
    
    Usage: randomNumber(min, max){} 
    */
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

char generateRandomLetter() {
    /*
    
    Generates a random character in the alphabet
    
    */
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    int random_index = randomNumber(0, 25); 
    
    return alphabet[random_index];
}

class Nerf {

    /*
    
    Model - The model of the gun
    Range - How far the gun can shoot (MAX VALUE)
    Capacity - How much ammo the gun has
    Ammo - The amount of ammo in gun automatically equals capacity
    ID - Name of the nerf gun
    Usage: Nerf(model, id, range, capacity) {}
    */

private:

    std::string model;
    int range;
    int capacity;
    int ammo;
    std::string ID;

public:
    Nerf(std::string m, std::string id, int r, int c): model(m), ID(id), range(r), capacity(c) {

        ammo = capacity;

        if (!validation()) {
            std::cout << "There may be a few problems with this object" << std::endl;
        }


    };

    bool validation() {
        try {
            if (capacity < 144) {
                throw std::string("Error, capacity is less than 144");
            }
        } catch(const std::string& e) {
            std::cout << e << std::endl;
            return false;
        }

        return true;
    }

    void reload(int amount) {

        int simulated_ammo;

        if (capacity == ammo) {
            std::cout << "Gun is already loaded" << std::endl;
            return;
        }

        try {

            
            simulated_ammo = ammo;
            simulated_ammo += amount;

            if (simulated_ammo > capacity) {
                throw std::overflow_error("Amount is greater than capacity!");
            }

        } catch (const std::overflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        std::cout << "Reloading gun" << std::endl;
        ammo += amount;
    }
    void fire() {
        int distance;

        if (ammo <= 0) {
            std::cout << "Gun is empty" << std::endl;
            return;
        }

        ammo -= 1;

        std::cout << "Firing gun" << "(" << ammo << "/" << capacity << ")" << std::endl;
        distance = randomNumber(1, range);        
        std::cout << "The dart flew " << distance << " miles away" << std::endl;
    }

    std::string getModel() const {
        return model;
    }

    int getCapacity() const {
        return capacity;
    }

    int getAmmo() const {
        return ammo;
    }
    std::string getID() const {
        return ID;
    }


    friend std::ostream& operator<<(std::ostream& out, const Nerf& nerfgun);


};

std::ostream& operator<<(std::ostream& out, const Nerf& nerfgun) {
    /*
   
    Outputs details about the gun
    
    */

    out << "Model: " << nerfgun.model << "\n" 
        << "Ammo: " << nerfgun.ammo << "/" << nerfgun.capacity << "\n"
        << "Max range: " << nerfgun.range << "\n"
        << "ID: " << nerfgun.ID;
    return out;
}

std::vector<Nerf> guns;
const Nerf& mostAmmo() {
    /*
   
    Checks which gun has the most ammo in it
    
    */
    
    if (guns.empty()) {
        throw std::runtime_error("This index is empty");
    }

    int max = guns[0].getAmmo();
    int index = 0;

    for (int i = 1; i < guns.size(); i++) {
        if (guns[i].getAmmo() > max) {
            max = guns[i].getAmmo();
            index = i;
        }
    }

    return guns[index];
}
std::string generateID() {
    /*
    
    Generates an ID for a gun by generating random letters and assigning them to a string 
    
    */
    std::string ID;
    for (int i = 0; i < 5; i++) {
        ID += generateRandomLetter();
    }
    return ID;
}

bool sameID(const std::string& id) {

    /*
   
    Checks if an ID is in the guns vector
    Usage: sameID(id)
    
    */

    for (const Nerf& gun : guns) {
        if (id == gun.getID()) {
            return true;
        }
    }
    return false;


}

void Automatic_Make(int maxGuns) {
    /*
   
    Automatically makes guns using the functions I created
    (Used for testing)

    usage: Automatic_Make(amount) 
    
    */

    std::string random_number_model;
    std::string id;
    int random_number_cap;
    int random_number_range;

    std::string possibleModels[5] = {"Elite", "Echo", "Mythic", "Commander", "Agility"};
    
    for (int i = 0; i < maxGuns; i++) {

        do {
            id = generateID();

        } while(sameID(id));

        random_number_model = possibleModels[randomNumber(0, 4)];
        random_number_cap = randomNumber(145, 200);
        random_number_range = randomNumber(100, 200);
        Nerf gun(random_number_model, id, random_number_range, random_number_cap);
        guns.push_back(gun);
    }

    const Nerf& GunWithMostAmmo = mostAmmo();

    for (Nerf& gun : guns) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << gun << std::endl;
        std::cout << std::string(50, '-') << std::endl;
    }

    std::cout << "The gun with the most ammo is currently: " << std::endl << GunWithMostAmmo << std::endl;



}

void Automatic_Fire(int amount) {
    /*
    
    Calls fire on all the guns and will fire a gun a gun X amount of times.
    Usage: Automatic_Fire(amount) 
    
    */
    if (amount < 0) {
        throw std::runtime_error("Amount is less than 0");
    }
    for (Nerf& gun : guns) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Firing: " << gun.getModel() << " (" << gun.getID() << ")" << std::endl;
        for (int i = 0; i < amount; i++) {
            gun.fire();
        }
        std::cout << std::string(50, '-') << std::endl;
    }
}


void Automatic_Reload(int amount) {
    /*
    
    Same as fire but for reload
    
    */
    if (amount < 0) {
        throw std::runtime_error("Amount is less than 0");
    }

    for (Nerf& gun : guns) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Reload: " << gun.getModel() << " (" << gun.getID() << ")" << std::endl;
        gun.reload(amount);
        std::cout << std::string(50, '-') << std::endl;
    }
}

int main(int argc, char *argv[]) {
    /*
    
    Used for testing
    
    */

    if (!(argc == 4)) {
        std::cout << "Usage: [guns amount: INT] [fire guns: INT] [reload guns: INT]" << std::endl;
        return 1;
    }

    int amount_make = std::stoi(argv[1]);
    int amount_fire = std::stoi(argv[2]);
    int amount_reload = std::stoi(argv[3]);

    Automatic_Make(amount_make);

    Automatic_Fire(amount_fire);
    Automatic_Reload(amount_reload);
    return 0;
}