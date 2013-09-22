#ifndef OLED_H_
#define OLED_H_

void OLED_init(void);
void OLED_writeData(char c);
void OLED_writeChar(int i);
void OLED_setCursor(int cursor);
void OLED_setPage(int page);
void OLED_writeString(char* s);
void OLED_blankScreen(void);

#endif 