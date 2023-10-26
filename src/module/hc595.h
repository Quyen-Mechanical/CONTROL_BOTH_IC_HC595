#include <Arduino.h>

class HC595
{
private:
public:
    uint8_t latch;
    uint8_t data;
    uint8_t clock;
    uint8_t num_register=1; // luu lai tong so thanh ghi(tong so ic 595) de dung lam lay so phan tu toi da trong mang
    bool transfer_dir=MSBFIRST;
    uint8_t Registers[];

    HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu);
    HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu, uint8_t num_of_register);
    HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu, uint8_t num_of_register, bool direction_of_transition);
    ~HC595();
    bool bat_chan(uint8_t chan_can_bat1);
    bool tat_chan(uint8_t chan_can_tat);
    void send(uint8_t register_to_port);
};