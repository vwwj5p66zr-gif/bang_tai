
#ifndef CAM_BIEN_HONG_NGOAI_H
#define CAM_BIEN_HONG_NGOAI_H

void khoi_tao_cam_bien_hong_ngoai();

void cap_nhat_cam_bien_hong_ngoai();

// 1, 2, 3 tương ứng servo 1, 2, 3
bool phat_hien_san_pham_truoc_servo(int so_servo);

// 1, 2, 3 tương ứng khay 1, 2, 3
bool phat_hien_san_pham_vao_khay(int so_khay);

// Kiểm tra khay đã đầy hay chưa
bool khay_da_day(int so_khay);

#endif
