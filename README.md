# ililo_hardware
about hardware device source
IF you want to know how the hardware works for this project\n you are welcomed

the main board of this device is nodeMCU 1.0V
due to the limits for not able to exeute multiple threads since it is single core controller,
i've developed transmitter and receiver independently for each boards. couldn't implement these two on the same board and make it a transevier.

but it still works fine.

requirements :
tx - nodeMCU 1ea, 433TX 1ea, LED 1ea, jumperwires
rx - nodeMCU 1ea, 433RX 1ea(VCC - 3.3v or else it might burn your main board circuit), LED 1ea, jumperwires
