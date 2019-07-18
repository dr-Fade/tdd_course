/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

/*
 * Architecture:
 * Coffee machine will have a single public method - void makeCoffee(CoffeeType type, CupSize size).
 * In this method a Recipe class will be called. It will iterate through a list of ingredients that call methods of the ISourceOfIngredients class.
 * Ingredients are going to belong to a single hierarchy.
 */

/*
 * Test plan:
 * 1. Temperature(0) -> Temperature.get() -> getTemperature(0)
 * 2. Water(0) -> Water.get() -> getWater(0)
 * 3. Sugar(0) -> Sugar.get() -> getSugar(0)
 * 4. Coffee(0) -> Coffee.get() -> getCoffee(0)
 * 5. Milk(0) -> Milk.get() -> getMilk(0)
 * 6. MilkFoam(0) -> MilkFoam.get() -> getMilkFoam(0)
 * 7. Chocolate(0) -> Chocolate.get() -> getChocolate(0)
 * 8. Cream(0) -> Cream.get() -> ISourceOfIngredients.getCream(0)
 *
 * 9. Americano.make(CupSize.SMALL) -> getWater(50), getCoffee(50), getTemperature(60)
 * 10 Americano.make(CupSize.BIG) -> getWater(70), getCoffee(70), getTemperature(60)
 * 11. Cappuccino.make(CupSize.SMALL) -> getMilk(33), getCoffee(33), getMilkFoam(33), getTemperature(80)
 * 12. Cappuccino.make(CupSize.BIG) -> getMilk(46), getCoffee(46), getMilkFoam(46), getTemperature(80)
 * 13. Latte.make(CupSize.SMALL) -> getMilk(25), getCoffee(50), getMilkFoam(25), getTemperature(90)
 * 14. Latte.make(CupSize.BIG) -> getMilk(35), getCoffee(70), getMilkFoam(35), getTemperature(90)
 * 15. Marochino.make(CupSize.SMALL) -> getChocolate(25), getCoffee(25), getMilkFoam(25)
 * 16. Marochino.make(CupSize.BIG) -> getChocolate(35), getCoffee(35), getMilkFoam(35)
 *
 * 17. makeCoffee(CoffeeType.AMERICANO, CupSize.LITTLE) -> Americano.make(CupSize.SMALL)
 * 18. makeCoffee(CoffeeType.AMERICANO, CupSize.BIG) -> Americano.make(CupSize.BIG)
 * 19. makeCoffee(CoffeeType.CAPPUCCINO, CupSize.LITTLE) -> Cappuccino.make(CupSize.SMALL))
 * 20. makeCoffee(CoffeeType.CAPPUCCINO, CupSize.BIG) -> Cappuccino.make(CupSize.BIG)
 * 21. makeCoffee(CoffeeType.LATTE, CupSize.LITTLE) -> Latte.make(CupSize.SMALL)
 * 22. makeCoffee(CoffeeType.LATTE, CupSize.BIG) -> Latte.make(CupSize.BIG)
 * 23. makeCoffee(CoffeeType.MAROCHINO, CupSize.LITTLE) -> Marochino.make(CupSize.SMALL)
 * 24. makeCoffee(CoffeeType.MAROCHINO, CupSize.BIG) -> Marochino.make(CupSize.BIG)
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::AtLeast;

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void getTemperature(int degrees) = 0;
    virtual void getWater(int gram) = 0;
    virtual void getSugar(int gram) = 0;
    virtual void getCoffee(int gram) = 0;
    virtual void getMilk(int gram) = 0;
    virtual void getMilkFoam(int gram) = 0;
    virtual void getChocolate(int gram) = 0;
    virtual void getCream(int gram) = 0;
};

class SourceOfIngredientsMock : public ISourceOfIngredients
{
public:
    MOCK_METHOD1(getTemperature, void(int degrees));
    MOCK_METHOD1(getWater, void(int gram));
    MOCK_METHOD1(getSugar, void(int gram));
    MOCK_METHOD1(getCoffee, void(int gram));
    MOCK_METHOD1(getMilk, void(int gram));
    MOCK_METHOD1(getMilkFoam, void(int gram));
    MOCK_METHOD1(getChocolate, void(int gram));
    MOCK_METHOD1(getCream, void(int gram));
};

class Ingredient
{
public:
    Ingredient(ISourceOfIngredients* src, int val)
        : m_src(src)
        , m_val(val)
    {}
    virtual void get() = 0;
protected:
    ISourceOfIngredients* m_src;
    int m_val;
};

class Temperature : public Ingredient
{
public:
    Temperature(ISourceOfIngredients* src, int degrees)
        : Ingredient(src, degrees) {}
    void get()
    {
        m_src->getTemperature(m_val);
    }
};

// 1. Temperature.get(0) -> getTemperature(0)

TEST(CoffeeMachine, TemperatureGet0CallsGetTemperature0)
{
    SourceOfIngredientsMock src;
    Temperature temp(&src, 0);
    EXPECT_CALL(src, getTemperature(0)).Times(AtLeast(1));
    temp.get();
}

