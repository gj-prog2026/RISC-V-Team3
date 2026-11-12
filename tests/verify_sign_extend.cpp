#include "gtest/gtest.h"
#include "Vsign_extend.h"
#include "verilated.h"

Vsign_extend *top;

class TestSignExtend : public ::testing::Test {
public:
    void set(uint32_t instr, bool immsrc) {
        top->instr = instr;
        top->Immsrc = immsrc;
        top->eval();
    }

    uint32_t immop_val(void){
        return top->immop;
    }
};

TEST_F(TestSignExtend, Addi) {
    set(0x0ff00313, 0);
    EXPECT_EQ(immop_val(), 0x000000ff);
}

TEST_F(TestSignExtend, Bne) {
    set(0x00158593, 1);
    EXPECT_EQ(immop_val(), 0x0000080a);
}


int main(int argc, char **argv) {
    top = new Vsign_extend;
    testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    top->final();
    delete top;
    return res;
}