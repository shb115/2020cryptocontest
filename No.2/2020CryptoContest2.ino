#pragma GCC optimize ("-O3")

#define ROUND_NUM 128
typedef unsigned char u8;
typedef unsigned short u16;

inline u8 ROL8(u8 x, u8 n) {
 return ((u8) ((x) << (n)) | (u8) ((x) >> (8 - (n))));
}
inline u16 ROL16(u16 x, u16 n) {
 return ((u16) ((x) << (n)) | (u16) ((x) >> (16 - (n))));
}

const u8 Sbox1[256] = {0, 34, 68, 102, 136, 170, 204, 238, 17, 51, 85, 119, 153, 187, 221, 255, 
                       34, 68, 102, 136, 170, 204, 238, 16, 51, 85, 119, 153, 187, 221, 255, 33, 
                       68, 102, 136, 170, 204, 238, 16, 50, 85, 119, 153, 187, 221, 255, 33, 67, 
                       102, 136, 170, 204, 238, 16, 50, 84, 119, 153, 187, 221, 255, 33, 67, 101, 
                       136, 170, 204, 238, 16, 50, 84, 118, 153, 187, 221, 255, 33, 67, 101, 135, 
                       170, 204, 238, 16, 50, 84, 118, 152, 187, 221, 255, 33, 67, 101, 135, 169, 
                       204, 238, 16, 50, 84, 118, 152, 186, 221, 255, 33, 67, 101, 135, 169, 203, 
                       238, 16, 50, 84, 118, 152, 186, 220, 255, 33, 67, 101, 135, 169, 203, 237, 
                       17, 51, 85, 119, 153, 187, 221, 255, 34, 68, 102, 136, 170, 204, 238, 16, 
                       51, 85, 119, 153, 187, 221, 255, 33, 68, 102, 136, 170, 204, 238, 16, 50, 
                       85, 119, 153, 187, 221, 255, 33, 67, 102, 136, 170, 204, 238, 16, 50, 84, 
                       119, 153, 187, 221, 255, 33, 67, 101, 136, 170, 204, 238, 16, 50, 84, 118, 
                       153, 187, 221, 255, 33, 67, 101, 135, 170, 204, 238, 16, 50, 84, 118, 152, 
                       187, 221, 255, 33, 67, 101, 135, 169, 204, 238, 16, 50, 84, 118, 152, 186, 
                       221, 255, 33, 67, 101, 135, 169, 203, 238, 16, 50, 84, 118, 152, 186, 220, 
                       255, 33, 67, 101, 135, 169, 203, 237, 16, 50, 84, 118, 152, 186, 220, 254};
                       
const u8 Sbox2[256] = {0, 136, 17, 153, 34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 
                       136,16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 
                       17, 153, 34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 
                       153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 
                       34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 
                       170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 
                       51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 
                       187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 
                       68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 
                       204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 
                       85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 
                       221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 
                       102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 
                       238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 101, 237, 
                       119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 
                       255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 101, 237, 118, 254}; 
                       
const u16 con[8] = {0x3579, 0xD5E4, 0x5793, 0x5E4D, 0x7935, 0xE4D5, 0x9357, 0x4D5E};

void key_gen(u8 *rnd, u8 *key) {

    u8 key_in[2];
    u8 tmp1, tmp2;
    u16 *key_p;
  
    key_in[0] = key[0];
    key_in[1] = key[1];
    key_p = (u16*) key_in;
  
    u8 tmp[3];
    u16 *tmp_p;
    tmp_p = (u16*) tmp;


tmp1 = Sbox1[key_in[0]];
tmp2 = Sbox2[key_in[1]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[0] = key_in[0];
rnd[1] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[2] = key_in[0] + key_in[1];
rnd[3] = key_in[0] ^ key_in[1];

tmp1 = Sbox1[rnd[2]];
tmp2 = Sbox2[rnd[3]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[4] = key_in[0];
rnd[5] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[6] = key_in[0] + key_in[1];
rnd[7] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[6]];
tmp2 = Sbox2[rnd[7]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[8] = key_in[0];
rnd[9] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[10] = key_in[0] + key_in[1];
rnd[11] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[10]];
tmp2 = Sbox2[rnd[11]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[12] = key_in[0];
rnd[13] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[14] = key_in[0] + key_in[1];
rnd[15] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[14]];
tmp2 = Sbox2[rnd[15]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[16] = key_in[0];
rnd[17] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[18] = key_in[0] + key_in[1];
rnd[19] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[18]];
tmp2 = Sbox2[rnd[19]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[20] = key_in[0];
rnd[21] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[22] = key_in[0] + key_in[1];
rnd[23] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[22]];
tmp2 = Sbox2[rnd[23]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[24] = key_in[0];
rnd[25] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[26] = key_in[0] + key_in[1];
rnd[27] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[26]];
tmp2 = Sbox2[rnd[27]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[28] = key_in[0];
rnd[29] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[30] = key_in[0] + key_in[1];
rnd[31] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[30]];
tmp2 = Sbox2[rnd[31]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[32] = key_in[0];
rnd[33] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[34] = key_in[0] + key_in[1];
rnd[35] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[34]];
tmp2 = Sbox2[rnd[35]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[36] = key_in[0];
rnd[37] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[38] = key_in[0] + key_in[1];
rnd[39] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[38]];
tmp2 = Sbox2[rnd[39]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[40] = key_in[0];
rnd[41] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[42] = key_in[0] + key_in[1];
rnd[43] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[42]];
tmp2 = Sbox2[rnd[43]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[44] = key_in[0];
rnd[45] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[46] = key_in[0] + key_in[1];
rnd[47] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[46]];
tmp2 = Sbox2[rnd[47]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[48] = key_in[0];
rnd[49] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[50] = key_in[0] + key_in[1];
rnd[51] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[50]];
tmp2 = Sbox2[rnd[51]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[52] = key_in[0];
rnd[53] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[54] = key_in[0] + key_in[1];
rnd[55] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[54]];
tmp2 = Sbox2[rnd[55]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[56] = key_in[0];
rnd[57] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[58] = key_in[0] + key_in[1];
rnd[59] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[58]];
tmp2 = Sbox2[rnd[59]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[60] = key_in[0];
rnd[61] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[62] = key_in[0] + key_in[1];
rnd[63] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[62]];
tmp2 = Sbox2[rnd[63]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[64] = key_in[0];
rnd[65] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[66] = key_in[0] + key_in[1];
rnd[67] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[66]];
tmp2 = Sbox2[rnd[67]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[68] = key_in[0];
rnd[69] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[70] = key_in[0] + key_in[1];
rnd[71] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[70]];
tmp2 = Sbox2[rnd[71]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[72] = key_in[0];
rnd[73] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[74] = key_in[0] + key_in[1];
rnd[75] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[74]];
tmp2 = Sbox2[rnd[75]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[76] = key_in[0];
rnd[77] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[78] = key_in[0] + key_in[1];
rnd[79] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[78]];
tmp2 = Sbox2[rnd[79]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[80] = key_in[0];
rnd[81] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[82] = key_in[0] + key_in[1];
rnd[83] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[82]];
tmp2 = Sbox2[rnd[83]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[84] = key_in[0];
rnd[85] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[86] = key_in[0] + key_in[1];
rnd[87] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[86]];
tmp2 = Sbox2[rnd[87]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[88] = key_in[0];
rnd[89] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[90] = key_in[0] + key_in[1];
rnd[91] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[90]];
tmp2 = Sbox2[rnd[91]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[92] = key_in[0];
rnd[93] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[94] = key_in[0] + key_in[1];
rnd[95] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[94]];
tmp2 = Sbox2[rnd[95]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[96] = key_in[0];
rnd[97] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[98] = key_in[0] + key_in[1];
rnd[99] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[98]];
tmp2 = Sbox2[rnd[99]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[100] = key_in[0];
rnd[101] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[102] = key_in[0] + key_in[1];
rnd[103] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[102]];
tmp2 = Sbox2[rnd[103]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[104] = key_in[0];
rnd[105] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[106] = key_in[0] + key_in[1];
rnd[107] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[106]];
tmp2 = Sbox2[rnd[107]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[108] = key_in[0];
rnd[109] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[110] = key_in[0] + key_in[1];
rnd[111] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[110]];
tmp2 = Sbox2[rnd[111]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[112] = key_in[0];
rnd[113] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[114] = key_in[0] + key_in[1];
rnd[115] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[114]];
tmp2 = Sbox2[rnd[115]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[116] = key_in[0];
rnd[117] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[118] = key_in[0] + key_in[1];
rnd[119] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[118]];
tmp2 = Sbox2[rnd[119]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[120] = key_in[0];
rnd[121] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[122] = key_in[0] + key_in[1];
rnd[123] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[122]];
tmp2 = Sbox2[rnd[123]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[124] = key_in[0];
rnd[125] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[126] = key_in[0] + key_in[1];
rnd[127] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[126]];
tmp2 = Sbox2[rnd[127]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[128] = key_in[0];
rnd[129] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[130] = key_in[0] + key_in[1];
rnd[131] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[130]];
tmp2 = Sbox2[rnd[131]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[132] = key_in[0];
rnd[133] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[134] = key_in[0] + key_in[1];
rnd[135] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[134]];
tmp2 = Sbox2[rnd[135]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[136] = key_in[0];
rnd[137] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[138] = key_in[0] + key_in[1];
rnd[139] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[138]];
tmp2 = Sbox2[rnd[139]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[140] = key_in[0];
rnd[141] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[142] = key_in[0] + key_in[1];
rnd[143] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[142]];
tmp2 = Sbox2[rnd[143]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[144] = key_in[0];
rnd[145] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[146] = key_in[0] + key_in[1];
rnd[147] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[146]];
tmp2 = Sbox2[rnd[147]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[148] = key_in[0];
rnd[149] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[150] = key_in[0] + key_in[1];
rnd[151] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[150]];
tmp2 = Sbox2[rnd[151]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[152] = key_in[0];
rnd[153] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[154] = key_in[0] + key_in[1];
rnd[155] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[154]];
tmp2 = Sbox2[rnd[155]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[156] = key_in[0];
rnd[157] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[158] = key_in[0] + key_in[1];
rnd[159] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[158]];
tmp2 = Sbox2[rnd[159]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[160] = key_in[0];
rnd[161] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[162] = key_in[0] + key_in[1];
rnd[163] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[162]];
tmp2 = Sbox2[rnd[163]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[164] = key_in[0];
rnd[165] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[166] = key_in[0] + key_in[1];
rnd[167] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[166]];
tmp2 = Sbox2[rnd[167]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[168] = key_in[0];
rnd[169] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[170] = key_in[0] + key_in[1];
rnd[171] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[170]];
tmp2 = Sbox2[rnd[171]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[172] = key_in[0];
rnd[173] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[174] = key_in[0] + key_in[1];
rnd[175] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[174]];
tmp2 = Sbox2[rnd[175]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[176] = key_in[0];
rnd[177] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[178] = key_in[0] + key_in[1];
rnd[179] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[178]];
tmp2 = Sbox2[rnd[179]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[180] = key_in[0];
rnd[181] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[182] = key_in[0] + key_in[1];
rnd[183] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[182]];
tmp2 = Sbox2[rnd[183]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[184] = key_in[0];
rnd[185] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[186] = key_in[0] + key_in[1];
rnd[187] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[186]];
tmp2 = Sbox2[rnd[187]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[188] = key_in[0];
rnd[189] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[190] = key_in[0] + key_in[1];
rnd[191] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[190]];
tmp2 = Sbox2[rnd[191]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[192] = key_in[0];
rnd[193] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[194] = key_in[0] + key_in[1];
rnd[195] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[194]];
tmp2 = Sbox2[rnd[195]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[196] = key_in[0];
rnd[197] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[198] = key_in[0] + key_in[1];
rnd[199] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[198]];
tmp2 = Sbox2[rnd[199]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[200] = key_in[0];
rnd[201] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[202] = key_in[0] + key_in[1];
rnd[203] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[202]];
tmp2 = Sbox2[rnd[203]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[204] = key_in[0];
rnd[205] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[206] = key_in[0] + key_in[1];
rnd[207] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[206]];
tmp2 = Sbox2[rnd[207]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[208] = key_in[0];
rnd[209] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[210] = key_in[0] + key_in[1];
rnd[211] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[210]];
tmp2 = Sbox2[rnd[211]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[212] = key_in[0];
rnd[213] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[214] = key_in[0] + key_in[1];
rnd[215] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[214]];
tmp2 = Sbox2[rnd[215]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[216] = key_in[0];
rnd[217] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[218] = key_in[0] + key_in[1];
rnd[219] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[218]];
tmp2 = Sbox2[rnd[219]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[220] = key_in[0];
rnd[221] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[222] = key_in[0] + key_in[1];
rnd[223] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[222]];
tmp2 = Sbox2[rnd[223]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[224] = key_in[0];
rnd[225] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[0];

rnd[226] = key_in[0] + key_in[1];
rnd[227] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[226]];
tmp2 = Sbox2[rnd[227]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[228] = key_in[0];
rnd[229] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[1];

rnd[230] = key_in[0] + key_in[1];
rnd[231] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[230]];
tmp2 = Sbox2[rnd[231]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[232] = key_in[0];
rnd[233] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[2];

rnd[234] = key_in[0] + key_in[1];
rnd[235] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[234]];
tmp2 = Sbox2[rnd[235]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[236] = key_in[0];
rnd[237] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[3];

rnd[238] = key_in[0] + key_in[1];
rnd[239] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[238]];
tmp2 = Sbox2[rnd[239]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[240] = key_in[0];
rnd[241] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[4];

rnd[242] = key_in[0] + key_in[1];
rnd[243] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[242]];
tmp2 = Sbox2[rnd[243]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[244] = key_in[0];
rnd[245] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[5];

rnd[246] = key_in[0] + key_in[1];
rnd[247] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[246]];
tmp2 = Sbox2[rnd[247]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[248] = key_in[0];
rnd[249] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[6];

rnd[250] = key_in[0] + key_in[1];
rnd[251] = key_in[0] ^ key_in[1];
tmp1 = Sbox1[rnd[250]];
tmp2 = Sbox2[rnd[251]];

key_in[0] = tmp1 + tmp2;
key_in[1] = tmp1 ^ tmp2;
rnd[252] = key_in[0];
rnd[253] = key_in[1];

*(u16*)(tmp+1) = ROL16(*key_p, 1);
tmp[0] = tmp[2];
*key_p = *(u16*)(tmp+1) + *tmp_p + con[7];

rnd[254] = key_in[0] + key_in[1];
rnd[255] = key_in[0] ^ key_in[1];

}


void enc(u8 *text, u8 *rnd) {
 u8 text_in[2];
 u16 *text_p;

 text_in[0] = text[0];
 text_in[1] = text[1];
 text_p = (u16*) text_in;

 *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[1]) + rnd[2];
  text_in[1] = (text_in[1] + rnd[0]) ^ rnd[3];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[5]) + rnd[6];
  text_in[1] = (text_in[1] + rnd[4]) ^ rnd[7];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[9]) + rnd[10];
  text_in[1] = (text_in[1] + rnd[8]) ^ rnd[11];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[13]) + rnd[14];
  text_in[1] = (text_in[1] + rnd[12]) ^ rnd[15];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[17]) + rnd[18];
  text_in[1] = (text_in[1] + rnd[16]) ^ rnd[19];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[21]) + rnd[22];
  text_in[1] = (text_in[1] + rnd[20]) ^ rnd[23];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[25]) + rnd[26];
  text_in[1] = (text_in[1] + rnd[24]) ^ rnd[27];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[29]) + rnd[30];
  text_in[1] = (text_in[1] + rnd[28]) ^ rnd[31];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[33]) + rnd[34];
  text_in[1] = (text_in[1] + rnd[32]) ^ rnd[35];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[37]) + rnd[38];
  text_in[1] = (text_in[1] + rnd[36]) ^ rnd[39];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[41]) + rnd[42];
  text_in[1] = (text_in[1] + rnd[40]) ^ rnd[43];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[45]) + rnd[46];
  text_in[1] = (text_in[1] + rnd[44]) ^ rnd[47];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[49]) + rnd[50];
  text_in[1] = (text_in[1] + rnd[48]) ^ rnd[51];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[53]) + rnd[54];
  text_in[1] = (text_in[1] + rnd[52]) ^ rnd[55];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[57]) + rnd[58];
  text_in[1] = (text_in[1] + rnd[56]) ^ rnd[59];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[61]) + rnd[62];
  text_in[1] = (text_in[1] + rnd[60]) ^ rnd[63];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[65]) + rnd[66];
  text_in[1] = (text_in[1] + rnd[64]) ^ rnd[67];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[69]) + rnd[70];
  text_in[1] = (text_in[1] + rnd[68]) ^ rnd[71];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[73]) + rnd[74];
  text_in[1] = (text_in[1] + rnd[72]) ^ rnd[75];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[77]) + rnd[78];
  text_in[1] = (text_in[1] + rnd[76]) ^ rnd[79];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[81]) + rnd[82];
  text_in[1] = (text_in[1] + rnd[80]) ^ rnd[83];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[85]) + rnd[86];
  text_in[1] = (text_in[1] + rnd[84]) ^ rnd[87];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[89]) + rnd[90];
  text_in[1] = (text_in[1] + rnd[88]) ^ rnd[91];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[93]) + rnd[94];
  text_in[1] = (text_in[1] + rnd[92]) ^ rnd[95];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[97]) + rnd[98];
  text_in[1] = (text_in[1] + rnd[96]) ^ rnd[99];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[101]) + rnd[102];
  text_in[1] = (text_in[1] + rnd[100]) ^ rnd[103];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[105]) + rnd[106];
  text_in[1] = (text_in[1] + rnd[104]) ^ rnd[107];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[109]) + rnd[110];
  text_in[1] = (text_in[1] + rnd[108]) ^ rnd[111];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[113]) + rnd[114];
  text_in[1] = (text_in[1] + rnd[112]) ^ rnd[115];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[117]) + rnd[118];
  text_in[1] = (text_in[1] + rnd[116]) ^ rnd[119];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[121]) + rnd[122];
  text_in[1] = (text_in[1] + rnd[120]) ^ rnd[123];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[125]) + rnd[126];
  text_in[1] = (text_in[1] + rnd[124]) ^ rnd[127];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[129]) + rnd[130];
  text_in[1] = (text_in[1] + rnd[128]) ^ rnd[131];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[133]) + rnd[134];
  text_in[1] = (text_in[1] + rnd[132]) ^ rnd[135];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[137]) + rnd[138];
  text_in[1] = (text_in[1] + rnd[136]) ^ rnd[139];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[141]) + rnd[142];
  text_in[1] = (text_in[1] + rnd[140]) ^ rnd[143];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[145]) + rnd[146];
  text_in[1] = (text_in[1] + rnd[144]) ^ rnd[147];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[149]) + rnd[150];
  text_in[1] = (text_in[1] + rnd[148]) ^ rnd[151];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[153]) + rnd[154];
  text_in[1] = (text_in[1] + rnd[152]) ^ rnd[155];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[157]) + rnd[158];
  text_in[1] = (text_in[1] + rnd[156]) ^ rnd[159];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[161]) + rnd[162];
  text_in[1] = (text_in[1] + rnd[160]) ^ rnd[163];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[165]) + rnd[166];
  text_in[1] = (text_in[1] + rnd[164]) ^ rnd[167];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[169]) + rnd[170];
  text_in[1] = (text_in[1] + rnd[168]) ^ rnd[171];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[173]) + rnd[174];
  text_in[1] = (text_in[1] + rnd[172]) ^ rnd[175];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[177]) + rnd[178];
  text_in[1] = (text_in[1] + rnd[176]) ^ rnd[179];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[181]) + rnd[182];
  text_in[1] = (text_in[1] + rnd[180]) ^ rnd[183];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[185]) + rnd[186];
  text_in[1] = (text_in[1] + rnd[184]) ^ rnd[187];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[189]) + rnd[190];
  text_in[1] = (text_in[1] + rnd[188]) ^ rnd[191];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[193]) + rnd[194];
  text_in[1] = (text_in[1] + rnd[192]) ^ rnd[195];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[197]) + rnd[198];
  text_in[1] = (text_in[1] + rnd[196]) ^ rnd[199];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[201]) + rnd[202];
  text_in[1] = (text_in[1] + rnd[200]) ^ rnd[203];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[205]) + rnd[206];
  text_in[1] = (text_in[1] + rnd[204]) ^ rnd[207];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[209]) + rnd[210];
  text_in[1] = (text_in[1] + rnd[208]) ^ rnd[211];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[213]) + rnd[214];
  text_in[1] = (text_in[1] + rnd[212]) ^ rnd[215];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[217]) + rnd[218];
  text_in[1] = (text_in[1] + rnd[216]) ^ rnd[219];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[221]) + rnd[222];
  text_in[1] = (text_in[1] + rnd[220]) ^ rnd[223];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[225]) + rnd[226];
  text_in[1] = (text_in[1] + rnd[224]) ^ rnd[227];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[229]) + rnd[230];
  text_in[1] = (text_in[1] + rnd[228]) ^ rnd[231];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[233]) + rnd[234];
  text_in[1] = (text_in[1] + rnd[232]) ^ rnd[235];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[237]) + rnd[238];
  text_in[1] = (text_in[1] + rnd[236]) ^ rnd[239];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[241]) + rnd[242];
  text_in[1] = (text_in[1] + rnd[240]) ^ rnd[243];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[245]) + rnd[246];
  text_in[1] = (text_in[1] + rnd[244]) ^ rnd[247];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[249]) + rnd[250];
  text_in[1] = (text_in[1] + rnd[248]) ^ rnd[251];
  
  *text_p = ROL16(*text_p, 12);
  
  text_in[0] = (text_in[0] ^ rnd[253]) + rnd[254];
  text_in[1] = (text_in[1] + rnd[252]) ^ rnd[255];
  
  text[0] = text_in[0];
  text[1] = text_in[1];
 
}





u8 TEST_VECTOR(u8 *in, u8 *answer) {
 return (in[0] == answer[0] && in[1] == answer[1]);
}

void setup() {
 Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);
 
 u8 key[3][2] = { {0x12, 0x34}, {0x9A, 0xBD}, {0x11, 0x22} };
 u8 rnd[ROUND_NUM * 2] = { 0, };
 u8 text[3][2] = { {0x56, 0x78}, {0xDE, 0xF0}, {0x33, 0x44} };
 u8 out_text[3][2] = { {0x50, 0x3F}, {0x88, 0x28}, {0x7F, 0x33} };
 
 Serial.println("-----------------");
 Serial.println(" TEST VECTOR ");
 Serial.println("-----------------");

 for(int i=0; i<3; i++) {
    key_gen(rnd, key[i]);
    enc(text[i], rnd);
    
    if(TEST_VECTOR(text[i], out_text[i])){
        Serial.println(">> CORRECT");
    }else{
        Serial.println(">> WRONG");
    }
 }
 
 Serial.println("-----------------");
 Serial.println(" BENCHMARK ");
 Serial.println("-----------------");

 u8 key_bench[2] = { 0x12, 0x34 };
 u8 text_bench[2] = { 0x56, 0x78 };

 u32 time1;
 u32 time2;
 time1 = millis();
 
 for(int i=0; i<4096; i++) {
    key_gen(rnd,key_bench);
    enc(text_bench,rnd);
    
    if(text_bench[0]>0x80){
       digitalWrite(LED_BUILTIN, HIGH);
    }else{
       digitalWrite(LED_BUILTIN, LOW);
    }

 }

 time2 = millis();
 Serial.print(">> ");
 Serial.println((time2-time1));
 Serial.println("-----------------");
}


void loop() {
}
