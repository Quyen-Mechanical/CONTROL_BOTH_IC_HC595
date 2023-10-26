#include <module/hc595.h>

HC595::HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu)
{
    latch = chan_chot;
    clock = chan_xung_thoi_gian;
    data = chan_tin_hieu;
    pinMode(latch, 1);
    pinMode(clock, 1);
    pinMode(data, 1);
}
bool HC595::bat_chan(uint8_t chan_can_bat)
{
    if (chan_can_bat > 0 && chan_can_bat <= 8)
    {
        port |= 1 << (chan_can_bat - 1); // bitRegister=bitRegister|1<<(bit_need_to_change)
        digitalWrite(latch, 0);
        shiftOut(data, clock, MSBFIRST, port);
        digitalWrite(latch, 1);
        return true;
    }
    else
    {
        return false;
    }
}

void HC595::tat_chan(uint8_t chan_can_tat)
{
    port &= ~(1 << (chan_can_tat - 1));
    digitalWrite(latch, 0);
    shiftOut(data, clock, MSBFIRST, port);
    digitalWrite(latch, 1);
}
void HC595::send(uint8_t register_to_port)
{
    port = register_to_port;
    digitalWrite(latch, 0);
    shiftOut(data, clock, MSBFIRST, port);
    digitalWrite(latch, 1);
}
HC595::~HC595()
{
}