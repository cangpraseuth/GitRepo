// Rachel Roley
// rroley@hmc.edu
// 9/14/14
// Module: lab1_rr
// The top level module contained in this file will take in a number using DISP switches
// pass that number to the 7 segment display module 
// and light the LED on the board as specified in Lab 1 instructions, at 
// http://www3.hmc.edu/~jspjut/class/f2014/e155/lab/lab01.pdf

module final_project(input logic       clk, // the clock
					input logic[3:0]  s, // the input logic for the switches
					output logic[7:0] led); // the led on the board
					
//assign the logic as outlined in the lounge
always_comb
	begin 
	led[0] = s[0];
	led[1] = s[1];
	led[2] = s[2];
	end	
	

endmodule


