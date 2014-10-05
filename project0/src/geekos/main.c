/*
 * GeekOS C code entry point
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2004, Iulian Neamtiu <neamtiu@cs.umd.edu>
 * $Revision: 1.51 $
 * 
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/bootinfo.h>
#include <geekos/string.h>
#include <geekos/screen.h>
#include <geekos/mem.h>
#include <geekos/crc32.h>
#include <geekos/tss.h>
#include <geekos/int.h>
#include <geekos/kthread.h>
#include <geekos/trap.h>
#include <geekos/timer.h>
#include <geekos/keyboard.h>

void EchoCount()
{
    Keycode keycode;
    int count;
    count = 0;
    while (1)
    {
        if (Read_Key(&keycode))
        {
            if ((keycode & 0x4000) == 0x4000)
            {
                if ((Wait_For_Key() & 0x00ff) == 'q')
                {
                    Set_Current_Attr(ATTRIB(BLACK, RED));
                    Print("Ctrl+q is entered! \nGAME over!!\n\n");
                    Exit(1);
                }
            }
            else if ( !(keycode & KEY_SPECIAL_FLAG) && !(keycode & KEY_RELEASE_FLAG))
            {
                keycode &= 0xff;
                count = count + 1;
                Set_Current_Attr(ATTRIB(BLACK,CYAN));
                Print("%c",(keycode == '\r') ? '\n':keycode);
                if (keycode == '\r')
                {
                    count = count -1;
                    Set_Current_Attr(ATTRIB(GRAY,BLUE));
                    Print("The NUM you enter is : %d",count);
                    Print("\n");
                    count = 0;
                }
            }
        }            
    }
}

/*
 * Kernel C code entry point.
 * Initializes kernel subsystems, mounts filesystems,
 * and spawns init process.
 */
void Main(struct Boot_Info* bootInfo)
{
    Init_BSS();
    Init_Screen();
    Init_Mem(bootInfo);
    Init_CRC32();
    Init_TSS();
    Init_Interrupts();
    Init_Scheduler();
    Init_Traps();
    Init_Timer();
    Init_Keyboard();

    Set_Current_Attr(ATTRIB(BLACK,BLUE|BRIGHT));
    Print("=====>>Welcome to GeekOS<<=====\n");
    Print("=====>>Hello from Late Lee %s %s <<===\n", __DATE__, __TIME__);
    Print("This is the test of project0:Getting Started\n\n");
    Print("\tFightNow! Team\n\nctrl+q:quit\n");
    Set_Current_Attr(ATTRIB(BLACK,GRAY));
  /*  TODO("Start a kernel thread to echo pressed keys and print counts");*/

    //new here
    struct Kernel_Thread *kerThd;
    kerThd = Start_Kernel_Thread(&EchoCount,0,PRIORITY_NORMAL,false);
    /* Now this thread is done. */
    Exit(0);
}

