int i;
int j=14;
char *str="hello, world!\n";

main() {

	for(     ;
           j--;
           read(0,str[i++],1);
	);

}

read (j,i,p)
{ 
  // ssize_t write(int fd, const void *buf, size_t count);
   write ( 1, i ,1);
}
