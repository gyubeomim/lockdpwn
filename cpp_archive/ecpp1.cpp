#include <cstring>
#include <iostream>
#include <tr1/functional>

using namespace std;

class GameCharacter;

struct HealthCalculator
{
    int operator()(const GameCharacter&) const
    {}
};

class GameLevel
{
  public:
    float health(const GameCharacter&) const;
};

int defaultHealthCalc(const GameCharacter& gc);
short calcHealth(const GameCharacter&);

class GameCharacter
{
  public:
    typedef tr1::function<int (const GameCharacter&)> HealthCalcFunc;

    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
            :HealthFunc(hcf)
    {}

  private:
    HealthCalcFunc HealthFunc;
};

class EyeCandyChracter : public GameCharacter
{
  public:
    explicit EyeCandyChracter(HealthCalcFunc hcf = defaultHealthCalc)
            : GameCharacter(hcf)
    {}
};

class BadGuy : public GameCharacter
{
  public:
    explicit BadGuy(HealthCalcFunc hcf = defaultHealthCalc)
            : GameCharacter(hcf)
    {}
};

int main()
{
    int loseHealthQuickly(const GameCharacter&);
    int loseHealthSlowly(const GameCharacter&);

    BadGuy bg1(loseHealthQuickly);
    BadGuy bg2(loseHealthSlowly);
    BadGuy bg3(calcHealth);

    EyeCandyChracter ecc1(HealthCalculator());
    GameLevel currentLevel;
    BadGuy bg4(tr1::bind(&GameLevel::health, currentLevel,1));

    return 0;
}
