#include "gtest/gtest.h"
#include "Vcontrol_unit.h"
#include "verilated.h"

Vcontrol_unit *top;

class TestControlUnit : public ::testing::Test {
public:
    void set(uint8_t op, bool eq) {
        top->opcode = op;
        top->EQ = eq;
        top->eval();
    }
};

TEST_F(TestControlUnit, Addi) {
    set(0b0010011, 0);
    EXPECT_EQ(top->RegWrite, 1);
    EXPECT_EQ(top->ALUsrc,   1);
    EXPECT_EQ(top->ImmSrc,   0);
    EXPECT_EQ(top->ALUctrl,  0);
    EXPECT_EQ(top->PCsrc,    0);
}

TEST_F(TestControlUnit, BneTaken) {
    set(0b1100011, 0);          // not equal -> branch
    EXPECT_EQ(top->RegWrite, 0);
    EXPECT_EQ(top->ALUsrc,   0);
    EXPECT_EQ(top->ImmSrc,   1);
    EXPECT_EQ(top->PCsrc,    1);
}

TEST_F(TestControlUnit, BneNotTaken) {
    set(0b1100011, 1);          // equal -> no branch
    EXPECT_EQ(top->PCsrc, 0);
}

TEST_F(TestControlUnit, UnknownOpcode) {
    set(0b0000000, 0);
    EXPECT_EQ(top->RegWrite, 0);
    EXPECT_EQ(top->PCsrc,    0);
}

int main(int argc, char **argv) {
    top = new Vcontrol_unit;
    testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    top->final();
    delete top;
    return res;
}