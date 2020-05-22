
module nios_core (
	clk_clk,
	data_master_waitrequest,
	data_master_readdata,
	data_master_readdatavalid,
	data_master_burstcount,
	data_master_writedata,
	data_master_address,
	data_master_write,
	data_master_read,
	data_master_byteenable,
	data_master_debugaccess,
	mailbox_in_address,
	mailbox_in_writedata,
	mailbox_in_write,
	mailbox_in_read,
	mailbox_in_readdata,
	mailbox_in_waitrequest,
	mailbox_out_address,
	mailbox_out_read,
	mailbox_out_writedata,
	mailbox_out_write,
	mailbox_out_readdata,
	reset_reset_n);	

	input		clk_clk;
	input		data_master_waitrequest;
	input	[31:0]	data_master_readdata;
	input		data_master_readdatavalid;
	output	[0:0]	data_master_burstcount;
	output	[31:0]	data_master_writedata;
	output	[19:0]	data_master_address;
	output		data_master_write;
	output		data_master_read;
	output	[3:0]	data_master_byteenable;
	output		data_master_debugaccess;
	input	[1:0]	mailbox_in_address;
	input	[31:0]	mailbox_in_writedata;
	input		mailbox_in_write;
	input		mailbox_in_read;
	output	[31:0]	mailbox_in_readdata;
	output		mailbox_in_waitrequest;
	input	[1:0]	mailbox_out_address;
	input		mailbox_out_read;
	input	[31:0]	mailbox_out_writedata;
	input		mailbox_out_write;
	output	[31:0]	mailbox_out_readdata;
	input		reset_reset_n;
endmodule
