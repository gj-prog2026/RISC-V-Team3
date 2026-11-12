/*
 *  Unit tests for rtl/regfile.sv
 *
 *  Ports under test
 *    clk                 clock (write happens on the rising edge)
 *    AD1, AD2            read addresses   -> RD1, RD2 (asynchronous)
 *    AD3, WD3, WE3       write address, write data, write enable (synchronous)
 *    a0                  always shows register x10
 */

#include "gtest/gtest.h"
#include "Vregfile.h"
#include "verilated.h"

class RegfileTest : public ::testing::Test
{
protected:
    Vregfile *top;

    //this runs before every test, resets all the registers
    void SetUp() override
    {
        top = new Vregfile;
        top->clk = 0;
        top->AD1 = 0;
        top->AD2 = 0;
        top->AD3 = 0;
        top->WE3 = 0;
        top->WD3 = 0;
        top->eval();
    }

    void TearDown() override
    {
        top->final();
        delete top;
    }

    //one clock cycle
    void tick()
    {
        top->clk = 1;
        top->eval();
        top->clk = 0;
        top->eval();
    }

    // writes into registers (on clock edge)
    void write(uint8_t reg, uint32_t value)
    {
        top->AD3 = reg;
        top->WD3 = value;
        top->WE3 = 1;
        tick();
        top->WE3 = 0;
        top->eval();
    }

    //reads registers (no need for clock)
    uint32_t read1(uint8_t reg)
    {
        top->AD1 = reg;
        top->eval();
        return top->RD1;
    }
};

//write and read
//store number, read it, is it the same number
TEST_F(RegfileTest, WriteThenRead)
{
    write(5, 0x12345678);
    EXPECT_EQ(read1(5), 0x12345678u);
}

//write should not be till after clock edge
//before the clock edge the register is unchanged, and after it the new value is there
TEST_F(RegfileTest, WriteOnlyOnClockEdge)
{
    top->AD3 = 6;
    top->WD3 = 42;
    top->WE3 = 1;
    top->AD1 = 6;
    top->eval();                 // inputs set, but no clock edge yet
    EXPECT_EQ(top->RD1, 0u) << "Register changed before the clock edge";

    tick();                      // now the rising edge
    EXPECT_EQ(top->RD1, 42u) << "Register did not update on the clock edge";
}

//no writes when not enabled
//WE3=0
// a clock edge changes nothing.
TEST_F(RegfileTest, NoWriteWhenDisabled)
{
    write(7, 100);

    top->AD3 = 7;
    top->WD3 = 999;
    top->WE3 = 0;
    tick();

    EXPECT_EQ(read1(7), 100u);
}

//writing to register 0 is ignored
//in RISC-V x0 is always 0.
TEST_F(RegfileTest, X0AlwaysZero)
{
    write(0, 0xDEADBEEF);
    EXPECT_EQ(read1(0), 0u);
}

//read ports work at the same time
// RD1 shows one register and RD2 shows another.
TEST_F(RegfileTest, TwoReadPortsAtOnce)
{
    write(1, 11);
    write(2, 22);

    top->AD1 = 1;
    top->AD2 = 2;
    top->eval();

    EXPECT_EQ(top->RD1, 11u);
    EXPECT_EQ(top->RD2, 22u);
}

//The a0 output shows register 10 only
//writing to register 11 leaves a0 at 0
//writing 254 to register 10 makes a0 = 254.
TEST_F(RegfileTest, A0OutputIsRegister10)
{
    write(11, 5);                // a1 should not appear on a0
    EXPECT_EQ(top->a0, 0u);

    write(10, 254);
    EXPECT_EQ(top->a0, 254u);
}

//largest 32-bit value (0xFFFFFFFF) is stored without any bits being lost
TEST_F(RegfileTest, Full32BitValue)
{
    write(31, 0xFFFFFFFF);
    EXPECT_EQ(read1(31), 0xFFFFFFFFu);
}

//reading and writing the same register in one cycle
//new value must appear only once after the edge.
TEST_F(RegfileTest, ReadAndWriteSameRegister)
{
    write(11, 5);

    top->AD1 = 11;
    top->AD3 = 11;
    top->WD3 = 6;
    top->WE3 = 1;
    top->eval();
    EXPECT_EQ(top->RD1, 5u) << "Old value should still be visible before the edge";

    tick();
    top->WE3 = 0;
    top->eval();
    EXPECT_EQ(top->RD1, 6u);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
