#include "gtest/gtest.h"
#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

Valu *top;

class ALUTest : public ::testing::Test
{
public:
    
    uint32_t add_or_sub(uint32_t ALUop1, uint32_t ALUop2, bool ALUctrl){   
        top->ALUop1 = ALUop1;
        top->ALUop2 = ALUop2;
        top->ALUctrl = ALUctrl;
        top->eval();
        return top->ALUout;
    }

    bool checkEQ(uint32_t ALUop1, uint32_t ALUop2, bool ALUctrl){
        top->ALUop1 = ALUop1;
        top->ALUop2 = ALUop2;
        top->ALUctrl = ALUctrl;
        top->eval();
        return top->EQ;
    }
};

TEST_F(ALUTest, InstructionForAddi)
{
    EXPECT_EQ(add_or_sub(0x00500513, 0x02337001, 0), 0x02837514);
    EXPECT_EQ(add_or_sub(0x01, 0x02, 0), 0x3);
}

TEST_F(ALUTest, InstructionForBne)
{
    EXPECT_EQ(add_or_sub(0x00500513, 0x02337001, 1), 0xFE1C9512);
    EXPECT_EQ(add_or_sub(0x01, 0x01, 1), 0x0);
}

TEST_F(ALUTest, TestForEqual)
{
    EXPECT_EQ(checkEQ(0x01, 0x01, 1), 1);
}

TEST_F(ALUTest, TestForUnequal)
{
    EXPECT_EQ(checkEQ(0x00500513, 0x02337001, 1), 0);
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    top = new Valu;

    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();

    top->final();

    delete top;
    return res;
}