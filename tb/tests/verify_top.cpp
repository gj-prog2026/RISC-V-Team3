#include <memory>

#include "Vtop.h"
#include "verilated.h"
#include "gtest/gtest.h"

#define CYCLES 10000

unsigned int ticks = 0;

class CpuTestbench : public ::testing::Test
{
public:
    void SetUp() override
    {
        top = std::make_unique<Vtop>();
        initializeInputs();
    }

    void TearDown() override
    {
        top->final();
    }

    void initializeInputs()
    {
        top->clk = 1;
        top->rst = 0;
    }

    void runSimulation(int cycles = 1)
    {
        for (int i = 0; i < cycles; i++)
        {
            for (int clk = 0; clk < 2; clk++)
            {
                top->eval();
                top->clk = !top->clk;
            }
            ticks++;
        }
    }

protected:
    std::unique_ptr<Vtop> top;
};

//a0 must reach 254
TEST_F(CpuTestbench, BaseProgramTest)
{
    bool success = false;

    for (int i = 0; i < CYCLES; i++)
    {
        runSimulation(1);
        if (top->a0 == 254)
        {
            SUCCEED();
            success = true;
            break;
        }
    }
    if (!success)
    {
        FAIL() << "Counter did not reach 254";
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    return res;
}
