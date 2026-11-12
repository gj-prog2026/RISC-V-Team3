#include "gtest/gtest.h"
#include "Vinstr_mem.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cmath>

Vinstr_mem *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TestInstr_mem : public ::testing::Test
{
public:
    uint32_t read(uint32_t addr){
        top->addr = addr;
        top->eval();
        tfp->dump(ticks++);
        return top->instr;
    }
};

TEST_F(TestInstr_mem, ReadAddr4)
{
    EXPECT_EQ(read(0x4), 0x00000513);
}


TEST_F(TestInstr_mem, ReadAddr8)
{
    EXPECT_EQ(read(0x8), 0x00000593);
}

int main(int argc, char **argv)
{
    top = new Vinstr_mem;
    tfp = new VerilatedVcdC;

    Verilated::traceEverOn(true);
    top->trace(tfp, 99);
    tfp->open("waveform.vcd");

    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();

    top->final();
    tfp->close();

    delete top;
    delete tfp;

    return res;
}