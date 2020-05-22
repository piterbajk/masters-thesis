	nios_core u0 (
		.clk_clk                   (<connected-to-clk_clk>),                   //         clk.clk
		.data_master_waitrequest   (<connected-to-data_master_waitrequest>),   // data_master.waitrequest
		.data_master_readdata      (<connected-to-data_master_readdata>),      //            .readdata
		.data_master_readdatavalid (<connected-to-data_master_readdatavalid>), //            .readdatavalid
		.data_master_burstcount    (<connected-to-data_master_burstcount>),    //            .burstcount
		.data_master_writedata     (<connected-to-data_master_writedata>),     //            .writedata
		.data_master_address       (<connected-to-data_master_address>),       //            .address
		.data_master_write         (<connected-to-data_master_write>),         //            .write
		.data_master_read          (<connected-to-data_master_read>),          //            .read
		.data_master_byteenable    (<connected-to-data_master_byteenable>),    //            .byteenable
		.data_master_debugaccess   (<connected-to-data_master_debugaccess>),   //            .debugaccess
		.mailbox_in_address        (<connected-to-mailbox_in_address>),        //  mailbox_in.address
		.mailbox_in_writedata      (<connected-to-mailbox_in_writedata>),      //            .writedata
		.mailbox_in_write          (<connected-to-mailbox_in_write>),          //            .write
		.mailbox_in_read           (<connected-to-mailbox_in_read>),           //            .read
		.mailbox_in_readdata       (<connected-to-mailbox_in_readdata>),       //            .readdata
		.mailbox_in_waitrequest    (<connected-to-mailbox_in_waitrequest>),    //            .waitrequest
		.mailbox_out_address       (<connected-to-mailbox_out_address>),       // mailbox_out.address
		.mailbox_out_read          (<connected-to-mailbox_out_read>),          //            .read
		.mailbox_out_writedata     (<connected-to-mailbox_out_writedata>),     //            .writedata
		.mailbox_out_write         (<connected-to-mailbox_out_write>),         //            .write
		.mailbox_out_readdata      (<connected-to-mailbox_out_readdata>),      //            .readdata
		.reset_reset_n             (<connected-to-reset_reset_n>)              //       reset.reset_n
	);

