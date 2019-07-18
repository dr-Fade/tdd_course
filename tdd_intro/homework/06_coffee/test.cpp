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
#include <memory>
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
    virtual ~Ingredient() {}
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

class Water : public Ingredient
{
public:
    Water(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getWater(m_val);
    }
};

class Sugar : public Ingredient
{
public:
    Sugar(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getSugar(m_val);
    }
};

class Coffee : public Ingredient
{
public:
    Coffee(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getCoffee(m_val);
    }
};

class Milk : public Ingredient
{
public:
    Milk(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getMilk(m_val);
    }
};

class MilkFoam : public Ingredient
{
public:
    MilkFoam(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getMilkFoam(m_val);
    }
};

class Chocolate : public Ingredient
{
public:
    Chocolate(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getChocolate(m_val);
    }
};

class Cream : public Ingredient
{
public:
    Cream(ISourceOfIngredients* src, int gram)
        : Ingredient(src, gram) {}
    void get()
    {
        m_src->getCream(m_val);
    }
};

enum CupSize {
    SMALL, BIG
};

class IRecipe
{
public:
    IRecipe(CupSize size, ISourceOfIngredients* src) {}
    ~IRecipe() {
        for(auto i : m_ingredients)
        {
            delete i;
        }
        m_ingredients.clear();
    }

    virtual void make() = 0;
protected:
    std::vector<Ingredient*> m_ingredients;
};

class Americano : public IRecipe
{
public:
    Americano(CupSize size, ISourceOfIngredients* src)
        : IRecipe(size, src)
    {
        if(size == CupSize::SMALL)
        {
            m_ingredients = {
                new Water(src, 50),
                new Coffee(src, 50),
                new Temperature(src, 60)
            };
        }
        if(size == CupSize::BIG)
        {
            m_ingredients = {
                new Water(src, 70),
                new Coffee(src, 70),
                new Temperature(src, 60)
            };
        }
    }
    void make()
    {
        for(auto i : m_ingredients) {
            i->get();
        }
    }
};

class Cappuccino : public IRecipe
{
public:
    Cappuccino(CupSize size, ISourceOfIngredients* src)
        : IRecipe(size, src)
    {
        if(size == CupSize::SMALL)
        {
            m_ingredients = {
                new Milk(src, 33),
                new Coffee(src, 33),
                new MilkFoam(src, 33),
                new Temperature(src, 80)
            };
        }
        if(size == CupSize::BIG)
        {
            m_ingredients = {
                new Milk(src, 46),
                new Coffee(src, 46),
                new MilkFoam(src, 46),
                new Temperature(src, 80)
            };
        }
    }
    void make()
    {
        for(auto i : m_ingredients) {
            i->get();
        }
    }
};

class Latte : public IRecipe
{
public:
    Latte(CupSize size, ISourceOfIngredients* src)
        : IRecipe(size, src)
    {
        if(size == CupSize::SMALL)
        {
            m_ingredients = {
                new Milk(src, 25),
                new Coffee(src, 50),
                new MilkFoam(src, 25),
                new Temperature(src, 90)
            };
        }
    }
    void make()
    {
        for(auto i : m_ingredients) {
            i->get();
        }
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

// 2. Water(0) -> Water.get() -> getWater(0)

TEST(CoffeeMachine, WaterGet0CallsGetWater0)
{
    SourceOfIngredientsMock src;
    Water water(&src, 0);
    EXPECT_CALL(src, getWater(0)).Times(AtLeast(1));
    water.get();
}

// 3. Sugar(0) -> Sugar.get() -> getSugar(0)

TEST(CoffeeMachine, SugarGet0CallsGetSugar0)
{
    SourceOfIngredientsMock src;
    Sugar sugar(&src, 0);
    EXPECT_CALL(src, getSugar(0)).Times(AtLeast(1));
    sugar.get();
}

// 4. Coffee(0) -> Coffee.get() -> getCoffee(0)

TEST(CoffeeMachine, CoffeeGet0CallsGetCoffee0)
{
    SourceOfIngredientsMock src;
    Coffee coffee(&src, 0);
    EXPECT_CALL(src, getCoffee(0)).Times(AtLeast(1));
    coffee.get();
}

// 5. Milk(0) -> Milk.get() -> getMilk(0)

TEST(CoffeeMachine, MilkGet0CallsGetMilk0)
{
    SourceOfIngredientsMock src;
    Milk milk(&src, 0);
    EXPECT_CALL(src, getMilk(0)).Times(AtLeast(1));
    milk.get();
}

// 6. MilkFoam(0) -> MilkFoam.get() -> getMilkFoam(0)

TEST(CoffeeMachine, MilkFoamGet0CallsGetMilkFoam0)
{
    SourceOfIngredientsMock src;
    MilkFoam milkFoam(&src, 0);
    EXPECT_CALL(src, getMilkFoam(0)).Times(AtLeast(1));
    milkFoam.get();
}

// 7. Chocolate(0) -> Chocolate.get() -> getChocolate(0)

TEST(CoffeeMachine, ChocolateGet0CallsGetChocolate0)
{
    SourceOfIngredientsMock src;
    Chocolate chocolate(&src, 0);
    EXPECT_CALL(src, getChocolate(0)).Times(AtLeast(1));
    chocolate.get();
}

// 8. Cream(0) -> Cream.get() -> ISourceOfIngredients.getCream(0)

TEST(CoffeeMachine, CreamGet0CallsGetCream0)
{
    SourceOfIngredientsMock src;
    Cream cream(&src, 0);
    EXPECT_CALL(src, getCream(0)).Times(AtLeast(1));
    cream.get();
}

// 9. Americano.make(CupSize.SMALL) -> getWater(50), getCoffee(50), getTemperature(60)

TEST(CoffeeMachine, AmericanoMakeSmallCup)
{
    SourceOfIngredientsMock src;
    Americano americano(CupSize::SMALL, &src);
    EXPECT_CALL(src, getWater(50)).Times(AtLeast(1));
    EXPECT_CALL(src, getCoffee(50)).Times(AtLeast(1));
    EXPECT_CALL(src, getTemperature(60)).Times(AtLeast(1));
    americano.make();
}

// 10 Americano.make(CupSize.BIG) -> getWater(70), getCoffee(70), getTemperature(60)

TEST(CoffeeMachine, AmericanoMakeBigCup)
{
    SourceOfIngredientsMock src;
    Americano americano(CupSize::BIG, &src);
    EXPECT_CALL(src, getWater(70)).Times(AtLeast(1));
    EXPECT_CALL(src, getCoffee(70)).Times(AtLeast(1));
    EXPECT_CALL(src, getTemperature(60)).Times(AtLeast(1));
    americano.make();
}

// 11. Cappuccino.make(CupSize.SMALL) -> getMilk(33), getCoffee(33), getMilkFoam(33), getTemperature(80)

TEST(CoffeeMachine, CappuccinoSmallCup)
{
    SourceOfIngredientsMock src;
    Cappuccino cappuccino(CupSize::SMALL, &src);
    EXPECT_CALL(src, getMilk(33)).Times(AtLeast(1));
    EXPECT_CALL(src, getCoffee(33)).Times(AtLeast(1));
    EXPECT_CALL(src, getMilkFoam(33)).Times(AtLeast(1));
    EXPECT_CALL(src, getTemperature(80)).Times(AtLeast(1));
    cappuccino.make();
}

// 12. Cappuccino.make(CupSize.BIG) -> getMilk(46), getCoffee(46), getMilkFoam(46), getTemperature(80)

TEST(CoffeeMachine, CappuccinoBigCup)
{
    SourceOfIngredientsMock src;
    Cappuccino cappuccino(CupSize::BIG, &src);
    EXPECT_CALL(src, getMilk(46)).Times(AtLeast(1));
    EXPECT_CALL(src, getCoffee(46)).Times(AtLeast(1));
    EXPECT_CALL(src, getMilkFoam(46)).Times(AtLeast(1));
    EXPECT_CALL(src, getTemperature(80)).Times(AtLeast(1));
    cappuccino.make();
}
// 13. Latte.make(CupSize.SMALL) -> getMilk(25), getCoffee(50), getMilkFoam(25), getTemperature(90)

TEST(CoffeeMachine, LatteSmallCup)
{
    SourceOfIngredientsMock src;
    Latte latte(CupSize::SMALL, &src);
    EXPECT_CALL(src, getMilk(25)).Times(AtLeast(1));
    EXPECT_CALL(src, getCoffee(50)).Times(AtLeast(1));
    EXPECT_CALL(src, getMilkFoam(25)).Times(AtLeast(1));
    EXPECT_CALL(src, getTemperature(90)).Times(AtLeast(1));
    latte.make();
}

// 14. Latte.make(CupSize.BIG) -> getMilk(35), getCoffee(70), getMilkFoam(35), getTemperature(90)
// 15. Marochino.make(CupSize.SMALL) -> getChocolate(25), getCoffee(25), getMilkFoam(25)
// 16. Marochino.make(CupSize.BIG) -> getChocolate(35), getCoffee(35), getMilkFoam(35)

// 17. makeCoffee(CoffeeType.AMERICANO, CupSize.LITTLE) -> Americano.make(CupSize.SMALL)
// 18. makeCoffee(CoffeeType.AMERICANO, CupSize.BIG) -> Americano.make(CupSize.BIG)
// 19. makeCoffee(CoffeeType.CAPPUCCINO, CupSize.LITTLE) -> Cappuccino.make(CupSize.SMALL))
// 20. makeCoffee(CoffeeType.CAPPUCCINO, CupSize.BIG) -> Cappuccino.make(CupSize.BIG)
// 21. makeCoffee(CoffeeType.LATTE, CupSize.LITTLE) -> Latte.make(CupSize.SMALL)
// 22. makeCoffee(CoffeeType.LATTE, CupSize.BIG) -> Latte.make(CupSize.BIG)
// 23. makeCoffee(CoffeeType.MAROCHINO, CupSize.LITTLE) -> Marochino.make(CupSize.SMALL)
// 24. makeCoffee(CoffeeType.MAROCHINO, CupSize.BIG) -> Marochino.make(CupSize.BIG)
