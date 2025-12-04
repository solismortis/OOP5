#include <format>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


class BaseNoVirtual {
public:
    BaseNoVirtual() {}

    void method1() {
        std::cout << "Inside BaseNoVirtual method1\n";
        method2();
    }

    void method2() {
        std::cout << "Inside BaseNoVirtual method2\n";
    }

    ~BaseNoVirtual() {
        std::cout << "Inside BaseNoVirtual destructor\n";
    }

};

class Derived1 : public BaseNoVirtual {
public:
    Derived1() : BaseNoVirtual() {}

    void method2() {
        std::cout << "Inside Derived1 method2\n";
    }

    ~Derived1() {
        std::cout << "Inside Derived1 destructor\n";
    }
};

class BaseVirtual {
public:
    // Won't work
    //virtual BaseNoVirtual() {}

    BaseVirtual() {}

    void method1() {
        std::cout << "Inside BaseVirtual method1\n";
        method2();
    }

    virtual void method2() {
        std::cout << "Inside BaseVirtual method2\n";
    }

    virtual ~BaseVirtual() {
        std::cout << "Inside BaseVirtual destructor\n";
    }
};

class Derived2 : public BaseVirtual {
public:
    Derived2() : BaseVirtual() {}

    void method2() {
        std::cout << "Inside Derived2 method2\n";
    }

    ~Derived2() {
        std::cout << "Inside Derived2 destructor\n";
    }
};

class Planet {
public:
    std::string m_classname;

    Planet() : m_classname{ "Planet"  } {}

    virtual void mine() {
        std::cout << "Initiating mining a planet\n";
    }

    virtual std::string classname() {
        return m_classname;
    }

    virtual bool is_a(std::string classname) {
        return classname == m_classname;
    }
};

class GasGiant : public Planet {
public:
    GasGiant() : Planet() {
        m_classname = "GasGiant";
    }

    void mine() override {
        std::cout << "Can't mine a gas giant\n";
    }

    std::string classname() override {
        return m_classname;
    }

    bool is_a(std::string classname) override {
        return classname == m_classname;
    }
};

class DeadAsteroid : public Planet {
public:
    DeadAsteroid() : Planet() {
        m_classname = "DeadAsteroid";
    }

    void mine() override {
        std::cout << "Already mined out\n";
    }

    std::string classname() override {
        return "DeadAsteroid";
    }

    bool is_a(std::string classname) override {
        return classname == m_classname;
    }

    std::string mined_out_date() {
        return "2201.11.09";
    }
};

class Animal {
public:
    Animal() {
        std::cout << "Inside default Animal constructor\n";
    }

    Animal(Animal* obj) {
        std::cout << "Inside pointer Animal constructor\n";
    }

    Animal(Animal& obj) {
        std::cout << "Inside reference (copy) Animal constructor\n";
    }

    virtual void method1() {
        std::cout << "Inside Animal method1\n";
    }

    ~Animal() {
        std::cout << "Inside Animal destructor\n";
    }
};

class Cat : public Animal {
public:
    Cat() {
        std::cout << "Inside default Cat constructor\n";
    }

    Cat(Cat* obj) {
        std::cout << "Inside pointer Cat constructor\n";
    }

    Cat(Cat& obj) {
        std::cout << "Inside reference (copy) Cat constructor\n";
    }

    void method1() override {
        std::cout << "Inside Cat method1\n";
    }

    ~Cat() {
        std::cout << "Inside Cat destructor\n";
    }
};

void func1(Animal animal) {
    std::cout << "Inside func1\n";
}

void func2(Animal* animal) {
    std::cout << "Inside func2\n";
}

void func3(Animal& animal) {
    std::cout << "Inside func3\n";
}

Animal function1() {
    Animal animal;
    return animal;
};

Animal* function2() {
    Animal* animal_ptr;
    return animal_ptr;
};

Animal& function3() {
    Animal animal;
    return animal;
};

Animal function4() {
    Animal* animal_ptr{ new Animal };
    return *animal_ptr;
};

Animal* function5() {
    Animal* animal_ptr{ new Animal };
    return animal_ptr;
};

Animal& function6() {
    Animal* animal_ptr{ new Animal };
    return *animal_ptr;
};

int main()
{
    /* Виртуальные конструкторы в C++ не разрешены :
    E0377: 'virtual' is not allowed */

    /* Виртуальные деструкторы нужны, когда мы в переменную или
    контейнер для указателей на предков кладем указатели на потомков.
    Тогда при удалении через такие указатели, если деструкторы у предков
    не виртуальные, то
    вызовутся только они */

    // Вызовется только деструктор базового, так как не virtual
    std::cout << ">> Testing no virtual destructor\n";
    BaseNoVirtual* base_ptr1 = new Derived1;
    delete base_ptr1;
    std::cout << "\n";

    // Вызовутся оба деструктора
    std::cout << ">> Testing with virtual destructor\n";
    BaseVirtual* base_ptr2 = new Derived2;
    delete base_ptr2;
    std::cout << "\n";

    /* В методе1 базового класса вызывается метод2, который определен в
    этом же классе как невиртуальный, у класса-потомка метод2
    переопределен. Вызовется метод2 базового класса */
    std::cout << ">> Testing calling methods no virtual\n";
    Derived1 derived1;
    derived1.method1();
    std::cout << "\n";

    /* В методе1 базового класса вызывается метод2, который определен в
    этом же классе как виртуальный, у класса-потомка метод2 переопределен.
    Вызовется метод2 потомка */
    std::cout << ">> Testing calling methods with virtual\n";
    Derived2 derived2;
    derived2.method1();
    std::cout << "\n";

    /* В базовом классе объявить метод невиртуальный, а в классе-потомке
    объявить метод с таким же именем*/
    // Здесь будет вызываться метод предка
    std::cout << ">> Testing methods other 1\n";
    BaseNoVirtual* base_ptr3 = new Derived1;
    base_ptr3->method2();
    // Здесь будет вызываться метод потомка
    Derived1* der_ptr3 = new Derived1;
    der_ptr3->method2();
    std::cout << "\n";

    /* В базовом классе объявить метод виртуальный, а в классе-потомке
    объявить метод с таким же именем*/
    // Здесь будет вызываться метод потомка
    std::cout << ">> Testing methods other 2\n";
    BaseVirtual* base_ptr4 = new Derived2;
    base_ptr4->method2();
    // Здесь тоже будет вызываться вызываться метод потомка
    Derived2* der_ptr4 = new Derived2;
    der_ptr4->method2();
    std::cout << "\n";

    /* Зачем нужны виртуальные методы? Зачем может понадобиться
    хранить объект не в указателе на свой собственный класс, а указателе
    на класс-предок? Чтобы единообразно работать и с базовым,
    и с потомками */
    std::cout << ">> I don't even know how to call this section\n";
    Planet* planets[3]{ new Planet, new GasGiant, new DeadAsteroid };
    for (Planet* planet : planets) {
        planet->mine();
    }
    std::cout << "\n";

    /* Зачем нужна проверка на принадлежность некоторому классу? */
    /* Для проверки на принадлежность некоторому классу необходимо
    реализовать: */
	/* Базовый виртуальный метод string classname(), перекрыть его в
    потомках, проверить работу и показать, какие проблемы возникают при
    его использовании */
    std::cout << ">> Testing classname()\n";
    Planet planet;
    std::cout << planet.classname() << "\n";
    GasGiant gas_giant;
    std::cout << gas_giant.classname() << "\n";
    // Проблема в том, что каждому новому потомку надо прописывать
    // classname() вручную
    std::cout << "\n";

    /* Базовый виртуальный метод bool isA(string classname), перекрыть его
    в потомках и показать отличие от метода classname */
    std::cout << ">> Testing is_a()\n";
    DeadAsteroid dead_asteroid;
    std::cout << std::boolalpha;
    std::cout << dead_asteroid.is_a("Planet") << "\n";
    std::cout << dead_asteroid.is_a("GasGiant") << "\n";
    std::cout << dead_asteroid.is_a("DeadAsteroid") << "\n";
    // Проблема этого метода в том, что в него необходимо отправлять
    // все имена релевантных классов
    std::cout << "\n";

    /* Зачем нужна проверка на принадлежность некоторому классу? */
    /* У нас может быть контейнер для указателей на базовый класс,
    который хранит указатели на разные классы-потомки. Тогда не у всех
    потомков может быть реализован какой-либо метод */
    std::cout << ">> Why do we need to check class?\n";
    Planet* planets1[2]{ new GasGiant, new DeadAsteroid };
    for (Planet* planet : planets1) {
        if (planet->is_a("DeadAsteroid"))
            std::cout << static_cast<DeadAsteroid*>(planet)->mined_out_date() << "\n";
    }
    std::cout << "\n";


    /* Продемонстрировать опасное приведение типов и предварительную
    проверку типа с помощью реализованного метода is_a */
    std::cout << ">> Testing static casting\n";
    DeadAsteroid dead_asteroid1;
    Planet* planet_ptr = &dead_asteroid1;
    if (planet_ptr->is_a("DeadAsteroid")) {
        DeadAsteroid* dc_res = static_cast<DeadAsteroid*>(planet_ptr);
        std::cout << "Casting successful\n";
    }
    else {
        std::cout << "Casting failed\n";
    }
    std::cout << "\n";

    /* Зачем и в каких случаях требуется производить безопасное
    приведение типов? */
    // Когда мы не знаем, какой потомок лежит в указателе на переменную
    // предка.
    /* В каком случае может понадобиться вызвать метод
    потомка для объекта, который лежит в переменной предка? */
    // Когда у нас есть контейнер с разными потомками, но только у некоторых
    // наших потомков есть нужный нам метод
    /* Продемонстрировать использование стандартных средств языка
    (dynamic_cast в c++ или аналог на используемом языке) */
    std::cout << ">> Testing dynamic casting\n";
    Planet* planets3[2]{ new GasGiant, new DeadAsteroid };
    for (Planet* planet : planets3) {
        DeadAsteroid* dc_res = dynamic_cast<DeadAsteroid*>(planet);
        if (dc_res) {
            std::cout << dc_res->mined_out_date() << "\n";
        }
    }
    std::cout << "\n";

    /* Передача объектов как параметров в функции */
    std::cout << ">> Testing using objects as parameters\n";
    Animal animal;
    std::cout << "----------\n";
    std::cout << "func1(Animal obj):\n";
    // Создаст копию, удалит ее по завершении работы функции
    func1(animal);
    std::cout << "----------\n";
    std::cout << "func2(Animal* obj):\n";
    // Примет либо адрес объекта, либо указатель
    func2(&animal);
    std::cout << "----------\n";
    std::cout << "func3(Animal& obj):\n";
    func3(animal);
    std::cout << "++++++++++\n";
    Cat cat;
    std::cout << "----------\n";
    std::cout << "func1(Animal obj):\n";
    // Создаст копию, удалит ее по завершении работы функции.
    // При этом обрежет у копии потомка все, чего нет у предка
    func1(cat);
    std::cout << "----------\n";
    std::cout << "func2(Animal* obj):\n";
    // Примет либо адрес объекта, либо указатель
    func2(&cat);
    std::cout << "----------\n";
    std::cout << "func3(Animal& obj):\n";
    func3(cat);
    std::cout << "\n";

    /* Можно ли внутри функции привести переданный Base к Desc с помощью
    приведения типов? */
    // Невозможно. Ни static_cast, ни dynamic_cast не вернут потомка

    /* Необходимо уметь объяснять достоинства и недостатки каждого из вариантов функции */
    // Отправка по значению создает копию, что невсегда нужно.
    // Указатели могут баговать, поэтому рекомендуется тогда уж по ссылке.
    // Но при этом в указатель можно отправить nullptr, тогда как ссылка
    // обязана на что-либо указывать

    std::cout << "\n\n\n\n>> Cleaning up the mess\n";
}