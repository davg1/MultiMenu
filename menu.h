
/** 使用方法
  * 1.使用MenuItemDef(ItemName, name, Func, child)声明全部选项
  * 2.使用ComMenuItemDef(Arrname,...)将同一菜单选项合并成一个数组
  * 3.使用MenuDef(MenuName, name, ArrName, Parent)声明所有菜单
  * 4.使用InitMenuState(name, MaxRow, MainMenu)初始化菜单状态
  */  
#ifndef _MENU_H_
#define _MENU_H_

/************用于配合的头文件************/



/****************************************/

#define lcdMenu_callFunction(fp) ( ( *fp )( ) )

typedef struct sMENU sMENU;
typedef struct sMENUITEM sMENUITEM;
typedef struct sMENUSTATE sMENUSTATE;

/**********************************************************************************/
typedef struct sMENU
{
	char * name;							/* 菜单名 */
	sMENUITEM ** menuarr;					/* 菜单内容(数组) */
	uint8_t last_top;						/* 上级菜单的顶部是第几位 */
	uint8_t lastCurrItem;					/* 上级菜单选中的是第几个选项 */
	sMENU * parent;							/* 上级菜单 */
	
} sMENU;

/**********************************************************************************/
typedef struct sMENUITEM
{
	char * name;							/* 选项名 */
	void ( *Func_Handler )();				/* 选项功能 */
	sMENU * child;							/* 下级菜单 */
} sMENUITEM;

/**********************************************************************************/
typedef struct sMENUSTATE
{
	uint8_t top;							/* 当前显示菜单顶部是第几个 */
	uint8_t MAX_ROWS;						/* 一个屏幕最多显示几个选项 */
	uint8_t currItem;						/* 当前选中的是第几个选项 */
	sMENU * currMenu;						/* 当前显示的菜单 */
} sMENUSTATE;

/**********************************************************************************/
/* 创建菜单选项宏 
 * ItemName 该选项的变量名
 * name		选项名
 * Func		选项功能函数指针
 * child	下级菜单指针
 */
#define MenuItemDef( ItemName, name, Func, child) \
const sMENUITEM MI_##ItemName = {name, (Func), (child)}

/* 获取选项变量的指针的宏 */
#define MenuItem( ItemName )    (&MI_##ItemName)

/* 封装MenuItem数组(单组菜单) 
 * Arrname 该菜单数组名
 * ... 输入需要填入的GMIP(ItemName)
 */
#define ComMenuItemDef( ArrName,...) \
const sMENUITEM * MIA_##ArrName[] = {__VA_ARGS__}

/* 获取菜单数组名宏 */
#define ComMenuItem( ArrName )    (CMI_##ArrName)

/* 封装Menu
 * MenuName 菜单变量名
 * name		菜单标题
 * Arrname	菜单包含选项数组
 * Parent	上级菜单指针
 */
#define MenuDef( MenuName, name, ArrName, Parent ) \
sMENU M_##MenuName = {name, (ArrName), 0, 0, (Parent)}

/* 获取菜单名的指针宏 */
#define Menu( MenuName )    (&M_##MenuName)

/* 初始化菜单状态 */
#define InitMenuState(name, MaxRow, MainMenu)  \
sMENUSTATE MS_##name = {0, (MaxRow), 0, (MainMenu)}

/* 获取菜单状态名的指针宏 */
#define MenuState(name)    (&MS_##name)

/**********************************************************************************/
void Menu_goBack( sMENUSTATE * ms );
/**********************************************************************************/
void Menu_select( sMENUSTATE * ms );
/**********************************************************************************/
void Menu_goUp( sMENUSTATE * ms );
/**********************************************************************************/
void Menu_goDown( sMENUSTATE * ms );
/**********************************************************************************/
void LCD_drawMenu( sMENUSTATE * ms );
/***********************************************************************************
以下函数需要自己根据需要改写
***********************************************************************************/
void lcdMenu_clearScreen( void );
/**********************************************************************************/
void lcdMenu_printTitle( void );
/**********************************************************************************/
void lcdMenu_printSelect( void );
/**********************************************************************************/
void lcdMenu_printNormal( void );
/**********************************************************************************/

#endif
