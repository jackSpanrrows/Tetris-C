#include <stdio.h>

int colors_test(void)
{
	// insert code here...
    HANDLE hOut;  
 
    //  获取输出流的句柄
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);    
 
    printf("普通颜色看看n");
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_GREEN |      // 前景色_绿色
                            FOREGROUND_INTENSITY ); // 前景色_加强
    printf("设置了浅绿色.n");  
    printf("并且完了之后就一直是浅绿色n");
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_BLUE |       // 前景色_蓝色
                            FOREGROUND_INTENSITY |  // 前景色_加强
                            COMMON_LVB_UNDERSCORE); // 添加下划线
    printf("文字蓝色，再加个下划线.n");    
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_RED |        // 前景色_红色
                            FOREGROUND_INTENSITY |  // 前景色_加强
                            BACKGROUND_BLUE );      // 背景色_蓝色
    printf("设置文字红色，背景蓝色n");  
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_RED |            // 前景色_红色
                            FOREGROUND_INTENSITY |      // 前景色_加强
                            COMMON_LVB_GRID_LVERTICAL );// 网格_左_竖
    printf("                      加 左 网格n");  
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_RED |            // 前景色_红色
                            FOREGROUND_INTENSITY |      // 前景色_加强
                            COMMON_LVB_GRID_RVERTICAL );// 网格_右_竖  
    printf("                      加 右 网格n");    
 
    SetConsoleTextAttribute(hOut,  
                            FOREGROUND_RED |    // 前景色_红色
                            FOREGROUND_GREEN |  // 前景色_绿色
                            FOREGROUND_BLUE );  // 前景色_蓝色
    printf("改回白色n");  
 
    system("pause");
    return 0;  
}
