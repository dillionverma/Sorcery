#ifndef DECORATOR_H
#define DECORATOR_H
#include "Minion.h"
#include "Player.h"

class Decorator: public Minion {
    protected:
        std::shared_ptr<Minion> minion;
    public:
        Decorator(std::shared_ptr<Minion> minion);
        card_template_t display() override;
        void changeAttack(const int amount) override;
        void changeDefence(const int amount) override;
        void changeAC(const int amount) override; 
        void changeAction(const int amount) override;
        void setAction(const int amount) override;
        int getAction() const override;
        int getAttack() const override;
        int getDefence() const override;
        int getAC() const override;
        std::string getAA() const override;
        std::string getTA() const override;
        int getAADamage() const override;
        std::string getSummonName() const override;
        int getSummonAmount() const override;
        std::string getName() const override;
        std::string getInfo() const override;
        int getCost() const;
        std::shared_ptr<Minion> getMinion();
        void attackMinion(Minion &m) override;
        void attackPlayer(Player &p) override;
        void notify(Board &b, Player &p, int target = -1) override;
        void addEnchantment(std::shared_ptr<Enchantment> e) override;
        void removeEnchantment() override;
        std::vector<std::shared_ptr<Enchantment>> getEnchantments() override;
};

#endif
