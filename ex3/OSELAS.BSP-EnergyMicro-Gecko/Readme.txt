----------------------------------------README-------------------------------------------------------
How to run the game:
  - Build the initial uClinux build from the files on itslearning.
  - Replace the local_src folder in OSELAS.BSP-EnergyMicro-Gecko with the one we delievered.
  - Put the Makefile in the OSELAS.BSP-EnergyMicro-Gecko folder as well.
  - Type "make game" in the terminal and wait till it is finished.
  - Then type "make gameup" to upload the game onto the microcontroller.
  - Type "miniterm.py -b 115200 -p /dev/ttyS0" in the terminal and hit the reset button on the board.
  - Now type "modprobe driver-gamepad" so the game can access the driver.
  - Finally typing "game" will run the game.
  
How to play the game:
  - Use button SW2 and SW4 on the gamepad to make the block move down and up.
  - If you fail the Game over screen will load. Hit SW3 on the gamepad to reset the game.

GL & HF =)
-----------------------------------------------------------------------------------------------------
