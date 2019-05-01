Readme.txt (1/6/2015)

I have been working on this on a windows PC but it should be more simple
on a linux box.  I don't really have any development experiance on OS-X but it 
looks like linux.

At the current time: 
	The minimal test is working well 
	The full test is starting with no asserts
	The full test has issues I have not chased:
		1) After a perodic test fails the fast blink will quit after a while (couple hours)
		2) Cannot last more than a few seconds running the tests:
				if( xAreDynamicPriorityTasksStillRunning() != pdTRUE )
				if ( xAreBlockTimeTestTasksStillRunning() != pdTRUE )
				if ( xAreRecursiveMutexTasksStillRunning() != pdTRUE )
				if( xIsCreateTaskStillRunning() != pdTRUE )
				but the rest run ok for a while.. (not indefinatly)

My environment:
	Windows 7, 64 bit
	Tiva™ C Series TM4C123G LaunchPad Evaluation Board (http://www.digilentinc.com/)
	TivaWare_C_Series-2.0.1.11577 (From Ti)
	LM Flash Programmer - Build 1613 (From Ti)
	gcc-arm-none-eabi-4_9 (Windows binary package)
	openocd-0.8.0 (Windows binary package)
	FreeRTOSV8.1.2 (from FreeRTOS.org)
	
Oddities:
 -> I was easily able to rebuld the TI Tivaware driver library but could 
	not get it to link from the destination directory.. I finally added it 
	(libdriver.a) to my src directory in order to get it to compile.
 -> The LMFlash commands in the 'make flash' target sometimes fail to reflash 
    the board properly.. From the user groups this is a known LMFlash issue..
	A second 'make flash' usually works for me.
 -> I added an assert that will flash red and blue if any of the error hooks 
    are hit.  I use gdb to examine failures.. If I get motovated I'll blink out 
	file and line numbers on a button press...
	
TI Tivaware:
	After you install the compiler and Tivaware you'll need to 
	build libdriver.a for the TM4C123G board.  This is only used in 
	this project to set the processor speed and blink an LED. All
	references to libdriver.a are in the file hardware_tm4c123g.c
	
	My makefile uses the tivaware makedefs file.  the ROOT makefile
	variable should point to your tivaware install directory.
	
The notes I use to get GDB up and running...
  Cmd Window 1:
	openocd-0.8.0.exe --file J:\openocd-0.8.0\openocd-0.8.0\scripts\board\ek-tm4c123gxl.cfg
  Cmd Window 2:
	arm-none-eabi-gdb.exe gcc\main.axf
	(gdb) target extended-remote :3333
	(gdb) monitor reset halt
	(gdb) load
	(gdb) monitor reset init
	(gdb) continue
	
	To make life a little easier, I use the following .gdbinint file
	
		target extended-remote :3333
		monitor reset halt
		load
		monitor reset init
		b main
		b _assert_failed
		continue

Some Handy Resources
	http://processors.wiki.ti.com/index.php/LaunchPad_Resources
	http://processors.wiki.ti.com/index.php/Stellaris_Launchpad_with_OpenOCD_and_Linux
	http://openocd.sourceforge.net/getting-openocd/
	https://launchpad.net/gcc-arm-embedded/+download
	http://www.freddiechopin.info/en/download/category/4-openocd
	http://cengiz.akinli.org/gdbprimer.htm

Have Fun!

Miller