ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx)		: ORIGIN = 0x08000000, LENGTH = 1024K
	CCMRAM (xrw)	: ORIGIN = 0x10000000, LENGTH = 64K
	SRAM (xrw)		: ORIGIN = 0x20000000, LENGTH = 112K
	ETHRAM (xrw)	: ORIGIN = 0x2001C000, LENGTH = 16K
}

_estack = 0x2001C000;

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))

		. = ALIGN(4);
	} > FLASH
	
	.text :
	{
		. = ALIGN(4);
		_stext = .;
		*(.text*)
		*(.rodata*)
		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		_etext = .;
	} > FLASH

	/*
	 * Stack unwinding and exception handling sections.
	 *
	 * ARM compilers emit object files with .ARM.extab and .ARM.exidx sections
	 * when using C++ exceptions. Also, at least GCC emits those sections when
	 * dividing large numbers (64-bit) in C. So we have to handle them.
	 *
	 * (ARM uses .ARM.extab and .ARM.exidx instead of the .eh_frame section
	 * used on x86.)
	 */
	.ARM.extab : /* exception unwinding information */
	{
		*(.ARM.extab*)
	} > FLASH
	.ARM.exidx : /* index entries for section unwinding */
	{
		*(.ARM.exidx*)
	} > FLASH

	_sidata = .;
	.data : AT ( _sidata )
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data*)

		. = ALIGN(4);
		_edata = .;
	} > SRAM

	_sibss = .;
	.bss : AT ( _sibss )
	{
		. = ALIGN(4);
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss*)
		*(COMMON)

		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
	} > SRAM
}
