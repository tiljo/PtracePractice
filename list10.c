//compile: cc filename.c -lbfd -liberty
#include "ptrchdr.h"
//argv[1] should be name of an object file
int main(int argc,char *argv[])
{
	long storage_needed,num_symbols,i;
	asymbol **symbol_table;
	bfd *abfd;
	char filename[100];

	bfd_init();

	abfd = bfd_openr(argv[1],NULL);
	assert(abfd != NULL);
	bfd_check_format(abfd,bfd_object);
	storage_needed = bfd_get_symtab_upper_bound(abfd);
	assert(storage_needed >= 0);
	printf("storage = %ld\n",storage_needed);

	symbol_table = (asymbol**)malloc(storage_needed);
	assert(symbol_table !=0);
	num_symbols = bfd_canonicalize_symtab(abfd,symbol_table);
	assert(num_symbols >=0);
	printf("num syms = %ld\n",num_symbols);
	for(i=0; i<num_symbols; i++){
		printf("%s: %lx\n",bfd_asymbol_name(symbol_table[i]),bfd_asymbol_value(symbol_table[i]));
	}
	return 0;
}

