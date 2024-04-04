#include <iostream>
#include <string>
#include <vector>

// Car parts

class Wheel
{
  private:
    int size;

  public:
    Wheel(int s) { size = s; }

    int getSize() const { return size; }
};

class Engine
{
  private:
    int ps;

  public:
    Engine(int p) : ps(p){};

    int getPs() const { return ps; }
};

class Body
{
  private:
    std::string shape;

  public:
    Body(std::string s) { shape = s; }
    std::string getShape() { return shape; }
};

// Final product -- a car
class Car
{
  private:
    std::vector<Wheel> wheels{};
    Engine engine;
    Body body;

  public:
    Car(const std::vector<Wheel>& wheels, const Engine& engine, const Body& body)
        : wheels(wheels), engine(engine), body(body){};
    void setWheel(Wheel ws, int index) { wheels[index] = ws; }
    void setEngine(Engine e) { engine = e; }
    void setBody(Body b) { body = b; }

    void display()
    {
        std::cout << "Body:" << body.getShape() << std::endl;
        std::cout << "Engine (PS):" << engine.getPs() << std::endl;
        std::cout << "Tire size:" << wheels[0].getSize() << "'" << std::endl;
    }
};

// Director is responsible for the whole process
template <typename Builder>
class Director
{
  public:
    Car buildCar() const
    {
        Builder builder{};
        std::vector<Wheel> wheels{
            builder.buildWheel(), builder.buildWheel(), builder.buildWheel(), builder.buildWheel()};
        return {wheels, builder.buildEngine(), builder.buildBody()};
   }
};

// Concrete Builder for SUV cars
class SUVBuilder
{
  public:
    ~SUVBuilder() = default;

    Wheel buildWheel() const { return {22}; }
    Engine buildEngine() const { return {400}; }
    Body buildBody() const { return {"SUV"}; }
};

// Concrete builder for city cars
class CityCarBuilder
{
  public:
    ~CityCarBuilder() = default;

    Wheel buildWheel() const { return {16}; }
    Engine buildEngine() const { return {85}; }
    Body buildBody() const { return {"Hatchback"}; }
};

int main()
{
    // Build an SUV
    std::cout << "SUV" << std::endl;
    Director<SUVBuilder> director{};
    auto car1 = director.buildCar();
    car1.display();

    std::cout << std::endl;

    // Build a City Car
    std::cout << "City Car" << std::endl;
    Director<CityCarBuilder> cc_director{};
    auto car2 = cc_director.buildCar();
    car2.display();

    return 0;
}