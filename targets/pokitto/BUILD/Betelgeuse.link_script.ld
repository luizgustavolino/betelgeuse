MEMORY
{
  MFlash256 (rx) : ORIGIN = 0x0, LENGTH = 0x40000
  Ram0_32 (rwx) : ORIGIN = 0x10000000+0x100, LENGTH = 0x8000-0x100
  Ram1_2 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x800
  Ram2USB_2 (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800
}
  __top_MFlash256 = 0x0 + 0x40000;
  __top_Ram0_32 = 0x10000000 + 0x8000;
  __top_Ram1_2 = 0x20000000 + 0x800;
  __top_Ram2USB_2 = 0x20004000 + 0x800;
ENTRY(ResetISR)
SECTIONS
{
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG( ADDR(.data));
        LONG( SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG( ADDR(.data_RAM2));
        LONG( SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG( ADDR(.data_RAM3));
        LONG( SIZEOF(.data_RAM3));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG( ADDR(.bss));
        LONG( SIZEOF(.bss));
        LONG( ADDR(.bss_RAM2));
        LONG( SIZEOF(.bss_RAM2));
        LONG( ADDR(.bss_RAM3));
        LONG( SIZEOF(.bss_RAM3));
        __bss_section_table_end = .;
        __section_table_end = . ;
        *(.after_vectors*)
        *(.text*)
        *(.rodata .rodata.*)
        . = ALIGN(4);
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
        KEEP(*(.fini));
        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))
        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))
    } > MFlash256
    .ARM.extab : ALIGN(4)
    {
     *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlash256
    __exidx_start = .;
    .ARM.exidx : ALIGN(4)
    {
     *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlash256
    __exidx_end = .;
    _etext = .;
    .mtb_buffer_RAM2 (NOLOAD) :
    {
        KEEP(*(.mtb.$RAM2*))
        KEEP(*(.mtb.$RAM1_2*))
    } > Ram1_2
    .data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       *(.ramfunc.$RAM2)
       *(.ramfunc.$Ram1_2)
     *(.data.$RAM2*)
     *(.data.$Ram1_2*)
       . = ALIGN(4) ;
    } > Ram1_2 AT>MFlash256
    .mtb_buffer_RAM3 (NOLOAD) :
    {
        KEEP(*(.mtb.$RAM3*))
        KEEP(*(.mtb.$RAM2USB_2*))
    } > Ram2USB_2
    .data_RAM3 : ALIGN(4)
    {
       FILL(0xff)
       *(.ramfunc.$RAM3)
       *(.ramfunc.$Ram2USB_2)
     *(.data.$RAM3*)
     *(.data.$Ram2USB_2*)
       . = ALIGN(4) ;
    } > Ram2USB_2 AT>MFlash256
    .mtb_buffer_default (NOLOAD) :
    {
       KEEP(*(.mtb*))
    } > Ram0_32
    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > Ram0_32
 .data : ALIGN(4)
 {
    FILL(0xff)
    _data = . ;
    *(vtable)
    *(.ramfunc*)
    *(.data*)
    . = ALIGN(4) ;
    _edata = . ;
 } > Ram0_32 AT>MFlash256
    .bss_RAM2 : ALIGN(4)
    {
     *(.bss.$RAM2*)
     *(.bss.$Ram1_2*)
       . = ALIGN(4) ;
    } > Ram1_2
    .bss_RAM3 : ALIGN(4)
    {
     *(.bss.$RAM3*)
     *(.bss.$Ram2USB_2*)
       . = ALIGN(4) ;
    } > Ram2USB_2
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
        __end__ = .;
    } > Ram0_32
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
     *(.noinit.$RAM2*)
     *(.noinit.$Ram1_2*)
       . = ALIGN(4) ;
    } > Ram1_2
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
     *(.noinit.$RAM3*)
     *(.noinit.$Ram2USB_2*)
       . = ALIGN(4) ;
    } > Ram2USB_2
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
    } > Ram0_32
    PROVIDE(_pvHeapStart = .);
    PROVIDE(_vStackTop = __top_Ram0_32 - 0);
}
