void main(void)
{
    printf("Content-Type: text/plain\n");
    printf("Access-Control-Allow-Origin: *\n");
    printf("\n");

    system("uart_ctl 33");

   // printf("uart_ctl 3\n");
    return;
}
