#include <string>
#include <iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{

    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        std::string name;
        int health, attack;
        bool alive, defensive;
        inline static int aliveNumber = 0;

    protected:
        Base(const std::string& name_, const int health_, const int attack_)
            : name(name_), health(health_), attack(attack_), alive(true), defensive(false) {
            ++aliveNumber;
        }

        static void handle_death(Base* who, const char* roleName){
            if (who->alive && who->health <= 0){
                who->alive = false;
                --aliveNumber;
                std::cout << roleName << ' ' << who->name << " is killed\n";
            }
        }

    public:
        virtual ~Base(){
            if (alive) {
                alive = false;
                --aliveNumber;
            }
        }
        static int getAliveNumber(){ return aliveNumber; }
        bool isAlive(){ return alive; }
        bool isDefensive(){ return defensive; }
        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;
    };

    class Fighter:public Base{
    public:
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    inline const char* role_name_of(Base* p){
        if (dynamic_cast<Fighter*>(p)) return "Fighter";
        if (dynamic_cast<Protector*>(p)) return "Protector";
        return "Caster";
    }

    inline void Fighter::launch_attack(Base* target){
        if (!alive) return;
        int mul = dynamic_cast<Caster*>(target) ? 2 : 1;
        int atk_val = attack * mul;
        if (target->defensive){
            int dmg = atk_val - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            this->health -= target->attack;
            handle_death(target, role_name_of(target));
            handle_death(this, "Fighter");
        } else {
            target->health -= atk_val;
            handle_death(target, role_name_of(target));
        }
    }

    inline void Protector::launch_attack(Base* target){
        if (!alive) return;
        int mul = dynamic_cast<Fighter*>(target) ? 2 : 1;
        int atk_val = attack * mul;
        if (target->defensive){
            int dmg = atk_val - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            this->health -= target->attack;
            handle_death(target, role_name_of(target));
            handle_death(this, "Protector");
        } else {
            target->health -= atk_val;
            handle_death(target, role_name_of(target));
        }
    }

    inline void Caster::launch_attack(Base* target){
        if (!alive) return;
        int mul = dynamic_cast<Protector*>(target) ? 2 : 1;
        int atk_val = attack * mul;
        if (target->defensive){
            int dmg = atk_val - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            handle_death(target, role_name_of(target));
        } else {
            target->health -= atk_val;
            handle_death(target, role_name_of(target));
        }
    }
}
#endif // ROLE_HPP
