#include "gtest/gtest.h"
#include "VPc_counter.h"
#include "verilated.h"

VPc_counter *top;

class TestPC : public ::testing::Test {
protected:
    void tick() {                 // one rising clock edge
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();
    }

    void SetUp() override {       // runs before every test
        top->PCsrc = 0;
        top->ImmOp = 0;
        top->rst = 1;
        tick();
        top->rst = 0;
    }
};

TEST_F(TestPC, ResetToZero) {
    EXPECT_EQ(top->PC_out, 0x0);
}

TEST_F(TestPC, IncrementsBy4) {
    for (uint32_t expected = 4; expected <= 20; expected += 4) {
        tick();
        EXPECT_EQ(top->PC_out, expected);
    }
}

TEST_F(TestPC, BranchForward) {
    top->PCsrc = 1;
    top->ImmOp = 0x20;
    tick();
    EXPECT_EQ(top->PC_out, 0x20);
}

TEST_F(TestPC, BranchBackward) {
    tick(); tick(); tick();       // PC = 0xC
    top->PCsrc = 1;
    top->ImmOp = (uint32_t)-8;    // 0xFFFFFFF8
    tick();
    EXPECT_EQ(top->PC_out, 0x4);
}

TEST_F(TestPC, ResetMidRun) {
    tick(); tick();               // PC = 0x8
    top->rst = 1;
    tick();
    EXPECT_EQ(top->PC_out, 0x0);
}

int main(int argc, char **argv) {
    top = new VPc_counter;
    testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    top->final();
    delete top;
    return res;
}