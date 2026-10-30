#ifndef CAM_BIEN_MAU_H
#define CAM_BIEN_MAU_H

// Cac loai mau san pham
enum MauSanPham {
    KHONG_XAC_DINH,
    DO,
    VANG,
    XANH_DUONG
};

// Khoi tao cam bien mau
void khoi_tao_cam_bien_mau();

// Doc va nhan dien mau san pham
MauSanPham doc_mau_san_pham();

// Chuyen ma mau thanh chuoi
const char* ten_mau_san_pham(MauSanPham mau);

void doc_du_lieu_mau(
    unsigned long &do_do,
    unsigned long &do_vang,
    unsigned long &do_xanh_duong
);
#endif