module TopLevel (
		input  wire  clk_clk,       //   clk.clk
		input  wire  reset_reset_n  // reset.reset_n
	);

    multicore_system_core_0 core_0 (
        .clk_clk(CLOCK_50),
        .reset_reset_n(KEY)
    );
endmodule