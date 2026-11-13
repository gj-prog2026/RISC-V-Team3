
#include "gtest/gtest.h"
#include "Vreddatapath.h"
#include "verilated.h"

#define ZERO 0
#define T1   6
#define A0   10
#define A1   11

class DatapathTest : public ::testing::Test
{
protected:
    Vreddatapath *top;

    //sets up each test, everything resets
    void SetUp() override
    {
        top = new Vreddatapath;
        top->clk = 0;
        top->rs1 = 0;
        top->rs2 = 0;
        top->rd = 0;
        top->RegWrite = 0;
        top->ALUsrc = 0;
        top->ALUctrl = 0;
        top->ImmOp = 0;
        top->eval();
    }

    //runs after test, clears the results
    void TearDown() override
    {
        top->final();
        delete top;
    }

    //clock cycle
    void tick()
    {
        top->eval();
        top->clk = 1;
        top->eval();
        top->clk = 0;
        top->eval();
    }

    //addi rd, rs1, imm  instruction
    void addi(uint8_t rd, uint8_t rs1, int32_t imm)
    {
        top->rs1 = rs1;
        top->rd = rd;
        top->ImmOp = imm;
        top->ALUsrc = 1;
        top->ALUctrl = 0;
        top->RegWrite = 1;
        tick();
        top->RegWrite = 0;
        top->eval();
    }

    //bne rs1, rs2 instruction
    bool compare(uint8_t rs1, uint8_t rs2)
    {
        top->rs1 = rs1;
        top->rs2 = rs2;
        top->ALUsrc = 0;
        top->ALUctrl = 1;
        top->RegWrite = 0;
        top->eval();
        return top->EQ;
    }
};

//addi a0, zero, 5
//a0 = 5
TEST_F(DatapathTest, AddiFromZero)
{
    addi(A0, ZERO, 5);
    EXPECT_EQ(top->a0, 5);
}

//addi a0, zero, -1
//a0 = 0xFFFFFFFF (negative immediates work)
TEST_F(DatapathTest, AddiNegativeImmediate)
{
    addi(A0, ZERO, -1);
    EXPECT_EQ(top->a0, 0xFFFFFFFFu);
}

//addi a1, zero, 7 ; addi a0, a1, 3
//a0 = 10
//checks that the value in a register saves to next isntruction
TEST_F(DatapathTest, AddiUsesRegisterValue)
{
    addi(A1, ZERO, 7);
    addi(A0, A1, 3);
    EXPECT_EQ(top->a0, 10);
}

//addi a0, a0, 1  three times
//a0 = 3
//same register read and written each cycle
TEST_F(DatapathTest, IncrementSameRegister)
{
    addi(A0, A0, 1);
    addi(A0, A0, 1);
    addi(A0, A0, 1);
    EXPECT_EQ(top->a0, 3);
}

//when RegWrite = 0 no changes are made
TEST_F(DatapathTest, NoWriteWhenRegWriteLow)
{
    addi(A0, ZERO, 7);

    //addi but with RegWrite = 0
    top->rs1 = ZERO;
    top->rd = A0;
    top->ImmOp = 99;
    top->ALUsrc = 1;
    top->ALUctrl = 0;
    top->RegWrite = 0;
    tick();

    EXPECT_EQ(top->a0, 7);
}

//bne compare, equal registers
//expect EQ = 1
TEST_F(DatapathTest, CompareEqual)
{
    addi(A1, ZERO, 255);
    addi(T1, ZERO, 255);
    EXPECT_EQ(compare(A1, T1), 1);
}

//bne compare, different registers
//expect EQ = 0 (branch taken)
TEST_F(DatapathTest, CompareNotEqual)
{
    addi(A1, ZERO, 254);
    addi(T1, ZERO, 255);
    EXPECT_EQ(compare(A1, T1), 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
