void main(void)
{
    printf("Content-Type: text/plain\n");
    printf("Access-Control-Allow-Origin: *\n");
    printf("\n");

    system("uart_ctl 22");

   // printf("uart_ctl 2\n");
    return;
}
