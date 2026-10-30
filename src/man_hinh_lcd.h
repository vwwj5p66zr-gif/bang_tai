#ifndef LCD_H
#define LCD_H

// Khoi tao LCD
void khoi_tao_lcd();

// Xoa noi dung LCD
void xoa_man_hinh_lcd();

// Hien thi noi dung tai vi tri cot, dong
void hien_thi_lcd(int cot, int dong, const char *noi_dung);

// Hien thi thong tin dem san pham
void hien_thi_thong_ke(int tong, int dem_khay_1, int dem_khay_2, int dem_khay_3);

#endif