void kernel_main()
{
    const char *str = "HELLO FROM DHIRAJ's New OS";
    char *video_memory = (char *)0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; // Light grey text
    }

    while (1)
    {
    }
}