void main(void)
{
    printf("Content-Type: text/plain\n");
    printf("Access-Control-Allow-Origin: *\n");
    printf("\n");

    system("uart_ctl 11");

   // printf("uart_ctl 1\n");
    return;
}
