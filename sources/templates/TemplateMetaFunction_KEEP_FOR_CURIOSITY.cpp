// TemplateMetaFunction.cpp by Ulrich Eisenecker, June 2, 2022
// This program illustrates another use of template template parameters

#include <iostream>
using namespace std;

template <unsigned n,template <unsigned m> class Operation>
struct Sum
{
   static const inline unsigned long long result { Operation<n>::result + Sum<n -
   1,Operation>::result };
};

template <template <unsigned m> class Operation>
struct Sum<0,Operation>
{
   static const inline unsigned long long result { Operation<0>::result };
};

template <unsigned m>
struct Plus2
{
   static const inline unsigned long long result { m + 2 };
};

template <unsigned m>
struct Square
{
   static const inline unsigned long long result { m * m };
};

int main()
{
   cout << Sum<5,Plus2>::result << endl; // cout << 27 << endl;
   cout << Sum<3,Square>::result << endl; // cout << 14 << endl;
}

/*
   You can easily verify that the compiler produces the code for main()
   as described above. Execute
   g++ -S -std=c++20 TemplateMetaFunction.cpp
   in a terminal window.
   Afterwards load the resulting file TemplateMetaFunction.s
   into VIM or another editor of your choice. There, very much at the 
   beginning, the assembler code generated for main is displayed.
   You can immediately spot the constants 27 and 14 which are moved
   as data into %esi.

   Assembler code for main() included below:

   	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 12, 3
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	movl	$27, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEy
	movq	%rax, %rdi
	movq	__ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_@GOTPCREL(%rip), %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	movl	$14, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEy
	movq	%rax, %rdi
	movq	__ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_@GOTPCREL(%rip), %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
*/
