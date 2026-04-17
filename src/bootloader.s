; boatloader.asm
bits 16
org 0x7c00

jmp short start
nop

bdb_oem: db "DingOS"
bdb_bytes_per_sector: 		dw 512
bdb_sectors_per_cluster: 	db 1
bdb_reserved_sectors: 		dw 1
bdb_fat_count: 			db 2
bdb_dir_entries_count: 		dw 0xe0
bdb_total_sectors:		dw 2880			; 2880 * 512 = 1.44MB
bdb_media_desctiptor_type:	db 0xF0                 ; F0 = 3.5" floppy disk
bdb_sectors_per_fat:		dw 9			; 9 sectors/fat
bdb_sectors_per_track:		dw 18
bdb_heads:			dw 2
bdb_hidden_sectors:		dd 0
bdb_large_sector_count:		dd 0

ebr_drive_number:		db 0			; 0x00 floppy, 0x80 hdd, useless
				db 0			; Reserved
ebr_signature:			db 0x29
ebr_volume_id:			db 'bruh'		; Serial number value not important (4 bytes)
ebr_volume_label:		db 'DingOS'
ebr_system_id:			db 'FAT12   '		; 8 bytes


start:
    mov [ BOOT_DRIVE ], dl ; BIOS stores our boot drive in dl
    mov ah, 0x02           ; BIOS read sectors function
    mov al, 128            ; Number of sectors to read
    mov ch, 0              ; Cylinder 0
    mov cl, 2              ; Start reading at sector 2 (after the boot sector)
    mov dh, 0              ; Head 0
    mov dl, [ BOOT_DRIVE ] ; Drive number (0 for floppy, 0x80 for hard disk)
    mov bx, 0x7e00         ; Load additional sectors at 0x8000
    int 0x13               ; BIOS interrupt to read sectors
    lgdt [gdt_descriptor] 
    mov eax , cr0 ; To make the switch to protected mode
    or eax , 0x1 ; set the first bit of , a control register CR0
    mov cr0 , eax ; Update the control register
    cli
    jmp 0x08:init_pm ; Selector 0x08 points to the code segment
    
    ; Data
    BOOT_DRIVE : db 0
 
; GDT
gdt_start :
    dq 0x0000000000000000 ;null
    dq 0x00CF9A000000FFFF ;code
    dq 0x00CF92000000FFFF ;data
gdt_end :
gdt_descriptor :
    dw gdt_end - gdt_start - 1 ; Size of our GDT 
    dd gdt_start ; Start address of our GDT
[bits 32]
init_pm :
    mov ax , 0x10 ; Now in PM , our old segments are meaningless ,
    mov ds , ax ; so we point our segment registers to the
    mov ss , ax ; data selector we defined in our GDT
    mov es , ax
    mov fs , ax
    mov gs , ax
    mov esp, 0x7C00            ; Set stack pointer

    ; Your 32-bit protected mode code here
    jmp BEGIN_PM

times 510 - ($-$$) db 0
dw 0xaa55

[ bits 32]
BEGIN_PM :

;times 2048 -( $ - $$ ) db 0
