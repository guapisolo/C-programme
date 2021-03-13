1. CreateConsoleScreenBuffer：创建控制台屏幕缓冲区
outbuf = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    ); 
2. WriteConsoleOutputCharacterA : 把东西推进缓冲区
    WriteConsoleOutputCharacterA(hOutBuf,date[i],60,coord,&bytes); 
3. SetConsoleActiveScreenBuffer(hout); ：把hout缓冲区作为显示的缓冲区



