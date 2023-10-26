#include <module/hc595.h>

HC595::HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu) // ham` khoi tao mac dinh 1 ic 595
{
    latch = chan_chot;
    clock = chan_xung_thoi_gian;
    data = chan_tin_hieu;
    pinMode(latch, 1);
    pinMode(clock, 1);
    pinMode(data, 1);
    Registers[0] = 0b00000000;
    num_register = 1;
}
HC595::HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu, uint8_t num_of_register) // ham khoi tao nhieu ic 595
{
    latch = chan_chot;
    clock = chan_xung_thoi_gian;
    data = chan_tin_hieu;
    pinMode(latch, 1);
    pinMode(clock, 1);
    pinMode(data, 1);
    if (num_of_register > 0) // so ic phai lon hon 0
    {
        for (uint8_t i = 0; i < num_of_register; i++) // them thanh ghi vao mang? thanh ghi
        {
            Registers[i] = 0b00000000;
        }
        num_register = num_of_register; //  gan gia tri cua tong so thanh ghi bang gia tri cua nguoi dung nhap vao
    }
}
HC595::HC595(uint8_t chan_chot, uint8_t chan_xung_thoi_gian, uint8_t chan_tin_hieu, uint8_t num_of_register, bool direction_of_transition)
{
    latch = chan_chot;
    clock = chan_xung_thoi_gian;
    data = chan_tin_hieu;
    transfer_dir = direction_of_transition;
    pinMode(latch, 1);
    pinMode(clock, 1);
    pinMode(data, 1);
    if (num_of_register > 0) // so ic phai lon hon 0
    {
        for (uint8_t i = 0; i < num_of_register; i++) // them thanh ghi vao mang? thanh ghi
        {
            Registers[i] = 0b00000000;
        }
        num_register = num_of_register; //  gan gia tri cua tong so thanh ghi bang gia tri cua nguoi dung nhap vao
    }
};
bool HC595::bat_chan(uint8_t chan_can_bat)
{
    if (chan_can_bat > 0 && chan_can_bat <= 8 * num_register)
    {
        uint8_t register_order = chan_can_bat / 8; // so thu tu cua thanh ghi(BAT DAU TU 0) bang phan nguyen cua phep chia so chan can bat cho 8
        uint8_t bit_order = chan_can_bat % 8;
        if (bit_order == 0) //tai vi neu chan can bat =8 thi bit_order =0 va register_order=1 => se sang den so 9 nen moi co dk nay`
        {
            register_order--;
            Registers[register_order] |= 1 << 7; // bitRegister=bitRegister|1<<(bit_need_to_change)
        }
        else
        {
            Registers[register_order] |= 1 << (bit_order - 1); // bitRegister=bitRegister|1<<(bit_need_to_change)
        }

        // MSBFIRST VA LSBFIST La thu tu dem bit
        // vi du MSBFIST la chan 1 se la chan Q7,MSBFIRST se la nguoc lai( chan 1 se la chan Q1)
        // thu tu truyen thanh ghi den ic 595 se nguoc voi thu tu chan cua ic hc595
        digitalWrite(latch, 0);
        if (transfer_dir == MSBFIRST)
        {
            for (int i = num_register - 1; i >= 0; i--)
            {
                shiftOut(data, clock, MSBFIRST, Registers[i]);
            }
        }
        else
        {
            for (int i = 0; i < num_register; i++)
            {
                Serial.println(i);
                shiftOut(data, clock, LSBFIRST, Registers[i]);
            }
        }
        digitalWrite(latch, 1);

        return true;
    }
    else
    {
        return false;
    }
}

bool HC595::tat_chan(uint8_t chan_can_tat)
{
    if (chan_can_tat > 0 && chan_can_tat <= 8)
    {
        Registers[0] &= ~(1 << (chan_can_tat - 1));
        digitalWrite(latch, 0);
        shiftOut(data, clock, MSBFIRST, Registers[0]);
        digitalWrite(latch, 1);
        return true;
    }
    else
    {
        return false;
    }
}

void HC595::send(uint8_t register_to_port)
{
    Registers[0] = register_to_port;
    digitalWrite(latch, 0);
    shiftOut(data, clock, MSBFIRST, Registers[0]);
    digitalWrite(latch, 1);
}
HC595::~HC595()
{
}