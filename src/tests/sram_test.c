#include <tests/sram_test.h>


void SRAM_test(void)
{
    volatile char *ext_ram = (char *)0x1400; // Start address for the SRAM 1800 

    uint16_t ext_ram_size = 0xC00; //1200, 800 før
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    while (1){
        ext_ram[101]='b';
        volatile char u=ext_ram[101];
        printf("%c",u);
        if (u!='b'){
            printf("error");
        }
    }
    printf("Starting SRAM test...\n");

    // rand() stores some internal state, so calling this function in a loop
    // will yield different seeds each time (unless srand() is called before
    // this function).
    uint16_t seed = rand();

    // Write phase:
    // Immediately check that the correct value was stored.
    srand(seed);

    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retrieved_value = ext_ram[i];

        if (retrieved_value != some_value)
        {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retrieved_value, some_value);
            write_errors++;
        }

    }

    // Retrieval phase:
    // Check that no values were changed during or after the write phase.
    srand(seed);

    // Reset the PRNG to the state it had before the write phase.
    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = rand();
        uint8_t retrieved_value = ext_ram[i];

        if (retrieved_value != some_value)
        {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retrieved_value, some_value);
            retrieval_errors++;
        }
    }

    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

//njvnsiguie DRIVEr1


// git add driver1.c & driver1.h

// git add drive2 osv. 
// git comitt 1 2 -mm" dri1 2"


