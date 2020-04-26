



#define APPUYE 0x0000

#define W (GPIOA->IDR & 0x0001)
#define T (GPIOC->IDR & 0x2000)
#define U (GPIOG->IDR & 0x0100)
#define JL (GPIOG->IDR & 0x4000)
#define JR (GPIOG->IDR & 0x2000)
#define JU (GPIOG->IDR & 0x8000)
#define JD (GPIOD->IDR & 0x0008)
#define JS (GPIOG->IDR & 0x0080)

#define UIF (1<<0)

#define X_MIN 4
#define X_MAX 309
#define Y_MIN 13
#define Y_MAX 225
