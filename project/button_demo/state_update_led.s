	.arch msp430g2553
	.p2align 1,0

	.data
new_red_on:
	.word 0
new_green_on:
	.word 0
red_on:
	.word 0
green_on:
	.word 0
ledConf:
	.word 0
count:
	.word 0
	
	.text
jt:
	.word off		;jt[0]
	.word bright		;jt[1]
	.word dim		;jt[2]

	.global state_update_led
state_update_led:
	cmp #3, &ledConf	;s-3
	jnc off			;jmp of s > 2
	;; index onto jt
	mov &ledConf, r12
	add r12, r12		;r12=2*s
	mov jt(r12), r0		;jmp jt[ledConf]

	;; switch table
	
off:	mov.b #0, &new_red_on
	mov.b #1, &new_green_on
	jmp end			;break

bright:	mov.b #1, &new_red_on
	mov.b #0, &new_green_on
	jmp end			;break

dim:	cmp #1, &count
	jlo end
	mov.b &count, &new_red_on
	mov.b &count, &new_green_on
	jmp end			;break
if:	
	cmp &new_red_on, &red_on
	jeq end 		;red_on-new_red_on
	mov.b &new_red_on, &red_on
	mov.b #1, &led_changed
if1:	
	cmp &new_green_on, &green_on
	jeq end			;green_on-new_green_on
	mov.b &new_green_on, &green_on
	mov.b #1, &led_changed
	
end:	call #led_update	;call led_update function
	pop r0			;return

	
