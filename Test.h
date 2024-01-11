#ifndef TEST_H
#define TEST_H

void testSkipSpace(void)
{
    char *in0 = "asdf ppokasd";
    char *in1 = "      asdf ppokasd";
    char *in2 = "      \nasdf ppokasd";
    char *ins[3] = {in0, in1, in2};
    for (size_t i = 0; i < 3; i++) {
        printf("%zu -\n", i);
        printf("\tinc space: \"%s\"\n", ins[i]);
        printf("\trem space: \"%s\"\n\n", skipSpace(ins[i]));
    }
}

#endif /* end of include guard: TEST_H */
