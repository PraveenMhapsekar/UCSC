all: run clean

run: ex1_global_uninitialized ex2_global_initialized ex3_stack_uninitialized ex4_stack_initialized ex5_malloc ex4a_stack_initialized
	ls -l ex*initialized ex5_malloc
	size ex*initialized ex5_malloc
	
ex1_global_uninitialized: ex1_global_uninitialized.c

ex2_global_initialized: ex2_global_initialized.c

ex3_stack_uninitialized: ex3_stack_uninitialized.c

ex4_stack_initialized: ex4_stack_initialized.c

ex4a_stack_initialized: gen_ex4a.sh
	./gen_ex4a.sh
	gcc -o ex4a_stack_initialized ex4a_stack_initialized.c

ex5_malloc: ex5_malloc.c

clean: 
	rm -f ex*initialized ex5_malloc
