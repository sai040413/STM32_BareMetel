.syntax unified
.cpu cortex-m4
.thumb

.global g_pfnVectors
.global Reset_Handler

.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler

.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  // Initialize data and bss
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
copy_data:
  cmp r0, r1
  ittt lt
  ldrlt r3, [r2], #4
  strlt r3, [r0], #4
  blt copy_data

  ldr r0, =_sbss
  ldr r1, =_ebss
zero_bss:
  cmp r0, r1
  itt lt
  movlt r2, #0
  strlt r2, [r0], #4
  blt zero_bss


  bl main
  b .
.size Reset_Handler, .-Reset_Handler

