`timescale 1ns / 1ps

module tb_uart_frame;

    // =============================================================================
    // TESTBENCH FOR UART FRAME PARSER WITH tx_done_i OPTIMIZATION
    // =============================================================================
    // Tests:
    // - STEP 1: tx_done_i signal integration (replaces tx_busy_falling)
    // - Verify S_TX_SEND state machine transitions correctly
    // - Verify checksum calculation and frame reception
    // - Verify WRITE, READ, KICK, GET_STATUS commands
    // =============================================================================

    parameter CLK_FREQ = 27_000_000;
    parameter BAUD_RATE = 115200;
    localparam CLK_PERIOD = 37;  // 27MHz

    // Clock and Reset
    reg clk;
    reg rst_n;

    // UART RX interface (simulated input from uart_rx module)
    reg [7:0] rx_data_i;
    reg rx_done_i;

    // UART TX interface (output to uart_tx module)
    wire [7:0] tx_data_o;
    wire       tx_en_o;
    reg        tx_busy_i;
    reg        tx_done_i;       // NEW: tx_done_o from uart_tx, input to parser

    // Register File interface
    wire [7:0]  reg_addr_o;
    wire        reg_we_o;
    wire        reg_re_o;
    wire [31:0] reg_wdata_o;
    wire [31:0] reg_rdata_i;

    // Watchdog Core interface
    wire        uart_kick_pulse_o;
    wire        wdi_src_i;

    // Test signals
    integer tx_byte_count;
    integer tx_bytes [0:9];      // Expected TX bytes
    integer tx_idx_expected;
    integer test_passes;
    integer test_errors;

    // =========================================================
    // UART Frame Parser Module
    // =========================================================
    uart_frame_parser u_parser (
        .clk               (clk),
        .rst_n             (rst_n),
        .rx_data_i         (rx_data_i),
        .rx_done_i         (rx_done_i),
        .tx_data_o         (tx_data_o),
        .tx_en_o           (tx_en_o),
        .tx_busy_i         (tx_busy_i),
        .tx_done_i         (tx_done_i),        // NEW: tx_done signal input
        .reg_addr_o        (reg_addr_o),
        .reg_we_o          (reg_we_o),
        .reg_re_o          (reg_re_o),
        .reg_wdata_o       (reg_wdata_o),
        .reg_rdata_i       (reg_rdata_i),
        .uart_kick_pulse_o (uart_kick_pulse_o),
        .wdi_src_i         (wdi_src_i)
    );

    // =========================================================
    // Mock Regfile (simplified)
    // =========================================================
    reg [31:0] regfile [0:15];

    assign reg_rdata_i = regfile[reg_addr_o];

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            integer i;
            for (i = 0; i < 16; i = i + 1)
                regfile[i] <= 32'd0;
        end else begin
            if (reg_we_o) begin
                regfile[reg_addr_o] <= reg_wdata_o;
            end
        end
    end

    assign wdi_src_i = 1'b1;  // Simulate SW kick enabled

    // =========================================================
    // Clock Generator
    // =========================================================
    initial begin
        clk = 0;
        forever #(CLK_PERIOD / 2.0) clk = ~clk;
    end

    // =========================================================
    // UART TX Simulator (generates tx_done_i pulse)
    // =========================================================
    // When tx_en_o fires and tx_busy is not already high,
    // simulate the byte transmission and then pulse tx_done_i
    always @(posedge clk) begin
        if (tx_en_o && !tx_busy_i) begin
            // Start transmission: set tx_busy
            tx_busy_i <= 1'b1;
            
            // After ~10 bit periods (simulated), trigger tx_done
            // At 115200 baud: 1 bit = ~8.68 µs, 10 bits = ~86.8 µs
            // At 27MHz clock: ~2344 cycles
            // For simulation speed, use much smaller delay
            #1000;  // Simulate transmission delay
            
            @(posedge clk);
            tx_done_i <= 1'b1;  // Pulse tx_done for 1 cycle
            
            @(posedge clk);
            tx_done_i <= 1'b0;
            tx_busy_i <= 1'b0;
        end
    end

    // =========================================================
    // MONITOR: Track TX bytes and verify order
    // =========================================================
    always @(posedge clk) begin
        if (tx_en_o && !tx_busy_i) begin
            $display("[%0t] [TX] Byte #%0d: 0x%02h", $time, tx_byte_count, tx_data_o);
            if (tx_byte_count < 10) begin
                tx_bytes[tx_byte_count] <= tx_data_o;
            end
            tx_byte_count <= tx_byte_count + 1;
        end
    end

    // =========================================================
    // MONITOR: Detect tx_done_i pulses (STEP 1 verification)
    // =========================================================
    integer tx_done_count;
    always @(posedge tx_done_i) begin
        tx_done_count = tx_done_count + 1;
        $display("[%0t] [STEP1] tx_done_i pulse #%0d detected", $time, tx_done_count);
    end

    // =========================================================
    // Task: Send 1 byte via RX interface
    // =========================================================
    task send_rx_byte;
        input [7:0] data;
        begin
            @(posedge clk);
            rx_data_i = data;
            rx_done_i = 1'b1;
            @(posedge clk);
            rx_done_i = 1'b0;
            #(CLK_PERIOD * 50);  // ~1.85 µs delay between bytes
        end
    endtask

    // =========================================================
    // Task: Send WRITE frame with checksum
    // =========================================================
    task send_write_frame;
        input [7:0] addr;
        input [31:0] data;
        input [7:0] len;
        reg [7:0] chk;
        begin
            $display("\n[%0t] === WRITE FRAME ===", $time);
            $display("  ADDR=0x%02h, LEN=%0d, DATA=0x%08h", addr, len, data);
            
            chk = 8'h01 ^ addr ^ len;
            send_rx_byte(8'h55);    // Sync
            send_rx_byte(8'h01);    // CMD
            send_rx_byte(addr);     // ADDR
            send_rx_byte(len);      // LEN

            if (len >= 4) begin
                send_rx_byte(data[31:24]); 
                chk = chk ^ data[31:24];
                send_rx_byte(data[23:16]); 
                chk = chk ^ data[23:16];
                send_rx_byte(data[15:8]);  
                chk = chk ^ data[15:8];
                send_rx_byte(data[7:0]);   
                chk = chk ^ data[7:0];
            end else if (len == 2) begin
                send_rx_byte(data[15:8]);  
                chk = chk ^ data[15:8];
                send_rx_byte(data[7:0]);   
                chk = chk ^ data[7:0];
            end else if (len == 1) begin
                send_rx_byte(data[7:0]);   
                chk = chk ^ data[7:0];
            end
            
            send_rx_byte(chk);      // CHK
            $display("  Checksum: 0x%02h", chk);
        end
    endtask

    // =========================================================
    // Task: Send command frame (READ, KICK, STATUS)
    // =========================================================
    task send_cmd_frame;
        input [7:0] cmd;
        input [7:0] addr;
        reg [7:0] chk;
        reg [7:0] cmd_name [0:4];
        begin
            cmd_name[1] = "WRITE";
            cmd_name[2] = "READ";
            cmd_name[3] = "KICK";
            cmd_name[4] = "STAT";
            
            $display("\n[%0t] === COMMAND FRAME (CMD=0x%02h: %s) ===", $time, cmd, 
                     (cmd >= 1 && cmd <= 4) ? cmd_name[cmd] : "UNKNOWN");
            
            chk = cmd ^ addr ^ 8'h00;
            send_rx_byte(8'h55);    // Sync
            send_rx_byte(cmd);      // CMD
            send_rx_byte(addr);     // ADDR
            send_rx_byte(8'h00);    // LEN = 0
            send_rx_byte(chk);      // CHK
            $display("  Checksum: 0x%02h", chk);
        end
    endtask

    // =========================================================
    // MAIN TEST SEQUENCE
    // =========================================================
    initial begin
        // Initialize
        clk = 0;
        rst_n = 0;
        rx_data_i = 0;
        rx_done_i = 0;
        tx_busy_i = 0;
        tx_done_i = 0;
        tx_byte_count = 0;
        tx_done_count = 0;
        test_passes = 0;
        test_errors = 0;

        #(CLK_PERIOD * 10);
        rst_n = 1;
        #(CLK_PERIOD * 10);

        $display("\n========================================================");
        $display("  UART Frame Parser Testbench");
        $display("  Testing STEP 1: tx_done_i Signal Integration");
        $display("  STEP 2: Checksum Verification");
        $display("========================================================\n");

        // ========== TEST CASE 1: WRITE Command ==========
        $display("\nTEST CASE 1: WRITE Command (4-byte data)");
        send_write_frame(8'h04, 32'h12345678, 8'd4);
        #50000;  // Wait for ACK transmission
        
        if (tx_byte_count >= 5) begin
            $display("✓ PASS: TX sent %0d bytes for WRITE ACK (5 expected)", tx_byte_count);
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: TX sent only %0d bytes (expected 5+)", tx_byte_count);
            test_errors = test_errors + 1;
        end
        tx_byte_count = 0;

        // ========== TEST CASE 2: READ Command ==========
        $display("\nTEST CASE 2: READ Command");
        send_cmd_frame(8'h02, 8'h04);
        #50000;  // Wait for response (should be 9 bytes: 55, CMD, ADDR, LEN, 4xDATA, CHK)
        
        if (tx_byte_count >= 9) begin
            $display("✓ PASS: TX sent %0d bytes for READ response (9 expected)", tx_byte_count);
            
            // Verify structure: tx_bytes[0]=0x55, tx_bytes[1]=CMD, tx_bytes[3]=LEN=0x04, etc.
            if (tx_bytes[0] == 8'h55) begin
                $display("  ✓ Byte[0] (Sync) = 0x%02h [CORRECT]", tx_bytes[0]);
                test_passes = test_passes + 1;
            end else begin
                $display("  ✗ Byte[0] (Sync) = 0x%02h [EXPECTED 0x55]", tx_bytes[0]);
                test_errors = test_errors + 1;
            end
            
            if (tx_bytes[3] == 8'h04) begin  // LEN byte
                $display("  ✓ Byte[3] (LEN) = 0x%02h [CORRECT]", tx_bytes[3]);
                test_passes = test_passes + 1;
            end else begin
                $display("  ✗ Byte[3] (LEN) = 0x%02h [EXPECTED 0x04]", tx_bytes[3]);
                test_errors = test_errors + 1;
            end
        end else begin
            $display("✗ FAIL: TX sent only %0d bytes (expected 9)", tx_byte_count);
            test_errors = test_errors + 1;
        end
        tx_byte_count = 0;

        // ========== TEST CASE 3: KICK Command ==========
        $display("\nTEST CASE 3: KICK Command");
        send_cmd_frame(8'h03, 8'h00);
        #50000;  // Wait for ACK (should be 5 bytes: 55, CMD, ADDR, LEN, CHK)
        
        if (tx_byte_count >= 5) begin
            $display("✓ PASS: TX sent %0d bytes for KICK ACK (5 expected)", tx_byte_count);
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: TX sent only %0d bytes (expected 5)", tx_byte_count);
            test_errors = test_errors + 1;
        end

        if (uart_kick_pulse_o) begin
            $display("✓ PASS: uart_kick_pulse_o detected");
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: uart_kick_pulse_o NOT detected");
            test_errors = test_errors + 1;
        end
        tx_byte_count = 0;

        // ========== TEST CASE 4: GET_STATUS Command ==========
        $display("\nTEST CASE 4: GET_STATUS Command");
        send_cmd_frame(8'h04, 8'h00);
        #50000;
        
        if (tx_byte_count >= 9) begin
            $display("✓ PASS: TX sent %0d bytes for STATUS response (9 expected)", tx_byte_count);
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: TX sent only %0d bytes (expected 9)", tx_byte_count);
            test_errors = test_errors + 1;
        end
        tx_byte_count = 0;

        // ========== TEST CASE 5: Bad Checksum (should drop frame) ==========
        $display("\nTEST CASE 5: Bad Checksum (frame should be dropped)");
        tx_byte_count = 0;
        
        send_rx_byte(8'h55);
        send_rx_byte(8'h03);     // KICK
        send_rx_byte(8'h00);     // ADDR
        send_rx_byte(8'h00);     // LEN
        send_rx_byte(8'hFF);     // BAD CHK (correct would be 0x03)
        
        #30000;
        
        if (tx_byte_count == 0) begin
            $display("✓ PASS: Bad checksum frame dropped (no TX)");
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: Frame with bad checksum was processed (%0d TX bytes)", tx_byte_count);
            test_errors = test_errors + 1;
        end

        // ========== TEST CASE 6: STEP 1 - Verify tx_done_i pulses ==========
        $display("\nTEST CASE 6: STEP 1 - tx_done_i pulse count verification");
        
        if (tx_done_count > 0) begin
            $display("✓ PASS: %0d tx_done_i pulses detected (should match TX byte count)", tx_done_count);
            test_passes = test_passes + 1;
        end else begin
            $display("✗ FAIL: No tx_done_i pulses detected");
            test_errors = test_errors + 1;
        end

        // ========== SUMMARY ==========
        $display("\n========================================================");
        $display("  TEST SUMMARY");
        $display("========================================================");
        $display("Total Passes: %0d", test_passes);
        $display("Total Errors: %0d", test_errors);
        
        if (test_errors == 0) begin
            $display("\n✓✓✓ ALL TESTS PASSED ✓✓✓\n");
        end else begin
            $display("\n✗✗✗ SOME TESTS FAILED ✗✗✗\n");
        end
        
        $finish;
    end

    // VCD dump for waveform analysis
    initial begin
        $dumpfile("tb_uart_frame.vcd");
        $dumpvars(0, tb_uart_frame);
    end

endmodule
