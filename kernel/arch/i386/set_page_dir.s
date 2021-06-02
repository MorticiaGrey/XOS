.text
.global set_page_dir
set_page_dir:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    pop %ebp
    ret

.global enable_paging
enable_paging:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000000, %eax
    # I move the result to ebx first because otherwise it was crashing grub, no idea why
    mov %ebx, %eax
    mov %ebx, %cr0 # Causing problem
    mov %ebp, %esp
    pop %ebp
    ret