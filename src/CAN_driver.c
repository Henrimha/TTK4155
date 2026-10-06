#include "CAN_driver.h"

#define RESET ((1<<7)|(1<<6))
#define READ ((1<<1)|(1<<0))
#define READ_RX_BUFFER (())
#define WRITE (1<<1)
#define READ_STATUS ((1<<7)|(1<<5))
#define RX_STATUS (0b10110000)
#define BIT_MODIFY (0b00000101)
#define CANCTRL (0b00001111)
void CAN_init(){
    //Need to delay 128 clock cycles

    CAN_transmit(RESET);
    //For now set after configuration state, loopback mode: when connecting others use normal mode
    char data[] = {BIT_MODIFY, CANCTRL, 0b11100011, 0b01000000};
    SPI_array_send(data, 4, CAN_CONTROLLER);
    // REQOP = REQuest OPeration mode bits
    // loopback mode (REQOP<2:0> = 010)
    // CANCTRL &= ~(1 << REQOP2);
    // CANCTRL |= (1 << REQOP1);
    // CANCTRL &= ~(1 << REQOP0);
    // // normal mode (REQOP<2:0> = 000)
    // CANCTRL &= ~(1 << REQOP2);
    // CANCTRL &= ~(1 << REQOP1);
    // CANCTRL &= ~(1 << REQOP0);
    
    // ABAT = ABort All pending Transmissions
    // OSM = One Shot Mode
    // CLKEN = CLKout pin ENable bit
    // CLKPRE = CLKout pin PREscaler bits
    // CANCTRL &= ~(1 << CLKPRE1);
    // CANCTRL &= ~(1 << CLKPRE0);



    //Reset command
    //wait 128 clock cycles
/*
    wait 128 TOSC for oscillator
    will be in config mode
    provide reset
*/




}






// modes: 
//     config
//         init only possible in config mode
//         autoselected after startup, reset or can be entered from any other mode (CANTRL.REQOP = 0b100)
//         when entered    
//             all error counters cleared
//         only mode when these registers can be modified:
//             CNF1, CNF2, CNF3
//             TXRTSCTRL
//             Filter registers
//             Mask registers 
//     normal
//         actively monitors all bus messages
//             generates acknowlegde bits, error frames, etc
//         only mode where mcp2515 wil transmitt messages over the CAN bus
//     sleep
//         minimize current consumption
//         can still read SPI and access all registers
//         to enter:
//             mode request bits in CANCTRL register (REQOP<2:0>)
//             CANSTAT.OPMODE indicate operation mode
//                 should be read after sending sleep command
//                 is not in sleep until these indicate sleep
//         when in sleep:
//             wake up interrupt is active (if enabled)
//             stops internal oscillator
//             can have a lowpass filter on RXCAN inpu line
//                 CNF3.WAKFIL bit controls this
//         wake up:
//             bus activity
//             MCU sets (SPI) CANINTF.WAKIE bit to 'generate' a wakeup attempt 
//                 CANINTE.WAKIE bit must also be set for interrupt to occur
//             functions:
//                 will monitor the RXCAN pin
//                     if CANINTE.WAKIE bit is set 
//                         wakeup and generate interrupt
//                 wil ignore wakeup message and any messages during wakeup
//             wakes up in listen only
//             oscillator startup timer = 128 TOSC
//     listen only
//         by configuring RXBnCTRL.RXM<1:0> bits
//         monitor bus 
//         detecting baud rate in hotplugging situations
//             at least two other nodes ar commnicating with each other
//             found empirically
//         no message will be transmitted
//             including error flags and aknowlgde signals
//         enter:
//             setting the mode request bits in the CANCTRL register
//     loopback
//         allows internal transmission of messages from transmit buffers to recieve buffers without transmitting messages on the CAN-bus
//         useed in system development and testing
//         ACK bit is ignored
//         allow incoming messages from itself as if they were from another node
//         silent node
//         TXCAN pin in recessive state
//         can filter particular messages to be loaded
//         activated by:
//             setting the mode request bits in the CANCTRL register 


// SPI interface
//     sent to the device via commands and data via SI pin
//     data clocked on rising edge og SCK
//     data driven out by mcp2515 (SO pin) on falling edge of SCK
//     CS pin must be low while any operation is performed
//         first byte after lowering is epected to be instruction/command
//         must be raised and lowered again to invoke another command
//     RESET instruction  
//         re initialize internal registers
//         command does the same via SPI, as the RESET-pin
//         single byte instruction
//             pull CS low
//             send instruction byte
//             raise CS high
//         recommended:
//             Reset command be sent (or RESET pin lowered) as part on power on init sequence
//     READ instruction
//         what happens
//             lower CS
//             send READ instruction to mcp2515
//             send 8 bit adress (A7-A0)
//             data stored at det selected adress shited to SO pin
//             operation terminated by setting CS high
//         internal adress pointer is automatically incrementet to next adress
//             after each byte is shifted out
//             possibe to read the next consecutive register adress by continuing to privde clock pulses
//                 can read ny number og sequentially stored data
//     READ RX BUFFER instruction
//         quickly adress a recieve buffer for reading
//         reduces the SPI overhead by one byte (adress byte)
//         four possible values that determine adress pointer location
//         once command byte is sent
//             controller clocks out the data at the adress location (same as READ instruction)
//         further reduces SPI by clearing the recieve flag (CANINTF.RXnIF) when CS is raised high at the end 
//     WRITE instruction
//         what happens
//             lower CS pin
//             WRITE instruction is sent to mcp2515
//             adress is sent
//             at least one byte of data is sent
//                 can write sequential register by continuing to clock in databytes (if CS is held low)
//         written to the register on rising edge og SCK for the D0 bit
//         if CS i raised high before eight bits is finished sending 
//             write will be aborted for that and previous bytes
//     LOAD TX BUFFER instruction
//         eliminates the adress required by normal WRITE 
//         eight bit instruction
//         sets the adress pointer to one of six adresses to quickly write to a transmit buffer that points to the ID or data adress of any of the three transmit buffers
//     REQUEST TO SEND (RTS) instruction   
//         initiate messages transmission for one or more transmit buffers
//         what happens
//             lower CS pin
//             RTS command byte is sent
//                 last 3 bits indicate which transmit buffers are enabled to send
//             sets TxBnCTRL.TXREQ bit for respective buffers
//                 any or all of the last three bits can b eset in a single command
//                 if RTS is sent with nnn = 000, command will be ignored
//     READ STATUS instruction 
//         allows single instruction access to some of the often used status bits
//         what happens    
//             lower CS pin
//             Read status command byte is sent to mcp2515
//             returns eight bits of data that contain status
//                 if more clocks are sent on SCK, the mcp2515 will conitnue to send the status bits when CS is lowered
//         each status bit can also be read by the standard read command
//     RX status instruction
//         quickly determine which FCLKOUT = System Clock/1filter mathced the message and type (standard. exended, remote)
//         after command is sent, returns 8 bits of status data
//         if more clocks on SCK and CS low, continue to send the same status bits
//     BIT MODIFY 
//         setting or clearing idividual bits in spesific status and cotnrol registers
//         not available for all registers
//         what happens
//             lower the CS
//             send BIT MODIFY
//             send adress of register
//             send mask byte 
//                 determines which bits in the register will be allowed to change
//                 1 allow, 0 not allow
//                 00110101
//             send data byte 
//                 XX10X0X1
//                 if the register was 01010001
//                 the bits in the maski will determine which bits in the register will be changed to match the data byte
//                 => new register = 01[1][0]0[0]0[1] with those inside [] having changed
        



// man kan si fra atmega til canctrl    
//     hva er CANINTF
//     canctrl skal svaret med CANINTF