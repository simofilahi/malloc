
int main()
{
    char *ptr;
    char *str;
    char *nbr;

    ptr = 0;
    str = 0;
    nbr = 0;

    ptr = (char *)malloc(5000);
    str = (char *)malloc(120);
    nbr = (char *)malloc(200);

    free(ptr);
    free(str);
    free(nbr);
    return 0;
}