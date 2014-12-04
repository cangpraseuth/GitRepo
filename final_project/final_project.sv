// Rachel Roley
// rroley@hmc.edu
// 9/14/14
// Module: lab1_rr


// toggle a pin with the clock for SCL 
// wait until data from SDO is 8 bits long 
// save that shit
// keep waiting
module final_project(input logic clk,
	input logic MISOx, // fron slave
	output logic MOSIx, // to slave
	input logic reset,
	input logic [7:0] d, // data to send 
	output logic [7:0] q); // data received

//bits sent to the accelerometer
//bit 0: RW bit. When 0, the data DI(7:0) is written to the device. When 1, the data DO(7:0)
//from the device is read. In the latter case, the chip will drive SDO at the start of bit 8.
//bit 1: MS bit. When 0, the address remains unchanged in multiple read/write commands.
//When 1, the address will be auto-incremented in multiple read/write commands.
//bit 2-7: address AD(5:0). This is the address field of the indexed register.
//bit 8-15: data DI(7:0) (write mode). This is the data that will be written to the device (MSb
//first).
//bit 8-15: data DO(7:0) (read mode). This is the data that will be read from the device (MSb
//first).

logic[2:0] counter; 
logic [2:0] cnt; 
logic qdelayed;
logic cs; 

// max frequency of 10 MHZ
// generate clock for accel slave
// given clock of 40 MHz/2^2= 10 MHz


always_ff@(posedge clk)
	counter <= counter+1;

assign sck = counter[1];


// 3-bit counter tracks when full byte is transmitted and new d should be sent
always_ff @(negedge sck, posedge reset) 
	if (reset) cnt = 0;
	else cnt = cnt + 3'b1;

// loadable shift register
// loads d at the start, shifts sdo into bottom position on subsequent step 
always_ff @(posedge sck)
	q <= (cnt == 0) ? d : {q[6:0], MISOx};

// align sdi to falling edge of sck // load d at the start
always_ff @(negedge sck)
	qdelayed = q[7];

assign MOSIx = (cnt == 0) ? d[7] : qdelayed;


endmodule


